#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

// compilazione: g++ -xc++ lezione13-heap.c 
//
// Obiettivo:
// 1) analisi rappresentazione albero completo <---> array
// 2) implementazione inserimento su heap OK
// 3) estrazione massimo con funzione "heapify" (discesa del valore minimo dalla radice)

int Heap_Extract_Min();
void Min_Heap_Insert(int key);
void Min_Heapify(int i);

int ct_swap=0;
int ct_cmp=0;
int ct_op=0;  /// operazioni per la ricerca
int ct_read_heapsort = 0;
int ct_read_quick_sort = 0;


const int max_dim=1000;
const int ntests=1000;
int ndiv=100;
int details=0;
int graph=0;

int n=0; /// dimensione dell'array

/// file di output per grafo
ofstream output_graph;
int n_operazione=0; /// contatore di operazioni per visualizzare i vari step

const int MAX_SIZE=256;  /// allocazione statica
int heap[max_dim];
int heap_size=0;   /// dimensione attuale dell'heap

int A[max_dim];
/// uso -1 per indicare un indice non esistente

void print_array(int* A, int dim){
    for (int j=0; j<dim; j++) {
      printf("%d ",A[j]);
    }
    printf("\n");
}

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

/// stampa il codice del nodo per dot
void print_node_code(int n){
  output_graph << "node_" << n << "_" << n_operazione;
}

void node_print_graph(int n){
  if (details)
    printf("Stampo su grafo nodo %d\n",n);
  print_node_code(n);
  output_graph << "\n[label=<\n<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\" >\n<TR> <TD CELLPADDING=\"3\" BORDER=\"0\"  ALIGN=\"LEFT\" bgcolor=\"#f0f0f0\" PORT=\"id\">";
  output_graph << n << "</TD> </TR><TR>\n<TD PORT=\"val\" bgcolor=\"#a0FFa0\">";
  output_graph << heap[n] << "</TD>\n</TR></TABLE>>];\n";

  /// visualizzazione figli sullo stesso piano
  if (child_L_idx(n)!=-1 && child_R_idx(n)!=-1){
    output_graph << "rank = same; ";
    print_node_code(child_L_idx(n));
    output_graph <<";";
    print_node_code(child_R_idx(n));
    output_graph  <<";\n";
  }

  // mostro archi uscenti
  
  if (child_L_idx(n)!=-1){ /// disegno arco left
    print_node_code(n);
    output_graph  << ":s -> ";
    print_node_code(child_L_idx(n));
    output_graph  <<":id ;\n";
  }

  if (child_R_idx(n)!=-1){ /// disegno arco R
    print_node_code(n);
    output_graph << ":s -> ";
    print_node_code(child_R_idx(n));
    output_graph <<":id ;\n";
  }
  
}

void tree_print_rec_graph(int n){
  if (n!=-1){
    node_print_graph(n);
    tree_print_rec_graph(child_L_idx(n));
    tree_print_rec_graph(child_R_idx(n));
  }
}

void tree_print_graph(int n){
  /// stampa ricorsiva del nodo
  tree_print_rec_graph(n);
  n_operazione++;

}


void node_print(int n){
  if (n == -1)
    printf("nodo vuoto\n");  
  else
    printf("allocato in %d [Val: %d, L: %d, R: %d]\n",
	   n,
	   heap[n],
	   child_L_idx(n),
	   child_R_idx(n));  
}

void Min_Heapify(int i) {
  int l = child_L_idx(i);   //prendo indice figlio sinistro di i
  int r = child_R_idx(i);   //prendo indice figlio destro di i
  int min;

  //confronto se l'indice è positivo e minore della dimensione di heap
  // dopo confronto se il figlio sinistro è minore del padre
  // se si allora il mio indice diventa = l
  // se no = i
  ct_read_heapsort++;
  ct_read_heapsort++;
  if(l >=0 && l < heap_size && heap[l] < heap[i])
    min= l;
  else
    min = i;
  //faccio i soliti confronti e controllo se il figlio sinistro
  //è più piccolo del  valore in posizione min  
  if(r >=0 && r < heap_size && heap[r] < heap[min])
      min = r;
  if(min != i) {
    ct_read_heapsort++;
    int t = heap[i];
    ct_read_heapsort++;
    heap[i] = heap[min];
    heap[min] = t;
    //ripeto ricorsivamento sull'indice min per gestire le relazioni
    Min_Heapify(min);
  }
}

void Min_Heap_Insert(int key) {

  //inserisco primo elemento ed esco dalla funzione
  if(heap_size < 1){
    heap[heap_size] = key;
    ++heap_size;
    return;
  }
  //inserisco elemento nell'ultima posizione di heap ed incremento
  int i = heap_size;
  heap[i] = key;
  ++heap_size;

  int p = parent_idx(i);
  ct_read_heapsort++;
  ct_read_heapsort++;
  int heap_pa = heap[p];
  int heap_i = heap[i];

  //ciclo finchè non ho un'indice minore di 0 oppure il mio elemento
  // è maggiore del suo parent
  while(i >= 0 && heap_pa > heap_i){
    int t = heap_i;
    heap[i] = heap_pa;
    heap[parent_idx(i)] = t;

    i = parent_idx(i);
    p = parent_idx(i);
    ct_read_heapsort++;
    ct_read_heapsort++;
    heap_pa = heap[p];
    heap_i = heap[i];
  }
}

