#include "threadToSend.h"
#include <QDebug>

void ThreadToSend::run()
{

    Comm theComm=Comm();
    theComm.Communicate();

}
void ThreadToSend::recSigFromDialog()
{
    qDebug()<<"rec sig from dialog"<<"current thread id is"<<currentThreadId();
}

