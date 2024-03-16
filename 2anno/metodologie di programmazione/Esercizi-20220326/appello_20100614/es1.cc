#include <iostream>
using namespace std;
namespace N {
    struct C {
        C(int){cout << "funzione 1" << endl;}
        C(const C&){cout << "funzione 2" << endl;}
        void m(){cout << "funzione 3" << endl;}
        void m(int){cout << "funzione 4" << endl;}
    };
    void f(double d){cout << "funzione 5" << endl;}
    void f(const C& c){cout << "funzione 6" << endl;}
    void g(int i, double d){cout << "funzione 7" << endl;}
    void g(int i, int j){cout << "funzione 8" << endl;}
    void h(C* pc){cout << "funzione 9" << endl;}
} // namespace N

void f(char){cout << "funzione 10" << endl;}
int h(const char* s = 0){cout << "funzione 11" << endl;}
int h(const N::C* pc){cout << "funzione 12" << endl;}



int main() {
    N::C c(5);// chiamata A
    f(5);   // chiamata B
    f(c);   // chiamata C
    N::f('a');  // chiamata D
    //g(5, 3.7); // chiamata E
    N::g(2.3, 5); // chiamata F
    N::g(5, 2.3); // chiamata G
    h(&c);// chiamata H
    h();    // chiamata I
    //m(&c);// chiamata J
}

/*
chiamata A: cand{1,2} util{1} best{1}  
chiamata B: cand{10} util{10} best{10} 
chiamata C: cand{5,6,10} util{6} best{6}
chiamata D: cand{5,6} util{5,6} best{5}
chiamata E: cand{} util{} best{}
chiamata F: cand{7,8} util{7,8} best{8}
chiamata G: cand{7,8} util{7,8} best{7}
chiamata H: cand{9,11,12} util{9,12} best{9}
chiamata I: cand{11,12} util{11} best{11}
chiamata J: cand{} util{} best{}


*/