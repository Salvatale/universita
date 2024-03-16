// File FaxModem.hh
class FaxModem_AllStars {
private:
// ...
public:
    void fax_function_1();
    void fax_function_2(const char*);
    void fax_function_3(int);
    // ...
    void modem_function_1(const char*);
    void modem_function_2();
    void modem_function_3(unsigned int);
    // ...
};

// File User.cc
#include "FaxModem.hh"
void user_function_1(FaxModem_AllStars& f) {
    f.fax_function_1();
    // ...
    f.fax_function_3(12);
    // ...
}
void user_function_2(FaxModem_AllStars& m, const char* command) {
    m.modem_function_1(command);
    // ...
    m.modem_function_3(1024);
    // ...
}
void user_function_3(FaxModem_AllStars& f, FaxModem_AllStars& m) {
    f.fax_function_2("+390521906950");
    // ...
    m.modem_function_2();
    // ...
}

//////////////////////////////////////////
//Fax.hh
class Fax {
private:
// ...
public:
    virtual void fax_function_1() = 0;
    virtual void fax_function_2(const char*) = 0;
    virtual void fax_function_3(int) = 0;
    // ...
    virtual ~Fax(){}
};


//////////////////////////////////////////
//Modem.hh
class Modem {
private:
// ...
public:
    virtual void modem_function_1() = 0;
    virtual void modem_function_2(const char*) = 0;
    virtual void modem_function_3(int) = 0;
    // ...
    virtual ~Modem(){}
};

//////////////////////////////////////////
//Fax_Adapter.hh
#include "FaxModem_AllStars.hh"
#include "Fax.hh"
class Fax_Adapter : public Fax{
private:
    FaxModem_AllStars fm;
// ...
public:
    void fax_function_1() {
        fm.fax_function_1();
    }
    void fax_function_2(const char*) {
        fm.fax_function_2();
    }
    void fax_function_3(int) {
        fm.fax_function_3();
    }
    // ...
};

//////////////////////////////////////////
//Fax_Adapter.hh
#include "FaxModem_AllStars.hh"
#include "Modem.hh"

class Modem_Adapter : public Modem{
private:
    FaxModem_AllStars fm;
// ...
public:
    void modem_function_1() {
        fm.modem_function_1();
    }
    void modem_function_2(const char*) {
        fm.modem_function_2();
    }
    void modem_function_3(int) {
        fm.modem_function_3();
    }
    // ...
};

// File User.cc
#include "Fax.hh"
#include "Modem.hh"
#include "Fax_Adapter.hh"
#include "Modem_Adapter.hh"

void user_function_1(Fax& f) {
    f.fax_function_1();
    // ...
    f.fax_function_3(12);
    // ...
}
void user_function_2(Modem& m, const char* command) {
    m.modem_function_1(command);
    // ...
    m.modem_function_3(1024);
    // ...
}
void user_function_3(Fax& f, Modem& m) {
    f.fax_function_2("+390521906950");
    // ...
    m.modem_function_2();
    // ...
}