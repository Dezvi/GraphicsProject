#include "esfera.h"

#define PI 3.14159265

Esfera::Esfera()
{
    const double incr_ang = PI /100;

    for(int i = 50;i>=-50;--i){
            perfil.push_back({cos(incr_ang*i),sin(incr_ang*i),0});
    }

    revolucion(30);
    makeTriangles();
    calcularNormales();
    calcularNormalesSmooth();
}
