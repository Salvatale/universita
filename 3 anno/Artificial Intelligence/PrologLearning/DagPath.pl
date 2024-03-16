:- op(500,xfy,->).

arc(a,b).
arc(a,c).
arc(a,d).
arc(b,e).
arc(b,f).
arc(c,d).
arc(c,e).
arc(d,g).
arc(d,h).
arc(e,i).
arc(f,l).
arc(g,m).
arc(h,n).
arc(n,o).
arc(n,p).


%path(X,Y, ->(X,Y)):-
%    arc(X,Y).
%path(X,Y, ->(X,P)):-
%    arc(X,Z),
%    path(Z,Y,P).

path(X,Y, X->Y):-
    arc(X,Y).
path(X,Y, X->P):-
    arc(X,Z),
    path(Z,Y,P).