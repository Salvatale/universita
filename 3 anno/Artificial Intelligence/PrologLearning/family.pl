%Es Family

father(a,b).
father(a,c).
father(b,d).
father(b,e).
father(c,f).

brother(X,Y):-
    father(Z,X),
    father(Z,Y),
    not(X=Y).

cousin(X,Y):-
    father(Z,X),
    father(F,Y),
    brother(Z,F).

grandson(X,Y):-
    father(Z,X),
    father(Y,Z).

descendent(X,Y):-
    father(Y,X).
descendent(X,Y):-
    father(Z,X),
    descendent(Z,Y).