#include <iostream>
#include <iterator>
#include <forward_list>


template < typename InputIterator, typename T>
long
count(InputIterator first,InputIterator last,const T& elem){
    long c = 0;
    for(; first != last; ++first){
        if(*first == elem)
            ++c;
    }
    return c;
}


int main(){
    std::forward_list<int> l = {1,40,23,37,40,23,40};
    std::forward_list<int>::const_iterator first = l.cbegin();
    std::forward_list<int>::const_iterator last = l.cend();
    auto c = count(first,last,40);
    std::cout << c << std::endl;
    
}