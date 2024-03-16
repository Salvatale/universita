:- use_module(library(clpfd)).

length1([],0).
length1([_|L],Length):-
    Length #>= 1,
    N1 #= Length - 1,
    length1(L,N1).


member(X,[X|_]).
member(X,[_|L]):-
    member(X,L).


nonmember(X,[X|_]):-
    !,
    fail.
nonmember(_,[]).
nonmember(X,[_|L]):-
    nonmember(X,L).

append([],L,L).
append([X|L1],L2,[X|L3]):-
       append(L1,L2,L3).

prefix([],_).
prefix([X|L1],[X|L2]):-
    prefix(L1,L2).
    
reverse(L1,L2):-
    reverse1(L1,L2,[]).

reverse1([],L,L).
reverse1([X|L1],L2,L3):-
    reverse1(L1,L2,[X|L3]).


select(X,[X|L],L).
select(X,[_|L1],[_|L2]):-
    select(X,L1,L2).

intersection([],_,[]).
intersection([X|L1],L2,L3):-
    member(X,L2),
    !,
    L3 = [X|L3t],
    intersection(L1,L2,L3t).
intersection([_|L1],L2,L3):-
    intersection(L1,L2,L3).

subset([],_).
subset([X|L1],L2):-
    member(X,L2),
    subset(L1,L2).

substract([],_,[]).
substract([X|L1],L2,L3):-
    member(X,L2),
    !,
    substract(L1,L2,L3).
substract([X|L1],L2,[X|L3]):-
    substract(L1,L2,L3).

union([],L,L).
union([X|L1],L2,L3):-
    member(X,L2),
    !,
    union(L1,L2,L3).
union([X|L1],L2,[X|L3]):-
    union(L1,L2,L3).


father(a,b).
father(a,c).
father(b,d).
father(b,e).
father(c,f).
father(c,g).
father(c,h).
father(d,i).
father(e,l).
father(e,m).
father(f,n).

brother(X,Y):-
    father(Z,X),
    father(Z,Y).

cousin(X,Y):-
    father(Z1,X),
    father(Z2,Y),
    Z2 \= Z1,
    brother(Z1,Z2).

grandson(X,Y):-
    father(Z,Y),
    father(X,Z).

descendent(X,Y):-
    father(Y,X).
descendent(X,Y):-
    father(Z,X),
    descendent(Z,Y).

occurences(_,[],0).
occurences(X,[X|L],N):-
    !,
    occurences(X,L,M),
    N #= M + 1.
occurences(X,[_|L],N):-
    occurences(X,L,N).

occurs([X|_],1,X).
occurs([_|L],N,X):-
    N #> 1,
    M #= N - 1,
    occurs(L,M,X).

sumlist([],0).
sumlist([X|L],N):-
    sumlist(L,M),
    N #= M + X.

add_up_list(L,K):-
    add(L,K,0).
add([],[],_).
add([X|L],[Y|K],N):-
    Y #= N + X,
    add(L,K,Y).


my_last(X,[X]).
my_last(X,[_|L]):-
    my_last(X,L).

element_at(X,[X|_],1).
element_at(X,[_|L],N):-
    M #= N - 1,
    element_at(X,L,M).

compress([],[]).
compress([X],[X]).
compress([X,X|L],K):-
	!,
    compress([X|L],K).
compress([X,Y|L],[X|K]):-
    compress([Y|L],K).

pack([],[]).
pack([X],[[X]]).
pack([X,X|L],[[X|RX]|R]):-
    !,
    pack([X|L],[RX|R]).
pack([X,Y|L],[[X]|R]):-
    pack([Y|L],R).

encode(L,X):-
    pack(L,K),
    encode1(K,X).
encode1([],[]).
encode1([[X|L]|R],[[X,N]|RT]):-
   	length(L,M),
    N #= M + 1,
    encode1(R,RT).


soluzioni(X,Y):-
    [X,Y] ins 1..10,
    X*X + Y*Y #=< 36,
    X + Y #=< 20,
    X #\= 2,
    label([X,Y]).

%:- debug.

alberi(N,N):-
    N in 1..10,
    label([N]).
alberi(nodo(N,L,R),S):-
    alberi(L,S1),
    alberi(R,S2),
    N in 1..10,
    label([N]),
    S #= S1 + S2 + N.

no_common_elements([],_).
no_common_elements([X|_],L2):-
    member(X,L2),
    !,
    fail.
no_common_elements([_|L1],L2):-
    no_common_elements(L1,L2).

even(X):-
    check(X,even),
    !.

check(0,even):-
    !.
check(0,odd):-
    !,
    fail.
check(X,even):-
    Y #= X - 1,
    check(Y,odd).
check(X,odd):-
    Y #= X - 1,
    check(Y,even).

print_even([],[]).
print_even([X|L],[X|K]):-
    even(X),
    !,
    print_even(L,K).
print_even([_|L],K):-
    print_even(L,K).

double(L1,L2):-
    length(L1,N),
    length(L2,M),
    N #= 2*M.




















