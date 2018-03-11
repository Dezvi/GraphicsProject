#include "brazopr.h"

BrazoPr::BrazoPr()
{

}

void BrazoPr::draw(char a)
{
    glPushMatrix();
    glTranslatef(0.0,0.25,0.0);
        Base::draw(a);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,3.0,0.0);
        Soporte::draw(a);
    glPopMatrix();
}

void BrazoPr::animacion(double angulo, char a)
{
    glPushMatrix();
    glTranslatef(0.0,0.25,0.0);
        Base::draw(a);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,3.0,0.0);
    glRotatef(angulo, 0.0, 1.0, 0.0);
        Soporte::draw(a);
    glPopMatrix();
}
