// File Generatore_Doc.hh
struct Generatore_Doc {
    virtual void stampa(const std::string& s) = 0;
    void link(const std::string& uri, const std::string& testo);
    virtual void grassetto(bool mode) = 0;
    virtual void corsivo(bool mode) = 0;
    ~Generatore_Doc() {}
};

// File Generatore_HTML.hh
#include "Generatore_Doc.hh"
    struct Generatore_HTML : private Generatore_Doc {
    void stampa(const std::string& s);
    void grassetto(bool mode);
    void corsivo(bool mode);
};
// File Generatore_PDF.hh
#include "Generatore_Doc.hh"
    struct Generatore_PDF : private Generatore_Doc {
    void stampa(const std::string& s);
    void grassetto(bool mode);
    void corsivo(bool mode);
    void salto_pagina();
};


// File Codice_Utente.cc
#include "Generatore_Doc.hh"
#include "Generatore_HTML.hh"
#include "Generatore_PDF.hh"
void codice_utente(Generatore_Doc* gdoc) {
gdoc->hyperlink("http://www.unipr.it", "UNIPR");
if (Generatore_PDF gpdf = dynamic_cast<Generatore_PDF>(gdoc))
gpdf->salto_pagina();
else
gdoc->stampa("<HR>"); // Simulo il cambio pagina in HTML.
}


//correzione
// File Generatore_Doc.hh
struct Generatore_Doc {
    virtual void stampa(const std::string& s) = 0;
    virtual void hyperlink(const std::string& uri, const std::string& testo) = 0;
    virtual void grassetto(bool mode) = 0;
    virtual void corsivo(bool mode) = 0;
    virtual void salto_pagina() = 0;
    virtual ~Generatore_Doc() {}
};

// File Generatore_HTML.hh
#include "Generatore_Doc.hh"
    struct Generatore_HTML : private Generatore_Doc {
    virtual void stampa(const std::string& s);
    virtual void hyperlink(const std::string& uri, const std::string& testo);
    virtual void grassetto(bool mode);
    virtual void corsivo(bool mode);
    virtual void salto_pagina(){
        stampa("<HR>");
    }
    virtual ~Generatore_HTML(){}
};
// File Generatore_PDF.hh
#include "Generatore_Doc.hh"
    struct Generatore_PDF : private Generatore_Doc {
    virtual void stampa(const std::string& s);
    virtual void hyperlink(const std::string& uri, const std::string& testo);
    virtual void grassetto(bool mode);
    virtual void corsivo(bool mode);
    virtual void salto_pagina();
    virtual ~Generatore_PDF(){}
};


// File Codice_Utente.cc
#include "Generatore_Doc.hh"
#include "Generatore_HTML.hh"
#include "Generatore_PDF.hh"

void codice_utente(Generatore_Doc* gdoc) {
    gdoc->hyperlink("http://www.unipr.it", "UNIPR");
    gdoc->salto_pagina();
}