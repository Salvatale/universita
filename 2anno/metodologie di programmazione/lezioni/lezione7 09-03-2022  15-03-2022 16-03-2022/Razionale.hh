// #pragma once

#ifndef NUMERICA_RAZIONALE_HH_GUARDIA
#define NUMERICA_RAZIONALE_HH_GUARDIA 1

#include <iostream>
#include <numeric>
/*
Dato che <numeric> funziona solo dallo standard c++2017, ci sono due possibili soluzioni.
La prima è definire a modo nostro la funzione gcd che ci serve.
La seconda è inidcare al nostro compilatore di compilare secondo uno standard
da utilizzare.
Esempio: g++ -Wall -Wextra -std=c++17 -o Razionale.o -c Razionale.cc
*/
#include <cassert>

namespace Numerica {

    class Razionale {
    public:
        using Integer = long;
        
        //COSTRUTTORI DI DEFAULT

        //Razionale() = default;   //Dico che mi sta bene l'implementazione di default
                                 // del compilatore
                                 // butterebbe due secchiate di bit casuali dentro num e den.
        /*
        Razionale(const Razionale&) = default;
        Razionale(Razionale&&) = default;
        //Razionale& operator=(const Razionale&) = default;
        const Razionale& operator=(const Razionale&);
        Razionale& operator=(Razionale&&) = default;
        ~Razionale() = default;
        */

        //COSTRUTTORI DEFINITI DA UTENTE

        Razionale() : Razionale(0,1) {}
        //Metodo alternativo 
        //Razionale() : Razionale(0) {}
        //explicit Razionale(const Integer& num = 0)
        //    :Razionale(num, 1) {}   //delegating constructor
        // conoscendo come effettuare l'implementazione allora si può ottimizzare
        //Razionale() : num_(0), den_(1) {assert(check_inv());}

        //Razionale(const Integer& num);
        explicit Razionale(const Integer& num)
            :Razionale(num, 1) {}   //delegating constructor

        Razionale(const Integer& num, const Integer& den)
            : num_(num),den_(den){
            //proprietà invariante di classe
            //implementazione che assicura la canonicità

            assert(den != 0);   //controllo precondizioni

            if(num == 0){
                den_ = 1;
                //qui controlla invariate prima di ritornare l'oggetto
                assert(check_inv());
                return;
            }
            if(den < 0){
                num_ = -num_;
                den_ = -den_;
            }
            Integer gcd = std::gcd(num_,den_);
            if (gcd != 1){
                num_ /= gcd;
                den_ /= gcd;
            }
            // qui controlla invariante
            /*if(!check_inv()) {
                std::cerr << "Aiuto!!!!!!!";
            }*/
            assert(check_inv());
            /*
            Se assert ritorna falso allora si chiama una funzione abort che fa terminare
            il programma in quel determinato punto.
            Succede quando si compila il programma in modalità di debugging.
             */
        }


        //Metodo alternativo
        //explicit Razionale(const Integer& num, const Integer& den = 1);
        //altro metodo dove svolge anche il ruolo di costruttore di default
        //explicit Razionale(const Integer& num = 0, const Integer& den = 1);

        //Operatori binari
        /*Razionale operator+(const Razionale& y) const {  // restituisco per valore e non per riferimento
                                                        //perchè senno diventerebbe dandling
            Razionale res = *this;
            res += y;
            return res;
        }
        Razionale operator-(const Razionale& y) const;
        Razionale operator*(const Razionale& y) const;
        Razionale operator/(const Razionale& y) const;                                                    
        */

        //Operatori unari
        Razionale operator+() const {
            assert(check_inv());
            return *this;
        }
        void negate() {
            assert(check_inv());
            num_ = -num_;
            assert(check_inv());
        }
        Razionale operator-() const {
            const Razionale& x = *this;
            assert(x.check_inv());
            Razionale res = x;
            res.negate();
            return res;
        }

        //Op assign
        Razionale& operator+=(const Razionale& y){
            Razionale& x = *this;
            //assert(x.check_inv() && y.check_inv());
            // si cerca di tenere separato il controllo così si capisce chi
            // non soddisfa l'invariante
            assert(x.check_inv());
            assert(y.check_inv());
            // fai la cosa giusta
            x.num_ = x.num_ * y.den_ + x.den_ * y.num_;
            x.den_ = x.den_ * y.den_;
            semplifica();   //funzione che semplifica il nostro razionale.
            assert(x.check_inv()); // controllo invarianti in uscita
            //Il controllo su y non lo facciamo dato che era dichiarata const.
            return x;
        }
        Razionale& operator-=(const Razionale& y){
            Razionale& x = *this;
            assert(x.check_inv());
            assert(y.check_inv());
            x.num_ = x.num_ * y.den_ - x.den_ * y.num_;
            x.den_ = x.den_ * y.den_;
            semplifica();
            assert(x.check_inv());
            return x;
        }
        Razionale& operator*=(const Razionale& y){
            Razionale& x = *this;
            assert(x.check_inv());
            assert(y.check_inv());
            x.num_ *= y.num_;
            x.den_ *= y.den_;
            semplifica();
            assert(x.check_inv());
            return x;
        }
        Razionale& operator/=(const Razionale& y){
            Razionale& x = *this;
            assert(x.check_inv());
            assert(y.check_inv());
            assert(y.num_ != 0);    //controllo precondizioni.
            x.num_ *= y.den_;
            x.den_ *= y.num_;
            semplifica();
            assert(x.check_inv());
            return x;
        }

