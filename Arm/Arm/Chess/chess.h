#ifndef CHESS_H
#define CHESS_H
#include <QtGui/QtGui>
#include <QWidget>
#include <QMessageBox>
#include <QApplication>
#include "ChessSubBoard.h"
#include "Point.h"
#include "../Cognition/cognition.h"
#include "../Vision/vision.h"
#include "../Representation/Blackboard.h"
#include <QTimer>
#include <QWidget>
#include "../Audio/playmp3.h"
#define TOP_HEIGHT 18
#define LEFT_WIDEH 14
#define GRID_WIDTH 39
#define GRID_HEIGHT 39
#define BOTTOM_HEIGHT TOP_HEIGHT+9*GRID_HEIGHT
#define RIGHT_WIDTH LEFT_WIDEH +8*GRID_WIDTH

namespace Ui {
class Chess;
}

class Chess : public QWidget
{
    Q_OBJECT

public:
    explicit Chess(QWidget *parent = 0);
    bool visionFlag;
    ~Chess();
protected:
    void paintEvent (QPaintEvent *);
    void mousePressEvent ( QMouseEvent * event);
    void move(int x, int y);
    void compmove();
    int PVS(short ,int ,int);
    void go(OurPoint start,OurPoint target);
    void showMoveByComputer(short start,short target);

private slots:
    void on_RESET_clicked();

    void on_vision_clicked();
    void myUpdate();

private:
    Ui::Chess *ui;
    QPixmap chessPixmap;
    QPixmap chess;
    QPixmap chess_sub[14];
    ChessSubBoard* theBoard;
    QTimer *theTimer;
    int x,y;
    bool get_flag;
    bool toMove_flag;
    Vision *theVision;
    PlayMp3 *play1;


};

#endif // CHESS_H
