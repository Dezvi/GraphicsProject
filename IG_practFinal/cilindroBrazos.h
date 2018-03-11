#ifndef CILINDROTR_H
#define CILINDROTR_H

#include "disco.h"
#include "esferas.h"
#include "brazosinf.h"
#include "brazossup.h"

class CilindroBrazos : public BrazosSup, public BrazosInf, public Disco, public Palito
{
public:
    CilindroBrazos();
    void draw(char a);
    void grado23(double angulo, char a);
};

#endif // CILINDROTR_H
