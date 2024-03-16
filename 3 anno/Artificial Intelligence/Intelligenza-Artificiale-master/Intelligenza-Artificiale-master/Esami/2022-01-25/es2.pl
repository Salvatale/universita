:- use_module(library(clpfd)).

alberi(V,V):-
    V in 1..10,
    label([V]).
alberi(nodo(V,T1,T2),T):-
    alberi(T1,V1),
    alberi(T2,V2),
    
    V in 1..10,
    label([V]),
    
    T #= V + V1 + V2.


















