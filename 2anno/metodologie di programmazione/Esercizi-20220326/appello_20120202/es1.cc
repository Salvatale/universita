#include <iostream>
using namespace std;
class Base {
public:
    void f(int, double){cout <<"funzione 1" << endl;}
    void f(double, int) const{cout <<"funzione 2" << endl;}
    void g(double){cout <<"funzione 3" << endl;}
    void print(std::ostream&) const{cout <<"funzione 4" << endl;}
};
class Derived : public Base {
public:
    using Base::f;
    void f(double, double){cout <<"funzione 5" << endl;}
    void g(double) const{cout <<"funzione 6" << endl;}
    private:
    void print(std::ostream&){cout <<"funzione 7" << endl;}
};
int main() {
    Base b;
    Derived d;
    Base* pb = &d;
    const Derived* pd = &d;
    pb->print(std::cerr); // chiamata (a)
    //pd->print(std::cout);// chiamata (b)
    b.f('a', 0.7);// chiamata (c)
    d.f(12.5, 1.4); // chiamata (d)
    //pb->f(2, 0); // chiamata (e)
    pd->f(7.2, 7); // chiamata (f)
    const Base* pb2 = static_cast<const Base*>(pd);
    //pb2->g(0.0);// chiamata (g)
    pd->g(0.0);// chiamata (h)
}


/*
chiamata a: cand{4} util{4} best{4}  
chiamata b: cand{7} util{} best{} non utilizzabile dato che ho un oggetto const e mi serve un metodo print const
chiamata c: cand{1,2,5} util{1,2,5} best{1}
chiamata d: cand{1,2,5} util{1,2,5} best{5}
chiamata e: cand{1,2} util{1,2} best{} ambigua 
chiamata f: cand{5,1,2} util{2} best{2}
chiamata g: cand{3} util{} best{} metodo non const
chiamata h: cand{6} util{6} best{6}


*/