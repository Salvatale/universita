#include <iostream>
#include <vector>
#include <iterator>

template <typename T,typename U>
bool uguale(T t,U u){
    return u == t;
}

template <typename Iter1,typename Iter2,typename BinaryPred>
Iter1
find_first_of1(Iter1 first1,Iter1 last1,Iter2 first2,Iter2 last2,BinaryPred cmp){
    for(;first1 != last1;++first1){
        for(;first2 != last2;++first2){
            if(cmp(*first1,*first2))
                return first1;
        }
    }
    return last1;
}


int main(){
    std::vector<char> vs = {'a','b'};
    std::vector<int> vi = {1,2,3,4,5};
    vi.push_back('b');
    vi.push_back('a');
    auto iter = find_first_of1(vs.begin(),vs.end(),vi.begin(),vi.end(),uguale<char,int>);
    if( iter == vs.end())
        std::cout << "niente" << std::endl;
    else
        std::cout << *iter << std::endl;
}
