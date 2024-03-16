#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <queue>
#include <stack>

using namespace std;

// compilazione: g++ lezione7-13-tree-dot.c
//

// Alberi binari

// Obiettivo:
// 1) struttura dati, allocazione nodo, inserimento manuale nodi
// 2) creazione albero random

// 3) visita inorder
// 4) visita preorder, postorder

// 5) delete albero
// 6) euler tour: stampa e ricostruzione albero da lista nodi

// 7) flip albero

// 8) height - depth
// 9) isBalanced

int ct_swap = 0;
int ct_cmp = 0;
int ct_op = 0; /// operazioni per la ricerca
int ct_it = 0;

int max_dim = 0;
int ntests = 1;
int ndiv = 1;
int details = 0;
int graph = 0;

int n = 0; /// dimensione dell'array
int tree_dim = 0;

/// file di output per grafo
ofstream output_graph;
int n_operazione = 0; /// contatore di operazioni per visualizzare i vari step

ofstream output_visit;
ifstream input_visit;

//////////////////////////////////////////////////
/// Definizione della struttura dati tree
//////////////////////////////////////////////////

/// struct per il nodo dell'albero
typedef struct node {
    int val;
    struct node *L;
    struct node *R;

    // Se è vero allora il percorso L-L è isomorfo
    bool path = false;
    //Se è vero allora il percorso L-R è isomorfo
    bool opposite_path = false;
    // se è falso allora noi confrontiamo sempre dx-dx e sx-sx, se è vero allora confrontiamo sempre dx-sx e sx-dx
    bool change_path = false;
    //Se è vero allora il suo sottoalbero è isomorfo.
    bool is_ok = false;
    //Se è vero allora il suo sottoalbero non è isomorfo.
    bool is_not_ok = false;

} node_t;

//////////////////////////////////////////////////
/// Fine Definizione della struttura dati tree
//////////////////////////////////////////////////

/// Questo e' un modo per stampare l'indirizzo node relativamente ad un altro di riferimento.
/// Permette di ottenere offset di piccola dimensione per essere facilmente visualizzati
/// Nota: il metodo non e' robusto e potrebbe avere comportamenti indesiderati su architetture diverse
/// L'alternativa corretta' e' utilizzare %p di printf: es. printf("%p\n",(void*) node);
/// con lo svantaggio di avere interi a 64 bit poco leggibili

node_t *global_ptr_ref = NULL; /// usato per memorizzare il puntatore alla prima lista allocata

int get_address(void *node) {
    if (node == NULL)
        return 0;
    return (int)((long)node - (long)global_ptr_ref);
}

/// stampa il codice del nodo per dot
void print_node_code(node_t *n) {
    output_graph << "node_" << get_address(n) << "_" << n_operazione;
}

void node_print_graph(node_t *n) {

    print_node_code(n);
    output_graph << "\n[label=<\n<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\" >\n<TR> <TD CELLPADDING=\"3\" BORDER=\"0\"  ALIGN=\"LEFT\" bgcolor=\"#f0f0f0\" PORT=\"id\">";
    output_graph << get_address(n) << "</TD> </TR><TR>\n<TD PORT=\"val\" bgcolor=\"#a0FFa0\">";
    output_graph << n->val << "</TD>\n <TD PORT=\"L\" ";
    if (n->L == NULL)
        output_graph << "bgcolor=\"#808080\"> NULL";
    else
        output_graph << "> " << get_address(n->L);
    output_graph << "</TD>\n <TD PORT=\"R\" ";
    if (n->R == NULL)
        output_graph << "bgcolor=\"#808080\"> NULL";
    else
        output_graph << "> " << get_address(n->R);
    output_graph << "</TD>\n</TR></TABLE>>];\n";

    /// visualizzazione figli sullo stesso piano
    if (n->L != NULL && n->R != NULL) {
        output_graph << "rank = same; ";
        print_node_code(n);
        output_graph << ";";
        print_node_code(n->L);
        output_graph << ";\n";
    }

    // mostro archi uscenti

    if (n->L != NULL) { /// disegno arco left
        print_node_code(n);
        output_graph << ":L:c -> ";
        print_node_code(n->L);
        output_graph << ":id ;\n";
    }

    if (n->R != NULL) { /// disegno arco R
        print_node_code(n);
        output_graph << ":R:c -> ";
        print_node_code(n->R);
        output_graph << ":id ;\n";
    }
}

