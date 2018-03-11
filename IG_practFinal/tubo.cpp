#include <tubo.h>

Tubo::Tubo(){
    perfil.resize(2);
    perfil[0].asignar(1,1,0);
    perfil[1].asignar(1,-1,0);
    revolucion(30);
    makeTriangles();
    calcularNormales();
    calcularNormalesSmooth();
}
