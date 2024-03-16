#include <string>
#include <iostream>
class D;
class C {
private:
    // ...
public:
    C() {std::cout << "Funzione #1" << std::endl;}
    C(const D&){std::cout << "Funzione #2" << std::endl;}
    // ...
};
class D {
private:
    // ...
public:
    D() {std::cout << "Funzione #3" << std::endl;}
    D(const C&) {std::cout << "Funzione #4" << std::endl;}
    // ...
};
void f(double d) {std::cout << "Funzione #5" << std::endl;}
void f(int i, C c = C()) {std::cout << "Funzione #6" << std::endl;}
void f(double d, C c = C()) {std::cout << "Funzione #7" << std::endl;}
void g(C c, D d) {std::cout << "Funzione #8" << std::endl;}
void g(D d, C c = C()) {std::cout << "Funzione #9" << std::endl;}
void h(const char* s){std::cout << "Funzione #10" << std::endl;}
void h(const std::string& s){std::cout << "Funzione #11" << std::endl;}
int main() {
    C c;    // chiamata #1
    D d;    // chiamata #2
    f('a'); // chiamata #3
    f('a', c);  // chiamata #4
    //f(3.2); // chiamata #5
    g(c, d);   // chiamata #6
    g(d, c);    // chiamata #7
    g(c);   // chiamata #8
    g(d);   // chiamata #9
    h("abra");  // chiamata #10
    //h('a'); // chiamata #11
}

/*
chiamata 1: cand{1} util{1} best{1}
chiamata 2: cand{3} util{3} best{3}
chiamata 3: cand{5,6,7} util{5,6,7} best{6}
chiamata 4: cand{5,6,7} util{6,7} best{6}
chiamata 5: cand{5,6,7} util{5,6,7} best{} ambigua 
chiamata 6: cand{8,9} util{8,9} best{8}
chiamata 7: cand{8,9} util{8,9} best{9}
chiamata 8: cand{8,9} util{9} best{9}
chiamata 9: cand{8,9} util{9} best{9}
chiamata 10: cand{10,11} util{10,11} best{10}
chiamata 11: cand{10,11} util{} best{}

*/