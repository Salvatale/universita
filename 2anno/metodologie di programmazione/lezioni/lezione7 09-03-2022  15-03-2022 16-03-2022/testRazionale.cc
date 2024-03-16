#include "Razionale.hh"

#include <iostream>

void test01() {
    using Numerica::Razionale;

    Razionale r0;       // costruttore di default

    Razionale r1(r);        // costruttore di copia
    Razionale r2 = r;       // costruttore di copia
    Razionale r3 {r} ;      // costruttore di copia (C++11)
    Razionale r4 = {r} ;    // costruttore di copia (C++11)

    Razionale r5(1,2);      //costruzione diretta
    Razionale r6{1,2};      //costruzione diretta (C++11)
    Razionale r7(1);        //costruzione diretta
    Razionale r8{1};        //costruzione diretta (C++11)
    //Razionale r9 = 1234;    //costruzione implicita(da evitare!) non compila se
                            // c'è explicit
    Razionale r9 = Razionale(1234); // se il costruttore è definito explicit

    r = r1;                 //assegnamento per copia
    r = Razionale(1);       //assegnamento per spostamento
    r2 = r1 = r;            //concatenazione assegnamenti (evitare?)

    //Operatori aritmetici binari
    r1 = r + r;
    r1 = r - r;
    r1 = r * r;
    r1 = r / r;

    //Operatori aritmetici unari
    r1 = -r;
    r1 = +r;                //se fosse un int piccolo,ogni volta che lo utilizziamo
                            //in qualche espressione fa una promozione

    //op-assign
    r += r;
    r -= r;
    r *= r;
    r /= r;

    //Incremento e decremento (pre o post)
    ++r;
    r++;        /* dato che con questo bisogna creare un oggetto copia da restituire
                   come risulato e se un oggetto è molto grande questa copia costa
                   , quindi sarebbe da evitare dato che dopo la copia sarebbe da
                   buttare dopo essere stata restituita come risultato 
                */
    --r;
    r--;

    //casi in cui è utile utilizzare post
    //*(ptr++) = 0; prima azzero il puntatore e subito dopo punto alla cella successiva
    //ovviamente si potrebbe anche fare in questo modo
    //*ptr = 0;
    //++ptr;
    
    //Operatori relazionali
    bool b;
    b = (r == r);
    b = (r != r);
    b = (r <= r);
    b = (r >= r);
    b = (r < r);
    b = (r > r);

    //Input e Output
    std::cin >> r;
    std::cin >> r >> r1;
    std::cout << r << std::endl;
    std::cout << r1 << "+" << r2 << "=" << (r1 + r2) << std::endl;

    Razionale::Integer n = r.num();

    /*
    r.num() = 18;
    r.den() = -3;
    Queste due istruzioni potrebbero rompere l'invariante se noi facessimo accedere
    anche in scrittura oltre che in memoria.
    */
    const Razionale::Integer& n = r.num();
    Razionale::Integer& nn = const_cast<Razionale::Integer&>(n);
    n = 18;
    //In questo caso l'utente sta cercando di modificare il valore attraverso un casting.

    //invocazione implicita dei distruttori
}

int main() {
    Numerica::Razionale r;
    (std::cout << "il mio razionale r = ") << r << std::endl;
}