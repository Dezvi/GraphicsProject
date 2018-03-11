#include "soporte.h"

Soporte::Soporte()
{

}

void Soporte::draw(char a)
{
    //Brazos inferiores
    glPushMatrix();
    glScalef(0.17,2.6,0.17);
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
