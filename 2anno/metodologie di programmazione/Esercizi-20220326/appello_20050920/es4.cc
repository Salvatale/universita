//BSoft.hh

class BSoft {
private:
// ...
public:
    void s1();
    void s2(const BSoft& y, int n);
    void s3(int n);
// ...
};

/////////////////////////////////////////////////////////
//BWare.hh

class BWare {
private:
// ...
public:
    void w1();
    void w2_1(const BWare& y);
    void w2_2(int n);
    void w3(int n);
    // ... ecc.
};


///////////////////////////////////////////////////////////7
//Biblio.hh

class Biblio {
private:
// ...
public:
    virtual void f1()=0;
    virtual void f2(const Biblio& y,int n)=0;
    virtual void f3(int n)=0;
    // ... ecc.
    virtual ~Biblio(){}
};


///////////////////////////////////////////////////////////7
//BSoft_Adapter.hh
#include "Bsoft.hh"
#include "Biblio.hh"

class BSoft_Adapter : public Biblio {
private:
    BSoft b;
// ...
public:
    void f1() override{
        b.s1();
    }
    void f2(const Biblio& y,int n) override{
        y = dynamic_cast<BSoft&>(y);
        b.s2(y,n);
    }
    virtual void f3(int n) override{
        b.s3();
    }
    // ... ecc.
};


///////////////////////////////////////////////////////////7
//BSoft_Adapter.hh
#include "Bware.hh"
#include "Biblio.hh"

class Bware_Adapter : public Biblio {
private:
    BWare bw;
// ...
public:
    void f1() override{
        bw.w1();
    }
    void f2(const Biblio& y,int n) override{
        y = dynamic_cast<BWare&>(y);
        bw.w2_1(y);
        bw.w2_2(n);
    }
    virtual void f3(int n) override{
        bw.w3();
    }
    // ... ecc.
};


////////////////////////////////////////////////////////////////

//file.cc
#include "Bware.hh"
#include "Biblio.hh"
#include "BSoft.hh"

void f(Biblio& x, const Biblio& y, int n) {
// ...
    if (n > 0)
        x.f3(n);
    else {
        x.f1();
        n = 5;
    }
    // ...
    x.f2(y, n);
    // ...
}