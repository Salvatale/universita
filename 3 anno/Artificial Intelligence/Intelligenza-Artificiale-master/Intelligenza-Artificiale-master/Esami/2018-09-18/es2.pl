:- use_module(library(clpfd)).


rovescio(A,B):-
    rovescio1(A,B,[]).
rovescio1([],L,L).
rovescio1([X|L],K,B):-
    rovescio1(L,K,[X|B]).


















