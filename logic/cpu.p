:- use_module(library(aggregate)).

gt(infinity, _) :- !.
gt(_, -infinity) :- !.
gt(X, Y) :- number(X), number(Y), X > Y, !.

lt(-infinity, _) :- !.
lt(_, infinity) :- !.
lt(X, Y) :- number(X), number(Y), X < Y, !.

/** Obtains the (estimated) best next move from the given game state. The greater Plies is, the better the estimate
will be. */
best_move(Game, Plies, From, To) :-
	game(MaxPlayer, _) = Game,
	best_move(Game, MaxPlayer, Plies, -infinity, infinity, From, To, _).

/* When the recursion limit is reached, calculate a heuristic value for the resulting position */
best_move(game(_, Board), MaxPlayer, 0, _, _, _, Value) :-
	rate_board(Board, MaxPlayer, Value).

best_move(Game, MaxPlayer, Plies, Alpha, Beta, From, To, Value) :-
	game(Player, Board) = Game,
	((Plies = 0; \+ has_legal_move(Board, Player)) ->
		rate_board(Board, MaxPlayer, Value)
	;
		NP is Plies - 1,
		/* If Player is the maximizing player, maximize the value of the board for the latter; otherwise,
		   minimize it */
		(Player = MaxPlayer -> (
			Solution = sol(Alpha, _, _),
			/* Loop through all available moves */
			(move_piece(Game, NewGame, NFrom, NTo),
			Solution = sol(CurAlpha, _, _),
			best_move(NewGame, MaxPlayer, NP, CurAlpha, Beta, _, _, NValue),
			/* If a better solution is found, store it in Solution */
			(gt(NValue, CurAlpha) ->
				nb_setarg(1, Solution, NValue),
				nb_setarg(2, Solution, NFrom),
				nb_setarg(3, Solution, NTo)
			; true),
			/* Stop the search if the window for possible solutions becomes empty */
			Solution = sol(NewAlpha, _, _),
			\+ lt(NewAlpha, Beta);
			true)
		)
		; (
			Solution = sol(Beta, _, _),
			(move_piece(Game, NewGame, NFrom, NTo),
			Solution = sol(CurBeta, _, _),
			best_move(NewGame, MaxPlayer, NP, Alpha, CurBeta, _, _, NValue),
			(lt(NValue, CurBeta) ->
				nb_setarg(1, Solution, NValue),
				nb_setarg(2, Solution, NFrom),
				nb_setarg(3, Solution, NTo)
			; true),
			Solution = sol(NewBeta, _, _),
			\+ lt(Alpha, NewBeta);
			true)
		)),
		Solution = sol(Value, From, To)
	), !.

/** Estimates the value of the given board for the maximizing player. */
rate_board(Board, MaxPlayer, Value) :-
	opposite_color(MaxPlayer, OtherPlayer),
	(draw(Board) ->
		Value = -1000
	;
		(check_mate(Board, MaxPlayer) ->
			Value = infinity
		;
			(check_mate(Board, OtherPlayer) ->
				Value = -infinity
			;
				(aggregate_all(sum(S1), (piece_at(Board, _, Piece),piece_value_ai(Piece,S1), piece(MaxPlayer, _) = Piece), NMax),
				aggregate_all(sum(S2), (piece_at(Board, _, Piece),piece_value_ai(Piece,S2), piece(OtherPlayer, _) = Piece), NOther),
				Value is NMax - NOther)))).

/** Parses the value of each piece, for AI purposes */
piece_value_ai(piece(_,pawn), 1).
piece_value_ai(piece(_,knight), 3).
piece_value_ai(piece(_,bishop), 3).
piece_value_ai(piece(_,rook), 5).
piece_value_ai(piece(_,queen), 9).
