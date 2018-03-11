#ifndef GLWIDGET_H
#define GLWIDGET_H
//**************************************************************************
//
// Domingo Martin Perandres© 2014-2017
// http://calipso.ugr.es/dmartin
// dmartin@ugr.es
//
// GPL
//**************************************************************************

#include <GL/glew.h>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <iostream>
#include <QPushButton>
#include <QSignalMapper>
#include <QPainter>
#include <QPaintEngine>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QCoreApplication>
#include <math.h>
#include <GL/glut.h>
#include "vertex.h"
#include "o3d.h"
#include "cubo.h"
#include "tetraedro.h"
#include "file_ply_stl.h"
#include "window.h"
#include "cilindro.h"
//#include "peon.h"
#include "vaso.h"
#include "vasoinv.h"
#include "cono.h"
#include "peon.h"
#include "tubo.h"
#include "reguladorwatt.h"
#include "tierra.h"
#include "caja.h"

namespace _gl_widget_ne {

  const _vertex3f COLORS[]={{0,0,0},{1,0,0},{0,1,0},{0,0,1},{0,1,1},{1,0,1},{1,1,0},{1,1,1}};

  const float X_MIN=-0.5;
  const float X_MAX=0.5;
  const float Y_MIN=-0.5;
  const float Y_MAX=0.5;
  const float FRONT_PLANE_PERSPECTIVE=(X_MAX-X_MIN)/2;
  const float BACK_PLANE_PERSPECTIVE=1000;
  const float DEFAULT_DISTANCE=10;

  const float ANGLE_STEP=1;

  // axis
  const int AXIS_SIZE=5000;
}


class _window;

class _gl_widget : public QOpenGLWidget
{
    Q_OBJECT
public:
  _gl_widget(_window *Window1);

  void clear_window();
  void change_projection();
  void change_observer();
  void mousePressEvent(QMouseEvent *event);
  void drawWithNames();
  void setButtonPos(int ancho, int alto, int indice);
  void mouseMoveEvent(QMouseEvent* event);
  void wheelEvent(QWheelEvent* event);
  void draw_axis();
  void draw_objects();
///////////////////////////
  void cargarImagen();
  void luces();
  void pick(const int& x, const int& y, unsigned int Width, unsigned int Height);

protected:
  void resizeGL(int Width1, int Height1) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void initializeGL() Q_DECL_OVERRIDE;
  void keyPressEvent(QKeyEvent *Keyevent) Q_DECL_OVERRIDE;

private slots:

  void correspondenceButton(int num);

private:

  char opcion = 'c';

  bool puntos=true, alambre=false, solido=false, ajedrez=false, cambiante=false, para = false, luz1 = true, luz2 = true;
  bool smooth = true, tipoCamara = true, paralela = false, esmeralda = false, plata = false, goma = true;
  bool lighting=false, circle = false, circle1 = false, circley = false, circle1y = false, tablero = true;
  bool movimiento_camara=false;

  int i = 0, j = 0, k = 0, t = 0, velocidad=0, u = 1, v = 1, w = 1, figura=1, grado=0, numPrimitives=0, sel=-1;

  float Observer_angle_x, Observer_angle_y, Observer_distance;
  GLfloat distancia_luz1 = 5;
  double movimiento=0, movimiento1=0, distancia_de_x=0, distancia_de_y=0, scale, bef_posX=0, bef_posY=0, movimientoy=0, movimiento1y=0;
  double angulo_luz1_x=90, angulo_luz1_y=90, angulo_luz2_x=90, angulo_luz2_y=90;


  GLfloat position[4] = { 0.0, 0.0, 5.0, 0.0f };
  GLfloat position1[4] = { 0.0, 0.0, 5.0, 1.0f };

  QImage Imagen;
  Tierra *tierra;
  Caja *caja;
  O3d ply_figure_1;
  O3d* figura_sel;
  reguladorWatt a;
  O3d beet;

  _window *Window;
  vector<QPushButton*> buttons;
  string names[36] = {"puntos", "alambre", "solido", "ajedrez", "cubo", "tetraedro", "cilindro", "ply", "peon", "vaso", "vasoinv", "cono", "tubo", "reguladorWatt",
                      "animacion", "acelerar", "decelerar","parar", "acercar luz", "alejar luz", "luz1 infinito", "luz2", "desactivar Lighting","luz1 gira en Y", "luz2 gira en Y",
                      "luz1 gira en X", "luz2 gira en X", "smooth", "esmeralda", "plata", "goma", "textura", "tablero", "opcionTablero", "array Figuras", "tipo camara"};
};

#endif
