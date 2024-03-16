void foo() {
    A* a1 = new A(1);
    A* a2 = new A(2);
    job1(a1, a2)
    delete a2;
    A* a3 = new A(3);
    job2(a1, a3)
    job3(a3)
    delete a3;
    delete a1;
}

//CORREZIONE

class A{
private:
    int* a_;
    A& operator=(const A& a);
    A(const A& a);
    A();
public :
    explicit A(int a) : a_(new int(a)){}
    ~A(){
        delete a_;
    }
};

void foo(){
    A a1(1);
    A a2(2);
    job1(a1,a2);
    A a3(3);
    job2(a1,a3);
    job3(a3);
}