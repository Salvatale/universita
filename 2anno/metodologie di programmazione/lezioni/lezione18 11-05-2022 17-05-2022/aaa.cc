#include <iostream>


void foo() {

    try {

        //.......
    }
    // stampiamo il tipo di eccezione verificata
    catch(const std::exception& e){
        std::cerr << e.what();
    }
    catch(const std::bad_cast& e){
        std::cerr << e.what();
    }
    //catturare sempre l'eccezione per riferimento
    //mai per valore sennò perdiamo alcune informazione
    //riguardo quell'eccezione
}