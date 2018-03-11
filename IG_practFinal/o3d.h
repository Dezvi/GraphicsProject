#ifndef O3D_H
#define O3D_H


#include <o3ds.h>
#include <triangulo.h>
#include "vertex.h"


class O3d : public O3ds{
protected:
    bool regular = false;
    vector<Triangulo> triangulos;
    int rnumero;
    vector<Vertex> perfil;
    bool arriba;
    bool abajo;
    vector<Vertex> normalCon;
    vector<vector<int>> adyacentes;
    vector<Vertex> normalVertex;
public:
    void drawLines();
    void drawFill();
    void drawChest();
    void plyVertexTriangles(vector<_vertex3f> Vertices, vector<_vertex3i> Triangles);
    void calcularNormales();
    void calcularNormalesSmooth();
    void drawFillSmooth(bool ajedrez);

};

#endif // O3D_H
