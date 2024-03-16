#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

// compilazione: g++ lezione17-grafi-dijkstra.cpp
//
// Obiettivo:
// 1) grafo con archi pesati
// 2) implementazione shortest path

#define INFTY 1000000

int ct_swap = 0;
int ct_cmp = 0;
int ct_op = 0; /// operazioni per la ricerca

int max_dim = 0;
int ntests = 1;
int ndiv = 1;
int details = 0;
int graph = 0;

/// file di output per grafo
ofstream output_graph;
int n_operazione = 0; /// contatore di operazioni per visualizzare i vari step

int ct_visit = 0; // contatore durante visita
int biggest_weight = 0;

//////////////////////////////////////////////////
/// Definizione della struttura dati lista
//////////////////////////////////////////////////

/// struct per il nodo della lista
typedef struct node {
    int val; /// prossimo nodo
    float w; /// peso dell'arco
    struct node *next;
} node_t;

/// struct per la lista
typedef struct list {
    node *head;
} list_t;

//////////////////////////////////////////////////
/// Fine Definizione della struttura dati lista
//////////////////////////////////////////////////

//////////////////////////////////////////////////
/// Definizione della struttura dati grafo
//////////////////////////////////////////////////

int *V;          // elenco dei nodi del grafo
int *V_visitato; // nodo visitato?
int *V_prev;     // nodo precedente dalla visita
float *V_dist;   // distanza da sorgente

