#include <iostream>
#include <iterator>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <array>

template <typename Container>
double average(const Container& c){
    double media = 0;
    unsigned int counter = 0;
    for(auto a = c.begin();a != c.end();++a){
        media += *a;
        ++counter;
    }
    return media/counter;
}

template<typename Iter>
double average(Iter first,Iter last){
    double media = 0;
    unsigned int counter = 0;;
    for(;first != last;++first){
        media += *first;
        ++counter;
    }
    return media/counter;
}


int main(){
    std::vector<int> v = {1,2,7,4,2,8,4,2,6,8,33};
    std::forward_list<int> fl = {1,2,7,4,2,8,4,2,6,8,33};
    std::list<int> l = {1,2,7,4,2,8,4,2,6,8,33};
    std::deque<int> d = {1,2,7,4,2,8,4,2,6,8,33};
    std::array<int,11> a = {1,2,7,4,2,8,4,2,6,8,33};
    std::cout << average(v) << std::endl;
    std::cout << average(v.begin(),v.end()) << std::endl;
    std::cout << average(fl) << std::endl;
    std::cout << average(fl.begin(),fl.end()) << std::endl;
    std::cout << average(l) << std::endl;
    std::cout << average(l.begin(),l.end()) << std::endl;
    std::cout << average(d) << std::endl;
    std::cout << average(d.begin(),d.end()) << std::endl;
    std::cout << average(a) << std::endl;
    std::cout << average(a.begin(),a.end()) << std::endl;
    

}