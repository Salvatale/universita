#include <iostream>
#include <iterator>
#include <forward_list>


/*
Ma se volessimo non un elemento preciso ma magari il primo numero
primo presente nella sequenza:
*/

template <typename InputIterator, typename UnaryPred>
InputIterator
find_if(InputIterator first,InputIterator last, UnaryPred pred){
    for(; first != last;++first){
        if(pred(*first))
            return first;
    }
    return last;
}

bool numero_pari(int n){
    if((n%2)== 0)
        return true;
    return false;
}


int main(){
    std::forward_list<int> l = {1,35,23,37,40,23,59};
    std::forward_list<int>::const_iterator first = l.cbegin();
    std::forward_list<int>::const_iterator last = l.cend();
    std::forward_list<int>::const_iterator ric = find_if(first,last,numero_pari);
    if(ric != last)
        std::cout << *ric << std::endl;
}