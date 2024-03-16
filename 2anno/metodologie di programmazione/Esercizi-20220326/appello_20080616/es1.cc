#include <string>
#include <iostream>

using namespace std;

namespace N {
    class C {
    private:
        std::string s;
        std::string& first(){cout << "Funzione 1" << endl;
        return s;}
    public:
        const std::string& first() const{cout << "Funzione 2" << endl;
        return s;}
        std::string& last(){cout << "Funzione 3" << endl;
        return s;}
        const std::string& last() const{cout << "Funzione 4" << endl;
        return s;}
        C(const char*){cout << "Funzione 5" << endl;}
    }; // class C

    void print(const C&){cout << "Funzione 6" << endl;}
    std::string& f(int){cout << "Funzione 7" << endl;}
} // namespace N

class A {
public:
    explicit A(std::string&){cout << "Funzione 8" << endl;}
};
void print(const A&){cout << "Funzione 9" << endl;}

void f(N::C& c)
{
    cout << "Funzione 10" << endl;
    const std::string& f1 = c.first();  //chiamata 1
    std::string& f2 = c.first();        //chiamata 2
    const std::string& l1 = c.last();   //chiamata 3
    std::string& l2 = c.last();         //chiamata 4
}

void f(const N::C& c)
{
    cout << "Funzione 11" << endl;
    const std::string& f1 = c.first();      //chiamata 5
    std::string& f2 = c.first();    //chiamata 6
    const std::string& l1 = c.last();   //chiamata 7
    std::string& l2 = c.last(); //chiamata 8
}
int main() {
    N::C c("begin");            //chiamata 9
    f(c);           //chiamata 10
    f("middle");            //chiamata 11
    print("end");           //chiamata 12
}

/*
chiamata 1: cand{1,2} util{1,2} best{1} non accessibile  
chiamata 2: cand{1,2} util{1,2} best{1} non accessibile 
chiamata 3: cand{3,4} util{3,4} best{3}
chiamata 4: cand{3,4} util{3,4} best{3}
chiamata 5: cand{1,2} util{2} best{2}
chiamata 6: cand{1,2} util{} best{} nessuna delle due è utilizzabile
chiamata 7: cand{3,4} util{4} best{4}
chiamata 8: cand{3,4} util{} best{} nessuna delle due è utlizzabile
chiamata 9: cand{5} util{5} best{5}
chiamata 10: cand{7,10,11} util{10,11} best{10}
chiamata 11: cand{10,11} util{11} best{11}
chiamata 12: cand{9} util{} best{} impossibile conversione implicita definita da utente con explicit 


*/