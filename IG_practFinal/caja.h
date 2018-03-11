#ifndef CAJA_H
#define CAJA_H

#include "cubo.h"
#include "SOIL/SOIL.h"

class Caja : public Cubo
{
protected:
    unsigned int textura;
public:
    Caja();
    void draw(char opcion);
};

#endif // CAJA_H
