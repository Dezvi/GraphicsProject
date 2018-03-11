#include "cilindrobrazosup.h"

CilindroBrazoSup::CilindroBrazoSup()
{

}

void CilindroBrazoSup::draw(char a)
{
    //Brazos superiores
    glPushMatrix();
    glScalef(0.1,1.8,0.1);
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
