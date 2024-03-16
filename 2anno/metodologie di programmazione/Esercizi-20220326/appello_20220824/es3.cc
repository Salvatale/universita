#include <iostream>
#include <vector>

struct Uguale{
    bool operator()(int a,int b){
        return a == b;
    }
};


template < typename FwIter1,typename FwIter2,typename BinaryPred>
bool
contains(FwIter1 first1,FwIter1 last1,FwIter2 first2,FwIter2 last2,BinaryPred cmp){
    FwIter1 iter;
    for(; first2 != last2;++first2){
        for(iter = first1;iter != last1;++iter){
            if(cmp(*first2,*iter))
                break;
        }
        if(iter == last1)
            return false;
    }
    return true;
}

int main(){
    std::vector<int> vi1 = {1,2,5,2,7,3,1,7};
    std::vector<int> vi2 = {1,10,5,3,7,5,1,7};
    if(contains(vi1.begin(),vi1.end(),vi2.begin(),vi2.end(),Uguale()))
        std::cout << "contiene ogni elemento" << std::endl;
}