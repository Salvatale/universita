#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

typedef std::vector<std::string> vect;
typedef std::vector<std::string>::iterator iter;

void f(const vect& v) {
    auto i = std::find(v.begin(), v.end(), "inizio");
    auto i_end = std::find(v.begin(), v.end(), "fine");
    while (i != i_end) {
        std::cout << *i << std::endl;
        ++i;
    }
}
void g(vect& v) {
    iter i = v.begin(), i_end = v.end();
    if (i!=i_end){
        *i = "prima";
        std::cout << *i << std::endl;
        ++i;
    }
    if (i!=i_end){
        *i = "dopo";
        std::cout << *i << std::endl;
        ++i;
    }
}

int main(){
    std::vector<std::string> vs = {"inizio","ada","dsdsdr","fine"};
    f(vs);
    std::vector<std::string> va = {"asda","adass"};
    g(va);
}