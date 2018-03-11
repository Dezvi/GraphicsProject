#include "caja.h"

Caja::Caja()
{
     textura = SOIL_load_OGL_texture("/home/manuel/Escritorio/texturas/dia.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
     if(textura == 0)
         printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
     else
         cout << "Imagen cargada correctamente -- " << SOIL_last_result() <<endl;

     glBindTexture(GL_TEXTURE_2D, textura);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);

     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
     glTexImage2D(GL_TEXTURE_2D,0,10,2,2,0,GL_RGBA,GL_UNSIGNED_BYTE,&textura);
}

void Caja::draw(char opcion){
    calcularNormales();
    double m = 5, n = 5, ancho = 5, alto = 5;
    if(opcion == 'a'){
    glPushMatrix();
        glPolygonMode(GL_FRONT,GL_FILL);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glBindTexture (GL_TEXTURE_2D, textura);
            for(double i = 0; i<m;++i){
                for(double j = 0; j<n;++j){
                    glColor3f(0.8,0.8,0.8);
                    glBegin (GL_TRIANGLES);
                        glTexCoord2f (i/m, j/n);
                        glVertex3f ((i*ancho)/m, (j*alto)/n, 0.0);
                        glTexCoord2f ((i+1)/m, j/n);
                        glVertex3f ((i+1)*ancho/m, (j*alto)/n, 0.0);
                        glTexCoord2f ((i+1)/m, (j+1)/n);
                       glVertex3f ((i+1)*ancho/m, (j+1)*alto/n, 0.0);
                        glTexCoord2f (i/m, j/n);
                        glVertex3f ((i*ancho)/m, (j*alto)/n, 0.0);
                        glTexCoord2f ((i+1)/m, (j+1)/n);
                        glVertex3f ((i+1)*ancho/m, (j+1)*alto/n, 0.0);
                        glTexCoord2f (i/m, (j+1)/n);
                        glVertex3f ((i*ancho)/m, (j+1)*alto/n, 0.0);
                    glEnd ();
                }
            }
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    }else if(opcion == 'b'){
        glPushMatrix();
            glPolygonMode(GL_FRONT,GL_FILL);
                for(double i = 0; i<m;++i){
                    for(double j = 0; j<n;++j){
                        if(i != 2 || j != 2){
                        glColor3f(0,0,0);
                        glBegin (GL_TRIANGLES);
                            glVertex3f ((i*ancho)/m, (j*alto)/n, 0.0);
                            glVertex3f ((i+1)*ancho/m, (j*alto)/n, 0.0);
                            glVertex3f ((i+1)*ancho/m, (j+1)*alto/n, 0.0);
                            glEnd ();
                            glColor3f(1,1,1);
                            glBegin (GL_TRIANGLES);
                            glVertex3f ((i*ancho)/m, (j*alto)/n, 0.0);
                            glVertex3f ((i+1)*ancho/m, (j+1)*alto/n, 0.0);
                            glVertex3f ((i*ancho)/m, (j+1)*alto/n, 0.0);
                        glEnd ();
                        }
                    }
                }
                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                glBindTexture (GL_TEXTURE_2D, textura);
                glColor3f(0.8,0.8,0.8);
                for(double i = 2; i<3;++i){
                    for(double j = 2; j<3;++j){
                        glBegin (GL_TRIANGLES);
                            glTexCoord2f (0, 0);
                            glVertex3f ((i*ancho)/m, (j*alto)/n, 0.0);
                            glTexCoord2f (1, 0);
                            glVertex3f ((i+1)*ancho/m, (j*alto)/n, 0.0);
                            glTexCoord2f (1, 1);
                            glVertex3f ((i+1)*ancho/m, (j+1)*alto/n, 0.0);
                            glTexCoord2f (0, 0);
                            glVertex3f ((i*ancho)/m, (j*alto)/n, 0.0);
                            glTexCoord2f (1, 1);
                            glVertex3f ((i+1)*ancho/m, (j+1)*alto/n, 0.0);
                            glTexCoord2f (0, 1);
                            glVertex3f ((i*ancho)/m, (j+1)*alto/n, 0.0);
                        glEnd ();
                    }
                }
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }else if(opcion == 'c'){
        glPushMatrix();
            glPolygonMode(GL_FRONT,GL_FILL);
                for(double i = 0; i<m;++i){
                    for(double j = 2; j<n;++j){
                        glColor3f(0,0,0);
                        glBegin (GL_TRIANGLES);
                            glVertex3f ((i*ancho)/m, (j*alto)/n, 0.0);
                            glVertex3f ((i+1)*ancho/m, (j*alto)/n, 0.0);
                            glVertex3f ((i+1)*ancho/m, (j+1)*alto/n, 0.0);
                            glEnd ();
                            glColor3f(1,1,1);
                            glBegin (GL_TRIANGLES);
                            glVertex3f ((i*ancho)/m, (j*alto)/n, 0.0);
                            glVertex3f ((i+1)*ancho/m, (j+1)*alto/n, 0.0);
                            glVertex3f ((i*ancho)/m, (j+1)*alto/n, 0.0);
                        glEnd ();
                    }
                }
                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                glBindTexture (GL_TEXTURE_2D, textura);
                glColor3f(0.8,0.8,0.8);
                for(double i = 0; i<m;++i){
                    for(double j = 0; j<2;++j){
                        glBegin (GL_TRIANGLES);

                        glTexCoord2f (i/m, j/n+0.6);
                        glVertex3f ((i*ancho)/m, (j*alto)/n, 0.0);
                        glTexCoord2f ((i+1)/m, j/n+0.6);
                        glVertex3f ((i+1)*ancho/m, (j*alto)/n, 0.0);
                        glTexCoord2f ((i+1)/m, (j+1)/n+0.6);
                        glVertex3f ((i+1)*ancho/m, (j+1)*alto/n, 0.0);
                        glTexCoord2f (i/m, j/n+0.6);
                        glVertex3f ((i*ancho)/m, (j*alto)/n, 0.0);
                        glTexCoord2f ((i+1)/m, (j+1)/n+0.6);
                        glVertex3f ((i+1)*ancho/m, (j+1)*alto/n, 0.0);
                        glTexCoord2f (i/m, (j+1)/n+0.6);
                        glVertex3f ((i*ancho)/m, (j+1)*alto/n, 0.0);
                        glEnd ();
                    }
                }
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
}
