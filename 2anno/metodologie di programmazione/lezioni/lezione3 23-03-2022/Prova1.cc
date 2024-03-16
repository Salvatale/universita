#include <iostream>

struct S {
  int v;
  const int c;
  S(int cc) : c(cc) { v = 10; }
};

int main() {
  const S sc(5);
  //sc.v = 20; // errore: sc è const e anche le sue componenti

  S s(5);
  s.v = 20; // legittimo: s non è const e S::v non è const
  //s.c = 20; // errore: s non è const, ma S::c è const

  std::cout << s.c << " " << s.v << std::endl;
}