#include <vasoinv.h>

VasoInv::VasoInv(){
    perfil.resize(3);
    perfil[0].asignar(0,1,0);
    perfil[1].asignar(0.5,1,0);
    perfil[2].asignar(1,-1,0);
    revolucion(30);
    makeTriangles();
    calcularNormales();
    calcularNormalesSmooth();
}
