#include <iostream>

int main(){
    std::cout << sizeof(signed char) << std::endl;
    std::cout << sizeof(unsigned char) << std::endl;
    std::cout << sizeof(char) << std::endl;

    char c = 0;
    for(int i = 0; i < 256; ++i){
        std::cout << static_cast<int>(c) << c << std::endl;
        ++c;
    }
    signed char c1 = 0;
    for(int i = 0; i < 256; ++i){
        std::cout << static_cast<int>(c1) << c1 << std::endl;
        ++c1;
    }
    unsigned char c2 = 0;
    for(int i = 0; i < 256; ++i){
        std::cout << static_cast<int>(c2) << c2 << std::endl;
        ++c2;
    }
}