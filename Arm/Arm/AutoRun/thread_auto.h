#ifndef THREAD_AUTO_H
#define THREAD_AUTO_H
#include <QThread>
#include "myarm.h"
#include "Representation/Blackboard.h"
#include "ArmMove/armmodify.h"
#include <QDebug>
class ThreadAuto : public QThread
{
    Q_OBJECT
public:
    ThreadAuto() {moveToThread(this);}
protected:
    virtual void run();
signals:
    void threadSig();
public slots:
    void recSigFromDialog();
private:
    MyArm myarm;
    ArmModify armModify;
};
#endif // THREAD_AUTO_H
