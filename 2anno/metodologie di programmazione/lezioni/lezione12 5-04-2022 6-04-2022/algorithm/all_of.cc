#include <iostream>
#include <iterator>
#include <forward_list>



template <typename InputIterator, typename UnaryPred>
bool
all_of(InputIterator first,InputIterator last,UnaryPred pred){
    for(; first != last; ++first){
        if(!pred(*first))
            return false;
    }
    return true;
}



bool numero_pari(int n){
    if((n%2)== 0)
        return true;
    return false;
}


int main(){
    std::forward_list<int> l = {2,34,24,38,40,24,58};
    std::forward_list<int>::const_iterator first = l.cbegin();
    std::forward_list<int>::const_iterator last = l.cend();
    if(all_of(first,last,numero_pari))
        std::cout << "ok" << std::endl;

}