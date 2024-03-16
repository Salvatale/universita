#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

// compilazione: g++ -xc++ consegna1-loader.c 
//

// Il programma carica il file data.txt contenente 107 righe con i dati di contagi covid per provincia
// ./a.out
// In output viene mostrato il numero di accessi in read alla memoria per eseguire il sorting di ciascuna riga

// Obiettivo:
// Creare un algoritmo di sorting che minimizzi la somma del numero di accessi per ogni sorting di ciascuna riga del file

int ct_swap=0;
int ct_cmp=0;
int ct_read=0;

int max_dim=0;
int ntests=107;
int ndiv=1;
int details=0;
int graph=0;
int counting_sort_max_range = 100;
int letture = 100000;
int best_range;

int n=0; /// dimensione dell'array

void print_array(int* A, int dim){
    for (int j=0; j<dim; j++) {
      printf("%d ",A[j]);
    }
    printf("\n");
}


void swap(int &a, int &b){
  int tmp = a;
  a = b;
  b = tmp;
  /// aggiorno contatore globale di swap 
  ct_swap++;
}

void insertion_sort(int* A, int n) {
  int i,j;
  for (i=0; i<n; i++) {
    ct_cmp++;
    for (j=i-1; j>=0; j--) {
      ct_cmp++;
      int aj = A[j];
      int aj1 = A[j+1];
      ct_read++;
      ct_read++;
      if (aj>aj1) {
        ct_cmp++;
        A[j] = aj1;
        A[j+1] = aj;
        ct_swap++;
      } else {
	      break;
      }
    }    
  }
}

void counting_sort(int* A, int* B, int n, int k,int offset) {
  /// A: array in input 0..n-1
  /// B: array in output 0..n-1
  /// C: array per conteggi 0..k
  /// n: elementi da ordinare
  /// k: valore massimo contenuto in A

  int C[k+1];

  for (int i=0;i<=k;i++){ /// reset array conteggi
    C[i]=0;
    ct_cmp++;
  }

  for (int j=0;j<n;j++){ /// conteggio istogramma
    ct_cmp++;
    int a = A[j];
    ct_read++;
    C[a]++;
  }

  for (int i=1;i<=k;i++){ /// C[i] contiene il numero di elementi <= i
    ct_cmp++;
    C[i]+=C[i-1];
    ct_read++;
    ct_read++;
  }
  
  for (int j=n-1;j>=0;j--){ /// per ogni elemento originale in A ->
                            /// mi chiedo nel conteggio C quanti sono gli elementi minori o uguali:
                            /// questo corrisponde alla posizione dell'elemento in B
    ct_cmp++;
    
    int a = A[j];
    ct_read++;
    int c = C[a];
    ct_read++;
    B[c-1+offset]=a;
    C[a]=c-1;
  }
  /*for(int i = 0;i < max_dim-1;++i){
      cout << B[i] << ",";
    }
  */

}

int partition(int* A, int p, int r){

  /// copia valori delle due meta p..q e q+1..r
  ct_read++;
  int x=A[r];
  int i=p-1;
  
  for (int j=p;j<r;j++){
    ct_read++;
    int aj = A[j];
    if (aj<=x){
      i++;
      int ai = A[i];
      ct_read++;
      A[i] = aj;
      A[j] = ai;
    }    
  }
  ct_read++;
  ct_read++;
  swap(A[i+1],A[r]);

  return i+1;
}


void quick_sort(int* A, int p, int r) {
  /// gli array L e R sono utilizzati come appoggio per copiare i valori: evita le allocazioni nella fase di merge
  if (p<r) {
    ct_cmp++;
    int q= partition(A,p,r);
    quick_sort(A,p,q-1);
    quick_sort(A,q+1,r);
  }
}

int parse_cmd(int argc, char **argv){

  /// parsing argomento
  max_dim = 743;

  for (int i=1;i<argc;i++){
    if (argv[i][1]=='d')
      ndiv = atoi(argv[i]+3);
    if (argv[i][1]=='t')
      ntests = atoi(argv[i]+3);
    if (argv[i][1]=='v')
      details=1;    
    if (argv[i][1]=='g'){
      graph=1;
      ndiv=1;
      ntests=1;
    }
  }

  return 0;
}

