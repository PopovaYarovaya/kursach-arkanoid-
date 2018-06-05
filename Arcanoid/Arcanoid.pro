#-------------------------------------------------
#
# Project created by QtCreator 2017-02-14T21:35:12
#
#-------------------------------------------------

QT      += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Arcanoid
TEMPLATE = app
CONFIG += c++11
CONFIG += static

SOURCES += main.cpp\
        game.cpp \
    ball.cpp \
    playerplatform.cpp \
    brick.cpp

HEADERS  += game.h \
    ball.h \
    playerplatform.h \
    brick.h

FORMS    += game.ui
