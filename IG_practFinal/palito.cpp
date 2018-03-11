#include "palito.h"

Palito::Palito()
{

}

void Palito::draw(char a)
{
    //Brazos inferiores
    glPushMatrix();
    glScalef(0.07,2.5,0.07);
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
