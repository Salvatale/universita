#include <iostream>
#include <iterator>
#include <forward_list>

//scorre la sequenza dall'inizio fino alla fine e
//restituisce il primo elemento uguale ad elem
template <typename InputIterator, typename T>
InputIterator
find(InputIterator first,InputIterator last,const T& elem){
    for(;first != last; ++first){
        if(*first == elem)
            return first;
    }
    return last;
}

int main(){
    std::forward_list<int> l = {1,34,2,3,4,2,5};
    std::forward_list<int>::const_iterator first = l.cbegin();
    std::forward_list<int>::const_iterator last = l.cend();
    std::forward_list<int>::const_iterator ric = find(first,last,7);
    if(ric != last)
        std::cout << *ric << std::endl;
}