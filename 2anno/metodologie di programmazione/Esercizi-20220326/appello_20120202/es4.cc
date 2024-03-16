class BasicProtocol {
private:
/*...*/
public:
    BasicProtocol();
    virtual ~BasicProtocol();
    bool BasicMsgA( /*...*/ );
    bool BasicMsgB( /*...*/ );
    bool BasicMsgC( /*...*/ );
};
class Protocol1 : public BasicProtocol {
public:
    Protocol1();
    ~Protocol1();
    bool DoMsg1( /*...*/ );
    bool DoMsg2( /*...*/ );
    bool DoMsg3( /*...*/ );
};
class Protocol2 : public BasicProtocol {
public:
    Protocol2();
    ~Protocol2();
    bool DoMsg1( /*...*/ );
    bool DoMsg2( /*...*/ );
    bool DoMsg3( /*...*/ );
    bool DoMsg4( /*...*/ );
    bool DoMsg5( /*...*/ );
};

/*
In questo caso si viola il principio Liskov Substitution principle dato che la classe derivata non è in rapporto IS_A ma semplicemente
utilizza alcuni suoi metodi soltanto, sarebbe meglio includere un oggetto all'interno delle classi in modo da poter utilizzare
quei metodi senza derivazione.
*/

class BasicProtocol {
private:
/*...*/
public:
    BasicProtocol();
    virtual ~BasicProtocol();
    bool BasicMsgA( /*...*/ );
    bool BasicMsgB( /*...*/ );
    bool BasicMsgC( /*...*/ );
};
class Protocol1 {
private:
    BasicProtocol bp;
public:
    Protocol1();
    ~Protocol1();
    bool DoMsg1( /*...*/ );
    bool DoMsg2( /*...*/ );
    bool DoMsg3( /*...*/ );
};
class Protocol2 {
private:
    BasicProtocol bp;
public:
    Protocol2();
    ~Protocol2();
    bool DoMsg1( /*...*/ );
    bool DoMsg2( /*...*/ );
    bool DoMsg3( /*...*/ );
    bool DoMsg4( /*...*/ );
    bool DoMsg5( /*...*/ );
};