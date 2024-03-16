#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[])
{
    int A[744];
    ifstream data_input;
    int x;
    char comma;
    data_input.open("data.txt");
    for(int i = 0;i <= 743;++i){
        data_input >> x;
        data_input >> comma;
        cout << x << "   ";
    }
    return 0;
}
