#include <iostream>
#include <vector>

using Random_Access_Iterator = std::vector<int>::iterator;

int main(){
std::vector<int> vec = {1,2,3,4,5,6,7,8,9,10};

Random_Access_Iterator i1 = vec.begin();
Random_Access_Iterator i2 = i1 + 4;
std::cout << i1 - i2 << std::endl;

std::cout << i1[4] << " uguale a " << *i2 << std::endl;
for(auto i = vec.begin();i != vec.end();i+=2)
{
    *i += 20;
}

for(auto i = vec.begin();i!=vec.end();++i){
    std::cout << *i << std::endl;
}

}