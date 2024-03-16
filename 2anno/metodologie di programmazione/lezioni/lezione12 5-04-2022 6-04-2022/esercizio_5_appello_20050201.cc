//5. Utilizzando gli algoritmi generici forniti dalla libreria standard, implementare la funzione

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <deque>

bool
inizia_con_carattere(const std::string& s) {
    return !s.empty() && s[0] == 'c';
}

void f(const std::vector<std::string>& vs,const char /*c*/) {

    std::vector<std::string> temp;
    temp.resize(vs.size());

    //auto out = temp.begin();
    //out = copy_if(vs.begin(), vs.end(), out, inizia_con_carattere);
    //sort(temp.begin(),out);

    /*for(auto i = temp.begin(); i != out; ++i)
        std::cout << *i << std::endl;
    */

    //std::ostream_iterator<std::string> cout_iter(std::cout, "\n");
    //copy(temp.begin(), out, cout_iter);

    //Ogni volta che deve inserire, lo inserisce in fondo
    copy_if(vs.begin(), vs.end(),
            std::back_inserter(temp), inizia_con_carattere);

    sort(temp.begin(),temp.end());
    std::ostream_iterator<std::string> cout_iter(std::cout, "\n");
    cout_iter = copy(temp.begin(), temp.end(), cout_iter);

    std::deque<std::string> temp1;
    copy_if(vs.begin(), vs.end(),
            std::front_inserter(temp), inizia_con_carattere);

    sort(temp.begin(),temp.end());
    std::ostream_iterator<std::string> cout_iter(std::cout, "\n");
    cout_iter = copy(temp.begin(), temp.end(), cout_iter);
}


/*
che stampa, in ordine lessicografico, tutte le stringhe in vs che iniziano con
il carattere c.
Fornire una versione alternativa nella quale si inverte l’ordine di stampa.
Il mio iteratote di output lavora in sovrascrittura
*/


int main()
{
    std::vector<std::string> vs = {"cane", "gatto", "canarino"};

    f(vs,'c');
}
