#include "arm.h"
#include "Chess/chess.h"
#include "Cognition/cognition.h"
#include "ArmMove/armmodify.h"
#include <QApplication>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Arm w;
    w.show();
    Chess ch;
    ch.show();
    Cognition cog;
    cog.show();
    ArmModify modify;
    modify.show();

    return a.exec();
}
