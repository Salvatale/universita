#include <iostream>
#include <string>

int main() {
  using namespace std::literals;
  std::cout << "Hello" << std::endl;  // stampa la stringa C   (tipo const char[6])
  std::cout << "Hello"s << std::endl; // stampa la stringa C++ (tipo std::string)
}