

#include <cubo.h>

Cubo::Cubo(){
    puntos.resize(8);
    puntos[0].asignar(-0.5,-0.5,0.5);
    puntos[1].asignar(-0.5,-0.5,-0.5);
    puntos[2].asignar(0.5,-0.5,-0.5);
    puntos[3].asignar(0.5,-0.5,0.5);
    puntos[4].asignar(0.5,0.5,0.5);
    puntos[5].asignar(0.5,0.5,-0.5);
    puntos[6].asignar(-0.5,0.5,-0.5);
    puntos[7].asignar(-0.5,0.5,0.5);
    triangulos.resize(12);
    triangulos[0].asignar(0,1,3);
    triangulos[1].asignar(3,1,2);
    triangulos[2].asignar(0,7,1);
    triangulos[3].asignar(6,1,7);
    triangulos[4].asignar(3,4,0);
    triangulos[5].asignar(4,7,0);
    triangulos[6].asignar(5,4,3);
    triangulos[7].asignar(5,3,2);
    triangulos[8].asignar(6,5,2);
    triangulos[9].asignar(1,6,2);
    triangulos[10].asignar(4,5,7);
    triangulos[11].asignar(6,7,5);
    regular = true;
    calcularNormales();
    calcularNormalesSmooth();
}
