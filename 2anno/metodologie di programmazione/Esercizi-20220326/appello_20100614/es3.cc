class Expr {
public:
    enum Kind { VAR, CONST, ADD, SUB, /*...*/ };
    Kind kind;
    // ...
    void print() const {
        switch (kind) {
        case VAR:
            print(name());
            break;
        case CONST:
            print(value());
            break;
        case ADD:
            arg1().print();
            print(" + ");
            arg2().print();
            break;
        case SUB:
            arg1().print();
            print(" - ");
            arg2().print();
            break;
        /* ... */
        }
    }
    double eval(const Var_Bindings& vb) const {
    switch (kind) {
    case VAR:
        return vb[name()];
    case CONST:
        return value();
    case ADD:
        return arg1().eval(vb) + arg2().eval(vb);
    case SUB:
        return arg1().eval(vb) - arg2().eval(vb);
    /* ... */
    }
    }
// ...
};

//correzione
//////////////////////////////////////////////////7
//Expr.hh

class Expr {
    virtual void print() const = 0;
    virtual double eval(const Var_Bindings& vb) const = 0;

    virtual ~Expr(){}
};

//////////////////////////////////////////////////7
//VAR.hh

class VAR : public Expr {
    void print() const {
        print(name());
    }
    double eval(const Var_Bindings& vb) const {
        return vb[name()];
    }

    ~VAR(){}
};

//////////////////////////////////////////////////7
//CONST.hh

class CONST : public Expr {
    void print() const {
        print(value());
    }
    double eval(const Var_Bindings& vb) const {
        return value();
    }

    ~CONST(){}
};

//////////////////////////////////////////////////7
//ADD.hh

class ADD : public Expr {
    void print() const {
        arg1().print();
        print(" + ");
        arg2().print();
    }
    double eval(const Var_Bindings& vb) const {
        return arg1().eval(vb) + arg2().eval(vb);
    }

    ~ADD(){}
};

//////////////////////////////////////////////////7
//SUB.hh

class SUB : public Expr {
    void print() const {
        arg1().print();
        print(" - ");
        arg2().print();
    }
    double eval(const Var_Bindings& vb) const {
        return arg1().eval(vb) - arg2().eval(vb);
    }

    ~SUB(){}
};