#include <iostream>


template<typename Iter, typename T>
//scorre la sequenza dall'inizio fino alla fine e
//restituisce il primo elemento uguale ad elem
Iter find(Iter first, Iter last, const T& elem) {
    for( ; first != last; ++first) {
        if(*first == elem)
            return first;
    }
    return last;
}

/*
La find potrebbe utilizzare un input iterator e lo si può rendere
specifico nel nome
*/
template<typename InIter, typename T>
InIter find(InIter first, InIter last, const T& elem) {
    for( ; first != last; ++first) {
        if(*first == elem)
            return first;
    }
    return last;
}

/*
Ma se volessimo non un elemento preciso ma magari il primo numero
primo presente nella sequenza:
    Questa funzione find non funziona quindi proviamo find_if
*/

template<typename Iter, typename UnaryPred>
Iter find_if(Iter first, Iter last, UnaryPred pred) {
    for( ; first != last; ++first) {
        //fai la cosa giusta
        if(pred(*first))
            return first;
    }
    //restituisce l'ultimo elemento, compito dell'utente verificare
    //che sia quello giusto
    return last;
}

bool e_una_vocale(char c);

void foo(const std::string& s) {
    auto posizione_kappa = find(s.begin(), s.end(), 'k');
    if(posizione_kappa == s.end())
        std::cout << "Non ce ne stanno";
    else
        // qualcosa
    
    auto posizione_kappa2 = find(std::begin(s), std::end(s), 'k');

    auto posizione_vocale = find_if(std::begin(s), std::end(s), e_una_vocale);
}

/*
Gli passiamo un predicato unario che è una funzione che restituisce
un valore booleano ed è unario perchè prende un solo argomento,
gli diamo l'elemento della nostra sequenza e se è true si ferma
sennò continua con la sequenza.

*/

template<typename Iter, typename T>
unsigned long
count(Iter first, Iter last, const T& elem) {
    unsigned long num = 0;
    for( ; first != last; ++first) {
        //fai la cosa giusta
        if(*first == elem)
            ++num;
    }
    return num;
}

template<typename Iter, typename Unary_Pred>
unsigned long
count_if(Iter first, Iter last, Unary_Pred pred) {
    unsigned long num = 0;
    for( ; first != last; ++first) {
        //fai la cosa giusta
        if(pred(*first))
            ++num;
    }
    return num;
}


/*
La funzione count indica quanti elementi uguale ad elem ci sono nella sequenza
*/

template<typename Iter, typename UnaryPred>
bool
all_of(Iter first, Iter last, UnaryPred pred) {
    for( ; first != last; ++first) {
        //fai la cosa giusta
        if(!pred(*first))
            return false;
    }
    return true;
}

template<typename Iter, typename UnaryPred>
bool
any_of(Iter first, Iter last, UnaryPred pred) {
    for( ; first != last; ++first) {
        //fai la cosa giusta
        if(pred(*first))
            return true;
    }
    return false;
}


//replace
/*
cercami tutte le occorrenze con questo valore e me le rimpiazzi con quest'altro
valore.
*/

template <typename Iter, typename T>
void
replace(Iter first, Iter last, const T& x, const T& y) {
    for( ; first != last; ++first) {
        if(*first == x)
            *first = y;
    }
}

/*
sostituisce con il valore di y tutte le occorrenze che rispettano un determinato
predicato verbale
*/

template <typename Iter, typename UnaryPred, typename T>
void
replace(Iter first, Iter last, UnaryPred pred, const T& y) {
    for( ; first != last; ++first) {
        if(pred(*first))
            *first = y;
    }
}

/*
prende una sequenza e la copia all'interno di un'altra sequenza
Per lo standard quando si deve lavorare in scrittura su una sequenza, si
mette in modalità di sovrascrittura.
*/

template <typename Iter, typename OutIter>
OutIter
copy( Iter first /*sequenza_input */, Iter last, OutIter out /*sequenza_output*/) {
    for( ; first != last; ++first, ++out) {
        *out = *first;
        //++out;
        //++first;
    }
    return out;
}

template <typename Iter,typename UnaryPred, typename OutIter>
OutIter
copy_if( Iter first /*sequenza_input */, Iter last,UnaryPred pred, OutIter out /*sequenza_output*/) {
    for( ; first != last; ++first) {
        if(pred(*first)) {
        *out = *first;
        ++out;
        }
    }
    return out;
}

/*
Ad ogni elemento della sequenza, esegui questa operazione
*/

template<typename Iter, typename UnaryFun>
void
for_each( Iter first, Iter last, UnaryFun fun) {
    for( ; *first != last; ++first ) {
        fun(*first);
    }
}

// Se una determinata sequenza è ordinata
template <typename Iter>
bool
is_sorted(Iter first, Iter last) {
    if(first == last)
        return true;

    Iter next = first;
    ++next;

    for( ; next != last; ++first, ++next) {
        if(*next < *first)
            return false;
    }
    return true;
}
/*
In questo caso con gli iteratori di input potrebbe esserci un undefined behaviour
dato che andiamo a leggere di nuovo first che è il vecchio iteratore, non leggiamo
il vecchio valore che volevamo ma magari un valore già aggiornato e quindi serve
un forward iterator.
*/


// verifica se è ordinato secondo un criterio di confronto

template <typename Iter, typename Cmp>
bool
is_sorted(Iter first, Iter last, Cmp cmp) {
    if(first == last)
        return true;

    Iter next = first;
    ++next;

    for( ; next != last; ++first, ++next) {
        if(cmp(*next, *first))
            return false;
    }
    return true;
}

/*
fai l'unione di due insiemi, sequenze già ordinate e senza duplicati, quindi
fa la merge
*/

template <typename Iter, typename Out>
Out
set_union(Iter first1, Iter last1,
          Iter first2, Iter last2,
          Out out);


template<typename Iter1, typename Iter2>
Iter1
find_first_of(Iter1 first1, Iter1 last1, //dove cerco
                   Iter2 first2, Iter2 last2) { //cosa cerco
    for( ; first1 != last1; ++first1) {
        for( Iter2 i2 = first2; i2 != last2; ++i2)
        //fai la cosa giusta
        if(*first1 == *i2)
            return first1;
    }
    return last1;
}