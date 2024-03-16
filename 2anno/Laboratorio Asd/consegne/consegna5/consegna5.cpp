#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

// compilazione: g++ lezione19.cpp
//
// Obiettivo:
// 1)

int ct_swap = 0;
int ct_cmp = 0;
int ct_op = 0; /// operazioni per la ricerca

int max_dim = 0;
int ntests = 1;
int ndiv = 1;
int details = 0;
int graph = 0;

int n = 0; /// dimensione dell'array

/// file di output per grafo
ofstream output_graph;
int n_operazione = 0; /// contatore di operazioni per visualizzare i vari step

int ct_visit = 0; // contatore durante visita

typedef struct list my_stack;

my_stack *s;

int idx = 0;

//////////////////////////////////////////////////
/// Definizione della struttura dati lista
//////////////////////////////////////////////////

/// struct per il nodo della lista
typedef struct node {
    int val;
    struct node *next;
} node_t;

/// struct per la lista
typedef struct list {
    node *head;
    // node* tail; /// per lista doubly linked
} list_t;

//////////////////////////////////////////////////
/// Fine Definizione della struttura dati lista
//////////////////////////////////////////////////

//////////////////////////////////////////////////
/// Definizione della struttura dati grafo
//////////////////////////////////////////////////

int *V;          // elenco dei nodi del grafo
int *V_visitato; // nodo visitato?
int *V_lowlink;  //
int *V_onStack;

int **M;

// list_t* E;  /// array con le liste di adiacenza per ogni nodo
list_t **E; /// array di puntatori a le liste di adiacenza per ogni nodo
int n_nodi;

//////////////////////////////////////////////////
/// Fine Definizione della struttura dati grafo
//////////////////////////////////////////////////

/// Questo e' un modo per stampare l'indirizzo node relativamente ad un altro di riferimento.
/// Permette di ottenere offset di piccola dimensione per essere facilmente visualizzati
/// Nota: il metodo non e' robusto e potrebbe avere comportamenti indesiderati su architetture diverse
/// L'alternativa corretta' e' utilizzare %p di printf: es. printf("%p\n",(void*) node);
/// con lo svantaggio di avere interi a 64 bit poco leggibili

list_t *global_ptr_ref = NULL; /// usato per memorizzare il puntatore alla prima lista allocata

int get_address(void *node) {
    return (int)((long)node - (long)global_ptr_ref);
}

void node_print(int n) {

    output_graph << "node_" << n << "_" << n_operazione << endl;
    output_graph << "[ shape = oval; ";
    if (V_visitato[n] == -1)
        output_graph << "fillcolor = \"#aaaaaa\"; style=filled; ";
    output_graph << "label = "
                 << "\"Idx: " << n << ", val: " << V[n] << " index: " << V_visitato[n] << " lowlink: " << V_lowlink[n] << "\" ];\n";

    node_t *elem = E[n]->head;
    while (elem != NULL) { /// disegno arco
        output_graph << "node_" << n << "_" << n_operazione << " -> ";
        output_graph << "node_" << elem->val << "_" << n_operazione << " [  color=gray ]\n";
        elem = elem->next;
    }
}

void graph_print() {
    for (int i = 0; i < n_nodi; i++)
        node_print(i);
    n_operazione++;
}

void list_print(list_t *l) {
    printf("Stampa lista\n");

    if (l->head == NULL) {
        printf("Lista vuota\n");
    } else {
        node_t *current = l->head;

        while (current != NULL) {
            if (!details)
                printf("%d, ", current->val);
            else { /// stampa completa
                if (current->next == NULL)
                    printf("allocato in %d [Val: %d, Next: NULL]\n",
                           get_address(current),
                           current->val);
                else
                    printf("allocato in %d [Val: %d, Next: %d]\n",
                           get_address(current),
                           current->val,
                           get_address(current->next));
            }
            current = current->next;
        }
        printf("\n");
    }
}

list_t *list_new(void) {
    list_t *l = new list;
    if (details) {
        printf("Lista creata\n");
    }

    l->head = NULL; //// perche' non e' l.head ?
    if (details) {
        printf("Imposto a NULL head\n");
    }

    return l;
}

void list_delete(list_t *l) {
    //// implementare rimozione dal fondo della lista
    //// deallocazione struct list
}

void list_insert_front(list_t *l, int elem) {
    /// inserisce un elemento all'inizio della lista
    node_t *new_node = new node_t;
    new_node->next = NULL;

    new_node->val = elem;

    new_node->next = l->head;

    l->head = new_node;
}

void list_delete_front(list_t *l) {
    /// elimina il primo elemento della lista
    node_t *node = l->head; // il nodo da eliminare

    if (node == NULL) // lista vuota
        return;

    l->head = node->next;

    // if (graph) print_status(l,node,"DEL FRONT: aggancio lista a nodo successivo");

    node->next = NULL;

    // if (graph) print_status(l,node,"DEL FRONT: sgancio puntatore da nodo da cancellare");

    delete node;

    //  if (graph) print_status(l,NULL,"DEL FRONT: cancello nodo");
}

////////// operazioni stack

