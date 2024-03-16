:- use_module(library(clpfd)).

filter([],[]).
filter([X|L1],L2):-
    X in 1..10,
    filter(L1,L2).
filter([X|L1],[X,X|L2]):-
    X in 11..20,
    filter(L1,L2).
filter([X|L1],[N|L2]):-
    X in 21..30,
    N #= X + 1,
    filter(L1,L2).
filter([X|L1],[X|L2]):-
    X in 31..50,
    filter(L1,L2).
filter([X|L1],L2):-
    X #> 50;
    X #< 
    filter(L1,L2).










