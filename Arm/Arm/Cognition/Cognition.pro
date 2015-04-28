#-------------------------------------------------
#
# Project created by QtCreator 2014-05-22T19:19:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cognition
TEMPLATE = app


SOURCES += main.cpp\
        cognition.cpp \
    forArm.cpp \
    QuickSort.cpp

HEADERS  += cognition.h \
    QuickSort.h
LIBS +=`pkg-config opencv --libs`
FORMS    += cognition.ui