void tree_print_rec_graph(node_t *n) {
    if (n != NULL) {
        node_print_graph(n);
        tree_print_rec_graph(n->L);
        tree_print_rec_graph(n->R);
    }
}

void tree_print_graph(node_t *n) {
    /// stampa ricorsiva del nodo
    tree_print_rec_graph(n);
    n_operazione++;
}

void node_print(node_t *n) {
    if (n == NULL)
        printf("Puntatore vuoto\n");
    else
        printf("allocato in %d [Val: %d, L: %d, R: %d]\n",
               get_address(n),
               n->val,
               get_address(n->R),
               get_address(n->L));
}

node_t *node_new(int elem) { /// crea nuovo nodo
    node_t *t = new node_t;
    if (details) {
        printf("nodo creato\n");
    }

    t->val = elem;
    t->L = NULL;
    t->R = NULL;
    if (details) {
        printf("Imposto a NULL children\n");
    }

    return t;
}

void tree_insert_child_L(node_t *n, int elem) {
    /// inserisco il nuovo nodo con contenuto elem
    /// come figlio Left del nodo n

    /// creo nodo
    n->L = node_new(elem);
}

void tree_insert_child_R(node_t *n, int elem) {
    /// inserisco il nuovo nodo con contenuto elem
    /// come figlio Right del nodo n
    n->R = node_new(elem);
}

int max_nodes = 100;
int n_nodes = 0;

void insert_random_rec(node_t *n) {
    //// inserisce in modo random un nodo L e R e prosegue ricorsivamente
    /// limito i nodi interni totali, in modo da evitare alberi troppo grandi

    //printf("inserisco %d\n", n_nodes);

    if (n_nodes++ >= max_nodes) /// limito il numero di nodi
        return;
    //printf("inserisco %d\n", n_nodes);

    float probabilita = 0.5; /// tra 0 e 1

    if (rand() % 100 < probabilita * 100) { // se numero random e' minore della probabilita' -> aggiungo nodo R con valore a caso
        tree_insert_child_R(n, rand() % 100);
        tree_dim++;
    }
    if (rand() % 100 < probabilita * 100) { // se numero random e' minore della probabilita' -> aggiungo nodo L con valore a caso
        tree_insert_child_L(n, rand() % 100);
        tree_dim++;
    }
    if (n->L != NULL)
        insert_random_rec(n->L);
    if (n->R != NULL)
        insert_random_rec(n->R);
}

int ct_visit = 0;

void inOrder(node_t *n) {

    if (n->L != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":id:w -> ";
            print_node_code(n->L);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }

        inOrder(n->L);

        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->L);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":val:s [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }

    if (details)
        printf("%d ", n->val);

    if (graph) {
        node_print_graph(n);
    }

    if (n->R != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":val:s -> ";
            print_node_code(n->R);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
        inOrder(n->R);
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->R);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":id:e [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }
}

void preOrder(node_t *n) {

    if (details)
        printf("%d ", n->val);

    if (graph) {
        node_print_graph(n);
    }

    if (n->L != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":id:w -> ";
            print_node_code(n->L);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }

        preOrder(n->L);

        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->L);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":val:s [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }

    if (n->R != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":val:s -> ";
            print_node_code(n->R);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
        preOrder(n->R);
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->R);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":id:e [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }
}

void postOrder(node_t *n) {

    if (n->L != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":id:w -> ";
            print_node_code(n->L);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }

        postOrder(n->L);

        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->L);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":val:s [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }

    if (n->R != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":val:s -> ";
            print_node_code(n->R);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
        postOrder(n->R);
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->R);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":id:e [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }

    if (details)
        printf("%d ", n->val);

    if (graph) {
        node_print_graph(n);
    }
}

void EulerOrder(node_t *n) {

    if (details)
        printf("%d ", n->val);

    output_visit << n->val << "\n";

    if (graph) {
        node_print_graph(n);
    }

    if (n->L != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":id:w -> ";
            print_node_code(n->L);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }

        EulerOrder(n->L);

        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->L);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":val:s [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }

    if (details)
        printf("%d ", n->val);
    output_visit << n->val << "\n";

    if (n->R != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":val:s -> ";
            print_node_code(n->R);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
        EulerOrder(n->R);
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->R);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":id:e [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }

    if (details)
        printf("%d ", n->val);
    output_visit << n->val << "\n";
}

