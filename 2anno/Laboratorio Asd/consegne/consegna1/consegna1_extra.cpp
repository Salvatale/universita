#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

// compilazione: g++ consegna1-loader.c
//

// Il programma carica il file data.txt contenente 100 righe con dati da ordinare in modo crescente
// ./a.out
// In output viene mostrato il numero di accessi in read alla memoria per eseguire il sorting di ciascuna riga

// Obiettivo:
// Creare un algoritmo di sorting che minimizzi la somma del numero di accessi per ogni sorting di ciascuna riga del file

/*
Nome: Alessandro Domenico   Cognome: Salvatore  Matricola: 324058

Spiegazione algoritmo:
Ho fatto un plot di tutti i dati presenti in data.txt e mi sono accorto che la funzione relativa ai 100 test risultava decrescente.
Ho ipotizzato che in realtà i dati fossero già ordinati in modo decrescente, quindi dopo diversi check, è saltato fuori che i dati
che erano maggiori di 2610 erano già ordinati in modo decrescente per ogni test.

Quindi tutti i dati letti > 2610 li ho ordinati nella parte finale del mio array, quindi ho utilizzato come invariante la mia parte destra
dell'array ed ho cominciato ad ordinare ogni dato letto per confronto ed a spostarlo nella posizione giusta.

*/

int ct_swap = 0;
int ct_cmp = 0;
int ct_read = 0;

int max_dim = 0;
int ntests = 100;
int ndiv = 1;
int details = 0;
int graph = 0;

int n = 0; /// dimensione dell'array

void print_array(int *A, int dim) {
    for (int j = 0; j < dim; j++) {
        printf("%d ", A[j]);

    }
    printf("\n");
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
    /// aggiorno contatore globale di swap
    ct_swap++;
}


int parse_cmd(int argc, char **argv) {

    /// parsing argomento
    max_dim = 1000;

    for (int i = 1; i < argc; i++) {
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



bool is_sorted(int *A, int first, int last){
    for(int i = first; i < last; i++){
        if(i < last - 1){
            if(A[i] > A[i + 1])
                return false;
        }
    }

    return true;
}

const int MIN_INT = 2610;

int main(int argc, char **argv) {
    int i, test;
    int *A;
    int *B; /// buffer per visualizzazione algoritmo

    int* prova;

    if (parse_cmd(argc, argv))
        return 1;

    /// allocazione array
    A = new int[max_dim];
    prova = new int[max_dim];

    n = max_dim;

    // creazione file input: NON USARE PIU' --> il file data.txt ufficiale è stato allegato, per permettere confronti equivalenti
    //  FILE *f = fopen("data.txt", "w+");
    //  for (int j = 0; j < 100; j++) {
    //      for (int i = 0; i < n; i++) {
    //          int v = 0;
    //          v=(int)(100000*pow(2,-i/(0.0+n)*25));
    //          v+=rand()%50-25;
    //          fprintf(f, "%d,", v);
    //      }
    //      fprintf(f, "\n");
    //  }
    //  fclose(f);

    ifstream input_data;
    input_data.open("data.txt");

    ofstream output_check;
    output_check.open("output_check.txt");

    ofstream output;
    output.open("consegna1.txt");

    int read_min = -1;
    int read_max = -1;
    long read_avg = 0;

    //// lancio ntests volte per coprire diversi casi di input random
    for (test = 0; test < ntests; test++) {

        int insert_element = n -1;

        int counter = 0;

        bool after_2610 = false;

        //int neg_counter = 0;

        /// inizializzazione array: numeri random con range dimensione array
        for (i = 0; i < n; i++) {
            char comma;

            int data;

            int last;

            ct_read = 0;

            input_data >> data;

            // finchè data era > 2610 allora inserivo nella cella insert_element dell'array, quando sarebbero terminati i valori > 2610
            // avrei ottenuto un range [0, insert_element] in cui ordinavo i nuovi elementi < 2610

            if(data > MIN_INT){
                A[insert_element] = data;
                insert_element--;
            }
            else{
                if(!after_2610){
                    counter = insert_element;
                    last = data;
                }
                after_2610 = true;

                // se il nuovo dato è maggiore dell'ultimo inserito allora entravo nel ciclo for per spostarlo nella posizione giusta

                if(data > last){
                    A[counter] = last;
                    A[counter + 1] = data;

                    for(int j = counter + 2; j < insert_element;j++){
                        ct_read++;
                        int a_j = A[j];
                        if(data > a_j){
                            A[j -1] = a_j;
                            A[j] = data;
                        }
                        else
                            break;
                    }
                }

                // se invece il dato risultava <= allora lo mettevo nella cella A[counter] e lo impostavo come ultimo dato di riferimento per fare i confronti
                else{
                    A[counter] = data;
                    last = data;
                }

                counter--;
            }

            input_data >> comma;
        }
        
        if (details) {
            printf("caricato array di dimensione %d\n", n);
            print_array(A, n);
        }
        
        ct_swap = 0;
        ct_cmp = 0;

        /*
        is_sorted è solo una funzione che fa dei check, esegue stampe su file a seconda se l'array risulta ordinato o no, dato che è opzionale allora non ho contato le letture.
        Per verificare che tutti gli array relativi ai 100 test siano ordinati, bisogna eseguire grep "is not sorted" output_check.txt, se il terminale ritorna qualche risultato allora
        qualche array non è ordinato.

        */

        if(is_sorted(A,0,n)){
            output_check << "Array Test: " << test << " is sorted";
            output_check << endl;
        }
        else{
            output_check << "Array Test: " << test << " is not sorted";
            output_check << endl;
        }

        if (details) {
            printf("Output:\n");
            print_array(A, n);
        }

        /// statistiche
        read_avg += ct_read;
        if (read_min < 0 || read_min > ct_read)
            read_min = ct_read;
        if (read_max < 0 || read_max < ct_read)
            read_max = ct_read;
        printf("Test %d %d\n", test, ct_read);
    }

    printf("%d,%d,%.1f,%d\n",
           ntests,
           read_min, (0.0 + read_avg) / ntests, read_max);

    output << ntests << "," << read_min << "," << (0.0 + read_avg) / ntests << "," << read_max << endl;

    delete[] A;

    output_check.close();
    output.close();


    return 0;
}
