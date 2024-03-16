#include <iostream>
using namespace std;

struct Base {
    void foo(int, double){cout << "funzione 1" << endl;}
    void foo(double, int) const{cout << "funzione 2" << endl;}
    void bar(double) {cout << "funzione 3" << endl;}
    void print(std::ostream&){cout << "funzione 4" << endl;}
};

struct Derived : public Base {
    void foo(double, double){cout << "funzione 5" << endl;}
    void bar(double) const{cout << "funzione 6" << endl;}
private:
    void print(std::ostream&) const{cout << "funzione 7" << endl;}
};


int main() {
    Base bas;
    Derived der;
    const Base* pbas = &der;
    Derived* pder = &der;
    //pbas->print(std::cerr); //chiamata 1
    //pder->print(std::cout); //chiamata 2
    pbas->foo(2, 0); //chiamata 3
    pder->foo(7.2, 7); //chiamata 4
    //pbas->bar(0.0); //chiamata 5
    pder->bar(0.0); //chiamata 6
}

/*
chiamata 1: cand{4} util{} best{} metodo non const quindi non utilizzabile  
chiamata 2: cand{7} util{7} best{7} ma non utlizabbile perchè private 
chiamata 3: cand{1,2} util{2} best{2}
chiamata 4: cand{5} util{5} best{5}
chiamata 5: cand{3} util{} best{} metodo non const
chiamata 6: cand{6} util{6} best{6}

*/