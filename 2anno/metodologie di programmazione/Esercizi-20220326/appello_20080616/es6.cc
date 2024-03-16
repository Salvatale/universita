#include <iostream>

struct Sched{}

void foo(Sched& v, Sched& w, unsigned n) {
    get_mutex_for(v);
    try {
        get_mutex_for(w);
        try {
            transmit(v, w, n);
            release_mutex_for(w);
            release_mutex_for(v);
        }
        catch (...) {
            release_mutex_for(w);
            throw;
        }
    }   
    catch (...) {
        release_mutex_for(v);
        throw;
    }
}

// è exception safe solo se release mutex e get mutex gestiscono le eccezioni all'interno della propria funzione

//inizializzazione RAII

class Mutex{
    private:
        Mutex& operator=(const Mutex& m);
        Mutex(const Mutex& m);
        const Sched* s;
        Mutex();
    public:
        Mutex(const Sched& sc){
            s = &sc;
            get_mutex_for(s);
        }
        ~Mutex(){
            release_mutex_for(s);
            s = nullptr;
        }
        const Sched* const get_Sched(){
            return s;
        }

};

void foo(Sched& v,Sched& w,unsigned n){
    Mutex v1(v);
    Mutex w1(w);
    transmit(w1.get_Sched(),v1.get_Sched(),n);
}