#include <tetraedro.h>


Tetraedro::Tetraedro(){
    puntos.resize(4);
    puntos[0].asignar(0,-0.20711,0.5);
    puntos[1].asignar(0.43301,-0.20711,-0.25);
    puntos[2].asignar(-0.43301,-0.20711,-0.25);
    puntos[3].asignar(0,0.5,0);
    triangulos.resize(4);
    triangulos[0].asignar(0,2,1);
    triangulos[1].asignar(0,1,3);
    triangulos[2].asignar(0,3,2);
    triangulos[3].asignar(1,2,3);
    regular = true;
    calcularNormales();
    calcularNormalesSmooth();
}
