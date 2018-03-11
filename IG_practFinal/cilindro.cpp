
#include <cilindro.h>

Cilindro::Cilindro(){
    perfil.resize(4);
    perfil[0].asignar(0,1,0);
    perfil[1].asignar(1,1,0);
    perfil[2].asignar(1,-1,0);
    perfil[3].asignar(0,-1,0);
    revolucion(30);
    makeTriangles();
    calcularNormales();
    calcularNormalesSmooth();
}

