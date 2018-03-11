#ifndef TIERRA_H
#define TIERRA_H

#include "esfera.h"
#include "SOIL/SOIL.h"

class Tierra : public Esfera
{
protected:
    unsigned int textura;
    unsigned int textura_fondo;
public:
    Tierra();
    void drawFill();
    void drawFillSmooth();
};

#endif // TIERRA_H
