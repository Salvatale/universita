#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

#define INFTY 1000000
const int Edges = 735;
const int n_clusters = 5;
const int n_iterations = 7;

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
    float w;
    struct node *next;
    int cluster;
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
int *V_prev;     // nodo precedente dalla visita
float *V_dist;   // distanza da sorgente

int **M;

// list_t* E;  /// array con le liste di adiacenza per ogni nodo
list_t **E; /// array di puntatori a le liste di adiacenza per ogni nodo
list_t **E_ssc;
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

void node_print_scc(int n) {

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

void graph_print_scc() {
    for (int i = 0; i < n_nodi; i++)
        node_print_scc(i);
    n_operazione++;
}

void node_print(int n) {

    /// calcolo massima distanza (eccetto infinito)
    float max_d = 0;
    for (int i = 0; i < n_nodi; i++)
        if (max_d < V_dist[i] && V_dist[i] < INFTY)
            max_d = V_dist[i];

    output_graph << "node_" << n << "_" << n_operazione << endl;
    output_graph << "[ shape = oval; ";

    if (V_visitato[n] == 1)
        output_graph << "penwidth = 4; ";

    float col = V_dist[n] / max_d; /// distanza in scala 0..1
    output_graph << "fillcolor = \"0.0 0.0 " << col / 2 + 0.5 << "\"; style=filled; ";
    if (V_dist[n] < INFTY)
        output_graph << "label = "
                     << "\"Idx: " << n << ", dist: " << V_dist[n] << "\" ];\n";
    else
        output_graph << "label = "
                     << "\"Idx: " << n << ", dist: INF\" ];\n";

    node_t *elem = E_ssc[n]->head;
    while (elem != NULL) { /// disegno arco
        output_graph << "node_" << n << "_" << n_operazione << " -> ";
        output_graph << "node_" << elem->val << "_" << n_operazione << " [ label=\"" << elem->w << "\", len=" << elem->w / 100 * 10 << " ]\n";
        elem = elem->next;
    }

    // if (V_prev[n] != -1) { // se c'e' un nodo precedente visitato -> disegno arco

    //     float len = 0;
    //     /*
    //     //cerco arco V_prev[n] --> V[n]
    //     node_t* elem=E[ V_prev[n] ]->head;
    //     while (elem!=NULL){
    //     int v=elem->val; /// arco u --> v
    //     if (v == V[n])
    //       len=elem->w;
    //     elem=elem->next;
    //       }
    //     */

    //     len = 1;
    //     output_graph << "node_" << n << "_" << n_operazione << " -> ";
    //     output_graph << "node_" << V_prev[n] << "_" << n_operazione << " [ color=blue, penwidth=5, len=" << len / 100 * 10 << " ]\n";
    // }
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

void list_insert_front(list_t *l, int elem, float w) {
    /// inserisce un elemento all'inizio della lista
    node_t *new_node = new node_t;
    new_node->next = NULL;

    new_node->val = elem;
    new_node->w = w;

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

//Imposto due variabili 
int total_weight = 0;
int w_arc = 0;

void scc(int v,int cluster) {

    //graph_print();

    if(total_weight == 0)
        V_dist[v] = 0;
    else
        V_dist[v] = w_arc;

    V_visitato[v] = idx;
    V_lowlink[v] = idx;
    idx = idx + 1;
    //printf("push %d\n", v);
    stack_push(s, v);
    V_onStack[v] = 1;

    /// esploro la lista di adiacenza
    node_t *elem = E[v]->head;
    while (elem != NULL) { /// elenco tutti i nodi nella lista

        // output_graph << "node_" << v << "_" << n_operazione << " -> ";
        // output_graph << "node_" << elem->val << "_" << n_operazione << "[color=blue, label = \"" << ct_visit++ << "\"]\n";

        //graph_print();

        // /// espando arco  n --> elem->val
        // /// quindi DFS(elem->val)
        // output_graph << "dfs_"<< n << " -> dfs_"<< elem->val;
        // if (V_visitato[elem->val])
        //   output_graph << "[color=gray, label = \""<< ct_visit++<< "\"]";
        // else
        //   output_graph << "[color=red, label = \""<< ct_visit++<< "\"]";
        // output_graph  <<endl;

        //Dato che ho diviso tutti gli archi di peso simile in cluster, controllo che ogni arco
        //appartenga al cluster giusto prima di poter procedere
        if(elem->cluster == cluster){

            int w = elem->val;
            //printf("esploro %d -> %d\n", v, w);

            if (V_visitato[w] == -1) {
                //printf("chiamo scc su %d\n", w);
                scc(w,cluster);
                if (V_lowlink[v] > V_lowlink[w]) // calcolo v.lowlink := min(v.lowlink, w.lowlink)
                    V_lowlink[v] = V_lowlink[w];
            } else {
                if (V_onStack[w] == 1)
                    if (V_lowlink[v] > V_visitato[w]) // calcolo v.lowlink := min(v.lowlink, w.index)
                        V_lowlink[v] = V_visitato[w];
            }
        }

        elem = elem->next;
    }

    //printf("finito il nodo %d\n", v);

    int succ = -1;

    if (V_lowlink[v] == V_visitato[v]) {
        // start a new strongly connected component
        int c = 0;
        int w = -1;
        node_t* elem;
        do {
            w = stack_pop(s);
            //Faccio questo controllo perchè se incontro un nodo che forma una componente connessa
            //da solo allora voglio renderlo disponibile perchè potrebbe rientrare nella componente
            //connessa per i successivi cluster, questo nodo potrebbe appartanere ad una componente connessa
            //con peso più basso
            if(w == v && c == 0){
                V_visitato[v] = -1;
                V_onStack[v] = 0;
                return;
            }
            if(c == 0)
                printf("Nuova componente connessa %d : ", v);

            //Questa parte succesiva invece mi permette di costruire un grafo contenente le componenti
            //fortemente connesse, serve solo a rendere questi elementi visibili graficamente,
            //Il percorso in questo grafo potrebbe non corrispondere con la scc, però ci permette
            // di vedere tutti i nodi.
            if(succ == -1){
                if(v != w)
                    list_insert_front(E_ssc[w],v,0);
            }    
            else
                list_insert_front(E_ssc[w],succ,0);
            succ = w;
            c++;
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


int main(int argc, char **argv) {
    int i, test;

    // init random
    srand((unsigned)time(NULL));

    if (parse_cmd(argc, argv))
        return 1;

    if (graph) {
        output_graph.open("graph.dot");
        /// preparo header
        output_graph << "digraph g" << endl;
        output_graph << "{ " << endl;
        output_graph << "node [shape=none]" << endl;
        output_graph << "rankdir=\"LR\"" << endl;
        ;
        //    output_graph << "edge[tailclip=false,arrowtail=dot];"<<endl;
    }

    int N = 10;
    n_nodi = N * N;

    n_nodi = 49;
    //n_nodi = 7;

    //// init nodi
    V = new int[n_nodi];
    V_visitato = new int[n_nodi];
    V_lowlink = new int[n_nodi];
    V_onStack = new int[n_nodi];
    V_prev = new int[n_nodi];
    V_dist = new float[n_nodi];
    s = stack_new();


    //// init archi
    E = new list_t *[n_nodi]; //(list_t**)malloc(n_nodi*sizeof(list_t*));
    //grafo per la visibilità delle scc
    E_ssc = new list_t *[n_nodi]; //(list_t**)malloc(n_nodi*sizeof(list_t*));


    // costruzione grafo
    for (int i = 0; i < n_nodi; i++) {
        V[i] = 2 * i;
        V_visitato[i] = 0; // flag = non visitato
        V_prev[i] = -1;    // non c'e' precedente
        V_dist[i] = INFTY; // infinito

        E[i] = list_new();
        E_ssc[i] = list_new();

        if (i == 0)
            global_ptr_ref = E[i];

        int x = i % N;
        int y = i / N;

        // for (int dx = -2; dx <= 2; dx += 1)
        //     for (int dy = -2; dy <= 2; dy += 1)
        //         if (abs(dx) + abs(dy) >= 1 &&
        //             abs(dx) + abs(dy) <= 1
        //             ) { // limito gli archi ai vicini con 1 variazione assoluta sulle coordinate

        //             int nx = x + dx;
        //             int ny = y + dy;

        //             if (nx >= 0 && nx < N &&
        //                 ny >= 0 && ny < N) { /// coordinate del nuovo nodo sono nel grafo

        //                 int j = nx + N * ny; /// indice del nuovo nodo
        //                 list_insert_front(E[i], j, 15 * sqrt(dx*dx + dy*dy));
        //             }
        //         }
    }

    int partenza = 0;
    int arrivo = n_nodi - 1;
    int w_max = 100;

    // for(int i = 0; i < n_nodi; i++){
    //     for(int j = 0; j < n_nodi; j++){
    //         if(i != j){
    //             if(rand()%100 <= 50)
    //                 list_insert_front(E[i],j);
    //         }
    //     }

    // }

    ifstream input_data;
    input_data.open("21-graph.txt");

    //Costruzione grafo su cui lavoriamo
    for(int i = 0; i < Edges; i++){

        int u;

        int v;

        int w;

        input_data >> u;
        input_data>> v;
        input_data >> w;

        list_insert_front(E[u],v,w);

    }
    //Impostazione cluster
    int c[n_clusters];
    //Centroidi iniziali del cluster, ne imposto 5 in modo da avere diversi cluster distinti
    c[0] = 5;
    c[1] = 15;
    c[2] = 30;
    c[3] = 50;
    c[4] = 80;
    int cluster_sum[n_clusters];
    int n_arc_cluster[n_clusters];

    node_t* elem;

    //Iterazione fino a quando non trovo dei centroidi soddisfacenti
    //Adotto l'algoritmo K-means che è un classico nei cluster
    for(int i = 0; i < n_iterations;i++){

        for(int j = 0; j < n_clusters; j++)
            cluster_sum[j] = 0;
        for(int j = 0; j < n_clusters; j++)
            n_arc_cluster[j] = 0;
        
        //Per ogni arco, lo assegno al cluster giusto
        //Misuro la distanza da ogni centroide, inserisco nel cluster con il centroide più vicino
        for(int j = 0; j < n_nodi; j++){

            elem = E[j]->head;
            while(elem != NULL){
                
                int index = 1;
                int min = 1000;
                int weight = elem->w;

                for(int k = 0; k < n_clusters; k++){
                    int d = abs(c[k] - weight);

                    if(min > d){
                        min = d;
                        index = k;
                    }
                }

                for(int k = 0; k < n_clusters; k++){
                    if(index == k){
                        cluster_sum[k] += weight;
                        elem->cluster = k;
                        n_arc_cluster[k]++;
                    }
                }
                
                elem = elem->next;
            }
        }
        elem = NULL;
        //Una volta finita un'iterazione calcolo il nuovo centroide facendo la media di tutti
        //gli archi appartenenti al relativo cluster
        if(i < n_iterations -1)
            for(int j = 0; j < n_clusters;j++)
                c[j] = cluster_sum[j]/n_arc_cluster[j];

    }

    // for (int i = 0; i < n_nodi; i++) {
    //     printf("Sono il nodo di indice %d nell'array\n", i);
    //     printf("Il valore del nodo e' %d\n", V[i]);
    //     printf("La lista di adiacenza e'\n");
    //     list_print(E[i]);
    // }

    for(int i = 0; i < n_nodi; i++)
        V_visitato[i] = -1;

    //Variazione rispetto all'algoritmo scc, adesso avviamo l'algoritmo scc per ogni cluster,
    //in modo che sappiamo di trovare componenti fortemente connesse che hanno archi di peso simile
    //cioè tutti gli archi appartenenti al cluster.
    for(int j = n_clusters - 1; j > -1;j--){
        cout << "Start of cluster : " << j << ", centroid: " << c[j] << endl;
        for(int i = 0; i < n_nodi; i++){
            total_weight = 0;
            w_arc = 0;
            if(V_visitato[i] == -1)
                scc(i,j);
        }
    }
    //Stampa per visualizzare le scc, modificata in modo che disegni E_scc
    graph_print();


    if (graph) {
        /// preparo footer e chiudo file
        output_graph << "}" << endl;
        output_graph.close();
        cout << " File graph.dot scritto" << endl
             << "****** Creare il grafo con: neato graph.dot -Tpdf -o graph.pdf" << endl;
    }

    return 0;
}
