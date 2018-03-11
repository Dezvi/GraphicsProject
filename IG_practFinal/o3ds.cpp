#include "o3ds.h"

void O3ds::drawPoints(){
    glPointSize(2);
    glBegin(GL_POINTS);
    for(unsigned int j = 0; j<especiales.size();++j){
            glVertex3fv(especiales[j].devolver());
    }
    for(auto & val: puntos){
        glVertex3fv(val.devolver());
    }
    glEnd();
}
