#include <iostream>


using namespace std;

const int max_size = 256;
int heap[max_size];
int heap_size = 0;

int Heap_Extract_Min();
void Min_Heap_Insert(int key);
int parent_idx(int n);
int child_L_idx(int n);
int child_R_idx(int n);
void Min_Heapify(int i);

int parent_idx(int n){
  if (n==0)
    return -1;
  return (n-1)/2;
}
int child_L_idx(int n){
  if (2*n+1>=heap_size)
    return -1;
  return 2*n+1;
}
int child_R_idx(int n){
  if (2*n+2>=heap_size)
    return -1;
  return 2*n+2;
}

int Heap_Extract_Min() {
    if(heap_size < 1) {
        std::cout << "Underflow dell'heap" << std::endl;
        return -1;
    }
    int min = heap[0];
    heap[0] = heap[heap_size-1];
    cout << "heap[0]=" << heap[0] << endl;
    --heap_size;
    cout << "min after Min_Heapify:" << min << endl;
    Min_Heapify(0);
    return min;
}

void Min_Heap_Insert(int key) {
    //cout << "key: " << key << endl;
    if(heap_size < 1){
        heap[heap_size] = key;
        //cout << "entrato primo elemento" << endl;
        ++heap_size;
        return;
    }
    int i = heap_size;
    heap[i] = key;
    ++heap_size;

    while(i >= 0 && heap[parent_idx(i)] > heap[i]){
        int t = heap[i];
        heap[i] = heap[parent_idx(i)];
        heap[parent_idx(i)] = t;

        i = parent_idx(i);
    }
}

void Min_Heapify(int i) {
    int l = child_L_idx(i);
    int r = child_R_idx(i);
    int min;
    if(l >=0 && l < heap_size && heap[l] < heap[i])
        min= l;
    else
        min = i;
    if(r>=0 && r < heap_size && heap[r] < heap[min])
        min = r;
    if(min != i) {
        int t = heap[i];
        heap[i] = heap[min];
        heap[min] = t;
        Min_Heapify(min);
    }
}

int main(){

    for(int i = 0;i < 10;++i){
        Min_Heap_Insert(i);
    }
    for(int i = 0;i < heap_size;++i){
        cout << heap[i];
    }
    cout << endl;
    for(int i=0;i<10;++i){
        int m = Heap_Extract_Min();
        cout << "m:" << m << endl;
    }
    return 0;
}