#ifndef O3DS_H
#define O3DS_H

#include <vector>
#include "vertexp.h"

using namespace std;

class O3ds{
protected:
    vector<Vertex> puntos;
    vector<Vertex> especiales;
public:
    void drawPoints();

};

#endif // O3DS_H
