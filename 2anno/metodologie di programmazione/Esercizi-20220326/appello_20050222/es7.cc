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

/*errori: bisogna fare la delete[] ps per eliminare un allocazione di celle di memoria contigue,
bisogna invertire l'ordine delle due componenti private sennò si alloca l'array con una secchiata di bit casuali.
Per l'exception safe dovremmo definire il costruttore di copia o l'assegnamento perchè sennò di default
avremmo due oggetti che puntano allo stessa allocazione e faranno due delete.



*/

template <typename T>
class Container {
public:
    Container(int size)
    : size_(size), ps_(new T[sz]) {
    }
    ~Container() {
        delete []ps;
    }
private:
    unsigned int size_;
    T* ps_;
    Container& operator=(const Container& container){}
    Container(const Container& container){}
};