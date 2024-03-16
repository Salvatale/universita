#include <iostream>
struct A {
    A() { std::cout << "Ctor A::A()" << std::endl; }
    virtual void f(int) { std::cout << "A::f(int)" << std::endl; }
    virtual void f(double) { std::cout << "A::f(double)" << std::endl; }
    virtual void g(int) { std::cout << "A::g(int)" << std::endl; }
    virtual ~A() { std::cout << "Dtor A::~A()" << std::endl; }
};
struct B : public A {
    B() { std::cout << "Ctor B::B()" << std::endl; }
    using A::f;
    virtual void f(char) { std::cout << "B::f(char)" << std::endl; }
    void g(int) { std::cout << "B::g(int)" << std::endl; }
    ~B() { std::cout << "Dtor B::~B()" << std::endl; }
};
struct C : public B {
    virtual void f(char) { std::cout << "C::f(char)" << std::endl; }
    ~C() { std::cout << "Dtor C::~C()" << std::endl; }
};


int main() {
    A a;
    C c;
    A& ra = a;
    B* pb = &c;
    std::cout << "=== 1 ===" << std::endl;
    pb->f(1.0);
    pb->f('a');
    pb->g(3.1415);
    std::cout << "=== 2 ===" << std::endl;
    c.f(1);
    c.f(1.0);
    c.g(3.1415);
    std::cout << "=== 3 ===" << std::endl;
    a.f(1);
    ra.f('a');
    ra.g(1);
    return 0;
}

/*
Ctor A::A()
Ctor A::A()
Ctor B::B()
=== 1 ===
A::f(double)
C::f(char)
B::g(int)
=== 2 ===
C::f(char)
C::f(char)
B::g(int)
=== 3 ===
A::f(int)
A::f(int)
A::g(int)
Dtor C::~C()
Dtor B::~B()
Dtor A::~A()
Dtor A::~A()
*/