my_stack *stack_new() {
    return list_new();
}

int stack_top(my_stack *s) {
    if (s->head != NULL)
        return s->head->val;
    printf("ERRORE: stack vuoto!\n");
    return -1;
}

int stack_pop(my_stack *s) {
    if (s->head != NULL) {
        int v = s->head->val;
        list_delete_front((list_t *)s);
        return v;
    }
    printf("ERRORE: stack vuoto!\n");
    return -1;
}

void stack_push(my_stack *s, int v) {
    list_insert_front((list_t *)s, v);
}

void stack_print(my_stack *s) {
    list_print((list_t *)s);
}

void print_array(int *A, int dim) {
    for (int j = 0; j < dim; j++) {
        printf("%d ", A[j]);
    }
    printf("\n");
}

void print_array_graph(int *A, int n, string c, int a, int l, int m, int r) {
    /// prepara il disegno dell'array A ed il suo contenuto (n celle)
    /// a e' il codice del nodo e c la stringa
    /// l,m,r i tre indici della bisezione

    // return ;

    output_graph << c << a << " [label=<" << endl;

    /// tabella con contenuto array
    output_graph << "<TABLE BORDER=\"0\" CELLBORDER=\"0\" CELLSPACING=\"0\" > " << endl;
    /// indici
    output_graph << "<TR  >";
    for (int j = 0; j < n; j++) {
        output_graph << "<TD ";
        output_graph << ">" << j << "</TD>" << endl;
    }
    output_graph << "</TR>" << endl;
    output_graph << "<TR>";
    // contenuto
    for (int j = 0; j < n; j++) {
        output_graph << "<TD BORDER=\"1\"";
        if (j == m)
            output_graph << " bgcolor=\"#00a000\""; /// valore testato
        else if (j >= l && j <= r)
            output_graph << " bgcolor=\"#80ff80\""; /// range di competenza
        output_graph << ">" << A[j] << "</TD>" << endl;
    }
    output_graph << "</TR>" << endl;
    output_graph << "</TABLE> " << endl;

    output_graph << ">];" << endl;
}

void scc(int v) {

    graph_print();

    V_visitato[v] = idx;
    V_lowlink[v] = idx;
    idx = idx + 1;
    printf("push %d\n", v);
    stack_push(s, v);
    V_onStack[v] = 1;

    /// esploro la lista di adiacenza
    node_t *elem = E[v]->head;
    while (elem != NULL) { /// elenco tutti i nodi nella lista

        output_graph << "node_" << v << "_" << n_operazione << " -> ";
        output_graph << "node_" << elem->val << "_" << n_operazione << "[color=blue, label = \"" << ct_visit++ << "\"]\n";

        graph_print();

        // /// espando arco  n --> elem->val
        // /// quindi DFS(elem->val)
        // output_graph << "dfs_"<< n << " -> dfs_"<< elem->val;
        // if (V_visitato[elem->val])
        //   output_graph << "[color=gray, label = \""<< ct_visit++<< "\"]";
        // else
        //   output_graph << "[color=red, label = \""<< ct_visit++<< "\"]";
        // output_graph  <<endl;

        int w = elem->val;
        printf("esploro %d -> %d\n", v, w);

        if (V_visitato[w] == -1) {
            printf("chiamo scc su %d\n", w);
            scc(w);
            if (V_lowlink[v] > V_lowlink[w]) // calcolo v.lowlink := min(v.lowlink, w.lowlink)
                V_lowlink[v] = V_lowlink[w];
        } else {
            if (V_onStack[w] == 1)
                if (V_lowlink[v] > V_visitato[w]) // calcolo v.lowlink := min(v.lowlink, w.index)
                    V_lowlink[v] = V_visitato[w];
        }

        elem = elem->next;
    }

    printf("finito il nodo %d\n", v);

    if (V_lowlink[v] == V_visitato[v]) {
        // start a new strongly connected component
        printf("Nuova componente connessa %d : ", v);

        int w = -1;
        do {
            w = stack_pop(s);
            V_onStack[w] = 0;
            printf("%d, ", w);
        } while (v != w); /// w!=v
        printf("\n");
    }
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
    /// aggiorno contatore globale di swap
    ct_swap++;
}

int parse_cmd(int argc, char **argv) {
    /// controllo argomenti
    int ok_parse = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][1] == 'v') {
            details = 1;
            ok_parse = 1;
        }
        if (argv[i][1] == 'g') {
            graph = 1;
            ok_parse = 1;
        }
    }

    if (argc > 1 && !ok_parse) {
        printf("Usage: %s [Options]\n", argv[0]);
        printf("Options:\n");
        printf("  -verbose: Abilita stampe durante l'esecuzione dell'algoritmo\n");
        printf("  -graph: creazione file di dot con il grafo dell'esecuzione (forza d=1 t=1)\n");
        return 1;
    }

    return 0;
}

int ct_fib = 0;

int fib(int n) {
    ct_fib++;

    if (V[n] != 0)
        return V[n];

    // non conosco la risposta
    int risposta = 0;

    if (n <= 2)
        risposta = 1;
    else
        risposta = fib(n - 1) + fib(n - 2);
    V[n] = risposta;
    return risposta;
}

