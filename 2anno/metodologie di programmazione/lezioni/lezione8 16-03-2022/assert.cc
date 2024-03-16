#include <cassert>

int foo(int a) {
    //contratto narrow
    assert(a > 0);  //precondizione
    return 2 * a;
}

int main()
{
    foo(5);
    foo(-5);
    //Tra le precondizioni del mio contratto c'è che a > 0.Allora colpa del
    //programmatore che non l'ha rispettata.
}


/*
Ottengo questo errore lanciando il programma :
assert: assert.cc:5: int foo(int): Assertion `a > 0' failed.
Aborted (core dumped)
Manda in abort perchè nel file sorgente assert.cc alla quinta riga nella funzione
foo, assert ha fatto un controllo che ha dato il valore booleano falso.
Con gdb possiamo chiamare il debugger del compilatore g++.
Con run si esegue il programma.
Con backtrace si chiede al debugger di far vedere la traccia delle chiamate delle
funzioni che si ottiene andando a vedere sullo stack di sistema.

Assert di tipo C è una macro, lavorano a livello di preprocessore, quindi dobbiamo
dare l'informazione al preprocessore che non si vuole fare debugging.
Si inserisce nella compilazione un -D che definisce una variabile che si chiama
NDEBUG, quindi nel comando:
g++ -DNDEBUG -g -Wall -Wextra -o assert assert.cc
In questo caso l'assert non viene controllata e quindi il programma causa undefined
behaviour.
*/