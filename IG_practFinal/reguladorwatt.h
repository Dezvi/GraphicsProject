#ifndef REGULADORWATT_H
#define REGULADORWATT_H

#include "cilindroBrazos.h"
#include "brazopr.h"

class reguladorWatt : public CilindroBrazos, public BrazoPr
{
    double angulo;
    double vel_rot;
public:
    reguladorWatt();
    void draw(char a);
    void grado1(double angulo, char a);
    void grado23(double angulo, char a);
    void grados(double movimiento, double angulo, char a);
    bool animacion(int velocidad, char a, bool cambio, bool para);
};

#endif // REGULADORWATT_H
