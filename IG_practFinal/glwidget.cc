//**************************************************************************
//
// Manuel Enrique López Roldán © 2017-2018
// manuellrgr@correo.ugr.es
//
//**************************************************************************

#include "glwidget.h"

using namespace std;
using namespace _gl_widget_ne;

//////////////////////////////////////////////////////////////////////

#define regulador 0
#define cubo 1
#define tetraedro 2
#define cilindro 3
#define plym 4
#define peon 5
#define vaso 6
#define vasoinv 7
#define cono 8
#define tubo 9
#define _animacion 10
#define brazo 11
#define textura 12
#define arrayMode 13


////////////////////////////////////////////////////////////////////


//**************************************************************************
//
//***************************************************************************

_gl_widget::_gl_widget(_window *Window1):Window(Window1)
{
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);

  QSignalMapper* signalMapper = new QSignalMapper (this);

  for(int i = 0; i < 36; ++i){
    QPushButton* button = new QPushButton(names[i].c_str(), this);
    buttons.push_back(button);

    setButtonPos(this->width(), this->height(), i);
    connect (buttons.at(i), SIGNAL(released()), signalMapper, SLOT(map()));
    signalMapper -> setMapping(buttons.at(i), i);
  }


  connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(correspondenceButton(int)));
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget::keyPressEvent(QKeyEvent *Keyevent)
{
  switch(Keyevent->key()){
  case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
  case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
  case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP;break;
  case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP;break;
  case Qt::Key_PageUp:Observer_distance*=1.2;break;
  case Qt::Key_PageDown:Observer_distance/=1.2;break;
  case Qt::Key_P:puntos=!puntos;break;
  case Qt::Key_L:alambre=!alambre;break;
  case Qt::Key_F:solido=!solido;ajedrez=false;break;
  case Qt::Key_C:ajedrez=!ajedrez;solido=false;break;
  case Qt::Key_1:figura=cubo;break;
  case Qt::Key_2:figura=tetraedro;break;
  case Qt::Key_3:figura=cilindro;break;
  case Qt::Key_4:figura=plym;break;
  case Qt::Key_5:figura=peon;break;
  case Qt::Key_6:figura=vaso;break;
  case Qt::Key_7:figura=vasoinv;break;
  case Qt::Key_8:figura=cono;break;
  case Qt::Key_9:figura=tubo;break;
  case Qt::Key_0:figura=regulador;break;
  case Qt::Key_Z:grado=1;if(Keyevent->modifiers() & Qt::SHIFT)i=i-u;else i=(i+u)%360;break;
  case Qt::Key_X:grado=2;if(Keyevent->modifiers() & Qt::SHIFT){j=j-v;if(j<0)j=0;}else{ j=j+v;if(j>360)j=360;}break;
  case Qt::Key_Y:grado=3;if(Keyevent->modifiers() & Qt::SHIFT){k=k-w;t=t-w;if(t<0)t=0;}else{k=(k+w)%360;t=(t+w);if(t>360)t=360;}break;
  case Qt::Key_B:if(Keyevent->modifiers() & Qt::SHIFT)--u;else ++u;break;
  case Qt::Key_N:if(Keyevent->modifiers() & Qt::SHIFT)--v;else ++v;break;
  case Qt::Key_M:if(Keyevent->modifiers() & Qt::SHIFT)--w;else ++w;break;
  case Qt::Key_I:cambiante=true;++velocidad;break;
  case Qt::Key_K:cambiante=true;--velocidad;break;
  case Qt::Key_S:para=!para;break;
  case Qt::Key_A:if(Keyevent->modifiers() & Qt::SHIFT)figura=brazo;else figura=_animacion;break;
  case Qt::Key_E:if(Keyevent->modifiers() & Qt::SHIFT){distancia_luz1=distancia_luz1-0.1; circle=true;}else{ distancia_luz1=distancia_luz1+0.1; circle=true;}break;
  case Qt::Key_F4:if(Keyevent->modifiers() & Qt::SHIFT)luz1=!luz1;else luz2=!luz2;break;
  case Qt::Key_F11:if(Keyevent->modifiers() & Qt::SHIFT)circle1=false; else lighting=!lighting;break;
  case Qt::Key_F12:if(Keyevent->modifiers() & Qt::SHIFT)circle=false; else circle=true;break;
  case Qt::Key_F5:smooth=!smooth;break;
  case Qt::Key_F6:esmeralda=!esmeralda;break;
  case Qt::Key_F7:plata=!plata;break;
  case Qt::Key_F8:if(Keyevent->modifiers() & Qt::SHIFT){if(opcion=='a')opcion='b';else if(opcion=='b')opcion='c';else if(opcion=='c')opcion='a';}else{goma=!goma;}break;
  case Qt::Key_F1:if(Keyevent->modifiers() & Qt::SHIFT)circley=false; else circley=true;break;
  case Qt::Key_F2:if(Keyevent->modifiers() & Qt::SHIFT)circle1y=false; else circle1y=true;break;
  case Qt::Key_F9:figura=textura;break;
  case Qt::Key_F10:if(Keyevent->modifiers() & Qt::SHIFT)circle1=true; else tablero=!tablero;break;
  case Qt::Key_Q:movimiento_camara = !movimiento_camara;break;
  }
  
  update();
}

