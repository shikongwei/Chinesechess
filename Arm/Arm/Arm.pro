#-------------------------------------------------
#
# Project created by QtCreator 2014-04-20T22:18:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Arm
TEMPLATE = app


SOURCES += main.cpp\
        arm.cpp \
    myarm.cpp \
    Chess/ChessSubBoard.cpp \
    Representation/actiontosend.cpp \
    Send/threadToSend.cpp \
    Send/comm.cpp \
    Representation/Blackboard.cpp \
    Chess/chess.cpp \
    Sim/drawTool.cpp \
    Sim/simarm.cpp \
    Sim/thread.cpp \
    AutoRun/thread_auto.cpp \
    Vision/vision.cpp \
    kernel/Alpha_Beta.cpp \
    kernel/board.cpp \
    kernel/define_global.cpp \
    kernel/mousepress.cpp \
    kernel/PVS.cpp \
    kernel/weight.cpp \
    kernel/move/advisor_move.cpp \
    kernel/move/cannon_move.cpp \
    kernel/move/chariot_move.cpp \
    kernel/move/elephant_move.cpp \
    kernel/move/general_move.cpp \
    kernel/move/horse_move.cpp \
    kernel/move/Move.cpp \
    kernel/move/soldier_move.cpp \
    kernel/check/check_cannon.cpp \
    kernel/check/check_chariot.cpp \
    kernel/check/check_general.cpp \
    kernel/check/check_horse.cpp \
    kernel/check/checkmate.cpp \
    kernel/check/check_soldier.cpp \
    Audio/playmp3.cpp \
    Cognition/cognition.cpp \
    Cognition/forArm.cpp \
    Cognition/QuickSort.cpp \
    ArmMove/armmodify.cpp \
    ArmMove/Send/comm_armMove.cpp

HEADERS  += arm.h \
    myarm.h \
    Chess/chess.h \
    Chess/ChessSubBoard.h \
    Chess/Point.h \
    Representation/Move.h \
    Representation/actiontosend.h \
    Send/threadToSend.h \
    Send/pyinit.hpp \
    Send/comm.h \
    Representation/Angle.h \
    Representation/Blackboard.h \
    Representation/length.h \
    Sim/drawTool.h \
    Sim/simarm.h \
    Sim/thread.h \
    AutoRun/thread_auto.h \
    Vision/vision.h \
    kernel/global.h \
    Audio/playmp3.h \
    Cognition/cognition.h \
    Cognition/QuickSort.h \
    ArmMove/armmodify.h \
    ArmMove/Send/pyinit.hpp \
    ArmMove/Send/comm_armMove.h
LIBS +=/usr/lib/i386-linux-gnu/libGL.so
LIBS +=/usr/lib/i386-linux-gnu/libGLU.so
LIBS +=/usr/lib/i386-linux-gnu/libglut.so
INCLUDEPATH +=/usr/include/python2.7
LIBS += -L /usr/lib/python2.7 -lpython2.7
LIBS +=  /usr/lib/i386-linux-gnu/libboost_python-py27.so
LIBS +=`pkg-config opencv --libs`
FORMS    += arm.ui \
    Chess/chess.ui \
    Cognition/cognition.ui \
    ArmMove/armmodify.ui

RESOURCES += \
    img.qrc

OTHER_FILES += \
    chess/board.bmp \
    chess/chessboard.bmp \
    chess/chessmen.png \
    Chess/board.bmp \
    Chess/chessboard.bmp \
    Chess/chessmen.png \
    chess/board.bmp \
    chess/chessboard.bmp \
    chess/chessmen.png \
    python/SerialW.py \
    kernel/define_global.cpp.bak \
    ArmMove/python/play.pyc \
    ArmMove/python/process \
    ArmMove/python/play.py~ \
    ArmMove/python/play.py \
    ArmMove/python/SerialW.py
QMAKE_CXXFLAGS += -std=c++11
