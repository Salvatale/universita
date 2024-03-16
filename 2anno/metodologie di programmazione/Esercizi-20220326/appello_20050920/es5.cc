#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
typedef std::vector<std::string> vect;
typedef std::vector<std::string>::iterator iter;

void f(const vect& v) {
    iter i = std::find(v.begin(), v.end(), "cioccolato");
    iter i_end = std::find(v.begin(), v.end(), "menta");
    while (i != i_end) {
        std::cout << *i << std::endl;
        ++i;
    }
}

void g(vect& v) {
    iter i = v.begin();
    iter i_end = v.end();
    *i = "cacao";
    v.insert(i, "vaniglia");
    while (i != i_end) {
        std::cout << *i << std::endl;
        ++i;
    }
}

/*
Primo problema:
Nella funzione f sarebbe meglio dare il tipo auto ai due iteratori 
i e i_end perchè potrebbero non esserci cast definiti da utente.

Secondo problema:
*i = "cacao" e v.insert(i, "vaniglia")
Nel primo caso se i = i_end allora vado a scrivere in una porzione di memoria in cui non dovrei farlo,
Nel secondo caso una volta inserito vaniglia, vado ad invalidare l'iteratore i non potendolo più utilizzare.
*/