int Heap_Extract_Min() {
  //controllo se heap è vuoto per non andare in underflow
  if(heap_size < 1) {
      std::cout << "Underflow dell'heap" << std::endl;
      return -1;
  }

  //estraggo il primo elemento ed imposto nella prima cella l'ultimo
  //elemento dell'array e dopo aggiusto ricorsivamente con Min_Heapify
  ct_read_heapsort++;
  int min = heap[0];
  ct_read_heapsort++;
  heap[0] = heap[heap_size-1];
  --heap_size;
  Min_Heapify(0);
  return min;
}

void Heapsort() {
  if(heap_size == 0){
    cout << "array vuoto!!!" << endl;
    return;
  }
  int d = heap_size;
  for(int i = d; i > 0;--i){
    int min = Heap_Extract_Min();
    heap[heap_size] = min;
  }
  heap_size = d; 
}

int parse_cmd(int argc, char **argv){
  /// controllo argomenti
  int ok_parse=0;
  for (int i=1;i<argc;i++){
    if (argv[i][1]=='v'){
      details=1;
      ok_parse=1;
    }
    if (argv[i][1]=='g'){
      graph=1;
      ok_parse=1;
    }
  }

  if (argc > 1 && !ok_parse) {
    printf("Usage: %s [Options]\n",argv[0]);
    printf("Options:\n");
    printf("  -verbose: Abilita stampe durante l'esecuzione dell'algoritmo\n");
    printf("  -graph: creazione file di dot con il grafo dell'esecuzione (forza d=1 t=1)\n");
    return 1;
  }

  return 0;
}

void swap(int &a, int &b){
  int tmp = a;
  a = b;
  b = tmp;
}

int partition(int* A, int p, int r){

  /// copia valori delle due meta p..q e q+1..r
  ct_read_quick_sort++;
  int x=A[r];
  int i=p-1;
  
  for (int j=p;j<r;j++){
    ct_read_quick_sort++;
    if (A[j]<=x){
      i++;
      ct_read_quick_sort++;
      ct_read_quick_sort++;
      swap(A[i],A[j]);
    }    
  }
  ct_read_quick_sort++;
  ct_read_quick_sort++;
  swap(A[i+1],A[r]);

  return i+1;
}

void quick_sort(int* A, int p, int r) {
  /// gli array L e R sono utilizzati come appoggio per copiare i valori: evita le allocazioni nella fase di merge
  if (p<r) {
    int q= partition(A,p,r);
    quick_sort(A,p,q-1);
    quick_sort(A,q+1,r);
  }
}



int main(int argc, char **argv) {
  int i,test;

  if (parse_cmd(argc,argv))
    return 1;

  // init random
  srand((unsigned) time(NULL));

  if (graph){
    output_graph.open("graph.dot");
    /// preparo header
    output_graph << "digraph g"<<endl; 
    output_graph << "{ "<<endl;
    output_graph << "node [shape=none]"<<endl;
    output_graph << "rankdir=\"TB\""<<endl;;
    output_graph << "edge[tailclip=false,arrowtail=dot];"<<endl;    
  }

  for (n = 100;n<=max_dim;n+=100){
    int read_min_quicksort=-1;
    int read_max_quicksort=-1;
    long read_avg_quicksort=0;

    int read_min_heapsort=-1;
    int read_max_heapsort=-1;
    long read_avg_heapsort=0;

    for(test=0;test<ntests;test++){
      
      heap_size = 0;
      for(i=0; i<n;i++){
        int random = rand()%100 ;
        A[i] = random;
        Min_Heap_Insert(random);
      }

      if (details){
	      printf("creato array di dimensione %d\n",n);
	      print_array(A,n);
        tree_print_graph(0);
      }

      ct_read_heapsort = 0;
      ct_read_quick_sort = 0;

      quick_sort(A,0,n-1);
      Heapsort();

      if(details){
        printf("Output:\n");
        print_array(A,n);
        for(int i=heap_size-1;i>=0;i--){
          cout << heap[i] << " ";
        }
        cout << endl;
      }
      //statistiche
      read_avg_quicksort += ct_read_quick_sort; 
      if (read_min_quicksort<0 || read_min_quicksort>ct_read_quick_sort) read_min_quicksort=ct_read_quick_sort;
      if (read_max_quicksort<0 || read_max_quicksort<ct_read_quick_sort) read_max_quicksort=ct_read_quick_sort;
      read_avg_heapsort += ct_read_heapsort;
      if (read_min_heapsort<0 || read_min_heapsort>ct_read_heapsort) read_min_heapsort=ct_read_heapsort;
      if (read_max_heapsort<0 || read_max_heapsort<ct_read_heapsort) read_max_heapsort=ct_read_heapsort;

    }
    printf("%d,%d,%d,%.1f,%d,%d,%.1f,%d\n",
        n,ntests,read_min_quicksort,(0.0+read_avg_quicksort)/ntests,
        read_max_quicksort,read_min_heapsort,
        (0.0+read_avg_heapsort)/ntests,read_max_heapsort);

  }


  return 0;
}


