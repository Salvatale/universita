
member(X, [X|_]).
member(X, [_|R]):-
    member(X,R).

append([],L,L).
append([X|L1],L2,[X|L3]):-
    append(L1,L2,L3).

prefix(X,Y):-
    append(X,_,Y).

select(E, [E|L],L).
select(E, [A,B|L1],[A|L2]):-
    select(E,[B|L1],L2).

reverse(L,R):-
    reverse(L,R,[]).

reverse([],L,L).
reverse([H|L],R,C):-
	reverse(L,R,[H|C]).