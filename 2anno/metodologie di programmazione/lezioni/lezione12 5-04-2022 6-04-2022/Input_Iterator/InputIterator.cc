#include <iterator>
#include <iostream>

template <typename T>
using Input = std::istream_iterator<T>;

void f(){
  std::cout << "Fatto" << std::endl;
  Input<int> i(std::cin); // inizio della (pseudo) sequenza
  auto j = i;
  // ora j e i puntano entrambi all'elemento corrente
  std::cout << *i << std::endl; // stampo l'elemento corrente
  std::cout << *j << std::endl; // stampo ancora l'elemento corrente
  std::cout << std::endl;
  ++i;             // avanzo con i: questa operazione rende j *invalido*
  std::cout << *j << std::endl; // errore: comportamento NON definito
}

int main() {

  // uso di iteratori per leggere numeri double da std::cin
  //f();

  Input<int> i(std::cin); // inizio della (pseudo) sequenza
  Input<int> iend;        // fine della (pseudo) sequenza

  // scorro la sequenza, stampando i double letti su std::cout
  for ( ; i != iend; ++i)
    std::cout << *i << std::endl;
}