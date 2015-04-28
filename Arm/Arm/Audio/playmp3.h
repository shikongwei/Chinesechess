#ifndef PLAYMP3_H
#define PLAYMP3_H
#include <QProcess>
#include <QString>
#include <QStringList>
#include "Representation/Blackboard.h"
#include "Chess/Point.h"
using namespace std;
class PlayMp3
{
public:
    PlayMp3();
    void play(QString num1,QString num2,QString num3,QString num4);
    void say(OurPoint from,OurPoint to);
    void sayHello();
private:
    QProcess *cmd;
};
 #endif // PLAYMP3_H
