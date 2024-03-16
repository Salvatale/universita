#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

using namespace std;

// compilazione: g++ consegna1-loader.c
//

// Il programma carica il file data.txt contenente 100 righe con dati da ordinare in modo crescente
// ./a.out
// In output viene mostrato il numero di accessi in read alla memoria per eseguire il sorting di ciascuna riga

// Obiettivo:
// Creare un algoritmo di sorting che minimizzi la somma del numero di accessi per ogni sorting di ciascuna riga del file

//Fasi dell'algoritmo:
//  - Inserire in fondo al mio array tutti gli elementi gia ordinati in senso decrescente, ho notato che fino ad un certo punto gli elementi sono già ordinati in senso decrescente.
//  - Interrompiamo gli inserimenti già ordinati ed iniziamo a mettere i numeri negativi all'inizio del mio array e quelli positivi tra quelli già ordinati e quelli negativi.
//  - Utilizziamo due tipi di algoritmi diversi per i numeri negativi e quelli positivi.

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

//Questo algoritmo semplicemente crea delle buche come dice anche il nome, inserisce gli elementi uguali nelle stesse buche e dopo fa una join di tutte le buche.
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

    vector<int> *holes;

    holes = new vector<int>[range];

    for(int i = first; i < last; ++i){

        int value = A[i];
        ct_read++;

        holes[value - min].push_back(value);

    }

    int index = 0;

    

    for(int i = 0; i < range; ++i){

        vector<int>::iterator it;

        it = holes[i].begin();
        ct_read++;

        vector<int>::iterator end;

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

// L'unica differenza di questo rispetto a quello precedente è quella di trasformare i numeri negativi in positivi e dopo fare una reverse join.
void pigeon_hole_neg_sort(int *A, int first, int last){

    int min = 10000000;
    int max = -1;

    for(int i = first; i < last; i++){

        int value = A[i] *(-1);
        ct_read++;

        if(value < min)
            min = value;

        if(value > max)
            max = value;

    }

    int range = max - min + 1;

    vector<int> *holes;

    holes = new vector<int>[range];

    for(int i = first; i < last; ++i){

        int value = A[i] * (-1);
        ct_read++;

        holes[value - min].push_back(value);

    }

    last--;

    for(int i = 0; i < range; ++i){

        vector<int>::iterator it;

        it = holes[i].begin();
        ct_read++;

        vector<int>::iterator end;

        end = holes[i].end();
        ct_read++;

        while(it != end){

            A[last] = *it *(-1);
            ct_read++;

            ++it;
            last--;


        }    

    }

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
            if(A[i] > A[i + 1]){
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char **argv) {
    int i, test;
    int *A;
    int *B; /// buffer per visualizzazione algoritmo

    int *C;

    C = new int[100];

    if (parse_cmd(argc, argv))
        return 1;

    /// allocazione array
    A = new int[max_dim];

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

    int data;

    const int MIN_INT = 2610;

    //// lancio ntests volte per coprire diversi casi di input random
    for (test = 0; test < ntests; test++) {

        int neg_count = 0;
        int reverse_count = max_dim -1;
        int index_first_element_sorted;
        int index_element_to_sort;
        int index_last_negative_number;
        bool insert_sorted = true;
        ct_read = 0;
        /// inizializzazione array: numeri random con range dimensione array
        for (i = 0; i < n; i++) {
            char comma;
            input_data >> data;
            
            // entriamo sempre qui finchè non troveremo il primo elemento non in ordine decrescente.
            if(insert_sorted){
                if(i == 0){
                    A[reverse_count] = data;
                    reverse_count--;

                }
                else{
                    
                    //Se il nuovo elemento è più piccolo di quello successivo allora inserisco normalmente
                    ct_read++;
                    if(data <= A[reverse_count + 1]){
                        A[reverse_count] = data;
                        reverse_count--;
                    }
                    //Se invece l'elemento è più grande allora lo sposto in avanti, smetto di inserire in ordine e mi segno l'indice pdove posso cominciare ad inserire i numeri positivi.
                    else{
                        ct_read++;
                        int value = A[reverse_count + 1];

                        A[reverse_count + 1] = data;
                        A[reverse_count] = value;

                        index_first_element_sorted = reverse_count + 1;
                        reverse_count--;

                        insert_sorted = false;

                    }

                }

            }
            //Adesso comincio a smistare i numeri negativi ed i numeri positivi non ordinati
            else{

                //Se è negativo allora lo inserisco nella parte iniziale dell'array ed incremento.
                if(data < 0){

                    A[neg_count] = data;
                    neg_count++;

                }
                //Se è positivo allora inserisco nelle celle prima della parte già ordinata e decremento.
                else{
                    A[reverse_count] = data;
                    reverse_count--;

                }


            }

            input_data >> comma;
        }


        
        index_element_to_sort = reverse_count +1;
        index_last_negative_number = neg_count - 1;

        if (details) {
            printf("caricato array di dimensione %d\n", n);
            print_array(A, n);
        }

        ct_swap = 0;
        ct_cmp = 0;
        
        //Adesso mi trovo l'array scomposto in tre blocchi:
        // - Parte destra con gli elementi già ordinati e quindi che escludiamo
        // - Parte centrale con gli elementi positivi che faccio ordinare all'algoritmo di pigeon hole sort
        // - Parte sinistra che contiene i numeri negativi che faccio ordinare a pigeon hole sort che prende solo numeri negativi

        /// algoritmo di sorting
        // Ho sperimentato anche bucket sort da solo, una combinazione di bucket sort e pigeon hole, ma alla fine questa soluzione mi forniva un risultato migliore
        pigeon_hole_sort(A,index_element_to_sort,index_first_element_sorted);
        pigeon_hole_neg_sort(A,0,index_last_negative_number+1);

        // una piccola funzione per controllare se tutti fossero ordinati
        if(is_sorted(A,0,n)){
            C[test] = 1;
        }
        else{
            C[test] = 200;
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

    output << ntests << "," << read_min << ","  << (0.0 + read_avg) / ntests << "," << read_max << endl;


    // Stampo nel file output_check.txt se sono tutti ordinati, per controllare basterà fare il comando grep 200 output_check.txt da terminale, se fornisce qualche risultato allora non è ordinato    
    for(int i = 0; i < ntests; i++){

        output_check << "Array test: " << i << " " << C[i] << endl;

    }
    
   
    
    

    delete[] A;
    delete[] C;


    output.close();
    output_check.close();


    return 0;
}
