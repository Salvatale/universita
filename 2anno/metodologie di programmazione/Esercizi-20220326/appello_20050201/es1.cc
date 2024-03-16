#include <iostream>

namespace NB {
    class D {};
} // namespace NB
namespace NA {
    class C {};
    void f(int i){std::cout << "Funzione #1" << std::endl;}
    void f(double d, C c = C()){std::cout << "Funzione #2" << std::endl;}
    void g(C c = C(), NB::D d = NB::D()){std::cout << "Funzione #3" << std::endl;}
    void h(C c){std::cout << "Funzione #4" << std::endl;}
    void test1() {
        f(2.0);     // chiamata #1
    }
} // namespace NA
namespace NB {
    void f(double d){std::cout << "Funzione #5" << std::endl;}
    void g(NA::C c = NA::C(), D d = D()){std::cout << "Funzione #6" << std::endl;}
    void h(NA::C c, D d){std::cout << "Funzione #7" << std::endl;}
    void test2(double d, NA::C c) {
        f(d);
        // chiamata #2
        //g(c);
        // chiamata #3
        h(c);
        // chiamata #4
    }
} // namespace NB
void f(NA::C c, NB::D d){std::cout << "Funzione #8" << std::endl;}
void test3(NA::C c, NB::D d) {
    //f(1.0);
    // chiamata #5
    //g();
    // chiamata #6
    g(c);
    // chiamata #7

    //g(c,d);  // chiamata #8

    }

/*
chiamata #1:  cand{1,2} util{1,2} best{2} 
chiamata #2: cand{5} util{5} best{5}
chiamata #3: cand{3,6} util{3,6} c'è ambiguità perchè non si sa quale utilizzare best{}
chiamata #4: cand{4,7} util{4} best{4}
chiamata #5: cand{8} util{} best{}
chiamata #6: cand{} util{} best{}
chiamata #7: cand{3} util{3} best{3}
chiamata #8: cand{3,6} util{3,6} best{}
*/


int main(){
    NA::C c;
    NB::D d1;
    double d;
    NA::test1();
    NB::test2(d,c);
    test3(c,d1);
    return 0;
    
}
