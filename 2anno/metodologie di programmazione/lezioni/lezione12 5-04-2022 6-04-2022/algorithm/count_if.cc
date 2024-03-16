#include <iostream>
#include <iterator>
#include <forward_list>


template < typename InputIterator, typename UnaryPred>
long
count_if(InputIterator first,InputIterator last,UnaryPred pred){
    long c = 0;
    for(; first != last; ++first){
        if(pred(*first))
            ++c;
    }
    return c;
}

bool numero_pari(int n){
    if((n%2)== 0)
        return true;
    return false;
}


int main(){
    std::forward_list<int> l = {1,40,23,37,40,23,40};
    std::forward_list<int>::const_iterator first = l.cbegin();
    std::forward_list<int>::const_iterator last = l.cend();
    auto c = count_if(first,last,numero_pari);
    std::cout << c << std::endl;
    
}