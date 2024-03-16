:- use_module(library(clpfd)).

%ES 2 19/09/2018

rovescio(L,R):-
    rovescio1(L,R,[]).

rovescio1([],R,R).
rovescio1([X|L],R,K):-
    rovescio1(L,R,[X|K]).

%ES 6 18/09/2019

arc(1,2).
arc(1,3).
arc(3,2).
arc(2,4).
arc(4,5).
arc(4,6).
arc(2,6).
arc(5,6).

path(X,Y,[arco(X,Y)]):-
    arc(X,Y).
path(X,Y,[arco(X,Z)|R]):-
  	arc(X,Z),
    path(Z,Y,R).

% ES3 25/01/22

soluzioni(X,Y):-
    X in 1..10,
    Y in 1..10,
    X #\== 2,
    X * X + Y * Y #=< 36,
    X + Y #=< 20,
    label([X,Y]).








