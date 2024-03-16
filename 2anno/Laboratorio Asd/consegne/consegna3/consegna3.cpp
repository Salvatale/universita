#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

// compilazione: g++ lezione4-6-quicksort.c
//
// Obiettivo:

// prove con array ordinato crescente, decrescente --> numero di confronti?
// ./a.out 1024 -d=16

// prove con array random --> numero di confronti?
// ./a.out 1024 -d=16 -t=100



int ct_swap = 0;
int ct_cmp = 0;
int ct_read_heapsort = 0;
int ct_read_quick_sort = 0;

int max_dim = 0;
int ntests = 1;
int ndiv = 1;
int details = 0;
int graph = 0;

int n = 0; /// dimensione dell'array
int heap_size = 0;

void print_array(int *A, int dim) {
    for (int j = 0; j < dim; j++) {
        cout << A[j] << " ";
    }
    cout << "\n";
}

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

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
    /// aggiorno contatore globale di swap
    ct_swap++;
}

int partition(int *A, int p, int r) {

    /// copia valori delle due meta p..q e q+1..r
    ct_read_quick_sort++;
    int x = A[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        ct_cmp++;
        ct_read_quick_sort++;
        if (A[j] <= x) {
            i++;
            ct_read_quick_sort++;
            ct_read_quick_sort++;
            swap(A[i], A[j]);
        }
    }
    ct_read_quick_sort++;
    ct_read_quick_sort++;
    swap(A[i + 1], A[r]);

    return i + 1;
}

void quick_sort(int *A, int p, int r) {
    /// gli array L e R sono utilizzati come appoggio per copiare i valori: evita le allocazioni nella fase di merge
    if (p < r) {
        int q = partition(A, p, r);
        quick_sort(A, p, q - 1);
        quick_sort(A, q + 1, r);
    }
}

int parse_cmd(int argc, char **argv) {
    /// controllo argomenti
    if (argc < 2) {
        cout << "Usage: " << argv[0] << "%s max-dim [Options]\n";
        cout << "   max-dim: specifica la massima dimensione n del problema\n";
        cout << "Options:\n";
        cout << "  -d=<int>: Specifica quali dimensioni n del problema vengono lanciate in sequenza [default: 1] \n";
        cout << "            n = k * max-dim / d, k=1 .. d\n";
        cout << "  -t=<int>: Specifica quanti volte viene lanciato l'algoritmo per una specifica dimensione n [default: 1]\n";
        cout << "            Utile nel caso in cui l'input viene inizializzato in modo random\n";
        cout << "  -verbose: Abilita stampe durante l'esecuzione dell'algoritmo\n";
        cout << "  -graph: creazione file di dot con il grafo dell'esecuzione (forza d=1 t=1)\n";
        return 1;
    }

    /// parsing argomento
    max_dim = atoi(argv[1]);

    for (int i = 2; i < argc; i++) {
        if (argv[i][1] == 'd')
            ndiv = atoi(argv[i] + 3);
        if (argv[i][1] == 't')
            ntests = atoi(argv[i] + 3);
        if (argv[i][1] == 'v')
            details = 1;
        if (argv[i][1] == 'g') {
            graph = 1;
            ndiv = 1;
            ntests = 1;
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    int i, test;
    int *A;
    int* heap;
    int *B; /// buffer per visualizzazione algoritmo

    if (parse_cmd(argc, argv))
        return 1;

    /// allocazione array
    A = new int[max_dim];
    heap = new int[max_dim];

    ntests = 1000;
    ndiv = 10;

    // init random
    srand((unsigned)time(NULL));

    if (ndiv > 1)
        cout << "Dim_array,avg_read_q,read_avg_h\n";

    // printf("Parametri: max-dim %d, d %d, t %d, verbose %d\n",max_dim,ndiv,ntests,details);

    //// inizio ciclo per calcolare ndiv dimensioni di array crescenti
    for (n = max_dim / ndiv; n <= max_dim; n += max_dim / ndiv) {

        int read_min_quicksort = -1;
        int read_max_quicksort = -1;
        long read_avg_quicksort = 0;

        int read_min_heapsort = -1;
        int read_max_heapsort = -1;
        long read_avg_heapsort = 0;

        //// lancio ntests volte per coprire diversi casi di input random
        for (test = 0; test < ntests; test++) {

            /// inizializzazione array: numeri random con range dimensione array
            for (i = 0; i < n; i++) {
                // A[i] = i;
                // A[i] = n - i;
                int random = rand() % (n * 50);

                A[i] = random;
                heap[i] = random;
            }

            if (details) {
                cout << "creato array di dimensione " << n << "\n";
                print_array(A, n);
            }

            ct_read_quick_sort = 0;
            ct_read_heapsort = 0;

            
            /// algoritmo di sorting
            quick_sort(A, 0, n - 1);
            Heapsort(heap, n);

            if (details) {
                cout << "Output:\n";
                print_array(A, n);
            }

            /// statistiche
            read_avg_quicksort += ct_read_quick_sort;
            if (read_min_quicksort < 0 || read_min_quicksort > ct_read_quick_sort)
                read_min_quicksort = ct_read_quick_sort;
            if (read_max_quicksort < 0 || read_max_quicksort < ct_read_quick_sort)
                read_max_quicksort = ct_read_quick_sort;
            
            read_avg_heapsort += ct_read_heapsort;
            if (read_min_heapsort < 0 || read_min_heapsort > ct_read_heapsort)
                read_min_heapsort = ct_read_heapsort;
            if (read_max_heapsort < 0 || read_max_heapsort < ct_read_heapsort)
                read_max_heapsort = ct_read_heapsort;
        }

        //if (ndiv > 1){
            cout << n << "," << (0.0 + read_avg_quicksort) / ntests << "," << (0.0 + read_avg_heapsort) / ntests << "\n";
        //}

    }

    delete[] A;
    delete[] heap;

    return 0;
}
