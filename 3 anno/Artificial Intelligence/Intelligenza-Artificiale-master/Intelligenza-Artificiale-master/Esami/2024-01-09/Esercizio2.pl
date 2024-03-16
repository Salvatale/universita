:- use_module(library(clpfd)).


cn(cane,cani).
cn(topo,topi).
det(il,i).
tv(rincorre,rincorrono).

parse(a(NP,VP),L):-
    np(P,NP,L,R),
    vp(P,VP,R).
np(s,np(det(Det),cn(CN)),[Det,CN|R],R):-
    det(Det,_),
    cn(CN,_).
np(p,np(det(Det),cn(CN)),[Det,CN|R],R):-
    det(_,Det),
    cn(_,CN).
vp(s,vp(tv(TV),NP),[TV|R]):-
    tv(TV,_),
    np(_,NP,R,_).
vp(p,vp(tv(TV),NP),[TV|R]):-
    tv(_,TV),
    np(_,NP,R,_).








