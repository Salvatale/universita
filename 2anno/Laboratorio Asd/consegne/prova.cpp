
#include <iostream>
#include <vector>
#include <cmath>

int ct_read = 0;


void pigeon_hole_sort(int *A, int first, int last){

    int min = 10000000;
    int max = -1;

    for(int i = first; i < last; i++){

        int value = A[i];
        ct_read++;

        if(value < min)
            min = value;

        if(value > max)
            max = value;

    }

    int range = max - min + 1;

    std::vector<int> *holes;

    holes = new std::vector<int>[range];

    for(int i = first; i < last; ++i){

        int value = A[i];
        ct_read++;

        holes[value - min].push_back(value);

    }

    int index = 0;

    

    for(int i = 0; i < range; ++i){

        std::vector<int>::iterator it;

        it = holes[i].begin();
        ct_read++;

        std::vector<int>::iterator end;

        end = holes[i].end();
        ct_read++;

        while(it != end){

            A[first] = *it;
            ct_read++;

            ++it;
            first++;


        }    

    }

}

void bucketSort(int *A,int max, int first, int last)
{

    const int N = 1000;

    std::vector<int> *vector = new std::vector<int>[N+1];

    for(int i = first; i < last; i++){

        ct_read++;
        int value = A[i];

        int index = floor(((value * N)/max));

        //std::cout << "index: " << index << " with value: " << value;

        ct_read++;
        int size = vector[index].size();

        //std::cout << " with size: " << size << std::endl;

        vector[index].push_back(value);

        for(int i = size; i > 0; i--){

            ct_read++;
            int next_value = vector[index][i-1];

            if(value < next_value){
                vector[index][i] = next_value;
                vector[index][i-1] = value;
            }
            else{
                break;

            }

        }

        //sizes[index] = size + 1;

    }

    for(int i = 0; i < N+1; i++){
        int size = vector[i].size();
        ct_read++;

        for(int j = 0; j < size; j++){
            ct_read++;
            A[first] = vector[i][j];

            //std::cout << "first: " << first << " with " << A[first] << std::endl;
            first++;
        }

    }
    
    delete[] vector;
}

bool is_sorted(int *A, int first, int last){
    for(int i = first; i < last; i++){
        if(i < last - 1){
            if(A[i] > A[i + 1]){
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char const *argv[])
{

    srand((unsigned) time(NULL));

    const int N = 1000;
    
    int *A = new int[N];

    int max = 0;

    for(int i = 0; i < N; i++){

        int value = rand()%1000;

        A[i] = value;

        if(max < value)
            max = value;

    }

    //pigeon_hole_sort(A,0,100);
    std::cout << max << std::endl;

    bucketSort(A,max,0,N);

    
    std::cout << "[";

    for(int i = 0; i < N; i++){

        std::cout << A[i] << " ";

    }

    std::cout << "]" << std::endl;
    

    if(is_sorted(A,0,N))
        std::cout << "Sorted" << std::endl;


    delete[] A;

    std::cout << ct_read << std::endl;

    return 0;

    
}
