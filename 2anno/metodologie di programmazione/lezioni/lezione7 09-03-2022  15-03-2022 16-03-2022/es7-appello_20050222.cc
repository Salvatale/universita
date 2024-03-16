#include <iostream>

template <typename T>
//class Set : public std::list<T> {
//C
//class Set : private std::list<T> {
class Set {
private:
    std::list<T> lista_;

public:
// Costruisce l’insieme vuoto.
Set();
// Costruisce il singoletto che contiene t.
//Set(T t);
//Correzione
explicit Set(const T& t);

//Set(Set y);
//Correzione
Set(const Set& y);

void operator=(Set y);

//virtual ~Set();
//Correzione
~Set();

//unsigned int size();
//Correzione
unsigned int size() const;

//bool is_empty();
//Correzione
bool is_empty() const
;
//bool contains(Set y);
//Correzione
bool contains(const Set& y) const;

//T& min();
//Correzione
const T& min() const;

void pop_min(){
    this->pop_front();
    lista_.pop_front();
}

//oppure senza ereditarietà
void pop_min() {
    lista_.pop_front();
}

//void insert(T z);
//Correzione
void insert(const T& z);

//void union_assign(Set y);
//C
void union_assign(const Set& y);


//void intersection_assign(Set y);
//C
void intersection_assign(const Set& y);

//void swap(Set y);
//C
void swap(Set& y);

//std::ostream operator<<(std::ostream os);
private:
// ...
};
//C
std::ostream&
operator<<(std::ostream& os,const Set& x);


/*
Set(); va bene perchè crea una lista vuota senza elementi.

Set(T t); in automatico un costruttore che prende un solo argomento funzionano
in automatico come operatori di conversione definita da utente.
Dato che non vogliamo che il parametro dato come argomento venga convertito dal sistema
e trasformato in un insieme di un solo elemento, allora possiamo scrivere explicit
nel caso in cui la si vuole implementare di proposito.
Aggiungiamo anche il riferimento e const dato che l'oggetto potrebbe essere un
oggetto molto grande e quindi passarlo per valore sarebbe costoso

Set(Set y) potrebbe creare un loop infinito dato che potrebbe prendere come
argomento il costruttore di copia stesso.

void operator=(Set y); Non posso concatenare gli assegnamenti in questo caso però.

T& min(); diamo la possibilita all'utente di rompere l'invariante in questo modo.

void swap(Set y); In questo caso volgiamo modificare l y passato dall'utente.

class Set : public std::list<T>  la classe Set eredita o estende pubblicamente
la classe list.
C'è una relazione di ereditarietà e quindi c'è una conversione che permette di
prendere un puntatore o un riferimento ad una classe derivata e trasformarlo
implicitamente ad uno della classe base e quindi l'utente potrebbe trasformare il
riferimento della classe derivata alla classe base tramite cast implicito.
Quindi l'utente potrebbe rompere l'invariante.
Possiamo considerare la list come dettaglio implementativo.
Con la correzione fatta allora l'upcast è possibile solo a chi può accedere ai metodi
friend oppure dall'implementatore ma non dall'utente.

*/