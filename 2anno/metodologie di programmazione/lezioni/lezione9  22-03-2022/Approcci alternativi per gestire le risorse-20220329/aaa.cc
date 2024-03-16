void foo() {

    Risorsa* r1 = acqu();
    Risorsa* r2 = acqu();

    try
    {
        usa(r1,r2);
        rilascia(r2);
        rilascia(r1);
    }
    catch(...)
    {
        rilascia(r2);
        rilascia(r1);
        throw;
    }
    
}


/*
Non funziona perchè se per caso l'acquisizione di r1 ha successo e non quella di r2
allora non si è ancora entrati nel try e nessuno entrerà nel catch e nessuno rilascia
r1.
*/