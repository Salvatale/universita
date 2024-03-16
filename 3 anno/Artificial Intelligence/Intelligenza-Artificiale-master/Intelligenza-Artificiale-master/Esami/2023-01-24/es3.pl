:- use_module(library(clpfd)).

ammissibile([[RA,CA],[RB,CB]|[]]):-
    RA - RB #\= CA - CB.
ammissibile([[RA,CA]|R]):-
    print([RA|CA]),nl,
    check([RA,CA],R),
    ammissibile(R).

check([RA,CA],[[RB,CB]]):-
	RA - RB #\= CA - CB.
check([RA,CA],[[RB,CB]|R]):-
    RA - RB #\= CA - CB,
    check([RA,CA],R).













