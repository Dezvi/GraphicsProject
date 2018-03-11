#include "tierra.h"

Tierra::Tierra()
{
     textura = SOIL_load_OGL_texture("/home/manuel/Escritorio/texturas/dia.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
     if(textura == 0)
         printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
     else
         cout << "Imagen cargada correctamente -- " << SOIL_last_result() <<endl;

     glBindTexture(GL_TEXTURE_2D, textura);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);

     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
     glTexImage2D(GL_TEXTURE_2D,0,10,8192,4096,0,GL_RGBA,GL_UNSIGNED_BYTE,&textura);

     textura_fondo = SOIL_load_OGL_texture("/home/manuel/Escritorio/texturas/estrellas_8192.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
     if(textura_fondo == 0)
         printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
     else
         cout << "Imagen cargada correctamente -- " << SOIL_last_result() <<endl;

     glBindTexture(GL_TEXTURE_2D, textura_fondo);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);

     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
     glTexImage2D(GL_TEXTURE_2D,0,10,8192,4096,0,GL_RGBA,GL_UNSIGNED_BYTE,&textura_fondo);
}

void Tierra::drawFillSmooth(){
    calcularNormales();

    glPushMatrix();
        glPolygonMode(GL_FRONT,GL_FILL);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glBindTexture(GL_TEXTURE_2D, textura);
            glBegin(GL_TRIANGLES);
            float tx, ty, tx1, ty1, tx2, ty2;
            for(uint i = 0; i < triangulos.size(); i++){
              glColor3f(0.5,0.5,0.5);


              glNormal3fv(normalVertex[triangulos[i].a].devolver());

              tx = atan2(puntos[triangulos[i].a].x, puntos[triangulos[i].a].z) / (2. * M_PI) + 0.5;
              ty = asin(puntos[triangulos[i].a].y) / M_PI + .5;
              glTexCoord2f(tx, ty);
              glVertex3fv(puntos[triangulos[i].a].devolver());

              glNormal3fv(normalVertex[triangulos[i].b].devolver());

              tx1 = atan2(puntos[triangulos[i].b].x, puntos[triangulos[i].b].z) / (2. * M_PI) + 0.5;
              ty1 = asin(puntos[triangulos[i].b].y) / M_PI + .5;
              if(tx1 < 0.75 && tx > 0.75)
                tx1 += 1.0;
              else if(tx1 > 0.75 && tx < 0.75)
                tx1 -= 1.0;
              glTexCoord2f(tx1, ty1);
              glVertex3fv(puntos[triangulos[i].b].devolver());

               glNormal3fv(normalVertex[triangulos[i].c].devolver());

              tx2 = atan2(puntos[triangulos[i].c].x, puntos[triangulos[i].c].z) / (2. * M_PI) + 0.5;
              ty2 = asin(puntos[triangulos[i].c].y) / M_PI + .5;
              if(tx2 < 0.75 && tx1 > 0.75)
                tx2 += 1.0;
              else if(tx2 > 0.75 && tx1 < 0.75)
                tx2 -= 1.0;
              glTexCoord2f(tx2, ty2);
              glVertex3fv(puntos[triangulos[i].c].devolver());
            }
            glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
        glScalef(343.0,343.0,343.0);
        glPolygonMode(GL_BACK,GL_FILL);
        glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glBindTexture(GL_TEXTURE_2D, textura_fondo);
            glBegin(GL_TRIANGLES);
            for(uint i = 0; i < triangulos.size(); i++){
              glColor3f(1.0,1.0,1.0);

              tx = atan2(puntos[triangulos[i].a].x, puntos[triangulos[i].a].z) / (2. * M_PI) + 0.5;
              ty = asin(puntos[triangulos[i].a].y) / M_PI + .5;
              glTexCoord2f(tx, ty);
              glVertex3fv(puntos[triangulos[i].a].devolver());

              tx1 = atan2(puntos[triangulos[i].b].x, puntos[triangulos[i].b].z) / (2. * M_PI) + 0.5;
              ty1 = asin(puntos[triangulos[i].b].y) / M_PI + .5;
              if(tx1 < 0.75 && tx > 0.75)
                tx1 += 1.0;
              else if(tx1 > 0.75 && tx < 0.75)
                tx1 -= 1.0;
              glTexCoord2f(tx1, ty1);
              glVertex3fv(puntos[triangulos[i].b].devolver());

              tx2 = atan2(puntos[triangulos[i].c].x, puntos[triangulos[i].c].z) / (2. * M_PI) + 0.5;
              ty2 = asin(puntos[triangulos[i].c].y) / M_PI + .5;
              if(tx2 < 0.75 && tx1 > 0.75)
                tx2 += 1.0;
              else if(tx2 > 0.75 && tx1 < 0.75)
                tx2 -= 1.0;
              glTexCoord2f(tx2, ty2);
              glVertex3fv(puntos[triangulos[i].c].devolver());
            }

            glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Tierra::drawFill(){
    calcularNormales();

    glPushMatrix();
        glPolygonMode(GL_FRONT,GL_FILL);
            glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glBindTexture(GL_TEXTURE_2D, textura);
            glBegin(GL_TRIANGLES);
            float tx, ty, tx1, ty1, tx2, ty2;
            for(uint i = 0; i < triangulos.size(); i++){
                glColor3f(0.5,0.5,0.5);
              glNormal3fv(normalCon[i].devolver());

              tx = atan2(puntos[triangulos[i].a].x, puntos[triangulos[i].a].z) / (2. * M_PI) + 0.5;
              ty = asin(puntos[triangulos[i].a].y) / M_PI + .5;
              glTexCoord2f(tx, ty);
              glVertex3fv(puntos[triangulos[i].a].devolver());

              tx1 = atan2(puntos[triangulos[i].b].x, puntos[triangulos[i].b].z) / (2. * M_PI) + 0.5;
              ty1 = asin(puntos[triangulos[i].b].y) / M_PI + .5;
              if(tx1 < 0.75 && tx > 0.75)
                tx1 += 1.0;
              else if(tx1 > 0.75 && tx < 0.75)
                tx1 -= 1.0;
              glTexCoord2f(tx1, ty1);
              glVertex3fv(puntos[triangulos[i].b].devolver());

              tx2 = atan2(puntos[triangulos[i].c].x, puntos[triangulos[i].c].z) / (2. * M_PI) + 0.5;
              ty2 = asin(puntos[triangulos[i].c].y) / M_PI + .5;
              if(tx2 < 0.75 && tx1 > 0.75)
                tx2 += 1.0;
              else if(tx2 > 0.75 && tx1 < 0.75)
                tx2 -= 1.0;
              glTexCoord2f(tx2, ty2);
              glVertex3fv(puntos[triangulos[i].c].devolver());
            }
            glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
        glScalef(343.0,343.0,343.0);
        glPolygonMode(GL_BACK,GL_FILL);
        glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glBindTexture(GL_TEXTURE_2D, textura_fondo);
            glBegin(GL_TRIANGLES);
            for(uint i = 0; i < triangulos.size(); i++){
              glColor3f(1.0,1.0,1.0);

              tx = atan2(puntos[triangulos[i].a].x, puntos[triangulos[i].a].z) / (2. * M_PI) + 0.5;
              ty = asin(puntos[triangulos[i].a].y) / M_PI + .5;
              glTexCoord2f(tx, ty);
              glVertex3fv(puntos[triangulos[i].a].devolver());

              tx1 = atan2(puntos[triangulos[i].b].x, puntos[triangulos[i].b].z) / (2. * M_PI) + 0.5;
              ty1 = asin(puntos[triangulos[i].b].y) / M_PI + .5;
              if(tx1 < 0.75 && tx > 0.75)
                tx1 += 1.0;
              else if(tx1 > 0.75 && tx < 0.75)
                tx1 -= 1.0;
              glTexCoord2f(tx1, ty1);
              glVertex3fv(puntos[triangulos[i].b].devolver());

              tx2 = atan2(puntos[triangulos[i].c].x, puntos[triangulos[i].c].z) / (2. * M_PI) + 0.5;
              ty2 = asin(puntos[triangulos[i].c].y) / M_PI + .5;
              if(tx2 < 0.75 && tx1 > 0.75)
                tx2 += 1.0;
              else if(tx2 > 0.75 && tx1 < 0.75)
                tx2 -= 1.0;
              glTexCoord2f(tx2, ty2);
              glVertex3fv(puntos[triangulos[i].c].devolver());
            }

            glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
