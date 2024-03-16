#include <iostream>
class Animale {
public:
    
    virtual void verso() const = 0;
    virtual ~Animale(){}
};

class Cane : public Animale {
public:
    virtual void verso() const { std::cout << "bau!" << std::endl; }
    virtual ~Cane(){}
};
class Pesce : public Animale {
public:
    virtual void verso() const { std::cout << "(glu glu)" << std::endl; }
    virtual ~Pesce(){}
};
class Pescecane : public Pesce {
public:
    virtual void verso() const { std::cout << "(glubau!)" << std::endl; }
    virtual ~Pescecane(){}
};


int main() {
    Animale *c = new Cane;
    c->verso();
    std::cout << "=== 1 ===" << std::endl;
    Animale *p = new Pescecane;
    p->verso();
}