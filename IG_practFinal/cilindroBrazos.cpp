#include "cilindroBrazos.h"

CilindroBrazos::CilindroBrazos()
{

}

void CilindroBrazos::draw(char a)
{

    //Esferas
    double radian = PI/180;


    //Disco
    glPushMatrix();
    glTranslatef(0.0,5.56,0.0);
    Disco::draw(a);
    glPopMatrix();

    //Brazos Superiores y esferas
    glPushMatrix();
    glTranslatef(0.4,5.6,0.0);
    glRotatef(-135,0.0,0.0,1.0);
    BrazosSup::draw(a);
    glPopMatrix();

    glPushMatrix();
    glRotatef(180,0.0,1.0,0.0);
    glTranslatef(0.4,5.6,0.0);
    glRotatef(-135,0.0,0.0,1.0);
    BrazosSup::draw(a);
    glPopMatrix();

    //Brazos inferiores
    glPushMatrix();
    glTranslatef(0.45,3.05,0.0);
    glRotatef(-45,0.0,0.0,1.0);
    glTranslatef(0.0,0.9,0.0);
    BrazosInf::draw(a);
    glPopMatrix();

    glPushMatrix();
    glRotatef(180,0.0,1.0,0.0);
    glTranslatef(0.45,3.05,0.0);
    glRotatef(-45,0.0,0.0,1.0);
    glTranslatef(0.0,0.9,0.0);
    BrazosInf::draw(a);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3,1.9,0.0);
        Palito::draw(a);
    glPopMatrix();
    //Disco inferior
    glPushMatrix();
    glTranslatef(0.0,3.0,0.0);
        Disco::draw(a);
    glPopMatrix();

}

void CilindroBrazos::grado23(double angulo, char a)
{
    //Disco
    double cuanto1 = 0.0060000000; // desplazamiento
    double cuanto2 = 0.0888888888; // rotacion brazos inferiores
    double cuanto3 = 0.125; // rotacion brazos superiores
    double total1 = cuanto1 * angulo;
    double total2 = -45-cuanto2 * angulo;
    double total3 = -135+cuanto3 * angulo;
    if(total1 < 0)
        total1 = 0;
    if(total2 > 135)
        total2 = 135;
    if(total3 > 135)
        total3 = 135;

    //Disco
    glPushMatrix();
    glTranslatef(0.0,5.56,0.0);
    Disco::draw(a);
    glPopMatrix();

    //Brazos superiores
    glPushMatrix();
    glTranslatef(0.4,5.6,0.0);
    glRotatef(total3,0.0,0.0,1.0);
        BrazosSup::draw(a);
    glPopMatrix();


    glPushMatrix();
    glRotatef(180,0.0,1.0,0.0);
    glTranslatef(0.4,5.6,0.0);
    glRotatef(total3,0.0,0.0,1.0);
        BrazosSup::draw(a);
    glPopMatrix();

    //Brazos inferiores
    glPushMatrix();
    glTranslatef(0.45,3.05+total1,0.0);
    glRotatef(total2,0.0,0.0,1.0);
    glTranslatef(0.0,0.9,0.0);
        BrazosInf::draw(a);
    glPopMatrix();
    glPushMatrix();
    glRotatef(180,0.0,1.0,0.0);
    glTranslatef(0.45,3.05+total1,0.0);
    glRotatef(total2,0.0,0.0,1.0);
    glTranslatef(0.0,0.9,0.0);
        BrazosInf::draw(a);
    glPopMatrix();

    //Palito
    glPushMatrix();
    glTranslatef(-0.3,1.9+total1,0.0);
        Palito::draw(a);
    glPopMatrix();

    //Disco inferior
    glPushMatrix();
    glTranslatef(0.0,3.0+total1,0.0);
        Disco::draw(a);
    glPopMatrix();
}
