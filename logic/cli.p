/** Starts a game of torus chess between any combination of human and computer players.
    Each of the player parameters may be 'human' or cpu(N), where N is the desired difficulty
    level. (Unless you have a really powerful machine, it is advisable to keep N below 5). */
start_cli(WhitePlayer, BlackPlayer) :-
	initial_board(X),
	cli_loop(game(white, X), WhitePlayer, BlackPlayer).
	
capitalize(white, 'White').
capitalize(black, 'Black').

/** Converts a cell reference from a term in standard chess notation (example: a4, b8, etc.) to a reference
in the form cell(X, Y). */
chess_notation_to_cell(ChessRef, cell(ColumnIndex, RowIndex)) :-
	atom_codes(ChessRef, [Column, Row]),
	ColumnIndex is Column - 97,
	RowIndex is Row - 49,
	ColumnIndex >= 0, ColumnIndex < 8,
	RowIndex >= 0, RowIndex < 8.
	
get_move(_, human, From, To) :-
	read(InputFrom - InputTo),
	chess_notation_to_cell(InputFrom, From),
	chess_notation_to_cell(InputTo, To).
	
get_move(Game, cpu(N), From, To) :-
	best_move(Game, N, From, To).
	
/** Given a color, and the player type playing each color, gives the type of player playing
    that particular color. */
select_player(white, WhitePlayer, _, WhitePlayer).
select_player(black, _, BlackPlayer, BlackPlayer).

cli_loop(Game, WhitePlayer, BlackPlayer) :-
	game(Player, Board) = Game,
	has_legal_move(Board, Player), !,
	capitalize(Player, PlayerName),
	writef('%t to move\n', [PlayerName]),
	write_board_color(Board),
	select_player(Player, WhitePlayer, BlackPlayer, PlayerType),
	get_move(Game, PlayerType, From, To),
	(move_piece(Game, NewGame, From, To) ;
	 NewGame = Game, writeln('Illegal move')),
	cli_loop(NewGame, WhitePlayer, BlackPlayer).

/* Used when the game is over */
cli_loop(game(Player, Board)) :-
	(check(Board, Player) ->
		writef('Checkmate for %t\n', [Player])
	;
		writef('Stalemate for %t\n', [Player])),
	write_board_color(Board),
	writeln('Game over.').