void insertionSortRecursive(int* A, int n)
{
    // Base case
    if (n <= 1)
        return;
 
    // Sort first n-1 elements
    insertionSortRecursive( A , n-1 );
 
    // Insert last element at its correct position
    // in sorted array.
    int last = A[n-1];
    ct_read++;
    int j = n-2;
    ct_read++;
    int aj = A[j];
    while (j >= 0 && aj > last)
    {
        A[j+1] = aj;
        j--;
    }
    A[j+1] = last;
}

int main(int argc, char **argv) {
  int i,test;
  int* A;
  int* B;  /// buffer per visualizzazione algoritmo
  int* C;


  if (parse_cmd(argc,argv))
    return 1;

  n=max_dim;
  
  /// allocazione array
  A = new int[max_dim];
  B = new int[max_dim];
  C = new int[max_dim];
  
  

  //// lancio ntests volte per coprire diversi casi di input random
  for(counting_sort_max_range = 100; counting_sort_max_range < 1200;++counting_sort_max_range){
    ifstream input_data;
    input_data.open("data.txt");
    int read_min=-1;
    int read_max=-1;
    long read_avg=0;
    for (test=0;test<ntests;test++){
      int left_A = 0;   //conteggio elementi che verranno riordinati con counting sort
      int right_A = max_dim-1;  //conteggio elementi riordinati con quick sort
      int max_elem_counting_sort = 0;
      int offset = 0;
    /// inizializzazione array: numeri random con range dimensione array
      for (i=0; i<n; i++) {
	      char comma;
        int data;
	      input_data >> data;
        input_data >> comma;
        //cout << data;
        //cout << comma;
        if(data >= 0 && data <= counting_sort_max_range){
          //cout << "p" ;
          B[left_A] = data;
          ++left_A;
          if(data > max_elem_counting_sort)
            max_elem_counting_sort = data;
        }
        else{
          if (data < 0){
            //cout << "s";
            A[offset] = data;
            offset++;
          }
          else{
            //cout << "t";
            A[right_A] = data;
           --right_A;
          }
        }
      }

      /*if (details){
	      printf("caricato array di dimensione %d\n",n);
	      print_array(A,n);
      }*/
      /*printf("caricato array di dimensione %d\n",n);
      for(int i = 0;i < offset;++i){
        cout << A[i] << ",";
      }
      for(int i = offset;i < left_A;++i){
        cout << B[i] << ",";
      }
      for(int i = right_A+1;i < max_dim;++i){
        cout << A[i] << ",";
      }
      */
      ct_swap=0;
      ct_cmp=0;
      ct_read=0;

      //cout << "right: " << right_A +1 << endl;
      //cout << "left: " << left_A + offset << endl;
      /// algoritmo di sorting
      counting_sort(B,A,left_A,max_elem_counting_sort,offset);
      quick_sort(A,right_A+1,max_dim-1);
      //insertion_sort(A,offset);
      insertionSortRecursive(A,offset-1);


      if (details){
	      printf("Output:\n");
	      print_array(A,n);
      }
        /// statistiche
        read_avg+=ct_read;
        if (read_min<0 || read_min>ct_read) read_min=ct_read;
        if (read_max<0 || read_max<ct_read) read_max=ct_read;
        cout << "range: " << counting_sort_max_range << endl;
        printf("Test %d %d\n",test,ct_read);
    }
        printf("%d,%d,%.1f,%d\n",
	       ntests,
	       read_min ,(0.0+read_avg)/ntests ,read_max);
         int letture_med = (0.0+read_avg)/ntests;
         cout << letture_med << endl;
         if(letture_med < letture){
          letture = letture_med;
          best_range = counting_sort_max_range;
        }
        input_data.close();
  }

  delete [] A;
  delete [] B;
  delete [] C;
  cout << "best range: " << best_range << endl;
  cout << "letture: " << letture << endl;
  return 0;
}
