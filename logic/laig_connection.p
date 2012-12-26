:- use_module(library(socket)).

/** Open Prolog in server mode */
server_port(60001).

create_server(Port) :-
        tcp_socket(Socket),
        tcp_bind(Socket, Port),
        tcp_listen(Socket, 5),
        tcp_open_socket(Socket, AcceptFd, _),
        dispatch(AcceptFd).
	
/** Main Loop - Wait and answer requests */
dispatch(AcceptFd) :-
        tcp_accept(AcceptFd, Socket, Peer),
        thread_create(process_client(Socket, Peer), _, [ detached(true) ]),
        dispatch(AcceptFd).

process_client(Socket, Peer) :-
        tcp_open_socket(Socket, In, Out),
        writeln('Connection established with new client'),
		process_msg(In,Out).
        %close_connection(In, Out).
		
process_msg(In, Out) :-
	read(In,Msg),
    writeln(Msg),
    parse_input(Msg, Answer),
    writeln(Answer),
    write(Out,Answer),
    nl(Out),
    flush_output(Out),
	writeln(Answer),
	process_msg(In, Out).
	
close_connection(In, Out) :-
        close(In, [force(true)]),
        close(Out, [force(true)]).
        
/** Parsing the inputs */
parse_input(comando(Arg1, Arg2), Answer) :-
	comando(Arg1, Arg2, Answer).
	
parse_input(ready,yes).

parse_input(select(BoardStr,Piece,Cell),Answer) :-
    make_select(BoardStr,Piece,Cell,Answer).
    
parse_input(play(BoardStr,CellOri,CellDest,PlayerColor,human), Answer) :-
    make_play(BoardStr,CellOri,CellDest,PlayerColor,Answer).

parse_input(check(BoardStr,PlayerColor),Answer) :-
    make_check_verification(BoardStr,PlayerColor,Answer).
    
parse_input(draw(BoardStr),Answer) :-
    make_draw_verification(BoardStr,Answer).
    
parse_input(checkmate(BoardStr,PlayerColor),Answer) :-
    make_check_mate_verification(BoardStr,PlayerColor,Answer).

parse_input(close,bye).
	
parse_input(_,Answer) :-
    Answer = 'undefined message'.
    
/** Executing requests */

comando(Arg1, Arg2, Arg1).

make_check_mate_verification(BoardStr,PlayerColor,Answer) :-
    string_to_board(BoardStr,Board),
    check_mate(Board,PlayerColor) ->
        Answer = 'yes'
    ;
        Answer = 'no'.

make_draw_verification(BoardStr,Answer) :-
    string_to_board(BoardStr,Board),
    draw(Board) ->
        Answer = 'yes'
    ;
        Answer = 'no'.

make_check_verification(BoardStr,PlayerColor,Answer) :-
    string_to_board(BoardStr,Board),
    check(Board, PlayerColor) ->
        Answer = 'yes'
    ;
        Answer = 'no'.

/** Make Select command - in prolog, this is an equivalent:
initial_board(X),board_to_string(X,S),string_to_board(S,B),findall(T,can_reach(B,piece(white,rook),cell(0,0),T),L). */
	
make_select(BoardStr,Piece,Cell,Answer) :-
    string_to_board(BoardStr,Board),
    findall(Possibilities,can_reach(Board,Piece,Cell,Possibilities),AllPlays),
    maplist(term_to_atom, AllPlays, AllPlaysAtom),
    list_string(AllPlaysAtom,Answer).
    
/** initial_board(X),board_to_string(X,S),string_to_board(S,B),make_play(S,cell(0,0),cell(1,0),white,A). */

make_play(BoardStr,CellOri,CellDest,PlayerColor,Answer) :-
    string_to_board(BoardStr,Board),
    move_piece(game(PlayerColor,Board),game(_,NewBoard),CellOri,CellDest),
    board_to_string(NewBoard,Answer).
