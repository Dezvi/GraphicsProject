#ifndef VERTEXP_H
#define VERTEXP_H

#include <QPainter>
#include <QPaintEngine>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QCoreApplication>

class Vertex{
public:
    GLfloat x;
    GLfloat y;
    GLfloat z;
    Vertex();
    Vertex(double a, double b, double c);
    void asignar(GLfloat a, GLfloat b, GLfloat c);
    GLfloat* devolver();
};


#endif // FIGURES_H
