#include <iostream>

int main()
{
    std::cout << "Hello, world!" << std::endl;

    (operator<<(std::cout,"Hello World")) << std::endl;
}

/*

Nella fase di preprocessing, ha preso il programma sorgente e include dentro questo
file un altro file chiamato iostream che è un header file che è presente nelle directory
di sistema.
Queste directory si trovano in /usr/include/c++/7.5.0/iostream.
Il preprocessore vede l'include e incolla in questo caso il contenuto del file iostream
, il preprocessore incolla iostream ma poi si riapplica ricorsivamente dato che il
file iostream conterrà altre direttive di preprocessing.
Dentro iostream c'è la dichiarazione della variabile extern ostream cout ed
anche dell external istream cin che si trovano dentro il namespace std.
Per visualizzare il risultato del preprocessing si deve scrivere questo comando da
terminale:
$ g++ -E(scrivere questo per il risultato del preprocessing) -Wall -Wextra hello.cpp
-o hello.pre.cpp
Il compilatore sta compilando questo oggetto qui che è chiamata unità di traduzione.
Anche il programma più semplice come questo lavora su tanti file sorgente ed il
compilatore lavora su porzioni dei file sorgenti che formano le unità di traduzione
che compilate formeranno n file oggetto per n unità di traduzione e il linker 
successivamente li unirà insieme.
extern ostream cout nel file iostream non è definito ma solo dichiarato, extern dirà
al compilatore che questa variabile sarà definita all'esterno, il linker collegherà poi
la parte che ha dichiarato la variabile cout con la parte che l'ha definita.
1:08:15

*/
