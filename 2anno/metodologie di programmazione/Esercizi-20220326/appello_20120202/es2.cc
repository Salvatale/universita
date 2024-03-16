#include <iostream>
#include <iterator>
#include <cstring>

const unsigned int dim = 10;

bool lunghezza(std::string s){
    return s.length() > dim;
}


template <typename InIter, typename UnaryPred>
unsigned long
count_if(InIter first,InIter last,UnaryPred pred){
    unsigned long count = 0;
    for(; first != last;++first){
        if(pred(*first))
            ++count;
    }
    return count;
}

using istream_iter = std::istream_iterator<std::string>;

int main(){
    istream_iter i(std::cin);
    istream_iter i_end;
    std::ostream_iterator<unsigned long> out_iter(std::cout,"\n");

    *out_iter = count_if(i,i_end,lunghezza); 
}