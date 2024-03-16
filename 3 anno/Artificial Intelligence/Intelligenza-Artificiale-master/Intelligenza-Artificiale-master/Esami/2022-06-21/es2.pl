:- use_module(library(clpfd)).

sottolista1(R,K):-
    sottolista(R,K).

sottolista([],_).
sottolista([H],[H|K]):-
   sottolista([],K).
sottolista([C,D|L],[C,D|K]):-
    sottolista([D|L],[D|K]).
sottolista(R,[_|K]):-
    sottolista1(R,K).
















