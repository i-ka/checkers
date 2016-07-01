#-------------------------------------------------
#
# Project created by QtCreator 2016-04-23T13:47:56
#
#-------------------------------------------------

QT       += core gui opengl quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Checkers
TEMPLATE = app


SOURCES += main.cpp\
    Field.cpp \
    Checker.cpp \
    Vector2D.cpp

HEADERS  += \
    Field.hpp \
    Checker.hpp \
    Vector2D.hpp

FORMS    +=

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    qml.qrc

DISTFILES += \
    main.qml

