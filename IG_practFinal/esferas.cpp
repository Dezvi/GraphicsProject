#include "esferas.h"

Esferas::Esferas()
{
}

void Esferas::draw(char a){
    cout << "a" << endl;
    glPushMatrix();
    glScalef(0.5,0.5,0.5);
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
