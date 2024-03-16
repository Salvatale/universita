template <typename T>
class Container {
public:
    Container(int size)
    : sz(size), ps(new T[sz]) {
    }
    ~Container() {
    delete ps;
    }
    private:
    T* ps;
    unsigned int sz;
};

/*
Il problema è che prima inizializziamo ps con un array di interi
di una dimensione casuale dato che sz contiene una secchiata di bit
casuali.
Il problema è che potrebbe anche contenere un numero negativo e
quindi potrebbe dare un errore.

*/

//Correzione:

template <typename T>
class Container {
public:
    Container(int size)
    : sz(size), ps(new T[sz]) {
    }
    ~Container() {
    delete ps;
    }
    private:
    unsigned int sz;
    T* ps;
};

/*
si comporta bene in presenza di eccezioni perchè se si verifica
un'eccezione durante la costruzione allora l'oggetto non viene costruito e invece se si
verifica un'eccezione in qualche altro punto, allora l'oggetto
verrebbe distrutto una volta finito il suo lifetime.
*/