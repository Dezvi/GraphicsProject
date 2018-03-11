#ifndef BRAZOPR_H
#define BRAZOPR_H

#include "soporte.h"
#include "base.h"
#include "disco.h"

class BrazoPr : public Soporte, public Base, public Disco
{
public:
    BrazoPr();
    void draw(char a);
    void animacion(double angulo, char a);
};

#endif // BRAZOPR_H
