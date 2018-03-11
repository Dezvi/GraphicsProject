#include <o3d.h>


// This is how a vector is specified in the base code
    // The origin is assumed to be [0,0,0]

    void normalize (Vertex & v)
    {
    // calculate the length of the vector
    float len = (float)(sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));

    // avoid division by 0
    if (len == 0.0f)
    len = 1.0f;

    // reduce to unit size
    v.x /= len;
    v.y /= len;
    v.z /= len;
    }

// normal(); - finds a normal vector and normalizes it
   void normal (Vertex & a, Vertex & b, Vertex & c, Vertex & normal)
   {
   Vertex a1, b1;

   // calculate the vectors A and B
   // note that v[3] is defined with counterclockwise winding in mind
   // a
   a1.x = a.x - b.x;
   a1.y = a.y - b.y;
   a1.z = a.z - b.z;
   // b
   b1.x = b.x - c.x;
   b1.y = b.y - c.y;
   b1.z = b.z - c.z;

   // calculate the cross product and place the resulting vector
   // into the address specified by vertex_t *normal
   normal.x = (a1.y * b1.z) - (a1.z * b1.y);
   normal.y = (a1.z * b1.x) - (a1.x * b1.z);
   normal.z = (a1.x * b1.y) - (a1.y * b1.x);

   // normalize
   normalize(normal);
   }


void O3d::drawLines(){
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glLineWidth(1);
    glBegin(GL_TRIANGLES);
    unsigned int i = 0;
    while(i < especiales.size()*rnumero){
        glVertex3fv(especiales[triangulos[i].a].devolver());
        glVertex3fv(puntos[triangulos[i].b].devolver());
        glVertex3fv(puntos[triangulos[i].c].devolver());
        ++i;
    }
    while(i < triangulos.size()){
        glVertex3fv(puntos[triangulos[i].a].devolver());
        glVertex3fv(puntos[triangulos[i].b].devolver());
        glVertex3fv(puntos[triangulos[i].c].devolver());
        ++i;
    }
    glEnd();
}

