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

int ct_read=0;
int max_dim=0;
int ntests=107;
int ndiv=1;
int details=0;
int range_cs = 359; //risultato migliore ottenuto dai test

int n=0; /// dimensione dell'array

void swap(int &a, int &b){
  int tmp = a;
  a = b;
  b = tmp;
  /// aggiorno contatore globale di swap
}

void print_array(int* A, int dim){
    for (int j=0; j<dim; j++) {
      printf("%d ",A[j]);
    }
    printf("\n");
}

//Algoritmi utilizzati per il riordinamento

void insertion_sort(int* A, int n) {
  int i,j;
  for (i=0; i<n; i++) {
    for (j=i-1; j>=0; j--) {
      int aj = A[j];
      int aj1 = A[j+1];
      ct_read++;
      ct_read++;
      if (aj>aj1) {
        A[j] = aj1;
        A[j+1] = aj;
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
  }

  for (int j=0;j<n;j++){ /// conteggio istogramma
    int a = A[j];
    ct_read++;
    C[a]++;
  }

  for (int i=1;i<=k;i++){ /// C[i] contiene il numero di elementi <= i
    C[i]+=C[i-1];
    ct_read++;
    ct_read++;
  }
  
  for (int j=n-1;j>=0;j--){ /// per ogni elemento originale in A ->
                            /// mi chiedo nel conteggio C quanti sono gli elementi minori o uguali:
                            /// questo corrisponde alla posizione dell'elemento in B
    
    int a = A[j];
    ct_read++;
    int c = C[a];
    ct_read++;
    B[c-1+offset]=a;
    C[a]=c-1;
  }
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
      ndiv=1;
      ntests=1;
    }
  }

  return 0;
}

int main(int argc, char **argv)
{
    int i,test;
    int* data_array; //array dei dati ordinati
    int* cs_array;   //array dei dati da ordinare con counting sort

    if (parse_cmd(argc,argv))
        return 1;

    n=max_dim;
  
    /// allocazione array
    data_array = new int[max_dim];
    cs_array = new int[max_dim];

    ifstream input_data;
    input_data.open("data.txt");
    
    int read_min=-1;
    int read_max=-1;
    long read_avg=0;
    
    for(test=0;test<ntests;test++){
        int ncs=0;   //elementi da ordinare con counting sort
        int nqs=max_dim-1;   //elementi da ordinare con quick sort
        int nneg = 0;   //numero di elementi negativi
        int max_elem_cs = 0; //elemento massimo counting sort

        for(i=0; i<n; i++){
            char comma;
            int data;
            input_data >> data;
            input_data >> comma;

            //controllo dei valori dei dati
            if(data >= 0 && data <= range_cs){
                cs_array[ncs] = data;
                ++ncs;
                if(data > max_elem_cs)
                    max_elem_cs = data;
            }
            else{
                if(data < 0){
                    data_array[nneg] = data;
                    ++nneg;
                }
                else{
                    data_array[nqs] = data;
                    --nqs;
                }
            }
        }
        //stampa array partizionato
        if(details){
            printf("caricato array di dimensione %d\n",n);
            for(int i = 0;i < nneg;++i){
              cout << data_array[i] << ",";
            }
            for(int i = 0;i < ncs;++i){
              cout << cs_array[i] << ",";
            }
            for(int i = nqs+1;i < max_dim;++i){
              cout << data_array[i] << ",";
            }  
            cout << endl;  
        }
        
        ct_read=0;
        //algoritmo di sorting
        counting_sort(cs_array,data_array,ncs,max_elem_cs,nneg);
        quick_sort(data_array,nqs+1,max_dim-1);
        insertion_sort(data_array,nneg);
        //stampa array ordinato
        if(details){
            printf("Output:\n");
            print_array(data_array,n);
        }
        //statistiche
        read_avg+=ct_read;
        if (read_min<0 || read_min>ct_read) read_min=ct_read;
        if (read_max<0 || read_max<ct_read) read_max=ct_read;
        printf("Test %d %d\n",test,ct_read);
    }
        

        printf("%d,%d,%.1f,%d\n",
	       ntests,
	       read_min ,(0.0+read_avg)/ntests ,read_max);
        
        //input_data.close();
        delete[] data_array;
        delete[] cs_array;
        return 0;


}






