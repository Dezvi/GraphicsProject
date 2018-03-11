
#include "vertexp.h"

Vertex::Vertex(){
    x=0;
    y=0;
    z=0;
}
Vertex::Vertex(double a, double b, double c){
    x=a;
    y=b;
    z=c;
}

void Vertex::asignar(GLfloat a, GLfloat b, GLfloat c){
    x=a;
    y=b;
    z=c;
}
GLfloat* Vertex::devolver(){
    GLfloat* vert = new GLfloat[3];
    vert[0] = x;
    vert[1] = y;
    vert[2] = z;
    return vert;
}

