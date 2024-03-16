#include <iostream>
#include <iterator>


template <typename Iter,typename T>
void replace(Iter first, Iter last, const T& old_value, const T& new_value){
    for(; first != last; ++first){
        if(*first == old_value)
            *first = new_value;
    }

}

/*
Principi: gli iteratori forniti devono poter fare confronti tramite deferenziazione, poter accedere in scrittura e lettura, old_value e new_value
devono essere dello stesso tipo della collezione del contenitore fornito
*/