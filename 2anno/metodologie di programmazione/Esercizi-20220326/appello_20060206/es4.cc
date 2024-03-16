#include <list>
#include <vector>
using namespace std;
/*
template <typename T>
void f(const list<list<T> >& ll, list<T>& l) {
    for (typename list<list<T> >::const_iterator ll_i = ll.begin(),
        ll_end = ll.end(); ll_i != ll_end; ++ll_i)
    for (typename list<T>::const_iterator i = ll_i->begin(),
        i_end = ll_i->end(); i != i_end; ++i)
        l.push_back(*i);
}
*/

//Correzione
template <typename DoubleContainer, typename Container>
void f(const DoubleContainer& ll, Container& l) {
    for (typename Double_Container::const_iterator ll_i = ll.begin(),
        ll_end = ll.end(); ll_i != ll_end; ++ll_i)
        for (typename Container::const_iterator i = ll_i->begin(),
        i_end = ll_i->end(); i != i_end; ++i)
            l.push_back(*i);
}

//Altra modifica
template <typename DoubleContainerIter, typename ContainerIter>
void f(const DoubleContainerIter first1, DoubleContainerIter last1,ContainerIter last2,ContainerIter first2) {
    for (; first1 != last1; ++first1)
        for (; *first1 != last2; ++(*first1))
            first2->push_back(*first1);
}

int main(){
    list<list<int> > ll;
    list<int> l1;
    for (typename list<list<int> >::iterator ll_i = ll.begin(),
        ll_end = ll.end(); ll_i != ll_end; ++ll_i){
        for(int i = 0;i < 10;++i){
            ll_i->push_back(i);
        }
    }
    f(ll.begin(),ll.end(),)
}