#ifndef ANGOLO_GUARD
#define ANGOLO_GUARD 1

#include "Costante.hh"

class Angolo {
public:
    const static double piatto = Costante::pi / 2;
    const static double retto = Costante::pi;
    const static double giro = Costante::pi * 2;
};

#endif // ANGOLO_GUARD