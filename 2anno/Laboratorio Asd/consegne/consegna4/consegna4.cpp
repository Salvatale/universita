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
int heap_size = 0;
const int MAX_SIZE = 256;

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
int* indici_heap; //tiene traccia del numero del nodo che si trova in posizione i in heap
int* indici_nodi_heap; // tiene traccia della posizione in heap dell'indice i di questo array
float* heap;    // array che contiene i valori di tipo float relative ai pesi degli archi.

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

int parent_idx(int n) {
    if (n == 0)
        return -1;
    return (n - 1) / 2;
}

int child_L_idx(int n) {
    if (2 * n + 1 >= heap_size)
        return -1;
    return 2 * n + 1;
}

int child_R_idx(int n) {
    if (2 * n + 2 >= heap_size)
        return -1;
    return 2 * n + 2;
}

/// restituisce 0 se il nodo in posizione n e' un nodo interno (almeno un figlio)
/// restituisce 1 se il nodo non ha figli
int is_leaf(int n) {
    return (child_L_idx(n) == -1); // non c'e' bisogno di controllare il figlio R

    /* versione equivalente
    if (child_L_idx(n)==-1)
      return 1;
    return 0;
    */
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

void heap_insert_min(int elem,int index) {
    /// inserisco il nuovo nodo con contenuto elem
    /// nell'ultima posizione dell'array
    /// ovvero continuo a completare il livello corrente

    if (details)
        printf("Inserisco elemento %d in posizione %d\n", elem, heap_size);

    cout << "elem: " << elem << " with index: " << index << endl;

    if (heap_size < MAX_SIZE) {
        int i = heap_size;
        indici_heap[i] = index;
        indici_nodi_heap[index] = i;
        heap_size++;

        heap[i] = elem;

        while (i != 0) {                          // non sono sulla radice
            if (heap[parent_idx(i)] <= heap[i]) { /// proprieta' dell' heap e' rispettata -> esco
                if (details)
                    printf("Il genitore ha valore %d >= del nodo %d, esco\n", heap[parent_idx(i)], heap[i]);
                return;
            }

            if (details)
                printf("Il genitore ha valore %d < del nodo %d, swap\n", heap[parent_idx(i)], heap[i]);
            /// il nodo ha un genitore sicuramente <   --> swap
            int t = heap[parent_idx(i)];
            heap[parent_idx(i)] = heap[i];
            heap[i] = t;

            int ind = indici_heap[parent_idx(i)];
            indici_heap[parent_idx(i)] = indici_heap[i];
            indici_heap[i] = ind;

            int p = indici_nodi_heap[ind];
            indici_nodi_heap[ind] = indici_nodi_heap[index];
            indici_nodi_heap[index] = p;



            //tree_print_graph(0); // radice
            // n_operazione++;

            i = parent_idx(i);
        }

    } else
        printf("Heap pieno!\n");
}
//Le uniche differenze sono solo le varie modifiche degli indici di indici_heap ed indici_nodi_heap.
void decrease_key(int indice_nodo, int key) {
    // key = nuovo valore

    if (indice_nodo < 0 || indice_nodo >= heap_size) {
        printf("Nodo non esistente\n");
        return;
    }

    if (heap[indice_nodo] < key) {
        printf("la chiave non e' piu' grande!\n");
        return;
    }

    heap[indice_nodo] = key;

    int i = indice_nodo;
    while (i != 0) {                          // non sono sulla radice
        if (heap[parent_idx(i)] <= heap[i]) { /// proprieta' dell' heap e' rispettata -> esco
            if (details)
                printf("Il genitore ha valore %d >= del nodo %d, esco\n", heap[parent_idx(i)], heap[i]);
            return;
        }

        if (details)
            printf("Il genitore ha valore %d < del nodo %d, swap\n", heap[parent_idx(i)], heap[i]);
        /// il nodo ha un genitore sicuramente <   --> swap
        int t = heap[parent_idx(i)];
        heap[parent_idx(i)] = heap[i];
        heap[i] = t;

        int ind = indici_heap[parent_idx(i)];
        indici_heap[parent_idx(i)] = indici_heap[i];
        indici_heap[i] = ind;

        int p = indici_nodi_heap[ind];
        indici_nodi_heap[ind] = indici_nodi_heap[i];
        indici_nodi_heap[i] = p;

        //tree_print_graph(0); // radice
        //n_operazione++;

        i = parent_idx(i);
    }
}

//Le uniche differenze sono solo le varie modifiche degli indici di indici_heap ed indici_nodi_heap.
float heap_remove_min() {

    if (heap_size <= 0) { /// heap vuoto!
        printf("Errore: heap vuoto\n");
        return -1;
    }

    float minimo = heap[0];

    if (details)
        printf("Massimo identificato %d\n", minimo);
    /// scambio la radice con l'ultima foglia a destra
    /// il massimo e' stato spostato in fondo --> pronto per l'eliminazione
    int t = heap[0];
    heap[0] = heap[heap_size - 1];
    heap[heap_size - 1] = t;

    int index = indici_heap[heap_size - 1];
    int index_0 = indici_heap[0];
    indici_heap[heap_size -1] = indici_heap[0];
    indici_heap[0] = index;

    indici_nodi_heap[index] = 0;
    indici_nodi_heap[index_0] = heap_size - 1;

    index = indici_heap[0];

    // elimino il massimo (ora in fondo all'array)
    heap_size--;

    //    tree_print_graph(0);  // radice

    /// nella radice c'e' un valore piccolo (minimo?)
    int i = 0; // indice di lavoro (parto dalla root)

    while (!is_leaf(i)) { /// garantisco di fermarmi alla foglia

        if (details)
            printf("Lavoro con il nodo in posizione i = %d, valore %d\n", i, heap[i]);

        int con_chi_mi_scambio = -1;

        /// controllo il nodo i con il suo figlio L
        if (heap[i] > heap[child_L_idx(i)]) { // il nodo i e' piu' piccolo
            /// attivare uno swap (la proprieta' heap non e' rispettata)
            con_chi_mi_scambio = child_L_idx(i);
            if (details)
                printf("Figlio L e' piu' grande (valore %d)\n", heap[child_L_idx(i)]);

            if (child_R_idx(i) >= 0 && // esiste il nodo destro
                heap[child_L_idx(i)] > heap[child_R_idx(i)]) {
                con_chi_mi_scambio = child_R_idx(i);
                if (details)
                    printf("Figlio R e' ancora piu' grande (valore %d)\n", heap[child_R_idx(i)]);
            }
        } else { // il nodo e' piu' grande del figlio L

            if (child_R_idx(i) >= 0) {                // esiste il figlio R
                if (heap[i] > heap[child_R_idx(i)]) { /// attivo lo swap
                    con_chi_mi_scambio = child_R_idx(i);
                    if (details)
                        printf("Figlio R e' piu' grande del nodo (valore %d)\n", heap[child_R_idx(i)]);
                } else
                    break;
            } else
                break;
        }

        /// swap tra i e con_chi_mi_scambio
        int t = heap[i];
        heap[i] = heap[con_chi_mi_scambio];
        heap[con_chi_mi_scambio] = t;

        int ind = indici_heap[con_chi_mi_scambio];
        indici_heap[con_chi_mi_scambio] = indici_heap[i];
        indici_heap[i] = ind;

        int p = indici_nodi_heap[ind];
        indici_nodi_heap[ind] = indici_nodi_heap[index];
        indici_nodi_heap[index] = p;


        i = con_chi_mi_scambio;

        // tree_print_graph(0);  // radice
        // n_operazione++;
    }

    return minimo;
}

void shortest_path(int n) {

    /*      V_visitato[i]=0;  // flag = non visitato
      V_prev[i]=-1;  // non c'e' precedente
      V_dist[i]=INFTY;  // infinito
    */

    //Prendo il nodo n di partenza ed imposto il valore della sua chiave a 0 dato che d(n,n) = 0, questa operazione la faccio con decrease key
    // che mi permette di modificare anche la struttura dell albero
    V_dist[n] = 0;
    decrease_key(n,0);

    int q_size = n_nodi; /// contatore degli elementi in coda (V_visitato)

    while (q_size != 0) {

        graph_print();

        int best_dist = INFTY;
        int best_idx = -1;

        if(heap_size > 0){
            //imposto come migliore indice quello contenuto nella prima posizione di indice_heap che poi sarà assegnato ad u
            best_idx = indici_heap[0];
            //Estraggo il min, ricostruisco il nuovo albero con il nuovo min in testa che ci servirà nella prossima iterazione del while.
            best_dist = heap_remove_min();
        }
        
        if (best_dist < INFTY) {
            /// estrai dalla coda
            /// trova il minimo in coda
            

            //cout << "prendo come best_idx: " << best_idx << " e best_dist: " << best_dist << endl;


            int u = best_idx;
            V_visitato[u] = 1;
            q_size--;

            /// esploro la lista di adiacenza
            //cout << "Visito la lista di adicenza di E[" << u << "]" << endl;
            node_t *elem = E[u]->head;
            while (elem != NULL) {
                int v = elem->val; /// arco u --> v
                //Dobbiamo capire dove si trova il nostro nodo v all'interno dell'heap, quindi mi basterà prelevarlo nell'array che ho creato per tenere traccia di questi indici
                //Cosi potremmo dare alla decrease key l'indice corretto del nostro nodo v all'interno di heap.
                int heap_index = indici_nodi_heap[v];

                /// alt ← dist[u] + Graph.Edges(u, v)
                float alt = V_dist[u] + elem->w; /// costo per arrivare al nuovo nodo passando per u
                //cout << u << " -> " << v << " : " << alt << endl;
                if (alt < V_dist[v]) {           // il percorso sorgente ---> u --> v migliora il percorso attuale sorgente --> v
                    V_dist[v] = alt;
                    V_prev[v] = u;
                    //Se non abbiamo ancora visitato allora decrementiamo la distanza per arrivare a v, magari può diventare il nuovo min nell'heap che poi estraiamo alla nuova iterazione
                    //Questa operazione non sarà effettuata nel caso avessimo già visitato quel nodo, dato che non ci interessa estrarlo di nuovo come min.
                    if(V_visitato[v] == 0)
                        decrease_key(heap_index,alt);

                }
                elem = elem->next;
            }

        } else { /// coda non vuota E nodi non raggiungibili ---> FINITO
            q_size = 0;
        }
    }

    graph_print();
}

int DFS(int n) {

    graph_print();

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

void Bellman_Ford(int n){
    
    V_dist[n] = 0;


    //Rilassiamo ogni arco almeno |V| - 1 volte, potremmo vedere evolvere le distanze ogni iterazione oppure rimanere immutate dato che potremmo avere già le
    //distanze minime alle prime iterazioni.
    for(int j = 1; j < n_nodi; j++){

        //Dobbiamo valutare ogni singolo arco, se avremmo un percorso migliore allora poi lo sistemeremo alla prossima iterazione di j.
        //Per ogni vertice prendiamo tutti gli archi e facciamo i confronti.
        for(int i = 0; i < n_nodi; i++){

            node_t* elem = E[j]->head;
            while(elem != NULL){

                int u = j;
                int v = elem->val;
                int w = elem->w;

                int alt = V_dist[u] + w;

                if(alt < V_dist[v]){
                    V_dist[v] = alt;
                    V_prev[v] = u;
                }

                elem = elem->next;

            }
        }
        //Facciamo una stampa del processo ogni volta che rilassiamo tutti gli archi. Potremmo avere anche stampe del grafo tutte uguali ad un certo punto delle iterazioni.
        graph_print();
    }

    //Qui ci sarebbe anche il controllo per la presenza di cicli negativi. La commento solo perchè nel main di prova non prevedo di inserire numeri negativi.
    // for(int i = 0; i < n_nodi; i++){

    //     node_t* elem = E[j]->head;
    //     while(elem != NULL){
    //         int u = j;
    //         int v = elem->val;
    //         int w = elem->w;

    //         int alt = V_dist[u] + w;

    //         if(alt < V_dist[v])
    //             cout << "Qui e' presente un ciclo negativo" << endl;

    //         elem = elem->next;

    //         }

    //graph_print();

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

    n_nodi = rand()%6 + 3;

    //// init nodi
    V = new int[n_nodi];
    V_visitato = new int[n_nodi];
    V_prev = new int[n_nodi];
    V_dist = new float[n_nodi];
    heap = new float[n_nodi];
    indici_heap = new int[n_nodi];
    indici_nodi_heap = new int[n_nodi];
    

    //// init archi
    E = new list_t *[n_nodi]; //(list_t**)malloc(n_nodi*sizeof(list_t*));

    // costruzione grafo
    for (int i = 0; i < n_nodi; i++) {
        V[i] = 2 * i;
        V_visitato[i] = 0; // flag = non visitato
        V_prev[i] = -1;    // non c'e' precedente
        V_dist[i] = INFTY; // infinito
        heap_insert_min(INFTY,i);

        E[i] = list_new();

        if (i == 0)
            global_ptr_ref = E[i];

        int x = i % N;
        int y = i / N;

        for(int j = 0; j < n_nodi; ++j){

            if(i != j){
                if(rand()%100 <= 50)
                    list_insert_front(E[i],j,rand()%15);
                //else
                //    list_insert_front(E[i],j,rand()%15 + 15);

            }

        }

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
    /*
    int partenza = 0;
    int arrivo = n_nodi - 1;
    int w_max = 100;
    
    for (int i = 0; i < n_nodi - 1; i++) {
        /// arco costoso
        list_insert_front(E[i], arrivo, w_max - 2 * i);
        /// arco 1
        if (i > 0)
            list_insert_front(E[i-1], i , 1);
    }
    */
    graph_print();

    for (int i = 0; i < n_nodi; i++) {
        printf("Sono il nodo di indice %d nell'array\n", i);
        printf("Il valore del nodo e' %d\n", V[i]);
        printf("La lista di adiacenza e'\n");
        list_print(E[i]);
    }

    //shortest_path(0);
    // shortest_path(44);
    int random = rand()%(n_nodi -1);
    Bellman_Ford(random);

    graph_print();

    for(int i = 0; i < n_nodi; i++){

        cout << "dist from " << i << " is " << V_dist[i] << endl;

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
