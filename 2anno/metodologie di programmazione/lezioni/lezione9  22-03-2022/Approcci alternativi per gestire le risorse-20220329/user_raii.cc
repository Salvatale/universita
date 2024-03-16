#include "risorsa_raii.hh"

//  RAII : Resource Acquisition Is Initialization
/*
L'acquisizione di risorse andrebbe fatta nella
fase di costruzione degli oggetti
*/

//  RRID : Resource Release Is Destruction
/* 
Il posto ideale per rilasciare le risorse è dentro
il distruttore
*/

void codice_utente() {
  Gestore_Risorsa r1;
  usa_risorsa_exc(r1.get());
  {
    Gestore_Risorsa r2;
    usa_risorse_exc(r1.get(), r2.get());
  } // r2 viene distrutta qui
  Gestore_Risorsa r3;
  usa_risorse_exc(r1.get(), r3.get());
} // r3 viene distrutta e subito dopo r1


