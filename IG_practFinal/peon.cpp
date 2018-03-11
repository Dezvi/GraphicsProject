#include "peon.h"

Peon::Peon(vector<_vertex3f> &Vertices)
{
    perfil.resize(Vertices.size());
    for( unsigned int i = 0; i < Vertices.size(); ++i){
        perfil[i].x = Vertices[i][0];
        perfil[i].y = Vertices[i][1];
        perfil[i].z = Vertices[i][2];
    }
    revolucion(30);
    makeTriangles();
    calcularNormales();
    calcularNormalesSmooth();
}
