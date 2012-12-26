piece_to_char(nil, ' ').
piece_to_char(piece(white, king), '♔').
piece_to_char(piece(white, pawn), '♙').
piece_to_char(piece(white, rook), '♖').
piece_to_char(piece(white, knight), '♘').
piece_to_char(piece(white, bishop), '♗').
piece_to_char(piece(white, queen), '♕').
piece_to_char(piece(black, king), '♚').
piece_to_char(piece(black, pawn), '♟').
piece_to_char(piece(black, rook), '♜').
piece_to_char(piece(black, knight), '♞').
piece_to_char(piece(black, bishop), '♝').
piece_to_char(piece(black, queen), '♛').

/** Writes a textual representation of the board to standard output.
White pieces are represented by lowercase characters, and black pieces by uppercase ones. */
write_board([Line | RestBoard]) :-
	write_board(RestBoard),
	write_line(Line).

write_board([]).

write_line([Piece | RestLine]) :-
	write_piece(Piece),
	/* Write a space between each two pieces */
	(RestLine \= [] -> write(' ') ; true),
	write_line(RestLine).

/** Write an empty line between each two lines */
write_line([]) :- nl.

write_piece(Piece) :-
	piece_to_char(Piece, Char),
	write(Char).
	
/** Writes a textual representation of the board to standard output, drawing the cells in
white and black, just as in a real chessboard.
White pieces are represented by green characters and black pieces by red ones. */
write_board_color(Board) :-
	write_board_color_loop(Board, white),
	/** Disable all visual styles at the end of drawing the board. */
	write('\e[0m').
	
write_board_color_loop([Line | RestBoard], LeftColor) :-
	opposite_color(LeftColor, NextColor),
	write_board_color_loop(RestBoard, NextColor),
	write_line_color(Line, Line, LeftColor).
	
write_board_color_loop([], _).

bgcolor(white) :- write('\e[47m').
bgcolor(black) :- write('\e[40m').

fgcolor(white) :- write('\e[34m').
fgcolor(black) :- write('\e[31m').

nocolor :- write('\e[0m').

write_line_color(Line, [Piece | RestLine], Color) :-
	bgcolor(Color),
	(piece(PColor, _) = Piece -> fgcolor(PColor) ; true),
	piece_to_char(Piece, Char),
	write(Char),
	write(' '),
	opposite_color(Color, NextColor),
	write_line_color(Line, RestLine, NextColor).
	
write_line_color(_, [], _) :- nocolor, nl.