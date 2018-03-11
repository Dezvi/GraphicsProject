#include "base.h"

Base::Base()
{

}

void Base::draw(char a)
{
    //Brazos inferiores
    glPushMatrix();
    glScalef(4,0.5,4);
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
