board_string_list_codes([], "").

board_string_list_codes([Atom], Codes) :-
    translate_cell(Atom,CharAtom),    
    atom_codes(CharAtom, Codes).

board_string_list_codes([Atom|ListTail], Codes) :-
    translate_cell(Atom,CharAtom),
    atom_codes(CharAtom, AtomCodes),
    append(AtomCodes, ListTailCodes, Codes),
    board_string_list_codes(ListTail, ListTailCodes).

/** Convert a plain string into a Board (list of lists) */
string_to_board(String,Board) :-
   string_to_board_aux([],String,0,Board).

string_to_board_aux(Board,String,N,NewBoard) :-
    N =< 56,
    NPlus is N+8,
    sub_string(String,N,8,_,SubStr),
    translate(List, SubStr),
    append(Board,[List],NBoard),
    string_to_board_aux(NBoard,String,NPlus,NewBoard).
    
string_to_board_aux(Board,_,64,Board).

/** Convert a Board (list of lists) into a plain string */
board_to_string(Board,String) :-
    %write(Board),nl,
    board_to_string_aux(Board,'',String).

board_to_string_aux([H|T],InitialStr,NewString) :-
    H \= [],
    translate(H,Str),
    string_concat(InitialStr,Str,StrCat),
    board_to_string_aux(T,StrCat,NewString).

board_to_string_aux([],InitialStr,InitialStr).

translate(List, String) :-
    ground(List),
    board_string_list_codes(List, Codes),
    atom_codes(String, Codes).

translate(List, String) :-
    ground(String),
    atom_codes(String, Codes),
    board_string_list_codes(List, Codes).
    
/** Empty cells */
translate_cell(nil,'e').
translate_cell('e',nil).

/** Black pieces */
translate_cell(piece(black,pawn),'a').
translate_cell(piece(black,rook),'o').
translate_cell(piece(black,bishop),'i').
translate_cell(piece(black,knight),'h').
translate_cell(piece(black,queen),'u').
translate_cell(piece(black,king),'g').

translate_cell('g','piece(black,king)').
translate_cell('u','piece(black,queen)').
translate_cell('h','piece(black,knight)').
translate_cell('i','piece(black,bishop)').
translate_cell('o','piece(black,rook)').
translate_cell('a','piece(black,pawn)').

/** White pieces */
translate_cell(piece(white,pawn),'p').
translate_cell(piece(white,rook),'r').
translate_cell(piece(white,bishop),'b').
translate_cell(piece(white,knight),'n').
translate_cell(piece(white,queen),'q').
translate_cell(piece(white,king),'k').

translate_cell('k','piece(white,king)').
translate_cell('q','piece(white,queen)').
translate_cell('h','piece(white,knight)').
translate_cell('b','piece(white,bishop)').
translate_cell('r','piece(white,rook)').
translate_cell('p','piece(white,pawn)').

/** Converts a list into a string, elements separated by commas */

list_codes([], "").

list_codes([Atom], Codes) :- atom_codes(Atom, Codes).

list_codes([Atom|ListTail], Codes) :-
    atom_codes(Atom, AtomCodes),
    append(AtomCodes, ",", AtomCodesWithComma),
    append(AtomCodesWithComma, ListTailCodes, Codes),
    list_codes(ListTail, ListTailCodes).

list_string(List, String) :-
    ground(List),
    list_codes(List, Codes),
    atom_codes(String, Codes).

list_string(List, String) :-
    ground(String),
    atom_codes(String, Codes),
    list_codes(List, Codes).
