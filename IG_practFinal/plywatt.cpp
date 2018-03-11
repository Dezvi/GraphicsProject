#include "plywatt.h"


PlyWatt::PlyWatt()
{
    _file_ply file;
    vector<_vertex3f> Vertices;
    vector<_vertex3i> Triangles;
    file.open("/home/manuel/Escritorio/beethoven.ply");
    file.read(Vertices, Triangles);
    file.close();
    plyVertexTriangles(Vertices, Triangles);

}

void PlyWatt::draw(char a)
{
    glPushMatrix();
    glScalef(0.03,0.03,0.03);
    if(a == 'p')
        drawPoints();
    if(a == 'l')
        drawLines();
    if(a == 'f')
        drawFill();
    if(a == 's')
        drawFillSmooth(false);
    if(a == 'a')
        drawFillSmooth(true);
    if(a == 'c')
        drawChest();

    glPopMatrix();

}

