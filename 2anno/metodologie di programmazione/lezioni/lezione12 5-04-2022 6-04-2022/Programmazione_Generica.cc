#include <iostream>
#include <vector>

bool e_pari(int pari);

template <typename Iter, typename UnaryPred>
auto
count_if(Iter first, Iter last, UnaryPred pred){
    unsigned long num = 0;

    for(; first != last; ++first){
        if(!pred(*first))
            ++num;
    }

    return num;
}

template < typename Iter, typename T>
Iter
find(Iter first, Iter last, const T& elem){
    for(; first != last; ++first){
        if(*first == elem)
            return first;
    }
    return last;
}

bool e_pari(int pari){
    return pari % 2;
}

int main(){

    std::vector<int> v;
    for(int i = 0; i < 100; ++i){
        v.push_back(i);
    }

    unsigned long l = count_if(v.begin(),v.end(),e_pari);
    std::cout << "numeri pari: " << l << std::endl;

    auto a = find(v.begin(), v.end(),6);
    if(a != v.end())
}