#include <iostream>

struct S
{
    // S() {}
    // S(const S& s) {}
    // S& operator=(const S& s) {}; è scritto con S& e non con void così si può concatenare
    // ~S();

    // S(S&& s);
    /*
    prende un riferimento a r-value a qualcosa che non è costante di tipo S
    */
   // S& operator=(S&& s);
};

// di default la struttura dati ha queste funzioni di default se non si specifica 

int main()
{
    S s1;
    S s2 = s1;
    s2 = s1;

    int i = 3;
    std::cout << (i = 18); // cattivo stile dato che si effettuano due operazioni contemporaneamente.


}


/*
S s1 compila dato che comunque c'è un costruttore di default se non si specifica.
S s2 = s1; chiama il costruttore di copia che fa la copia membro a membro.
    Se la classe fosse derivata chiamerebbe anche il costruttore di copia della classe base.
s2 = s1;  qui stiamo facendo l'assegnamento per copia, cioè prendiamo un oggetto già
          esistente e gli copiamo tutti i suoi campi con i relativi campi dell'altro oggetto.

Nel c++ non c'era un modo semplice di dire ad una funzione che un oggetto dato passato per
riferimento e prendere le risorse di questo oggetto dato che non serviva più al chiamante.
Quindi con S&& s crea un nuovo oggetto ma ruba tutto le risorse che può.
*/