#include <iostream>

/*
La find potrebbe utilizzare un input iterator e lo si può rendere
specifico nel nome
Iteratore di Input
*/
template<typename InIter, typename T>
InIter find(InIter first, InIter last, const T& elem) {
    for( ; first != last; ++first) {
        if(*first == elem)
            return first;
    }
    return last;
}



//Forward Iterator

template <typename FwdIter>
bool
is_sorted(FwdIter first, FwdIter last) {
    if(first == last)
        return true;

    FwdIter next = first;
    ++next;

    for( ; next != last; ++first, ++next) {
        if(*next < *first)
            return false;
    }
    return true;
}

template <typename FwdIter, typename Cmp>
bool
is_sorted(FwdIter first, FwdIter last, Cmp cmp) {
    if(first == last)
        return true;

    FwdIter next = first;
    ++next;

    for( ; next != last; ++first, ++next) {
        if(cmp(*next, *first))
            return false;
    }
    return true;
}

template<typename Iter1, typename FwdIter2>
Iter1
find_first_of(Iter1 first1, Iter1 last1, //dove cerco
                   FwdIter2 first2, FwdIter2 last2) { //cosa cerco
    for( ; first1 != last1; ++first1) {
        for( FwdIter2 i2 = first2; i2 != last2; ++i2)
        //fai la cosa giusta
        if(*first1 == *i2)
            return first1;
    }
    return last1;
}

/*
Per il primo iteratore è sufficiente un Input Iterator, invece nel secondo
serve un forward Iterator dato che deve essere riavvolgibile.
*/