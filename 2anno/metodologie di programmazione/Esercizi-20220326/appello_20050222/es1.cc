#include <iostream>


void f(const char* s){std::cout << "funzione #1" << std::endl;}
template <typename T>
void f(T t){std::cout << "funzione #2" << std::endl;}

template <typename T>
void f(T t1, T t2){std::cout << "funzione #3" << std::endl;}
template <typename T, typename U>
void f(T t, U u){std::cout << "funzione #4" << std::endl;}
template <typename T>
void f(T* pt, T t){std::cout << "funzione #5" << std::endl;}
template <typename T, typename U>
void f(T* pt, U u){std::cout << "funzione #6" << std::endl;}


template <typename T>
void g(T t, double d){std::cout << "funzione #7" << std::endl;}
template <typename T>
void g(T t1, T t2){std::cout << "funzione #8" << std::endl;}

void test() {
    f('a');     //chiamata 1
    f("aaa");   //chiamata 2
    int i;
    f(i);       //chiamata 3
    f(i, i);    //chiamata 4
    f(i, &i);   //chiamata 5
    f(&i, i);   //chiamata 6
    double d;   
    f(i, d);    //chiamata 8
    f(&d, i);   //chiamata 9
    long l;     
    g(l, i);    //chiamata 10
    g(l, l) ;   //chiamata 11
    g(l, d) ;   //chiamata 12
    //g(d, d) ;   //chiamata 13
}

int main(){
    test();
    return 0;
}

/*
chiamata 1: cand{1,2-void f<char>(char t)} util{2} best{2}
chiamata 2: cand{1,2-void f<const char*>(const char* t)} util{1,2} best{1}
chiamata 3: cand{1,2-void f<int>(int t)} util{2} best{2}
chiamata 4: cand{1,3-void f<int,int>(int t1,int t2)} util{3} best{3}
chiamata 5: cand{1,4-void f<int,int*>(int t,int* u)} util{4} best{4}
chiamata 6: cand{1,5-void f<int*,int>(int* pt,int t)} util{5} best{5}
chiamata 8: cand{1,4-void f<int,double>(int t,double u)} util{4} best{4}
chiamata 9: cand{1,6-void f<double*,int>(duoble* pt,int u)} util{6} best{6}
chiamata 10: cand{7-void g<long>(long t,double d)} util{7} best{7}
chiamata 11: cand{8-void g<long,long>(long t1,long t2)} util{8} cand{8}
chiamata 12: cand{7-void g<long>(long t, double d)} util{7} best{7}
chiamata 13: cand{} util{} best{} ambiguo
*/