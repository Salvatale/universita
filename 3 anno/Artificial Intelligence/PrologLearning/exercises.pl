%LISTS

%true if K is reverse of L
reverse(L,K):-
    reverse1(L,K,[]).

reverse1([],K,K).
reverse1([A|L1],K,L2):-
    reverse1(L1,K,[A|L2]).

%if X occurs in L
member(X,[X|_]).
member(X,[_|L]):-
    member(X,L).

%if L is a subset of K
subset([],_).
subset([X|L],K):-
    member(X,K),
    subset(L,K).

%L and K are disjoint
disjoint([],_).
disjoint([X|L],K):-
    not(member(X,K)),
    disjoint(L,K).

%M is union of L and K
union([],K,K).
union([A|L],K,[A|M]):-
    union(L,K,M).

%M is intersection of L and K
intersection([],_,[]).
intersection([A|L],K,[A|M]):-
    member(A,K),
    intersection(L,K,M).
intersection([A|L],K,M):-
    not(member(A,K)),
    intersection(L,K,M).

%M is difference between L and K
difference([],_,[]).
difference([A|L],K,[A|M]):-
    not(member(A,K)),
    difference(L,K,M).
difference([A|L],K,M):-
    member(A,K),
    difference(L,K,M).



















    

    