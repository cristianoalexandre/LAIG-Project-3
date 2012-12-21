mpred(A, B) :- msucc(B, A).
msucc2(A, B) :-	msucc(A, C), msucc(C, B).
mpred2(A, B) :- mpred(A, C), mpred(C, B).

pawn_step(white, FY, TY) :- msucc(FY, TY).
pawn_step(black, FY, TY) :- mpred(FY, TY).

/** can_reach(Board, Piece, From, To)
Succeeds if Piece can reach cell To from cell From in Board. */
can_reach(_, piece(_, king), cell(FX, FY), cell(TX, TY)) :-
	(msucc(FX, TX); mpred(FX, TX); FX = TX),
	(msucc(FY, TY); mpred(FY, TY); FY = TY),
	\+ (FX = TX, FY = TY).
	
can_reach(Board, piece(_, bishop), From, To) :-
	can_reach_dir(Board, From, From, To, mpred, mpred);
	can_reach_dir(Board, From, From, To, mpred, msucc);
	can_reach_dir(Board, From, From, To, msucc, mpred);
	can_reach_dir(Board, From, From, To, msucc, msucc).
	
can_reach(Board, piece(Color, pawn), cell(FX, FY), cell(TX, TY)) :-
	pawn_step(Color, FY, TY),
	/** Pawns advance diagonally if and only if they are capturing */
	(FX = TX, piece_at(Board, cell(TX, TY), nil)
	 ;
	 (msucc(FX, TX); mpred(FX, TX)),
	  opposite_color(Color, O),
	  piece_at(Board, cell(TX, TY), piece(O, _))).

can_reach(Board, piece(_, rook), From, To) :-
	can_reach_dir(Board, From, From, To, msucc, =);
	can_reach_dir(Board, From, From, To, mpred, =);
	can_reach_dir(Board, From, From, To, =, msucc);
	can_reach_dir(Board, From, From, To, =, mpred).
	
can_reach(Board, piece(_, queen), From, To) :-
	can_reach(Board, piece(_, bishop), From, To);
	can_reach(Board, piece(_, rook), From, To).

can_reach(_, piece(_,knight), cell(FX, FY), cell(TX, TY)) :-
	((mpred2(FX,TX); msucc2(FX, TX)),
	(mpred(FY,TY); msucc(FY,TY)))
	;
	((mpred2(FY,TY); msucc2(FY,TY)),
	(mpred(FX,TX); msucc(FX,TX))).

/** Succeeds if a piece at (X, Y) can reach (TX, TY) by following the direction specified by Horiz and Vert, which
are predicates that give the next coordinate to visit in each dimension. */
can_reach_dir(Board, From, cell(X, Y), To, Horiz, Vert) :-
	call(Horiz, X, NX),
	call(Vert, Y, NY),
	Next = cell(NX, NY),
	(Next = To
	;
	/* Check if all the cells on the path are empty */
	piece_at(Board, Next, nil),
	/* If we arrive at the starting cell, there is nowhere else to go */
	From \= Next,
	can_reach_dir(Board, From, Next, To, Horiz, Vert)).
