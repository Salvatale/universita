
#include <iostream>
#include <vector>
#include <iterator>


bool pari(int p){
    return p%2 != 0;
}

template <typename InIter, typename OutIter, typename UnaryPred>
OutIter
remove_copy_if(InIter first,InIter last,OutIter out,UnaryPred pred){
    for(; first!= last; ++first){
        if (!pred(*first))
            *out = *first;
    }
    return out;
}

template <typename RanIter, typename UnaryPred>
RanIter
remove_if(RanIter first,RanIter last,UnaryPred pred){
    while(first != last){
        if(!pred(*first)){
            auto i = first;
            --last;
            for(; i != last;++i){
                *i = *(i+1);
            }
        }
        else
            ++first;
    }
    return last;
}
template <typename InIter, typename OutIter>
void
copy1(InIter first,InIter last,OutIter out){
    for(; first!= last; ++first){
        *out = *first;
    }
}


int main(){
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    std::ostream_iterator<int> out_iter(std::cout,"\n");
    //out_iter = remove_copy_if(v.cbegin(),v.cend(),out_iter,pari);
    std::vector<int>::iterator i_end = remove_if(v.begin(),v.end(),pari);
    v.resize(v.end()-i_end);
    copy1(v.begin(),v.end(),out_iter);
}
