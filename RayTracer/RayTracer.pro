
QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Raytracer

DESTDIR = ./Release

TEMPLATE = app

CONFIG += console c++11



SOURCES += $$PWD/RayTracer/src/*.cpp \
            $$PWD/RayTracer/src/Cameras/*.cpp \
            $$PWD/RayTracer/src/Lights/*.cpp \
            $$PWD/RayTracer/src/Materials/*.cpp \
            $$PWD/RayTracer/src/Shaders/*.cpp \
            $$PWD/RayTracer/src/Geometry/*.cpp \
            $$PWD/RayTracer/src/Maths/*.cpp \
            $$PWD/RayTracer/src/Scenes/*.cpp \
            $$PWD/RayTracer/src/Raytracer/*.cpp

HEADERS  += $$PWD/RayTracer/include/*.h \
            $$PWD/RayTracer/include/Cameras/*.h \
            $$PWD/RayTracer/include/Lights/*.h \
            $$PWD/RayTracer/include/Materials/*.h \
            $$PWD/RayTracer/include/Shaders/*.h \
            $$PWD/RayTracer/include/Geometry/*.h\
            $$PWD/RayTracer/include/Maths/*.h \
            $$PWD/RayTracer/include/Scenes/*.h \
            $$PWD/RayTracer/include/Raytracer/*.h




INCLUDEPATH += $$PWD/RayTracer/include /usr/local/include /usr/include /usr/include /home/idris/dev/include

LIBS += -L/usr/local/lib -L/usr/lib -lGL -lGLU -lGLEW \
        -L${HOME}/dev/lib -L/usr/local/lib -lassimp \
        -L/usr/lib/x86_64-linux-gnu -lfreeimage


OBJECTS_DIR = ./obj

MOC_DIR = ./moc

#FORMS    += ./form/mainwindow.ui

UI_DIR += ./ui


