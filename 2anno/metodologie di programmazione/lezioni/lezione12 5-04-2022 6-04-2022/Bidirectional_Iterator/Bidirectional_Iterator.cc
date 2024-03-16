#include <iostream>
#include <list>



int main() {
    std::list<int> l= {1,2,3,4,5,6};
    // iteratori per scorrere in avanti
    std::list<int>::const_iterator i1 = l.cbegin();
    std::list<int>::const_iterator f1 = l.cend();

    //iteratori per scorrere alll'indietro
    std::list<int>::const_reverse_iterator i2 = l.crbegin();
    //std::list<int>::const_reverse_iterator f2 = l.crend();

    for(;i1 != f1;++i1){
        std::cout << *i1 << std::endl;
        std::cout << "inverso: " << *i2 << std::endl;
        ++i2;
    }

}