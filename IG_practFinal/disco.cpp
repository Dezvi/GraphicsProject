#include "disco.h"

Disco::Disco()
{

}


void Disco::draw(char a)
{
    glPushMatrix();
    glScalef(0.5,0.2,0.5);
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
