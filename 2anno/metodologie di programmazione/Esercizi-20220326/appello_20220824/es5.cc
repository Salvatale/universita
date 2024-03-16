#include <iostream>
using namespace std;
struct A {
    A() { cout << "Constructor A::A()" << endl; }
    void f(int) { cout << "A::f(int)" << endl; }
    virtual void f(double) { cout << "A::f(double)" << endl; }
    virtual void g(double) { cout << "A::g(double)" << endl; }
    virtual ~A() { cout << "Destructor A::~A()" << endl; }
};
struct B {
    B() { cout << "Constructor B::B()" << endl; }
    virtual void f(int) { cout << "B::f(int)" << endl; }
    void f(double) { cout << "B::f(double)" << endl; }
    virtual void g(int) { cout << "B::g(int)" << endl; }
    virtual ~B() { cout << "Destructor B::~B()" << endl; }
};
struct D : public B, public A {
    D() { cout << "Constructor D::D()" << endl; }
    void f(int) { cout << "D::f(int)" << endl; }
    using A::g;
    void g(int) { cout << "D::g(int)" << endl; }
    ~D() { cout << "Destructor D::~D()" << endl; }
};
void h(A& a, B& b, D& d) {
    a.g('a');
    B* pb = &b;
    pb->f(4);
    d.g(44);
}
int main() {
    D d;
    A& ra = d;
    B& rb = d;
    cout << "=== 1 ===" << endl;
    ra.f(1);
    ra.g(1);
    d.f(1.2);
    d.g(1.2);
    cout << "=== 2 ===" << endl;
    h(d, rb, d);
    return 0;
}

/*
Constructor B::B()
Constructor A::A()
Constructor D::D()
=== 1 ===
A::f(int)
A::g(double)
D::f(int)
A::g(double)
=== 2 ===
A::g(double)
D::f(int)
D::g(int)
Destructor D::~D()
Destructor A::~A()
Destructor B::~B()
*/