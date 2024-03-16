#include <forward_list>
#include <iostream>

using Forward_Iterator = std::forward_list<int>::iterator;

int main() {
    std::forward_list<int> l = {1,2,3,4,5,6};
    Forward_Iterator i = l.begin();
    Forward_Iterator f = l.end();
    Forward_Iterator c;

    for(;i!=f;++i){
        std::cout << *i << std::endl;
        if(*i == 3)
            c = i;
    }
    std::cout << *c << std::endl;
}
