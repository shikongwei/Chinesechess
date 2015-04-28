#ifndef ARMMODIFY_H
#define ARMMODIFY_H

#include <QMainWindow>
#include "Send/comm_armMove.h"
#include <QTimer>
#include <iostream>
#include <QMessageBox>
#include "Representation/Blackboard.h"
namespace Ui {
class ArmModify;
}

class ArmModify : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArmModify(QWidget *parent = 0);
    ~ArmModify();
public:
    void Move_Path(int from_line, int from_road, int to_line, int to_road, bool lift);
private slots:
    void on_Move_clicked();

    void on_MoveAngle_clicked();

    void on_pushButton_clicked();

    void on_move_path_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
    void timeToStop();

    void on_Lift_clicked();

private:
    Ui::ArmModify *ui;
    Comm_armMove *theComm;
    QTimer *timer;
    class Angle{
    public:
        double angle1;
        double angle2;
        double angle3;
        double angle4;
    };
    class Position{
    public:
        double x;
        double y;
        double z;
        Position(double xl,double yl,double zl)
        {
            x=xl;
            y=yl;
            z=zl;
        }
        Position()
        {

        }
    };
    Position chessPosition[10][9];
    Angle calculateAngel(double x,double y,double z);
};

#endif // ARMMODIFY_H
