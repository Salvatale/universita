#include <iostream>
#include <vector>

bool negativo(int a){
    return a < 0;
}


template <typename InIter, typename UnaryPred>
bool all_of(InIter first, InIter last, UnaryPred pred){
    for(;first != last; ++first){
        if(!pred(*first)){
            return false;
        }
    }
    return true;
}


int main(){
    std::vector<int> vi_neg = {-2,-3,-3,-5,-2};
    std::vector<int> vi_nneg = {-2,4,-1};
    if(all_of(vi_neg.cbegin(),vi_neg.cend(),negativo))
        std::cout << "tutti negativi" << std::endl;
    if(all_of(vi_nneg.cbegin(),vi_nneg.cend(),negativo))
        std::cout << "tutti negativi" << std::endl;
}

