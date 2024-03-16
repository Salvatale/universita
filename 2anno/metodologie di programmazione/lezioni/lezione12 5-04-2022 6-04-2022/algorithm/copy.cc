#include <iostream>
#include <iterator>
#include <forward_list>
#include <vector>


namespace s{

template <typename InputIterator, typename OutputIterator>
OutputIterator
copy(InputIterator first,InputIterator last, OutputIterator out){
    for(; first != last; ++first,++out){
        *out = *first;
    }
    return out;
}
}

int main(){
    
    std::vector<int> vec = {1,2,3,4,5,6,7};
    std::ostream_iterator<int> a(std::cout,"\n");
    a = s::copy(vec.cbegin(),vec.cend(),a);

}