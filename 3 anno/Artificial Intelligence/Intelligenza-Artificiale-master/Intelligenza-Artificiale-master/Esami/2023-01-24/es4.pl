:- use_module(library(clpfd)).

member(X,[[X,Y]|_],Y):-
    !.
member(X,[_|R],Z):-
    member(X,R,Z).

percorso(_,_,0,[]).
percorso(Graph,Node,N,[Node|Rest]):-
    N #>= 1,
    M #= N - 1,
    member(Node,Graph,Next),
    percorso(Graph,Next,M,Rest).












