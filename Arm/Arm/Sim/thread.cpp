#include "thread.h"
#include <QDebug>


void Thread::run()
{

         qDebug()<<"run in thread id is"<<currentThreadId();
//        emit threadSig();
//        exec();
//        sleep(1);
        SimArm mysim =SimArm();
        mysim.draw();


}
void Thread::recSigFromDialog()
{
    qDebug()<<"rec sig from dialog"<<"current thread id is"<<currentThreadId();
}
