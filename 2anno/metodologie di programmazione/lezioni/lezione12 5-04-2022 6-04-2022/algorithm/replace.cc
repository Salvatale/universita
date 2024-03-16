#include <iostream>
#include <iterator>
#include <forward_list>



template <typename  ForwardIterator, typename T>
void
replace(ForwardIterator first,ForwardIterator last,const T& x,const T& y){
    for(; first != last; ++first){
        if(*first == x)
            *first = y;
    }
    return;
}



bool numero_pari(int n){
    if((n%2)== 0)
        return true;
    return false;
}


int main(){
    std::forward_list<int> l = {2,34,24,38,40,24,58};
    std::forward_list<int>::iterator first = l.begin();
    std::forward_list<int>::iterator last = l.end();
    replace(first,last,40,70);
    for(; first != last; ++first){
        std::cout << *first << " " << std::endl;
    }

}