#include "brazosinf.h"

BrazosInf::BrazosInf()
{

}

void BrazosInf::draw(char a)
{
    glPushMatrix();
        CilindroBrazoInf::draw(a);
    glPopMatrix();
}
