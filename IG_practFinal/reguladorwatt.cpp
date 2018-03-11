#include "reguladorwatt.h"
#include "cilindroBrazos.h"

reguladorWatt::reguladorWatt()
{
}

void reguladorWatt::draw(char a)
{
    //Brazos superiores
    glPushMatrix();
    CilindroBrazos::draw(a);
    glPopMatrix();

    //Brazo principal
    glPushMatrix();
    BrazoPr::draw(a);
    glPopMatrix();

}
void reguladorWatt::grado1(double angulo, char a){
    //Brazos superiores
    glPushMatrix();
    glRotatef(angulo, 0.0, 1.0, 0.0);
    CilindroBrazos::draw(a);
    glPopMatrix();
    //Brazo principal
    glPushMatrix();
    BrazoPr::animacion(angulo,a);
    glPopMatrix();
}
void reguladorWatt::grado23(double angulo, char a){
    //Brazos superiores
    glPushMatrix();
    CilindroBrazos::grado23(angulo, a);
    glPopMatrix();
    //Brazo principal
    glPushMatrix();
    BrazoPr::draw(a);
    glPopMatrix();
}
void reguladorWatt::grados(double movimiento, double angulo, char a){
    //Brazos superiores
    glPushMatrix();
    glRotatef(movimiento, 0.0, 1.0, 0.0);
    CilindroBrazos::grado23(angulo, a);
    glPopMatrix();
    //Brazo principal
    glPushMatrix();
    BrazoPr::animacion(movimiento,a);
    glPopMatrix();
}
bool reguladorWatt::animacion(int velocidad, char a, bool cambio, bool para){
    double vel_rot=velocidad*0.2;
    double vel_mov;
    if(velocidad < 0){
        velocidad = velocidad * -1;
        vel_mov = pow(velocidad,1.4);
    }else
        vel_mov = pow(velocidad,1.4);
    if(cambio && !para){
        angulo = angulo + vel_rot;
        cambio = false;
    }
    if(vel_mov > 360){
        vel_mov = 360;
    }
    //Brazos superiores
    glPushMatrix();
    glRotatef(angulo, 0.0, 1.0, 0.0);
    CilindroBrazos::grado23(vel_mov, a);
    glPopMatrix();
    //Brazo principal
    glPushMatrix();
    BrazoPr::animacion(angulo, a);
    glPopMatrix();
    return cambio;
}
