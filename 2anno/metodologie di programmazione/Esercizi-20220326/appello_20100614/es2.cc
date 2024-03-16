#include <iostream>
using namespace std;
struct A {
    virtual void f(int){ cout << "A::f(int)" << endl; }
    virtual void f(double) { cout << "A::f(double)" << endl; }
    virtual void g() { cout << "A::g(double)" << endl; }
    virtual ~A() { cout << "Destructor A::~A()" << endl; }
};
struct B : public A {
    void f(int) { cout << "B::f(int)" << endl; }
    virtual void f(double) const { cout << "B::f(double)" << endl; }
    virtual void g(int) { cout << "B::g(int)" << endl; }
    ~B() { cout << "Destructor B::~B()" << endl; }
};
struct C : public B {
    void f(int) const { cout << "C::f(int)" << endl; }
    void g(int) { cout << "C::g(int)" << endl; }
    ~C() { cout << "Destructor C::~C()" << endl; }
};
int main() {
    A* a = new A;
    B b;
    C c;
    A& ra_b = b;
    B& rb_b = b;
    A& ra_c = c;
    B& rb_c = c;
    cout << "=== 1 ===" << endl;
    ra_b.f(1);
    rb_b.g(1);
    ra_c.f(1);
    rb_c.g(1);
    cout << "=== 2 ===" << endl;
    static_cast<A*>(&b)->f(1.2);
    static_cast<A*>(&c)->f(1);
    static_cast<B*>(&c)->g(1.2);
    cout << "=== 3 ===" << endl;
    b.f(2);
    c.g(3);
    cout << "=== 4 ===" << endl;
}

/*
---------------1
B::f(int)
B::g(int)
B::f(int)
C::g(int)
--------------- 2
A::f(double)
B::f(int)
C::g(int)
-------------- 3
B::f(int)
C::g(int)
--------------- 4
Destructor A::~C()
Destructor B::~B()
Destructor C::~A()
Destructor A::~B()
Destructor A::~A()
*/