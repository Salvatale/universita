#include <iterator>
#include <iostream>

int main() {

  std::ostream_iterator<double> out(std::cout, "\n"); // posizione iniziale
  // Nota: non esiste una "posizione finale"
  // Nota: il secondo argomento del costruttore serve da separatore;
  // se non viene fornito si assume la stringa vuota ""

  double pi = 3.1415;
  for (int i = 0; i != 10; ++i) {
    *out = (pi * i);  // scrittura di un double usando out
    ++out;            // NB: spostarsi in avanti dopo *ogni* scrittura
  }

}