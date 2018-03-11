#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "o3ds.h"

class Triangulo{
public:
    int a;
    int b;
    int c;
    Triangulo();
    Triangulo(int uno, int dos, int tres);
    void asignar(int uno, int dos, int tres);
};

#endif // TRIANGULO_H
