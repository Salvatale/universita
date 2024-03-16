
s(I,R):-
    a(I,R).
s(I,R):-
    q(I,R).

q(I,R):-
    qyn(I,R).
q(I,R):-
    qwhere(I,R).
q(I,R):-
    qwho(I,R).

qyn(I,R):-
    aux(I,R).
qwhere([where|R1],R):-
    aux(R1,R).
qwho([who|R1],R):-
    vp(_,R1,R).

aux([does|R1],R):-
    np(tps,R1,R2),
    vp(ntps,R2,R).
aux([do|R1],R):-
    np(ntps,R1,R2),
    vp(ntps,R2,R).

a(I,R):-
    np(P,I,R1),
    vp(P,R1,R).

np(tps,[PN|R],R):-
    pn(PN).
np(tps,[Det,CN|R1],R):-
    det(Det),
    cn(CN,_),
    ppstar(R1,R).
np(ntps,[Det,CN|R1],R):-
    det(Det),
    cn(_,CN),
    ppstar(R1,R).

ppstar(R,R).
ppstar(I,R):-
    pp(I,R1),
    ppstar(R1,R).

pp([Prep|R1],R):-
    prep(Prep),
    np(_,R1,R).

vp(tps,[IV|R1],R):-
    iv(_,IV),
    ppstar(R1,R).
vp(tps,[TV|R1],R):-
    tv(_,TV),
    np(_,R1,R2),
    ppstar(R2,R).
vp(ntps,[IV|R1],R):-
    iv(IV,_),
    ppstar(R1,R).
vp(ntps,[TV|R1],R):-
    tv(TV,_),
    np(_,R1,R2),
    ppstar(R2,R).
    


det(the).
prep(in).
prep(near).
pn(alice).
pn(bob).
pn(london).
cn(book,books).
cn(cake,cakes).
cn(garden,gardens).
cn(house,houses).
cn(kid,kids).
cn(lake,lakes).
tv(eat,eats).
tv(read,reads).
iv(live,lives).
iv(run,runs).











