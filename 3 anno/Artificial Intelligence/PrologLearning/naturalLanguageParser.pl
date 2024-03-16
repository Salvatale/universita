
a(I,R):-
    np(I,R1),
    vp(R1,R).

np([PN|R],R):-
    pn(PN).
np([Det,CN|R1],R):-
    det(Det),
    cn(CN),
    ppstar(R1,R).

ppstar(R,R).
ppstar(I,R):-
    pp(I,R1),
    ppstar(R1,R).

pp([Prep|R1],R):-
    prep(Prep),
    np(R1,R).

vp([IV|R1],R):-
    iv(IV),
    ppstar(R1,R).
vp([TV|R1],R):-
    tv(TV),
    np(R1,R2),
    ppstar(R2,R).
    


det(the).
prep(in).
prep(near).
pn(alice).
pn(bob).
pn(london).
cn(book).
cn(cake).
cn(garden).
cn(house).
cn(kid).
cn(lake).
tv(eats).
tv(reads).
iv(lives).
iv(runs).











