/*8. Il seguente codice non ha un comportamento corretto in presenza di eccezioni (nota: si assume che le
funzioni lock e unlock facciano la cosa giusta e che la funzione unlock non possa lanciare eccezioni).
Individuare il problema, indicando la sequenza di operazioni che porta alla sua occorrenza, e
correggerlo applicando un numero minimo di modifiche al codice. Fornire quindi una soluzione
alternativa applicando l’idioma “l’acquisizione di risorse è una inizializzazione”.*/


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
Il problema è che dato che unlock non può lanciare eccezioni allora questo codice non è neutrale,
se dentro il secondo try venisse lanciata un'eccezione allora riusciremmo a liberare lock2 ma non lock1
perchè il catch non rilancia l'eccezione a sua volta.
*/

//Correzione:

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
			throw;
		}
	} catch (...) {
		unlock("lock1");
	}
}

// Alternativa applicando idioma RAI:

class Lock{
private:
	const char* name_;
	Lock(){}
	Lock(const Lock& lock){}
	Lock& operator=(const Lock& lock){}
public:
	explicit Lock(const char* name) : name_(name){}
	~Lock(){
		unlock(name_);
	}

}

void f(){
	Lock lock1("lock1");
	Lock lock2("lock2");
	do_the_job();
}