/// crea una copia dell'albero in input, scambiando i sottoalberi L e R
node_t *flip(node_t *n) {
    node_t *n1 = node_new(n->val);

    /// chiamate ricorsive

    return n1;
}

// costruzione albero in base ai valori stampati dalla visita di eulero
// la funzione restituisce il puntatore alla radice dell'albero
// Es. input: 32 74 74 64 76 76 44 44 44 76 64 64 74 32 85 85 2 36 36 36 2 85 85 85 2 85 32
node_t *build_euler() {

    return NULL;
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

// Questo è l'algoritmo per verificare se due alberi sono uguali, è ricorsivo ed appena trova un'incongruenza ritorna false.
bool equals(node_t* root1, node_t* root2){

    if(root1 == NULL && root2 == NULL)
        return true;

    if((root1 != NULL && root2 == NULL) || 
        (root1 == NULL && root2 != NULL))
        return false;
    
    if((root1 != NULL && root2 != NULL)
        && (root1->val == root2->val)
        && (equals(root1->L,root2->L))
        && (equals(root1->R,root2->R)))
        return true;
    
    return false;

}

// Algoritmo iterativo per verificare se due alberi sono isomorfi.
// Sfrutto le code e gli stack per simulare una ricorsione, controllo quanti figli ha un nodo:
//  - Se il numero corrisponde allora vado avanti
//  - Sennò devo tornare sui miei passi estrando dalla coda.
bool is_isomorphism(node_t* root1, node_t* root2){

    if(root1 == NULL && root2 == NULL)
        return true;

    if(root1 == NULL || root2 == NULL)
        return false;

    int counter1 = 0;
    int counter2 = 0;

    if(root1->L != NULL)
        counter1++;
    if(root1->R != NULL)
        counter1++;
    if(root2->L != NULL)
        counter2++;
    if(root2->R != NULL)
        counter2++;

    if(counter1 != counter2)
        return false;

    queue<node_t*> queue1;
    queue<node_t*> queue2;

    stack<node_t*> stack1;
    stack<node_t*> stack2;

    queue1.push(root1);
    queue2.push(root2);

    if((counter1 == 1) && (counter1 == counter2)){
        root1->path = true;

        stack1.push(root1);
        stack2.push(root2);

    }

    ct_it = 1;

    while(!queue1.empty() || !queue2.empty()){

        counter1 = 0;
        counter2 = 0;
        bool skip = false;

        node_t* node1 = queue1.front();
        node_t* node2 = queue2.front();

        ct_it++;
        
        //cout << "Estraggo: " << node1->val << ", " << node2->val << endl;

        queue1.pop();
        queue2.pop();


        if(node1->L != NULL)
            counter1++;
        if(node1->R != NULL)
            counter1++;
        if(node2->L != NULL)
            counter2++;
        if(node2->R != NULL)
            counter2++;

        //cout << "counter1: " << counter1 << ", counter2: " << counter2 << endl;

        if(node1->is_ok){
            if(node1 == root1)
                return true;

            node_t* node1 = stack1.top();
            node_t* node2 = stack2.top();

            //cout << "estraggo dallo stack node: " << node1->val << " quando is_ok" << endl;

            stack1.pop();
            stack2.pop();

            if((node1->change_path) && (!node1->opposite_path)){
                node1->opposite_path = true;

            }
            else if((node1->change_path) && (node1->opposite_path)){
                node1->is_ok = true;
            }
            else if((!node1->change_path) && (!node1->path)){
                node1->path = true;

            }
            else if((!node1->change_path) && (node1->path)){
                node1->is_ok = true;
            }

            queue1.push(node1);
            queue2.push(node2);

            skip = true;

        }
        if(node1->is_not_ok)
            return false;
        if(skip == false){
            //Se il numero di figli è uguale allora posso continuare in questo percorso.
            if(counter1 == counter2){
                // Se i figli sono due allora inserisco nello stack perche cosi nel caso posso estrarre dallo stack a cambiare il modo di confrontare.
                if(counter1 == 2){

                    //cout << "Quando counter = 2 allora inserisco nello stack: " << node1->val << endl;
                    stack1.push(node1);
                    stack2.push(node2);

                    //Inseriamo i figli nella coda in base al nostro metodo di confronto, quindi se change_path = true o false.
                    //Dopo controlliamo se dobbiamo inserire i figli dell'altro nostro sottoalbero, solo se uno tra path ed opposite path è true.

                    if((node1->change_path) && (!node1->opposite_path)){
                        queue1.push(node1->L);
                        queue2.push(node2->R);

                    }

                    if((node1->change_path) && (node1->opposite_path)){
                        queue1.push(node1->R);
                        queue2.push(node2->L);

                    }

                    if((!node1->change_path) && (!node1->path)){
                        queue1.push(node1->L);
                        queue2.push(node2->L);
                    }

                    if((!node1->change_path) && (node1->path)){
                        queue1.push(node1->R);
                        queue2.push(node2->R);
                    }


                }
                //Se uguale ad 1 allora metto l'unico figlio nella coda.
                if(counter1 == 1){
                    
                    //cout << "counter = 1 del nodo: " << node1->val << endl;
                    
                    if(node1->L != NULL)
                        queue1.push(node1->L);
                    if(node1->R != NULL)
                        queue1.push(node1->R);
                    if(node2->L != NULL)
                        queue2.push(node2->L);
                    if(node2->R != NULL)
                        queue2.push(node2->R);

                }

                if(counter1 == 0){
                    //Se non ha figli allora se è la radice torna vero perchè abbiamo due alberi composti solo dalla radice,
                    // sennò dobbiamo estrarre dallo stack i genitori e dato che nello stack metto solo i nodi che hanno due figli, evito di fare un altro ciclo e faccio i controlli.

                    if(node1 == root1)
                        return true;

                    node_t* node1 = stack1.top();
                    stack1.pop();
                    node_t* node2 = stack2.top();
                    stack2.pop();

                    //cout << "with counter == 0, estraggo dallo stack: " << node1->val << endl;



                    if((node1->change_path) && (!node1->opposite_path)){
                        node1->opposite_path = true;

                    }
                    else if((node1->change_path) && (node1->opposite_path)){
                        node1->is_ok = true;
                    }
                    else if((!node1->change_path) && (!node1->path)){
                        node1->path = true;
                    }
                    else if((!node1->change_path) && (node1->path)){
                        node1->is_ok = true;
                    }

                    queue1.push(node1);
                    queue2.push(node2);


                }

            }
            else{
                //Invece tiro fuori dallo stack e controllo se ancora non ho cambiato il metodo di confronto(change_path == false),
                // se true allora vuol dire che non c'è isomorfismo nel nodo e quindi ritornare sui nostri passi,
                // se false allora dobbiamo cominciare i confronti dx-sx e sx-dx.


                node_t* node1 = stack1.top();
                node_t* node2 = stack2.top();

                //cout << "with counter1 != counter2 estraggo dallo stack: " << node1->val << endl;

                if(node1->change_path)
                    node1->is_not_ok = true;
                
                if(!node1->change_path)
                    node1->change_path = true;

                queue1.push(node1);
                queue2.push(node2);


            }
        }


    }

    return true;



}

void insert_random_rec(node_t *n1, node_t *n2) {
    //// inserisce in modo random un nodo L e R e prosegue ricorsivamente
    /// limito i nodi interni totali, in modo da evitare alberi troppo grandi

    //printf("inserisco %d\n", n_nodes);

    if (n_nodes++ >= max_nodes) /// limito il numero di nodi
        return;
    //printf("inserisco %d\n", n_nodes);

    float probabilita = 0.5; /// tra 0 e 1

    if (rand() % 100 < probabilita * 100) { // se numero random e' minore della probabilita' -> aggiungo nodo R con valore a caso
        int element = rand() % 100;
        
        tree_dim++;

        tree_insert_child_R(n1, element);
        tree_insert_child_R(n2, element);
    }
    if (rand() % 100 < probabilita * 100) { // se numero random e' minore della probabilita' -> aggiungo nodo L con valore a caso
        int element = rand() % 100;

        tree_dim++;

        tree_insert_child_L(n1, element);
        tree_insert_child_L(n2, element);
    }
    if (n1->L != NULL)
        insert_random_rec(n1->L,n2->L);
    if (n1->R != NULL)
        insert_random_rec(n1->R,n2->R);
}

void insert_random_rec_diff_value(node_t *n1, node_t *n2) {
    //// inserisce in modo random un nodo L e R e prosegue ricorsivamente
    /// limito i nodi interni totali, in modo da evitare alberi troppo grandi

    //printf("inserisco %d\n", n_nodes);

    if (n_nodes++ >= max_nodes) /// limito il numero di nodi
        return;
    //printf("inserisco %d\n", n_nodes);

    float probabilita = 0.5; /// tra 0 e 1

    if (rand() % 100 < probabilita * 100) { // se numero random e' minore della probabilita' -> aggiungo nodo R con valore a caso
        
        tree_dim++;

        tree_insert_child_R(n1, rand() % 100);
        tree_insert_child_R(n2, rand() % 100);
    }
    if (rand() % 100 < probabilita * 100) { // se numero random e' minore della probabilita' -> aggiungo nodo L con valore a caso

        tree_dim++;

        tree_insert_child_L(n1, rand() % 100);
        tree_insert_child_L(n2, rand() % 100);
    }
    if (n1->L != NULL)
        insert_random_rec(n1->L,n2->L);
    if (n1->R != NULL)
        insert_random_rec(n1->R,n2->R);
}

void insert_opposite_random_rec(node_t *n1, node_t *n2) {
    //// inserisce in modo random un nodo L e R e prosegue ricorsivamente
    /// limito i nodi interni totali, in modo da evitare alberi troppo grandi

    //printf("inserisco %d\n", n_nodes);

    if (n_nodes++ >= max_nodes) /// limito il numero di nodi
        return;
    //printf("inserisco %d\n", n_nodes);

    float probabilita = 0.5; /// tra 0 e 1

    if (rand() % 100 < probabilita * 100) { // se numero random e' minore della probabilita' -> aggiungo nodo R con valore a caso
        int element = rand() % 100;
        
        tree_dim++;

        tree_insert_child_L(n1, element);
        tree_insert_child_R(n2, element);
    }
    if (rand() % 100 < probabilita * 100) { // se numero random e' minore della probabilita' -> aggiungo nodo L con valore a caso
        int element = rand() % 100;

        tree_dim++;
        tree_insert_child_R(n1, element);
        tree_insert_child_L(n2, element);
    }
    if (n1->L != NULL)
        insert_opposite_random_rec(n1->L,n2->R);
    if (n1->R != NULL)
        insert_opposite_random_rec(n1->R,n2->L);
}



int main(int argc, char **argv) {
    int i, test;

    if (parse_cmd(argc, argv))
        return 1;

    // init random
    srand((unsigned)time(NULL));

    if (graph) {
        output_graph.open("graph.dot");
        /// preparo header
        output_graph << "digraph g" << endl;
        output_graph << "{ " << endl;
        output_graph << "node [shape=none]" << endl;
        output_graph << "rankdir=\"TB\"" << endl;
        ;
        output_graph << "edge[tailclip=false,arrowtail=dot];" << endl;
    }

    node_t *root = node_new(5);
    global_ptr_ref = root;

    // tree_print_graph(root);
    // tree_insert_child_L(root, 7);
    // tree_print_graph(root);
    // tree_insert_child_L(root->L, 8);
    // tree_print_graph(root);
    // tree_insert_child_L(root->L->L, 1);
    // tree_print_graph(root);
    // tree_insert_child_L(root->L->L->L, 10);
    // tree_print_graph(root);

    // creo albero random
    node_t* root1 = node_new(1);
    node_t* root2 = node_new(1);
    node_t *root3 = node_new(2);
    node_t *root4 = node_new(2);
    node_t *root5 = node_new(3);
    node_t *root6 = node_new(3);
    node_t *root7 = node_new(4);
    node_t *root8 = node_new(4);


    tree_dim = 1;

    insert_random_rec(root1);
    int dim1 = tree_dim;

    tree_dim = 1;

    insert_random_rec(root2);
    int dim2 = tree_dim;

    
    cout << "DUE ALBERI RANDOM:" << endl;
    if(equals(root1,root2))
        cout << "The tree are equals" << endl;
    else
        cout << "The tree are not equals" << endl;
    
    if(is_isomorphism(root1,root2))
        cout << "The tree are isomorphism" << endl;
    else
        cout << "The tree are not isomorphism" << endl;
    cout << "tree dimension: " << dim1 << ", " << dim2  << " and number of iteration: " << ct_it << endl;
    
    tree_dim = 1;
    insert_random_rec(root3,root4);

    cout << "DUE ALBERI CON STESSA STRUTTURA E STESSI VALORI:" << endl;
    if(equals(root3,root4))
        cout << "The tree are equals" << endl;
    else
        cout << "The tree are not equals" << endl;
    if(is_isomorphism(root3,root4))
        cout << "The tree are isomorphism" << endl;
    else
        cout << "The tree are not isomorphism" << endl;

    cout << "tree dimension: " << tree_dim << " and number of iteration: " << ct_it << endl;

    tree_dim = 1;
    insert_random_rec_diff_value(root5,root6);
    
    cout << "DUE ALBERI CON STESSA STRUTTURA E DIVERSI VALORI:" << endl;
    if(equals(root5,root6))
        cout << "The tree are equals" << endl;
    else
        cout << "The tree are not equals" << endl;
    if(is_isomorphism(root5,root6))
        cout << "The tree are isomorphism" << endl;
    else
        cout << "The tree are not isomorphism" << endl;


    cout << "tree dimension: " << tree_dim << " and number of iteration: " << ct_it << endl;

    tree_dim = 11;
    tree_insert_child_L(root7,2);
    tree_insert_child_R(root7,3);
    tree_insert_child_L(root7->L,4);
    tree_insert_child_R(root7->L,5);
    tree_insert_child_R(root7->R,6);
    tree_insert_child_L(root7->L->L,7);
    tree_insert_child_R(root7->L->L,8);
    tree_insert_child_L(root7->L->R,9);
    tree_insert_child_L(root7->R->R,10);
    tree_insert_child_R(root7->R->R,11);


    tree_insert_child_L(root8,2);
    tree_insert_child_R(root8,3);
    tree_insert_child_R(root8->L,4);
    tree_insert_child_L(root8->R,5);
    tree_insert_child_R(root8->R,6);
    tree_insert_child_L(root8->L->R,7);
    tree_insert_child_R(root8->L->R,8);
    tree_insert_child_R(root8->R->L,9);
    tree_insert_child_L(root8->R->R,10);
    tree_insert_child_R(root8->R->R,11);



    cout << "DUE ALBERI CON STRUTTURA OPPOSTA E STESSI VALORI: " << endl;
    if(equals(root7,root8))
        cout << "The tree are equals" << endl;
    else
        cout << "The tree are not equals" << endl;
    if(is_isomorphism(root7,root8))
        cout << "The tree are isomorphism" << endl;
    else
        cout << "The tree are not isomorphism" << endl;

    cout << "tree dimension: " << tree_dim << "and number of iteration: " << ct_it << endl;
    

    // ct_visit = 0;
    // inOrder(root);
    // n_operazione++;
    // printf("\n");

    // ct_visit = 0;
    // preOrder(root);
    // n_operazione++;
    // printf("\n");

    // ct_visit = 0;
    // postOrder(root);
    // n_operazione++;
    // printf("\n");

    // stampa visita di eulero
    // output_visit.open("visit.txt");
    // ct_visit = 0;
    // EulerOrder(root);
    // n_operazione++;
    // output_visit.close();
    // printf("\n");

    // stampa albero
    
    if(graph){
        tree_print_graph(root1);
        tree_print_graph(root2);
        tree_print_graph(root3);
        tree_print_graph(root4);
        tree_print_graph(root5);
        tree_print_graph(root6);
        tree_print_graph(root7);
        tree_print_graph(root8);


    }
    

    
    if (graph) {
        /// preparo footer e chiudo file
        output_graph << "}" << endl;
        output_graph.close();
        cout << " File graph.dot scritto" << endl
             << "Creare il grafo con: dot graph.dot -Tpdf -o graph.pdf" << endl;
    }
    
        
    n_operazione++;

    /* scheletro per la costruzione dell'albero a partire dalla visita di eulero
    input_visit.open("visit.txt");
    node_t* root=build_euler();
    global_ptr_ref=root;
    input_visit.close();
    tree_print_graph(root);
    */

    /*
      node_t* root1=flip(root);
      tree_print_graph(root);
    */

    

    return 0;
}
