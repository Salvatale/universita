#include <iostream>
class Base {
public:
    void f(int, double){std::cout << "Funzione 1" << std::endl;}
    void f(double, int) const{std::cout << "Funzione 2" << std::endl;}
    void g(double){std::cout << "Funzione 3" << std::endl;}
    void print(std::ostream&) const{std::cout << "Funzione 4" << std::endl;}
};
class Derived : public Base {
public:
    using Base::f;
    void f(double, double){std::cout << "Funzione 5" << std::endl;}
    void g(double) const{std::cout << "Funzione 6" << std::endl;}
private:
    void print(std::ostream&){std::cout << "Funzione 7" << std::endl;}
};

int main() {
    Base b;
    Derived d;
    Base* pb = &d;
    const Derived* pd = &d;
    b.print(std::cout);     //chiamata 1
    d.print(std::cerr);     //chiamata 2
    pb->print(std::cerr);   //chiamata 3
    pd->print(std::cout);   //chiamata 4
    b.f('a', 0.7);          //chiamata 5
    d.f(12.5, 1.4);         //chiamata 6
    pb->f(2, 0);            //chiamata 7
    pd->f(7.2, 7);          //chiamata 8
    pd->f(7, 7.2);          //chiamata 9
    const Base* pb2 = static_cast<const Base*>(pd);
    pb2->g(0.0);            //chiamata 10
    pd->g(0.0);             //chiamata 11
}

/*
chiamata 1: cand{4} util{4} best{4}
chiamata 2: cand{1} util{} best{}
chiamata 3: cand{4} util{4} best{4}
chiamata 4: cand{1} util{} best{}
chiamata 5: cand{1,2} util{1,2} best{1}
chiamata 6: cand{1,2,5} util{1,2,5} best{5}
chiamata 7: cand{1,2} util{1,2} best{} ambigua
chiamata 8: cand{1,2,5} util{2} best{2}
chiamata 9: cand{1,2,5} util{2} best{2}
chiamata 10: cand{3} util{} best{} 
chiamata 11: cand{6} util{6} best{6}

*/