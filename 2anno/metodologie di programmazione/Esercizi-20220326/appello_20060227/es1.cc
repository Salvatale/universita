#include <iostream>


void foo(int*){std::cout << "Funzione 1" << std::endl;}
template <typename T>
void foo(const T&){std::cout << "Funzione 2" << std::endl;}

template <typename T>
void foo(T, T){std::cout << "Funzione 3" << std::endl;}
template <typename T, typename U>
void foo(T, U){std::cout << "Funzione 4" << std::endl;}
template <typename T>
void foo(const T*, T){std::cout << "Funzione 5" << std::endl;}
template <typename T, typename U>
void foo(T*, U){std::cout << "Funzione 6" << std::endl;}

namespace A {

    struct Delta {
        Delta(double = 0) {};
    };

template <typename T>
void bar(T, double){std::cout << "Funzione 7" << std::endl;}
template <typename T, typename U>
void bar(T, U){std::cout << "Funzione 8" << std::endl;}
} // namespace A

template <typename T>
void bar(T, const A::Delta&){std::cout << "Funzione 9" << std::endl;}

int main() {
    int alfa;
    const int* p_alfa = &alfa;
    double beta;
    long gamma;
    A::Delta delta;
    foo(&alfa, beta);       //chiamata 1
    foo(&alfa, alfa);       //chiamata 2
    foo(p_alfa, alfa);      //chiamata 3
    foo(alfa, p_alfa);      //chiamata 4
    foo(alfa);              //chiamata 5
    foo(&alfa);             //chiamata 6
    foo(p_alfa);            //chiamata 7
    foo(const_cast<int*>(p_alfa));  //chiamata 8
    bar(gamma, gamma);      //chiamata 9
    bar(delta, alfa);       //chiamata 10
    bar(delta, beta);       //chiamata 11
    A::bar(beta, gamma);    //chiamata 12
}

/*
chiamta 1: cand{1,6-void foo<int,double>(int*,double)} util{6} best{6}
chiamta 2: cand{1,6- void foo<int,int>(int*,int)} util{6} best{6}
chiamta 3: cand{1,5- void foo<int>(const int*,int)} util{5} best{5}
chiamta 4: cand{1,4- void foo<int,const int*(int,const int*)} util{4} best{4}
chiamta 5: cand{1,2- void foo<int>(const int&)} util{2} best{2}
chiamta 6: cand{1,2- void foo<int*>(int* const &)} util{1,2} best{1}
chiamta 7: cand{1,2- void foo<const int*(const int* const &)} util{2} best{2}
chiamta 8: cand{1,2- void foo<int*>(int * const &)} util{1,2} best{1}
chiamta 9: cand{9-void bar<long>(long,const A::Delta&)} util{9} best{9}
chiamta 10: cand{8- void bar<A::Delta,int>(A::Delta,int)} util{8} best{8}
chiamta 11: cand{7- void bar<A::Delta>(A::Delta,double)} util{7} best{7}
chiamta 12: cand{8- void bar<double,long>(double,long)} util{8} best{8}

*/