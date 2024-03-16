#include <iostream>

struct S {
  int counter;
  S() : counter(0) { }
  ~S() { std::cout << "counter = " << counter << std::endl; }
};

void foo() {
 static S s; // allocazione locale statica
 ++s.counter;
}

int main() {
  for (int i = 0; i < 10; ++i) {
    foo();
  }
}