int is_match(char temp1, char temp2) {
    if (temp1 == temp2 &&
        (temp1 < 'a' || temp1 > 'z') &&
        (temp2 < 'a' || temp2 > 'z'))
        return 1;
    return 0;
}

//Funzione che assegna gli score per ogni carattere interessante
int is_match_consegna(char temp1, char temp2) {

    if(temp1 == temp2){
        if (
        (temp1 == ' ' || temp1 == '\t') &&
        (temp2 == ' ' || temp2 == '\t'))
        return 0;
    //Caratteri speciali che sono interi che vanno da 48 a 87 e hanno 3 come score, es:'='
    if (
        (temp1 > 47  && temp1 < 58) &&
        (temp2 > 47 && temp2 < 58))
        return 3;
    
    if (
        ((temp1 > 'a' && temp1 < 'z') || (temp1 > 'A'  && temp1 < 'Z')) &&
        (temp2 > 'a' && temp2 < 'z') || (temp1 > 'A'  && temp1 < 'Z'))
        return 2;
    else
        return 5;
    }
    

    return 0;
}

int main(int argc, char **argv) {
    int i, test;

    srand((unsigned)time(NULL));

    if (parse_cmd(argc, argv))
        return 1;

    // Per confrontare da file
    // ifstream file("test_consegna5.txt");

    // file.seekg(0,std::ios::end);
    // std::streampos filesize = file.tellg();
    // file.seekg(0,std::ios::beg);

    // const int s1 = filesize;
    // const int s2 = filesize;

    // char *str1 = new char[s1+1];
    // char *str2 = new char[s2+1];

    // file.read(str1,filesize);
    // file.seekg(0,std::ios::beg);
    // file.read(str2,filesize);

    // str1[s1] = '/0';
    // str2[s2] = '/0';

    char* temp1 = "int a = 0; char b = 'c';";
    char* temp2 = "int a = 10; char b = 'd';";

    const int s1 = strlen(temp1);
    const int s2 = strlen(temp2);

    char *str1;
    char *str2;

    str1 = new char[s1];
    str2 = new char[s2];

    for (i = 0; i < s1; i++) {
        str1[i] = temp1[i];
    }
    for (i = 0; i < s2; i++) {
        str2[i] = temp2[i];
    }

    M = new int *[s1 + 1];
    for (i = 0; i < s1 + 1; i++)
        M[i] = new int[s2 + 1];

    for (int i = 0; i < s1 + 1; i++)
        M[i][0] = 0;
    for (int j = 0; j < s2 + 1; j++)
        M[0][j] = 0;

    for (int i = 1; i < s1 + 1; i++)
        for (int j = 1; j < s2 + 1; j++) {

            /// sottostringa (con maiuscole/minuscole)
            int match = is_match_consegna(str1[i - 1], str2[j - 1]);

            // /// calcolo costo sottostringa (con maiuscole/minuscole)
            // int match = 0;
            // if (str1[i - 1] == str2[j - 1])
            //     match = 1;
            // else {
            //     char temp1 = str1[i - 1];
            //     if (temp1 >= 'a' && temp1 <= 'z')
            //         temp1 -= abs('A' - 'a');
            //     char temp2 = str2[j - 1];
            //     if (temp2 >= 'a' && temp2 <= 'z')
            //         temp2 -= abs('A' - 'a');
            //     if (temp1 == temp2)
            //         match = 1;
            // }

            /// sottosequenza
            if (match) { // match
                         /// M(i, j) ← 1 + M(i − 1, j − 1)
                M[i][j] = match + M[i - 1][j - 1];
            } else { // mismatch
                // M(i, j) ← max(M(i − 1, j), M(i, j − 1))
                int max = M[i - 1][j];
                if (max < M[i][j - 1])
                    max = M[i][j - 1];
                M[i][j] = max;
            }

            /// sottostringa
            // if (match) { // match
            //              /// M(i, j) ← 1 + M(i − 1, j − 1)
            //     M[i][j] = 1 + M[i - 1][j - 1];
            // } else { // mismatch
            //     M[i][j] = 0;
            // }
        }

    for (int i = 0; i < s1 + 1; i++) {

        // if (i == 0) {
        //     printf("   ");
        //     for (int j = 0; j < s2 + 1; j++)
        //         printf("%d ", j);
        //     printf("\n");
        // }

        printf("%2d: ", i);

        for (int j = 0; j < s2 + 1; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    i = s1;
    int j = s2;

    // ricostruzione sottosequenza
    while (i > 0 || j > 0) {
        // printf("posizione: %d %d\n", i, j);
        if (i > 0 && j > 0 && is_match_consegna(str1[i - 1],str2[j - 1])) {
            printf("%c", str1[i - 1]);
            i--;
            j--;
        } else {
            // if M(i,j) = M(i−1,j) then i ← i−1 else j ← j−1
            if (i > 0 && M[i][j] == M[i - 1][j])
                i--;
            else
                j--;
        }
    }
    printf("\n");

    //file.close();

    return 0;
}
