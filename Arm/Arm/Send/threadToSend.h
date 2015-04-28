#ifndef THREADTOSEND_H
#define THREADTOSEND_H
#include <QThread>
#include "comm.h"
class ThreadToSend : public QThread
{
    Q_OBJECT
public:
    ThreadToSend() {moveToThread(this);}
protected:
    virtual void run();
signals:
    void threadSig();
public slots:
    void recSigFromDialog();
};

#endif // THREADTOSEND_H