//**************************************************************************
//
//***************************************************************************

void _gl_widget::mouseMoveEvent(QMouseEvent* event)
{
    double posX = event ->x();
    double posY = event ->y();

    double translationX = posX - bef_posX;
    double translationY = posY - bef_posY;

    bef_posX = posX;
    bef_posY = posY;

    if(translationY < -40)
        translationY =-40;
    else if(translationY > 40)
        translationY = 40;
    if(translationX < -40)
        translationX =-40;
    else if(translationX > 40)
        translationX = 40;

    translationX/=5;
    translationY/=5;

    Observer_angle_x += translationY;
    Observer_angle_y += translationX;
    update();

}

//**************************************************************************
//
//***************************************************************************

void _gl_widget::wheelEvent(QWheelEvent* event)
{
    QPoint numDegrees = event->angleDelta() / 8;

    double movimiento =  numDegrees.y()/15;
    if(movimiento<0)
        Observer_distance*=1.2;
    else
        Observer_distance/=1.2;

    event->accept();
}

//**************************************************************************
//
//***************************************************************************

void _gl_widget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        pick(event->pos().x(), event->pos().y(), 3.0,3.0);
    }
}

//**************************************************************************
//
//***************************************************************************

void _gl_widget::clear_window()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void _gl_widget::change_projection()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  //  Front_plane>0  Back_plane>PlanoDelantero)
  if(tipoCamara)
      glOrtho(X_MIN-Observer_distance,X_MAX+Observer_distance,(Y_MIN-Observer_distance)*scale,(Y_MAX+Observer_distance)*scale,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
  else
      glFrustum(X_MIN,X_MAX,Y_MIN*scale,Y_MAX*scale,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void _gl_widget::change_observer()
{
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
  glTranslatef(-distancia_de_x, -distancia_de_y,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void _gl_widget::draw_axis()
{
  glBegin(GL_LINES);
  // eje X, color rojo
  glColor3f(1,0,0);
  glVertex3f(-AXIS_SIZE,0,0);
  glVertex3f(AXIS_SIZE,0,0);
  // eje Y, color verde
  glColor3f(0,1,0);
  glVertex3f(0,-AXIS_SIZE,0);
  glVertex3f(0,AXIS_SIZE,0);
  // eje Z, color azul
  glColor3f(0,0,1);
  glVertex3f(0,0,-AXIS_SIZE);
  glVertex3f(0,0,AXIS_SIZE);
  glEnd();
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget::pick(const int& x, const int& y, unsigned int Width, unsigned int Height) {
    GLint Hits, Viewport[4];
    map<int long, int> depthFigures;
    const int BUFFER_SIZE = 1024;
    GLuint Selection_buffer[BUFFER_SIZE];

    glGetIntegerv (GL_VIEWPORT, Viewport);
    glSelectBuffer (BUFFER_SIZE, Selection_buffer);

    glRenderMode (GL_SELECT);

    glMatrixMode (GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix(x, Viewport[3] - y, 3, 3, Viewport);

    if(tipoCamara)
        glOrtho(X_MIN-Observer_distance,X_MAX+Observer_distance,(Y_MIN-Observer_distance)*scale,(Y_MAX+Observer_distance)*scale,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
    else
        glFrustum(X_MIN,X_MAX,Y_MIN*scale,Y_MAX*scale,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);

    glInitNames();
    glPushName(-1);

    clear_window();
    change_observer();
    drawWithNames();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    Hits = glRenderMode (GL_RENDER);
    if (Hits > 0){
        cout << "Hits: " << Hits;
        for(int i = 0; i < 4 * Hits; i += 4) {
            cout << "\nName: " <<  Selection_buffer[i + 3];
            depthFigures.insert(make_pair(Selection_buffer[i + 1], Selection_buffer[i + 3]));
        }
        sel = depthFigures.begin()->second;
        cout << "\nSELECTED FIGURE: " << depthFigures.begin()->second << endl;
    }else{
        sel = -1;
        cout << "Nada seleccionado" << endl;
    }
    update();
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget::drawWithNames() {
    for(int i=0; i < 3; ++i){
        for(int j = 0; j < 3; ++j) {
            glPushMatrix();
            glTranslatef(i*15, j*15, 0);
            glLoadName(i*5+j);
            if((i*5+j)==sel && sel != -1){
                glColor3f(0.8,0.3,0.6);
                if(movimiento_camara){
                    glPushMatrix();
                    distancia_de_y = j*15;
                    distancia_de_x = i*15;
                    change_observer();
                    glPopMatrix();
                }
            }else{
                glColor3f(0.4,0.4,0.4);
            }
            if(puntos)
                beet.drawPoints();
            if(alambre)
                beet.drawLines();
            if(solido){
                    beet.drawFill();
            }
            else if( ajedrez){
                    beet.drawChest();
            }
            glPopMatrix();
        }
    }
    update();
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget::setButtonPos(int ancho, int alto, int indice){
    double posX = ancho/1000, posY=4, anchoBot=ancho/15, altoBot=alto/23;
    switch(indice){
        case 0: buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5, 100+posY+altoBot),QSize(anchoBot,altoBot)));break;
        case 1: buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5, 100+posY+(indice+1)*altoBot),QSize(anchoBot,altoBot)));break;
        case 2: buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5, 100+posY+(indice+1)*altoBot),QSize(anchoBot,altoBot)));break;
        case 3: buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5, 100+posY+(indice+1)*altoBot),QSize(anchoBot,altoBot)));break;
        case 4: buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-4)*anchoBot, posY),QSize(anchoBot,altoBot)));break;
        case 5: buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-4)*anchoBot, posY),QSize(anchoBot,altoBot)));break;
        case 6: buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-4)*anchoBot, posY),QSize(anchoBot,altoBot)));break;
        case 7: buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-4)*anchoBot, posY),QSize(anchoBot,altoBot)));break;
        case 8: buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-4)*anchoBot, posY),QSize(anchoBot,altoBot)));break;
        case 9: buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-4)*anchoBot, posY),QSize(anchoBot,altoBot)));break;
        case 10:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-4)*anchoBot, posY),QSize(anchoBot,altoBot)));break;
        case 11:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-4)*anchoBot, posY),QSize(anchoBot,altoBot)));break;
        case 12:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-4)*anchoBot, posY),QSize(anchoBot,altoBot)));break;
        case 13:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-4)*anchoBot, posY),QSize(anchoBot,altoBot)));break;
        case 14:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5, 100+posY+(indice-7)*altoBot),QSize(anchoBot,altoBot)));break;
        case 15:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5, 100+posY+(indice-7)*altoBot),QSize(anchoBot,altoBot)));break;
        case 16:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5, 100+posY+(indice-7)*altoBot),QSize(anchoBot,altoBot)));break;
        case 17:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5, 100+posY+(indice-7)*altoBot),QSize(anchoBot,altoBot)));break;
        case 18:buttons.at(indice)->setGeometry(QRect(QPoint(posX+(indice-18)*anchoBot, 100+posY+(indice-2)*altoBot),QSize(anchoBot,altoBot)));break;
        case 19:buttons.at(indice)->setGeometry(QRect(QPoint(posX+(indice-18)*anchoBot, 100+posY+(indice-3)*altoBot),QSize(anchoBot,altoBot)));break;
        case 20:buttons.at(indice)->setGeometry(QRect(QPoint(posX, 100+posY+(indice-7)*altoBot),QSize(anchoBot,altoBot)));break;
        case 21:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot, 100+posY+(indice-8)*altoBot),QSize(anchoBot,altoBot)));break;
        case 22:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5, 100+posY+(indice-10)*altoBot),QSize(anchoBot,altoBot)));break;
        case 23:buttons.at(indice)->setGeometry(QRect(QPoint(posX, 100+posY+(indice-9)*altoBot),QSize(anchoBot,altoBot)));break;
        case 24:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot, 100+posY+(indice-10)*altoBot),QSize(anchoBot,altoBot)));break;
        case 25:buttons.at(indice)->setGeometry(QRect(QPoint(posX, 100+posY+(indice-10)*altoBot),QSize(anchoBot,altoBot)));break;
        case 26:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot, 100+posY+(indice-11)*altoBot),QSize(anchoBot,altoBot)));break;
        case 27:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-27)*anchoBot, posY+alto-altoBot),QSize(anchoBot,altoBot)));break;
        case 28:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-27)*anchoBot, posY+alto-altoBot),QSize(anchoBot,altoBot)));break;
        case 29:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-27)*anchoBot, posY+alto-altoBot),QSize(anchoBot,altoBot)));break;
        case 30:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-27)*anchoBot, posY+alto-altoBot),QSize(anchoBot,altoBot)));break;
        case 31:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-27)*anchoBot, posY+alto-altoBot),QSize(anchoBot,altoBot)));break;
        case 32:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-27)*anchoBot, posY+alto-altoBot),QSize(anchoBot,altoBot)));break;
        case 33:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-27)*anchoBot, posY+alto-altoBot),QSize(anchoBot,altoBot)));break;
        case 34:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-24)*anchoBot, posY),QSize(anchoBot,altoBot)));break;
        case 35:buttons.at(indice)->setGeometry(QRect(QPoint(posX+anchoBot*0.5+(indice-28)*anchoBot, posY+alto-altoBot),QSize(anchoBot,altoBot)));break;
    }
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget::correspondenceButton(int num){
    switch(num){
        case 0:puntos=!puntos;break;
        case 1:alambre=!alambre;break;
        case 2:solido=!solido;ajedrez=false;break;
        case 3:ajedrez=!ajedrez;solido=false;break;
        case 4:figura=cubo;break;
        case 5:figura=tetraedro;break;
        case 6:figura=cilindro;break;
        case 7:figura=plym;break;
        case 8:figura=peon;break;
        case 9:figura=vaso;break;
        case 10:figura=vasoinv;break;
        case 11:figura=cono;break;
        case 12:figura=tubo;break;
        case 13:figura=regulador;break;
        case 14:figura=_animacion;break;
        case 15:++velocidad;break;
        case 16:--velocidad;break;
        case 17:para=!para;break;
        case 18:distancia_luz1=distancia_luz1-0.15;break;
        case 19:distancia_luz1=distancia_luz1+0.15;break;
        case 20:luz1=!luz1;break;
        case 21:luz2=!luz2;break;
        case 22:lighting=!lighting;break;
        case 23:circle=true;++angulo_luz1_x;break;
        case 24:circle1=true;++angulo_luz2_x;break;
        case 25:circle=true;++angulo_luz1_y;break;
        case 26:circle1=true;++angulo_luz2_y;break;
        case 27:smooth=!smooth;break;
        case 28:esmeralda=!esmeralda;break;
        case 29:plata=!plata;break;
        case 30:goma=!goma;break;
        case 31:figura=textura;tablero=false;break;
        case 32:figura=textura;tablero=true;break;
        case 33:if(opcion=='a')opcion='b';else if(opcion=='b')opcion='c';else if(opcion=='c')opcion='a';break;
        case 34:figura=arrayMode;break;
        case 35:tipoCamara=!tipoCamara;
    }
    update();
}

