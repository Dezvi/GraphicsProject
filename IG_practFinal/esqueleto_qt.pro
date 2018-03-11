HEADERS += \
  glwidget.h \
  window.h \
    o3ds.h \
    vertexp.h \
    o3d.h \
    cubo.h \
    tetraedro.h \
    triangulo.h \
    file_ply_stl.h \
    vertex.h \
    o3r.h \
    cilindro.h \
    tubo.h \
    vaso.h \
    vasoinv.h \
    cono.h \
    peon.h \
    cilindroBrazos.h \
    reguladorwatt.h \
    soporte.h \
    esferas.h \
    brazopr.h \
    esfera.h \
    brazosinf.h \
    brazossup.h \
    disco.h \
    cilindrobrazosup.h \
    cilindrobrazoinf.h \
    base.h \
    palito.h \
    plywatt.h \
    caja.h \
    tierra.h

SOURCES += \
  main.cc \
  glwidget.cc \
  window.cc \
    vertexp.cpp \
    o3ds.cpp \
    o3d.cpp \
    cubo.cpp \
    tetraedro.cpp \
    triangulo.cpp \
    file_ply_stl.cc \
    o3r.cpp \
    cilindro.cpp \
    tubo.cpp \
    cono.cpp \
    vaso.cpp \
    vasoinv.cpp \
    peon.cpp \
    cilindroBrazos.cpp \
    reguladorwatt.cpp \
    soporte.cpp \
    esferas.cpp \
    brazopr.cpp \
    esfera.cpp \
    brazosinf.cpp \
    brazossup.cpp \
    disco.cpp \
    cilindrobrazosup.cpp \
    cilindrobrazoinf.cpp \
    base.cpp \
    palito.cpp \
    plywatt.cpp \
    caja.cpp \
    tierra.cpp

INCLUDEPATH += /casa/dmartin/codigo/funciontecas/glew/include

LIBS += -L/usr/X11R6/lib64 -lGL \
        -L/usr/lib64 -lGLEW -lglut -lSOIL -lGLU

CONFIG += c++11
QT += widgets
