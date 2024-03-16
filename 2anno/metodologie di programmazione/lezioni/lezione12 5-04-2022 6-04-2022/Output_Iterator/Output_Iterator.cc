#include <iostream>
#include <cstring>
#include <iterator>

using Output_Iterator = std::ostream_iterator<std::string>;
using Input_Iterator = std::istream_iterator<std::string>;


int main(){

    Input_Iterator input(std::cin);
    Input_Iterator fine_input;

    
    Output_Iterator iter(std::cout,"\n");
    for(;input!=fine_input;++input){
        *iter = *input;
        ++iter; 
    }


    

}