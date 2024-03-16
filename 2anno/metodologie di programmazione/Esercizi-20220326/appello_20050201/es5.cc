#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iterator>

bool inizia_con_c(std::string s){
    return !s.empty() && s[0] == 'c';
}

struct inizia_c{
public:
    char c_;
    inizia_c(char c) : c_(c){}
    bool operator()(std::string s){
        return !s.empty() && s[0] == c_;
    }
};


void f(const std::vector<std::string>& vs, const char c){
    std::vector<std::string> temp;
    temp.resize(vs.size());
    

    copy_if(vs.begin(),vs.end(),std::back_inserter(temp),inizia_c(c));

    sort(temp.begin(),temp.end());

    std::ostream_iterator<std::string> out(std::cout,"\n");
    std::cout << "-------elenco ordinato-------------" << std::endl;
    copy(temp.cbegin(),temp.cend(),out);
    std::cout << "-------elenco decrescente----------" << std::endl;
    copy(temp.crbegin(),temp.crend(),out);

    
}


int main(){

    std::vector<std::string> vs = {"cicogna","ciuccio","cane"};
    f(vs,'c');
}