        //Incrementi e Decrementi
        Razionale& operator++(){
            Razionale& x = *this;
            assert(x.check_inv());
            x.num_ += x.den_;
            assert(x.check_inv());
            return x;
        }
        Razionale& operator--();
        //post
        //Razionale operator++();     //però avremmo lo stesso nome qualificato della funzione
                                    //e il numero e tipo di argomenti, ma ha un diverso tipo
                                    //del valore di ritorno
        //Razionale operator--();
        //soluzione post
        Razionale operator++(int){
            Razionale& x = *this;
            Razionale res = x;
            ++x;
            return res;
        }
        Razionale operator--(int);

        //Operatori Relazionali
        bool operator==(const Razionale& y) const{
            assert(check_inv() && y.check_inv());
            return num_ == y.num_ && den_ == y.den_;
        }
        bool operator<(const Razionale& y) const;

        /*
        bool operator!=(const Razionale& y) const;
        bool operator<=(const Razionale& y) const;
        bool operator>=(const Razionale& y) const;
        bool operator>(const Razionale& y) const;
        */

        //OUTPUT e INPUT
        //std::ostream& operator<<(std::ostream& os) const;
        //std::istream& operator>>(std::istream& os);
        //questo però viola il principio di sorpresa minima dato che funziona solo
        //se si scrive r >> std::cin;

        //Controllo della proprietà invariante
        bool check_inv() const{ //controlla che la proprietà invariante sia 
                                //soddisfatta su quest'oggetto
            if(num_ == 0)
                return den_ == 1;
            if(den_ <= 0)
                return false;
            if(std::gcd(num_,den_) != 1)
                return false;
            //invariante soddisfatta
            return true;
        }

        const Integer& num() const {
            assert(check_inv());
            return num_;
        }

        const Integer& den() const {
            assert(check_inv());
            return den_;
        }
        //Se si volesse accedere in scrittura:
        /*
        Integer& den() {
            assert(check_inv());
            return den_;
        }
        Risulta essere un disastro dato che abbiamo messo i dati in privato
        appunto per non poterli modificare liberamente e quindi non rispettare
        più la proprieta invariante.
        */


    private:
        Integer num_;
        Integer den_;
        /*
        Si utilizza un _ perchè i parametri che si passano ai costruttori hanno nomi
        uguali di solito e per evitare confusione li distinguiamo con _.
        Si mette in fondo e non davanti _den o _num perchè i nomi che iniziano con _
        di solito sono riservati al sistema e quindi lasciati ad altri utenti esterni.
        Il doppio __ non dovrebbe mai essere utilizzato, perchè sono riservati per 
        l'implementazione del linguaggio in qualunque scope.
        */
    };

}   //namespace Numerica

std::ostream& operator<<(std::ostream& os, const Numerica::Razionale& r);
std::istream& operator>>(std::istream& os,Numerica::Razionale& r);
//Non basta guardare solo la classe per conoscere l'interfaccia della classe,
//infatti questi due operatori fanno parte dell'implementazioni ma sono fuori dalla
//classe.
//L'idea è che se si prende una funzione e la si dichiara nell header file della
//classe e la distribuisco insieme allora chi vuole utilizzare quella classe allora
//vuole utilizzare anche quella funzione.Intituivamente fa parte dell'interfaccia.

/*inline
Razionale::Razionale(const Integer& num, const Integer& den)
            : num_(num),den_(den){
            //proprietà invariante di classe
            //implementazione che assicura la canonicità
            if(num == 0){
                den_ = 1;
                return;
            }
            if(den < 0){
                num_ = -num_;
                den_ = -den_;
            }
            Integer gcd = std::gcd(num_,den_);
            if (gcd != 1){
                num_ /= gcd;
                den_ /= gcd;
            }
        }
Questa sarebbe l'implementazione del costruttore fatta all'esterno della classe
ma all'interno dell header file oppure si dovrebbe fare l'implementazione magari
dentro un altro file che contiene l'implemetazione della classe Razionale.
*/
inline Numerica::Razionale
operator+(const Numerica::Razionale& x, const Numerica::Razionale& y){
    Numerica::Razionale res = x;
    res += y;
    return res;
}
inline Numerica::Razionale
operator-(const Numerica::Razionale& x, const Numerica::Razionale& y){
    Numerica::Razionale res = x;
    res -= y;
    return res;
}
inline Numerica::Razionale
operator*(const Numerica::Razionale& x, const Numerica::Razionale& y){
    Numerica::Razionale res = x;
    res *= y;
    return res;
}
inline Numerica::Razionale
operator/(const Numerica::Razionale& x, const Numerica::Razionale& y){
    Numerica::Razionale res = x;
    res /= y;
    return res;
}
/*
Metodo alternativo dell'operatore +, dal punto di vista dell'utente non cambia nulla,
Avendo estratto questa funzione fuori dalla classe e non avendola dichiarata friend,
abbiamo reso esplicito che questa funzione viene implementata senza sapere la
rappresentazione interna della classe, quindi viene implementata utilizzando gli
altri metodi, se dovessimo cercare ad un'errore nell'implementazione della classe,
sappiamo di già che l'errore non avviene dentro la classe ma dentro i metodi della
classe.
Se una funzione non deve fare accesso ai dati privati della classe, tanto vale
implementarla come funzione esterna alla classe.
*/
inline bool 
operator!=(const Numerica::Razionale& x,const Numerica::Razionale& y) const {
    return !(x == y);
}

inline bool 
operator<=(const Numerica::Razionale& x,const Numerica::Razionale& y) const;
bool operator>=(const Numerica::Razionale& x,const Numerica::Razionale& y) const;

inline bool 
operator>(const Numerica::Razionale& x,const Numerica::Razionale& y) const{
    return y < x;
}

#endif  //ifndef NUMERICA_RAZIONALE_HH_GUARDIA