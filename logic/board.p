:- use_module(library(lists)).

/** This position allows torus chess to be played with torus rules since the
beginning. The lower-left position in this matrix corresponds to the cell a1 on the chessboard. */ 
initial_board([
	[piece(white, rook), nil, piece(white, bishop), nil, nil, piece(white, bishop), nil, piece(white, rook)],
	[piece(white, pawn), piece(white, pawn), nil, nil, nil, nil, piece(white, pawn), piece(white, pawn)],
	[piece(white, knight), nil, piece(white, pawn), piece(white, queen), piece(white, king), piece(white, pawn), nil, piece(white, knight)],
	[nil, nil, nil, piece(white, pawn), piece(white, pawn), nil, nil, nil],
	[nil, nil, nil, piece(black, pawn), piece(black, pawn), nil, nil, nil],
	[piece(black, knight), nil, piece(black, pawn), piece(black, queen), piece(black, king), piece(black, pawn), nil, piece(black, knight)],
	[piece(black, pawn), piece(black, pawn), nil, nil, nil, nil, piece(black, pawn), piece(black, pawn)],
	[piece(black, rook), nil, piece(black, bishop), nil, nil, piece(black, bishop), nil, piece(black, rook)]
	]).
	
opposite_color(white, black).
opposite_color(black, white).
	
/** Piece is the piece located at position cell(x, y) on the given board. */
piece_at(Board, cell(X, Y), Piece) :-
	nth0(Y, Board, Line),
	nth0(X, Line, Piece).

/** Sets the piece at the position cell(x, y) on the given board. NewBoard is the board after
the change. */
set_piece_at(Board, cell(X, Y), Piece, NewBoard) :-
	nth0(Y, Board, Line),
	set_nth0(X, Line, Piece, NewLine),
	set_nth0(Y, Board, NewLine, NewBoard).

/** set_nth0(I, List, NewItem, NewList)
Replaces the I-th element of List with NewItem and returns the result as NewList. List is not modified.
Fails if the index I is out of bounds. */
set_nth0(I, _, _, _) :- I < 0, !, false.
set_nth0(0, [_ | Rest], NewItem, [NewItem | Rest]).
set_nth0(I, [Item | Rest], NewItem, [Item | NewRest]) :-
	J is I - 1,
	set_nth0(J, Rest, NewItem, NewRest).

/** Succeeds if B is the next index into the board after A, modulo 8 (in either dimension). Either A or B, but not both,
	may be variables. */
msucc(A, B) :-
	\+ var(A), B is (A + 1) mod 8;
	\+ var(B), A is (B - 1) mod 8.

/** move_piece(State, NewState, From, To)
Moves the piece in the cell From to the cell To, which are specified by
cell(x, y) pairs. NewState will be the game's state (board and turn) as it exists after the move.
This predicate fails if the move is illegal or out of turn. */
move_piece(game(Turn, Board), game(NewTurn, NewBoard), From, To) :-
	/* Check if there is a piece of the correct color at the chosen cell */
	piece_at(Board, From, Piece),
	piece(Turn, _) = Piece,
	can_reach(Board, Piece, From, To),
	/* Check if there is no piece of the same color at the destination cell
	(if the piece there is of the opposite color, it is captured) */
	\+ piece_at(Board, To, piece(Turn, _)),
	/* Generate the new state. */
	opposite_color(Turn, NewTurn),
	set_piece_at(Board, From, nil, TempBoard),
	set_piece_at(TempBoard, To, Piece, NewBoard),
	/* Make sure that the move does not result in check (or mantains it) */
	\+ check(NewBoard, Turn).

/** Succeeds if the given player is in check in the given board. */	
check(Board, Color) :-
	piece_at(Board, Cell, piece(Color, king)),
	opposite_color(Color, EnemyColor),
	/* Check if there is an enemy piece that can reach the king */
	piece_at(Board, EnemyCell, Piece),
	piece(EnemyColor, _) = Piece,
	can_reach(Board, Piece, EnemyCell, Cell).

/** Suceeds if there is at least one legal move for a given player */
has_legal_move(Board, Color) :-
	move_piece(game(Color,Board), _, _, _).

/** Succeeds if the given player is in check-mate in the given board. */
check_mate(Board, Color) :-
	\+ has_legal_move(Board, Color),
	check(Board, Color).

/** Succeeds if there is a draw on the given board (no possible moves, no check-mate). */
draw(Board) :-
	\+ check_mate(Board, _),
	\+ has_legal_move(Board, _).
