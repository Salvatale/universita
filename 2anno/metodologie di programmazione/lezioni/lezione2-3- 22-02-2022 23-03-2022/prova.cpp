#include <iostream>

int pippo(double)
{
    int d = 'e';
    char c = pippo(d);
    if(c == 'e')return 1;
    else return 0;
}
short int pippo(char d)
{
    return d;
}


int main(int argc, char const *argv[])
{
    int a;
    a = pippo(1.2);
    if(a == 1)std:: cout << "fatto" << std:: endl;
    else std:: cout << "fallito" << std:: endl;
    return 0;
}
