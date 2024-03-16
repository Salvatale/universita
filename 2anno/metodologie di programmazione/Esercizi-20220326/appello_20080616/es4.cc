#include <iostream>
#include <vector>

bool maggiore(int a,int b){
    return a > b;
}

template <typename Iter, typename BinaryPred>
Iter
max_elem(Iter first,Iter last, BinaryPred cmp){
    auto i = first;
    for(;first != last; ++first){
        if(cmp(*first,*i))
            *i = *first;
    }
    return i;
    
}




int main(){
    std::vector<int> v ;
    auto i = max_elem(v.begin(),v.end(),maggiore);
    if(i != v.end())
        std::cout << *i << std::endl;
    else
        std::cout << "sequenza vuota" << std::endl;
}