// list_t* E;  /// array con le liste di adiacenza per ogni nodo
list_t **E; /// array di puntatori a le liste di adiacenza per ogni nodo
list_t **E_2;
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

    node_t *elem = E[n]->head;
    while (elem != NULL) { /// disegno arco
        output_graph << "node_" << n << "_" << n_operazione << " -> ";
        output_graph << "node_" << elem->val << "_" << n_operazione << " [ label=\"" << elem->w << "\", len=" << elem->w / 100 * 10 << " ]\n";
        elem = elem->next;
    }

    if (V_prev[n] != -1) { // se c'e' un nodo precedente visitato -> disegno arco

        float len = 0;
        /*
        //cerco arco V_prev[n] --> V[n]
        node_t* elem=E[ V_prev[n] ]->head;
        while (elem!=NULL){
        int v=elem->val; /// arco u --> v
        if (v == V[n])
          len=elem->w;
        elem=elem->next;
          }
        */

        len = 1;
        output_graph << "node_" << n << "_" << n_operazione << " -> ";
        output_graph << "node_" << V_prev[n] << "_" << n_operazione << " [ color=blue, penwidth=5, len=" << len / 100 * 10 << " ]\n";
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
                printf("%d w:%f, ", current->val, current->w);
            else { /// stampa completa
                if (current->next == NULL)
                    printf("allocato in %d [Val: %d, W: %f, Next: NULL]\n",
                           get_address(current),
                           current->val,
                           current->w);
                else
                    printf("allocato in %d [Val: %d, W: %f, Next: %d]\n",
                           get_address(current),
                           current->val,
                           current->w,
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

void list_insert_front(list_t *l, int elem, float w) {
    /// inserisce un elemento all'inizio della lista
    node_t *new_node = new node_t;
    new_node->next = NULL;

    new_node->val = elem;
    new_node->w = w;

    new_node->next = l->head;

    l->head = new_node;
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

void shortest_path(int n) {

    /*      V_visitato[i]=0;  // flag = non visitato
      V_prev[i]=-1;  // non c'e' precedente
      V_dist[i]=INFTY;  // infinito
    */

    V_dist[n] = 0;

    int q_size = n_nodi; /// contatore degli elementi in coda (V_visitato)

    while (q_size != 0) {

        //graph_print();

        /// trova il minimo in coda
        float best_dist = INFTY;
        int best_idx = -1;
        for (int i = 0; i < n_nodi; i++) {
            if (V_visitato[i] == 0 && V_dist[i] < best_dist) { /// nodo e' in coda e e' migliore del nodo corrente
                best_dist = V_dist[i];
                best_idx = i;
            }
        }
        if (best_idx >= 0) {
            /// estrai dalla coda
            int u = best_idx;
            V_visitato[u] = 1;
            q_size--;

            /// esploro la lista di adiacenza
            node_t *elem = E[u]->head;
            while (elem != NULL) {
                int v = elem->val; /// arco u --> v

                /// alt ← dist[u] + Graph.Edges(u, v)
                float alt = V_dist[u] + elem->w; /// costo per arrivare al nuovo nodo passando per u
                if (alt < V_dist[v]) {           // il percorso sorgente ---> u --> v migliora il percorso attuale sorgente --> v
                    V_dist[v] = alt;
                    V_prev[v] = u;
                }
                elem = elem->next;
            }

        } else { /// coda non vuota E nodi non raggiungibili ---> FINITO
            q_size = 0;
        }
    }

    //graph_print();
}

int DFS(int n) {

    //graph_print();

    if (details)
        printf("DFS: lavoro sul nodo %d (visitato %d)\n", n, V_visitato[n]);

    if (V_visitato[n])
        return 0;

    V_visitato[n] = 1; // prima volta che incontro questo nodo

    if (details)
        printf("Visito il nodo %d (val %d)\n", n, V[n]);

    /// esploro la lista di adiacenza
    node_t *elem = E[n]->head;
    while (elem != NULL) { /// elenco tutti i nodi nella lista

        /// espando arco  n --> elem->val
        /// quindi DFS(elem->val)
        output_graph << "dfs_" << n << " -> dfs_" << elem->val;
        if (V_visitato[elem->val])
            output_graph << "[color=gray, label = \"" << ct_visit++ << "\"]";
        else
            output_graph << "[color=red, label = \"" << ct_visit++ << "\"]";
        output_graph << endl;

        if (V_visitato[elem->val] == 1)
            return 1;

        int ret = DFS(elem->val);

        if (ret == 1)
            return 1;

        elem = elem->next;
    }

    V_visitato[n] = 2; // abbandono il nodo per sempre
    return 0;
}

const int limit = 73;
//const int limit = 106;

int DFS_weight_path(int n, int w) {

    //graph_print();

    if (details)
        printf("DFS: lavoro sul nodo %d (visitato %d)\n", n, V_visitato[n]);

    if (V_visitato[n])
        return 0;

    V_visitato[n] = 1; // prima volta che incontro questo nodo

    if (details)
        printf("Visito il nodo %d (val %d)\n", n, V[n]);

    /// esploro la lista di adiacenza
    node_t *elem = E_2[n]->head;
    while (elem != NULL) { /// elenco tutti i nodi nella lista

        /// espando arco  n --> elem->val
        /// quindi DFS(elem->val)
        if(elem->w < limit){
            output_graph << "dfs_" << n << " -> dfs_" << elem->val;
            if (V_visitato[elem->val])
                output_graph << "[color=gray, label = \"" << ct_visit++ << "\"]";
            else
                output_graph << "[color=red, label = \"" << ct_visit++ << "\"]";
            output_graph << endl;
        }

        if (V_visitato[elem->val] == 1)
            return 1;

        int ret = 0;
        if(elem->w < limit)
            ret = DFS_weight_path(elem->val, w + elem->w);

        if (ret == 1)
            return 1;

        elem = elem->next;
    }

    V_visitato[n] = 2; // abbandono il nodo per sempre
    return 0;
}

int average_path(int n){

    int best_weight = 0;
    int index;
    bool next = false;

    V_visitato[n] = 1;
    if(n == 0)
        V_dist[n] = 0;

    node_t* elem = E[n]->head;
    while(elem != NULL){

        if(V_visitato[elem->val] == 0){
            if(elem->w > best_weight){
                best_weight = elem->w;
                
                index = elem->val;

                next = true;
            }
        }

        elem = elem->next;

    }

    int result = 0;

    //cout << n << "-> " << index << " con peso: " << best_weight << endl;

    if(next){

        V_prev[index] = n;
        result = average_path(index);

        V_dist[index] = best_weight;
    }
    else
        return 0;

    return result + best_weight;


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

    //// init nodi
    V = new int[n_nodi];
    V_visitato = new int[n_nodi];
    V_prev = new int[n_nodi];
    V_dist = new float[n_nodi];

    //// init archi
    E = new list_t *[n_nodi]; //(list_t**)malloc(n_nodi*sizeof(list_t*)); 

    // costruzione grafo
    for (int i = 0; i < n_nodi; i++) {
        V[i] = 2 * i;
        V_visitato[i] = 0; // flag = non visitato
        V_prev[i] = -1;    // non c'e' precedente
        V_dist[i] = INFTY; // infinito

        E[i] = list_new();

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

    // for (int i = 0; i < n_nodi - 1; i++) {
    //     /// arco costoso
    //     list_insert_front(E[i], arrivo, w_max - 2 * i);
    //     /// arco 1
    //     if (i > 0)
    //         list_insert_front(E[i-1], i , 1);
    // }

    // for(int i = 0; i < n_nodi; i++){
    //     for(int j = 0; j < n_nodi; j++){
    //         if(j != i){
    //             if(rand()%100 <= 50){

    //                 int random_number = (rand()%19) + 1;
    //                 if(random_number > biggest_weight)
    //                     biggest_weight = random_number;

    //                 list_insert_front(E[i],j,random_number);
    //             }
    //         }

    //     }

    // }

    int n_edges = 0;
    int w_sum = 0;

    ifstream input_data;
    input_data.open("21-graph.txt");

    for(int i = 0; i < 735; i++){

        int u;

        int v;

        int w;

        input_data >> u;
        input_data>> v;
        input_data >> w;

        w = 113 - w;

        list_insert_front(E[u],v,w);

        if(biggest_weight < w)
            biggest_weight = w;

        n_edges++;
        w_sum += w;

    }



    // for (int i = 0; i < n_nodi; i++) {
    //     printf("Sono il nodo di indice %d nell'array\n", i);
    //     printf("Il valore del nodo e' %d\n", V[i]);
    //     printf("La lista di adiacenza e'\n");
    //     list_print(E[i]);
    // }

    cout << "biggest_number: " << biggest_weight << endl;
    //graph_print();
    cout << "w_sum: " << w_sum << endl;
    cout << "n_edges: " << n_edges << endl;


    float average_weight = w_sum / n_edges;
    cout << "average weight: " << average_weight << endl;

    // int best_path = 0;
    // int best_index;
    // int path_weight;

    // for(int i = 0; i < n_nodi; i++){

    //     path_weight = average_path(i);

    //     for(int j = 0; j < n_nodi; j++)
    //         V_visitato[j] = 0;

    //     if(path_weight > best_path){

    //         best_path = path_weight;
    //         best_index = i;
    //     }

    //     //cout << "path_weight: " << path_weight << " con partenza da " << i << endl;
        

    // }

    // cout << "best_path: " << best_path << " con partenza da " << best_index << endl;


    // for(int i = 0; i < n_nodi; i++){
    //     E[i] = NULL;

    //     E[i] = list_new();

    //     if (i == 0)
    //         global_ptr_ref = E[i];
    // }


    // for(int i = 1; i < n_nodi; i++){
    //     if(V_prev[i] == -1){
    //         //cout << i << " non ha prev" << endl;
    //     }
    //     else{
    //         int u = V_prev[i];

    //         int v = i;

    //         int w = V_dist[v];
    //         list_insert_front(E[u],i,w);
    //     }
    // }
    

    // for(int i = 0; i < n_nodi; i++){

    //     node_t* elem = E[i]->head;

    //     while(elem != NULL){

    //         elem->w = biggest_weight - elem->w;

    //         elem = elem->next;

    //     }

    // }

    // //graph_print();

    for(int i = 0; i < n_nodi; i++){

        shortest_path(i);

        // for(int j = 0; j < n_nodi; j++){

        //     cout << "distance from " << j << ": " << V_dist[j] << endl;

        // }

        //cout << "effettuato shortest path: " << i << endl;

        E_2 = new list_t *[n_nodi];

        for(int j = 0; j < n_nodi; j++){
            E_2[j] = NULL;

            E_2[j] = list_new();

            V_visitato[j] = 0;

            if (j == 0)
                global_ptr_ref = E_2[j];
        }

        //cout << "superata allocazione E_2" << endl;


        for(int j = 0; j < n_nodi; j++){
            if(V_prev[j] == -1){
                //cout << i << " non ha prev" << endl;
            }
            else{
                int u = V_prev[j];

                int v = j;

                int w = V_dist[v] - V_dist[u];
                list_insert_front(E_2[u],j,w);

                V_prev[j] = -1;
                
            }
        }

        for(int j = 0; j < n_nodi; j++){

            V_dist[j] = INFTY;

        }

        //cout << "superato inserimento" << endl;

        //graph_print();

        int result = DFS_weight_path(i,0);

        //cout << "result: " << result << endl;
    
    }


    if (graph) {
        /// preparo footer e chiudo file
        output_graph << "}" << endl;
        output_graph.close();
        cout << " File graph.dot scritto" << endl
             << "****** Creare il grafo con: neato graph.dot -Tpdf -o graph.pdf" << endl;
    }

    return 0;
}
