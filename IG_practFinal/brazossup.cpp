#include "brazossup.h"

BrazosSup::BrazosSup()
{

}

void BrazosSup::draw(char a)
{
    //Brazos superiores
    glPushMatrix();
    glTranslatef(0.0,1.8,0.0);
        CilindroBrazoSup::draw(a);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,4.1,0.0);
        Esferas::draw(a);
    glPopMatrix();
}