void O3d::calcularNormales(){
    Vertex normalv;
    unsigned int i = 0;
    normalCon.resize(triangulos.size());
    if(regular){
        while(i < triangulos.size()){
            normal(puntos[triangulos[i].a], puntos[triangulos[i].b], puntos[triangulos[i].c], normalv);
            normalCon[i]=normalv;
            ++i;
        }
    }else{
        while(i < especiales.size()*rnumero){
            normal(especiales[triangulos[i].a], puntos[triangulos[i].b], puntos[triangulos[i].c], normalv);
            normalCon[i]=normalv;
            ++i;
        }
        while(i < triangulos.size()){
            normal(puntos[triangulos[i].a], puntos[triangulos[i].b], puntos[triangulos[i].c], normalv);
            normalCon[i]=normalv;
            ++i;
        }
    }
}
void O3d::calcularNormalesSmooth(){
    adyacentes.resize(puntos.size());
    for(int i = 0; i < triangulos.size(); ++i){
        adyacentes[triangulos[i].a].push_back(i);
        adyacentes[triangulos[i].b].push_back(i);
        adyacentes[triangulos[i].c].push_back(i);
    }
    Vertex normalv;
    vector<double> mediaNX, mediaNY, mediaNZ;
    mediaNX.resize(adyacentes.size());
    mediaNY.resize(adyacentes.size());
    mediaNZ.resize(adyacentes.size());
    for(int i = 0; i < adyacentes.size(); ++i){
        for(int j = 0; j < adyacentes[i].size(); ++j){
            mediaNX[i] += normalCon[adyacentes[i][j]].x;
            mediaNY[i] += normalCon[adyacentes[i][j]].y;
            mediaNZ[i] += normalCon[adyacentes[i][j]].z;
        }
        mediaNX[i] /= adyacentes[i].size();
        mediaNY[i] /= adyacentes[i].size();
        mediaNZ[i] /= adyacentes[i].size();
        normalv.x = mediaNX[i];
        normalv.y = mediaNY[i];
        normalv.z = mediaNZ[i];
        normalize(normalv);
        normalVertex.push_back(normalv);
    }
}
void O3d::drawFillSmooth(bool ajedrez){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);
    if(!ajedrez)
        glColor3d(1,0,0);
    unsigned int i = 0;
    if(regular){
        while(i < triangulos.size()){
            if(ajedrez){
                if(i%2==0)
                    glColor3f(1,0,1);
                else
                    glColor3f(0,1,1);
            }
            glNormal3fv(normalVertex[triangulos[i].a].devolver());
            glVertex3fv(puntos[triangulos[i].a].devolver());
            glNormal3fv(normalVertex[triangulos[i].b].devolver());
            glVertex3fv(puntos[triangulos[i].b].devolver());
            glNormal3fv(normalVertex[triangulos[i].c].devolver());
            glVertex3fv(puntos[triangulos[i].c].devolver());
            ++i;
        }
    }else{
        while(i < especiales.size()*rnumero){
            if(ajedrez){
                if(i%2==0)
                    glColor3f(1,0,1);
                else
                    glColor3f(0,1,1);
            }
            glNormal3fv(normalVertex[triangulos[i].a].devolver());
            glVertex3fv(especiales[triangulos[i].a].devolver());
            glNormal3fv(normalVertex[triangulos[i].b].devolver());
            glVertex3fv(puntos[triangulos[i].b].devolver());
            glNormal3fv(normalVertex[triangulos[i].c].devolver());
            glVertex3fv(puntos[triangulos[i].c].devolver());
            ++i;
        }
        while(i < triangulos.size()){
            if(ajedrez){
                if(i%2==0)
                    glColor3f(1,0,1);
                else
                    glColor3f(0,1,1);
            }
            glNormal3fv(normalVertex[triangulos[i].a].devolver());
            glVertex3fv(puntos[triangulos[i].a].devolver());
            glNormal3fv(normalVertex[triangulos[i].b].devolver());
            glVertex3fv(puntos[triangulos[i].b].devolver());
            glNormal3fv(normalVertex[triangulos[i].c].devolver());
            glVertex3fv(puntos[triangulos[i].c].devolver());
            ++i;
        }
    }
    glEnd();
}
void O3d::drawFill(){
    glPolygonMode(GL_FRONT,GL_FILL);
    //glColor3d(1,0,0);
    glBegin(GL_TRIANGLES);
    unsigned int i = 0;
    if(regular){
        while(i < triangulos.size()){
            glNormal3fv(normalCon[i].devolver());
            glVertex3fv(puntos[triangulos[i].a].devolver());
            glVertex3fv(puntos[triangulos[i].b].devolver());
            glVertex3fv(puntos[triangulos[i].c].devolver());
            ++i;
        }
    }else{
        while(i < especiales.size()*rnumero){
            glNormal3fv(normalCon[i].devolver());
            glVertex3fv(especiales[triangulos[i].a].devolver());
            glVertex3fv(puntos[triangulos[i].b].devolver());
            glVertex3fv(puntos[triangulos[i].c].devolver());
            ++i;
        }
        while(i < triangulos.size()){
            glNormal3fv(normalCon[i].devolver());
            glVertex3fv(puntos[triangulos[i].a].devolver());
            glVertex3fv(puntos[triangulos[i].b].devolver());
            glVertex3fv(puntos[triangulos[i].c].devolver());
            ++i;
        }
    }
    glEnd();
}
void O3d::drawChest(){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);
    Vertex normalv;
    unsigned int i = 0;
    while(i < especiales.size()*rnumero){
        if(i%2==0)
            glColor3f(1,0,1);
        else
            glColor3f(0,1,1);
        normal(especiales[triangulos[i].a], puntos[triangulos[i].b], puntos[triangulos[i].c], normalv);
        glNormal3fv(normalCon[i].devolver());
        glVertex3fv(especiales[triangulos[i].a].devolver());
        glVertex3fv(puntos[triangulos[i].b].devolver());
        glVertex3fv(puntos[triangulos[i].c].devolver());
        ++i;
    }
    while(i < triangulos.size()){
        if(i%2==0)
            glColor3f(1,0,1);
        else
            glColor3f(0,1,1);
        normal(puntos[triangulos[i].a], puntos[triangulos[i].b], puntos[triangulos[i].c], normalv);
        glNormal3fv(normalCon[i].devolver());
        glVertex3fv(puntos[triangulos[i].a].devolver());
        glVertex3fv(puntos[triangulos[i].b].devolver());
        glVertex3fv(puntos[triangulos[i].c].devolver());
        ++i;
    }
    glEnd();
}


void O3d::plyVertexTriangles(vector<_vertex3f> Vertices, vector<_vertex3i> Triangles){
    puntos.resize(Vertices.size());
    for( unsigned int i = 0; i < Vertices.size(); ++i){
        puntos[i].x = Vertices[i][0];
        puntos[i].y = Vertices[i][1];
        puntos[i].z = Vertices[i][2];
    }
    triangulos.resize(Triangles.size());
    for( unsigned int i = 0; i < Triangles.size(); ++i){
        triangulos[i].a = Triangles[i][0];
        triangulos[i].b = Triangles[i][1];
        triangulos[i].c = Triangles[i][2];
    }
    calcularNormales();
    calcularNormalesSmooth();
}

