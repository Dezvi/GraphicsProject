#ifndef BRAZOSSUP_H
#define BRAZOSSUP_H

#include "esferas.h"
#include "cilindrobrazosup.h"
#include "plywatt.h"

class BrazosSup : public CilindroBrazoSup, public Esferas, public PlyWatt
{
public:
    BrazosSup();
    void draw(char a);
};

#endif // BRAZOSSUP_H
