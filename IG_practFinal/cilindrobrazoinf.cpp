#include "cilindrobrazoinf.h"

CilindroBrazoInf::CilindroBrazoInf()
{

}

void CilindroBrazoInf::draw(char a)
{
    //Brazos inferiores
    glPushMatrix();
    glScalef(0.05,0.9,0.05);
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
