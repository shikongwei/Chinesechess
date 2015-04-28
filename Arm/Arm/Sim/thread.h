#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include "simarm.h"
class Thread : public QThread
{
    Q_OBJECT
public:
    Thread() {moveToThread(this);}
protected:
    virtual void run();
signals:
    void threadSig();
public slots:
    void recSigFromDialog();
};

#endif // THREAD_H
