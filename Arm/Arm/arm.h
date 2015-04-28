#ifndef ARM_H
#define ARM_H

#include <QMainWindow>
#include "myarm.h"
#include "Sim/simarm.h"
#include "Sim/thread.h"
#include "AutoRun/thread_auto.h"
#include "Send/threadToSend.h"
#include "Representation/Blackboard.h"
//extern SimArm mysim;
namespace Ui {
class Arm;
}

class Arm : public QMainWindow
{
    Q_OBJECT

public:
    explicit Arm(QWidget *parent = 0);
    ~Arm();

private slots:
    void on_Config_clicked();

    void on_Calculate_clicked();

    void on_Sim_clicked();

    void on_DrawCircle_clicked();

    void on_Move_clicked();

    void on_Auto_clicked();

private:
    Ui::Arm *ui;
    MyArm myarm;
    Thread *td;
    ThreadToSend *td_send;
    ThreadAuto *td_auto;
};

#endif // ARM_H
