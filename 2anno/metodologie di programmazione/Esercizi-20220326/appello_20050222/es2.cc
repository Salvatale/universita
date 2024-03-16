#include <iostream>
class ZooAnimal {
public:
    ZooAnimal() {
        std::cout << "Constructor ZooAnimal" << std::endl;
    }
    virtual void print() {
        std::cout << "ZooAnimal::print" << std::endl;
    }
    virtual ~ZooAnimal() {std::cout <<"Destructor ZooAnimal" << std::endl;}
};

class Bear : virtual public ZooAnimal {
public:
    Bear() {
        std::cout << "Constructor Bear" << std::endl;
    }
    void print() {
        std::cout << "Bear::print" << std::endl;
    }
    virtual ~Bear() {std::cout <<"Destructor Bear" << std::endl;}
};

class Raccoon : virtual public ZooAnimal {
public:
    Raccoon() {
        std::cout << "Constructor Raccoon" << std::endl;
    }
    virtual ~Raccoon() {std::cout <<"Destructor Racoon" << std::endl;}
};

class Endangered {
public:
    Endangered() {
        std::cout << "Constructor Endangered" << std::endl;
    }
    void print() {
        std::cout << "Endangered::print" << std::endl;
    }
    virtual ~Endangered() {std::cout <<"Destructor Endangered" << std::endl;}
};

class Panda : public Endangered, public Bear, public Raccoon {
public:
    Panda() {
        std::cout << "Constructor Panda" << std::endl;
    }
    void print() {
        std::cout << "Panda::print" << std::endl;
    }
    virtual ~Panda() {std::cout <<"Destructor Panda" << std::endl;}
};
int main() {
    Panda ying_yang;
    ying_yang.print();
    Bear b = ying_yang;
    b.print();
    ZooAnimal* pz = &ying_yang;
    pz->print();
    Endangered& re = ying_yang;
    re.print();
    return 0;
}

/*
Output di esecuzione:
Constructor ZooAnimal
Constructor Endangered
Constructor Bear
Constructor Raccoon
Constructor Panda
Panda::print
Bear::print
Panda::print
Endangered::print
Destructor ZooAnimal
Destructor Bear
Destructor Panda
Destructor Racoon
Destructor Bear
Destructor Endagered
Destructor ZooAnimal
*/