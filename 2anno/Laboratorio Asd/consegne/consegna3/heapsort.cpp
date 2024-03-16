#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

int heap_size = 0;
const int N = 100;

void print_array(int* A, int n);

int parent_idx(int n){
  if (n==0)
    return 100000;
  return (n-1)/2;
}

int child_L_idx(int n){
  if (2*n+1>=heap_size)
    return 10000;
  return 2*n+1;
}

int child_R_idx(int n){
  if (2*n+2>=heap_size)
    return 1000000;
  return 2*n+2;
}

int ct_read_heapsort;

void Max_Heapify(int* heap, int i) {
  int l = child_L_idx(i);   //prendo indice figlio sinistro di i
  int r = child_R_idx(i);   //prendo indice figlio destro di i
  int max;

  //cout << "Indice i = " << i << "con left: " << l << " e right: " << r << endl;

  //confronto se l'indice è positivo e minore della dimensione di heap
  // dopo confronto se il figlio sinistro è minore del padre
  // se si allora il mio indice diventa = l
  // se no = i
  if(l < heap_size)
    ct_read_heapsort += 2;
  if((l < heap_size) && (heap[l] > heap[i]))
    max= l;
  else
    max = i;

    //cout << "max: " << max << endl;

  //faccio i soliti confronti e controllo se il figlio sinistro
  //è più piccolo del  valore in posizione min 
  if(r < heap_size)
    ct_read_heapsort += 2; 
  if((r < heap_size) && (heap[r] > heap[max]))
      max = r;
    //cout << "max: " << max << endl;
  
  if(max != i) {
    ct_read_heapsort++;
    int t = heap[i];
    ct_read_heapsort++;
    heap[i] = heap[max];
    heap[max] = t;
    //ripeto ricorsivamento sull'indice min per gestire le relazioni
    Max_Heapify(heap, max);
  }
}

void Build_Max_Heap(int* heap, int n){

    heap_size = n;

    for(int i = (n/2); i >= 0; --i){
        Max_Heapify(heap,i);
    }

}

void Heapsort(int* heap, int n){

    Build_Max_Heap(heap,n);

    for(int i = n-1; i > 0; --i){

        ct_read_heapsort += 2;
        int temp = heap[0];
        heap[0] = heap[i];
        heap[i] = temp;

        heap_size--;

        Max_Heapify(heap,0);

    }

}

void print_array(int* A, int n){

    cout << "[";

    for(int i = 0; i < n; i++){

        cout << A[i];

        if(i < n -1)
            cout << ",";

    }

    cout << "]" << endl;

}

bool is_sorted(int* A, int n){

    for(int i = 0; i < n; i++){

        if(i < n-1){
            if(A[i] > A[i + 1])
                return false;
        }

    }

    return true;

}



int main(){

    int* heap;

    srand((unsigned)time(NULL));

    heap = new int[N];

    cout << "Array non ordinato:" << endl;

    for(int i = 0; i < N; i++){
        heap[i] = rand()%100;

    }

    print_array(heap, N);

    Heapsort(heap,N);

    cout << "Array ordinato:" << endl;

    print_array(heap,N);

    if(is_sorted(heap,N))
        cout << "is sorted" << endl;
    else
        cout << "is not sorted " << endl;


}