//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************


void _gl_widget::draw_objects()
{
    luces();
    // Guia reguladorWatt
    // Para ver solo el brazo pulsar A
    // Para animar pulsar a, para acelerar/desacelerar pulsar i/k, para parar/reanudar pulsar s
    // Para dibujar regulador pulsar 0
    // Para ver solo rotacion pulsar z/Z, para acelerar/desacelerar pulsar b/B
    // Para ver solo movimiento brazos pulsar x/X, para acelerar/desacelerar pulsar n/N
    // Para ver solo movimiento brazos y rotacion pulsar y/Y, para acelerar/desacelerar pulsar m/M
    Cubo dibCubo;
    Tetraedro dibTetraedro;
    Cilindro dibCilindro;
    Vaso dibVaso;
    Esfera dibEsfera;
    Cono dibCono;
    Tubo dibTubo;

    switch(figura){
        case plym:{
            _file_ply file;
            vector<_vertex3f> Vertices;
            vector<_vertex3i> Triangles;
            file.open("/home/manuel/Escritorio/beethoven.ply");
            file.read(Vertices, Triangles);
            file.close();
            O3d ply;
            ply.plyVertexTriangles(Vertices, Triangles);
            if(puntos)
                ply.drawPoints();
            if(alambre)
                ply.drawLines();
            if(solido){
                if(!smooth)
                    ply.drawFill();
                else
                    ply.drawFillSmooth(false);
            }
            else if( ajedrez){
                if(!smooth)
                    ply.drawChest();
                else
                    ply.drawFillSmooth(true);
            }
        }
            break;
        case peon:{
            _file_ply file;
            vector<_vertex3f> Vertices;
            vector<_vertex3i> Triangles;
            //Change directory
            file.open("/home/manuel/Escritorio/peon.ply");
            file.read(Vertices, Triangles);
            file.close();
            Peon dibPeon(Vertices);
            if(puntos)
                dibPeon.drawPoints();
            if(alambre)
                dibPeon.drawLines();
            if(solido)
                if(!smooth)
                    dibPeon.drawFill();
                else
                    dibPeon.drawFillSmooth(false);
            else if( ajedrez){
                if(!smooth)
                    dibPeon.drawChest();
                else
                    dibPeon.drawFillSmooth(true);
            }
        }
            break;
        case _animacion:{
            if(puntos)
                cambiante = a.animacion(velocidad,'p', cambiante, para);
            if(alambre)
                cambiante = a.animacion(velocidad,'l', cambiante, para);
            if(solido){
                if(!smooth)
                    cambiante = a.animacion(velocidad,'f', cambiante, para);
                else
                    cambiante = a.animacion(velocidad,'s', cambiante, para);
            }
            else if(ajedrez){
                if(!smooth)
                    cambiante = a.animacion(velocidad,'c', cambiante, para);
                else
                    cambiante = a.animacion(velocidad,'a', cambiante, para);
            }
            QWidget::update();
            cambiante = true;
        }
            break;
        case regulador:{
            glMatrixMode(GL_MODELVIEW);
            if(grado==0){
                if(puntos)
                    a.draw('p');
                if(alambre)
                    a.draw('l');
                if(solido)
                    if(!smooth)
                        a.draw('f');
                    else
                        a.draw('s');
                else if( ajedrez){
                    if(!smooth)
                        a.draw('c');
                    else
                        a.draw('a');
            }
            }if(grado==1){
                if(puntos)
                    a.grado1(i,'p');
                if(alambre)
                    a.grado1(i,'l');
                if(solido)
                    if(!smooth)
                        a.grado1(i,'f');
                    else
                        a.grado1(i,'s');
                else if( ajedrez){
                    if(!smooth)
                        a.grado1(i,'c');
                    else
                        a.grado1(i,'a');
                }
            }
            if(grado==2){
                if(puntos)
                    a.grado23(j,'p');
                if(alambre)
                    a.grado23(j,'l');
                if(solido)
                    if(!smooth)
                        a.grado23(j,'f');
                    else
                        a.grado23(j,'s');
                else if( ajedrez){
                    if(!smooth)
                        a.grado23(j,'c');
                    else
                        a.grado23(j,'a');
                }
            }
            if(grado==3){
                if(puntos)
                    a.grados(k%360, t,'p');
                if(alambre)
                    a.grados(k%360, t,'l');
                if(solido)
                    if(!smooth)
                        a.grados(k%360, t,'f');
                    else
                        a.grados(k%360, t,'s');
                else if( ajedrez){
                    if(!smooth)
                        a.grados(k%360, t,'c');
                    else
                        a.grados(k%360, t,'a');
                }
            }
        }
            break;
        case textura:{
                if(tablero){
                        caja->draw(opcion);
                }else {
                    if(!smooth)
                        tierra->drawFill();
                    else
                        tierra->drawFillSmooth();
                }
        }
                break;
        case brazo:{
            BrazosSup b;
            if(puntos)
                b.draw('p');
            if(alambre)
                b.draw('l');
            if(solido){
                if(!smooth)
                    b.draw('f');
                else
                    b.draw('s');
            }else if( ajedrez){
                if(!smooth)
                    b.draw('c');
                else
                    b.draw('a');
            }
        }
            break;
        case cubo:
            figura_sel = &dibCubo;
            break;
        case tetraedro:
            figura_sel = &dibTetraedro;
            break;
        case cilindro:
            figura_sel = &dibCilindro;
            break;
        case vaso:
            figura_sel = &dibVaso;
            break;
        case vasoinv:
            figura_sel = &dibEsfera;
            break;
        case cono:
            figura_sel = &dibCono;
            break;
        case tubo:
            figura_sel = &dibTubo;
            break;
        case arrayMode:
            drawWithNames();
            break;
    }
    if(figura!=brazo && figura!=textura && figura!=regulador && figura!=_animacion && figura!=plym && figura!=peon && figura != arrayMode){
        if(puntos)
            figura_sel->drawPoints();
        if(alambre)
            figura_sel->drawLines();
        if(solido){
            if(!smooth)
                figura_sel->drawFill();
            else
                figura_sel->drawFillSmooth(false);
        }
        else if( ajedrez){
            if(!smooth)
                figura_sel->drawChest();
            else
                figura_sel->drawFillSmooth(true);
        }
    }
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget::luces(){
    //Uso de luces practica4
//    Para mover la luz 0, q = ++x; w = ++y; e = ++z; Q = --x; W = --y; E = --z; f12 para activar modo girar; (mayus) F12 para desactivarlo
//    Para mover la luz 1, (mayus) F10 para activar modo girar; F11 para desactivarlo
//    Para quitar el modo lighting F11
//    Para quitar/poner la luz: luz0 = f4; (Mayus) luz1 = F4;
//    Para quita/poner el smooth: f5
//    Para quita/poner el material1 (esmeralda): f6
//    Para quita/poner el material2 (plata): f7
//    Para quita/poner el material3 (goma negra): f8
//    Si todos los materiales están quitados se pone con colores normales
//    Modo texturas f9; Para alternar entre Tablero/Tierra f10
    if(lighting)
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);
    if(luz1)
        glEnable(GL_LIGHT0);
    if(!luz1)
        glDisable(GL_LIGHT0);
    if(luz2)
        glEnable(GL_LIGHT1);
    if(!luz2)
        glDisable(GL_LIGHT1);

        // emerald,
    if(esmeralda){
        glDisable(GL_COLOR_MATERIAL);
        GLfloat ambientLight[] = {0.2f, 0.4f, 0.2f, 0.55f };
        GLfloat diffuseLight[] = {0.2f, 0.4f, 0.2f, 0.55f};
        GLfloat specularLight[] = {0.2f, 0.4f, 0.2f, 0.55f };
        GLfloat Shininess = 12.0f;
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambientLight);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseLight);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);
        glMaterialf(GL_FRONT, GL_SHININESS, Shininess);
    }else if(plata){
        glDisable(GL_COLOR_MATERIAL);
         //ruby
        GLfloat ambientLight[] = {0.23125f, 0.23125f, 0.23125f, 1.0f};
        GLfloat diffuseLight[] = {0.2775f, 0.2775f, 0.2775f, 1.0f};
        GLfloat specularLight[] = {0.773911f, 0.773911f, 0.773911f, 1.0f};
        GLfloat Shininess = 89.6f;
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambientLight);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseLight);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);
        glMaterialf(GL_FRONT, GL_SHININESS, Shininess);
    }else if(goma){
        glDisable(GL_COLOR_MATERIAL);
         //cyan rubber
        GLfloat ambientLight[] = { 0.02f, 0.02f, 0.02f, 1.0f};
        GLfloat diffuseLight[] = {0.01f, 0.01f, 0.01f, 1.0f};
        GLfloat specularLight[] = {0.4f, 0.4f, 0.4f, 1.0f };
        GLfloat Shininess =  10.0f;
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambientLight);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseLight);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);
        glMaterialf(GL_FRONT, GL_SHININESS, Shininess);
    }else{
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    }

    if(smooth)
        glShadeModel (GL_SMOOTH);
    else
        glShadeModel (GL_FLAT);

    GLfloat ambient[] = { 0.7f, 0.7f, 0.1f, 1.0f };
    GLfloat diffuse[] = { 0.7f, 0.7f, 0.1f, 1.0f };
    GLfloat specular[] ={ 0.7f, 0.7f, 0.1f, 1.0f };
    if(circle) {
        position[0] = cos(angulo_luz1_x*M_PIl/180)*distancia_luz1;
        position[1] = sin(angulo_luz1_y*M_PIl/180)*distancia_luz1;
        position[2] = cos(angulo_luz1_x*M_PIl/180)*sin(angulo_luz1_y*M_PIl/180)*distancia_luz1;
        circle = false;
    }else if(circle1){
        position1[0] = cos(angulo_luz2_x*M_PIl/180);
        position1[1] = sin(angulo_luz2_y*M_PIl/180);
        position1[2] = cos(angulo_luz2_x*M_PIl/180)*sin(angulo_luz2_y*M_PIl/180);
        circle1 = false;
    }
    cout << "0: " << position[0] << endl;
    cout << "1: " << position[1] << endl;
    cout << "2: " << position[2] << endl;

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    //glEnable(GL_LIGHTING);
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget::paintGL()
{
  clear_window();
  change_projection();
  change_observer();
  draw_axis();
  draw_objects();
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget::resizeGL(int Width1, int Height1)
{
    scale = 1.0*Height1/Width1;

    glViewport(0,0,Width1,Height1);

    for(uint i = 0; i < buttons.size(); ++i)
        setButtonPos(Width1,Height1,i);

}


//*************************************************************************
//
//*************************************************************************

void _gl_widget::initializeGL()
{
  const GLubyte* strm;
  caja = new Caja();
  tierra = new Tierra();
  _file_ply file;
  cout << "cargando archivo" << endl;
  vector<_vertex3f> Vertices;
  vector<_vertex3i> Triangles;
  //Change directory
  file.open("/home/manuel/Escritorio/beethoven.ply");
  file.read(Vertices, Triangles);
  file.close();
  beet.plyVertexTriangles(Vertices, Triangles);
  cout << "cargando archivo" << endl;
  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1'){
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
    }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";

  glewExperimental = GL_TRUE;
  int err = glewInit();
  if (GLEW_OK != err){
    std::cerr << "Error: " << glewGetErrorString(err) << "\n";
    exit (-1);
    }

  int Max_texture_size=0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cerr << "Max texture size: " << Max_texture_size << "\n";

  glClearColor(1.0,1.0,1.0,1.0);
  glEnable(GL_DEPTH_TEST);;

  Observer_angle_x=0;
  Observer_angle_y=0;
  Observer_distance=DEFAULT_DISTANCE;
}

