/*8. Il seguente codice non ha un comportamento corretto in presenza di eccezioni (nota: si assume che le
funzioni lock e unlock facciano la cosa giusta e che la funzione unlock non possa lanciare eccezioni).
Individuare il problema, indicando la sequenza di operazioni che porta alla sua occorrenza, e
correggerlo applicando un numero minimo di modifiche al codice. Fornire quindi una soluzione
alternativa applicando l’idioma “l’acquisizione di risorse è una inizializzazione”.
*/

void f() {
    lock("lock1");
    try {
        lock("lock2");
    try {
        do_the_job();
        unlock("lock2");
        unlock("lock1");
    } catch (...) {
        unlock("lock2");
    }
    } catch (...) {
        unlock("lock1");
    }
}

/*

*/
//Correzione prima parte
void f() {
    lock("lock1");
    try {
        lock("lock2");
    try {
        do_the_job();
        unlock("lock2");
        unlock("lock1");
    } catch (...) {
        unlock("lock2");
        throw;  //neutralità
    }
    } catch (...) {
        unlock("lock1");
        throw;  //neutralità
    }
}

////////////////////////////////////
class Lock {
public:
    explicit Lock(const char* name)
        : name_(name) {
        lock(name_);
    }

    ~Lock() {
        unlock(name_);
    }

private:
    const char* name_;

    Lock(const Lock&);  //non implementato (copia non abilitata)
    Lock& operator=(const Lock&);   //non implementato (copia non abilitata)
};


void f_raii() {
    Lock lock1("lock1");
    Lock lock2("lock2");
    do_the_job();
}