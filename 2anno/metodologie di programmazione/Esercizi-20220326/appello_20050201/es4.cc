

class Scheda_Prepagata {
public:
    enum Tipo_Scheda { PAGA_DI_PIU, COSTO_RANDOM, PAGA_LA_MAMMA };
    Tipo_Scheda tipo_scheda() const;
    void addebita_chiamata(const Chiamata& call);
    // ...
private:
    void fai_la_cosa_giusta_1(const Chiamata& call);
    void fai_la_cosa_giusta_2(const Chiamata& call);
    void fai_la_cosa_giusta_3(const Chiamata& call);
    // ...
};


void Scheda_Prepagata::addebita_chiamata(const Chiamata& call) {
    switch (tipo_scheda()) {
    case PAGA_DI_PIU:
        fai_la_cosa_giusta_1(call);
        break;
    case COSTO_RANDOM:
        fai_la_cosa_giusta_2(call);
        break;
    case PAGA_LA_MAMMA:
        fai_la_cosa_giusta_3(call);
        break;
}
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Scheda_Prepagata.hh

class Scheda_Prepagata {
public:
    virtual Tipo_Scheda tipo_scheda() const = 0;
    virtual void addebita_chiamata(const Chiamata& call) = 0;
    virtual ~Scheda_Prepagata(){}
};

/////////////////////////////////////////////////////////////////////////////////////////

//PAGA_DI_PIU.hh
class PAGA_DI_PIU : public Scheda_Prepagata{
public:
    Tipo_Scheda tipo_scheda()const override{}
    void addebita_chiamata(const Chiamata& call){
        fai_la_cosa_giusta_1(call);
    }


};


/////////////////////////////////////////////////////////////////////////////////////////

//COSTO_RANDOM.hh
class COSTO_RANDOM : public Scheda_Prepagata{
public:
    Tipo_Scheda tipo_scheda()const override{}
    void addebita_chiamata(const Chiamata& call){
        fai_la_cosa_giusta_2(call);
    }
};

/////////////////////////////////////////////////////////////////////////////////////////

//PAGA_LA_MAMMA.hh
class PAGA_LA_MAMMA : public Scheda_Prepagata{
public:
    Tipo_Scheda tipo_scheda()const override{}
    void addebita_chiamata(const Chiamata& call){
        fai_la_cosa_giusta_3(call);
    }
};