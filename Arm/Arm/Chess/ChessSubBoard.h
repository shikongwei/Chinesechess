#ifndef CHESSSUBBOARD_H
#define CHESSSUBBOARD_H
//#include "chessSubWindow.h"
#include <QtGui/QtGui>
#include <QWidget>
#include <QMessageBox>
#include <QApplication>
#include "Point.h"
enum CHESS{B_CAR,B_HORSE,B_MINISTER,B_IMPERIAL,B_KING,B_CANON,B_PAWN,R_CAR,R_HORSE,R_MINISTER,R_IMPERIAL,R_KING,R_CANON,R_PAWN,NOCHESS};

class ChessSubBoard
{
public:
    ChessSubBoard();
    bool setChess(OurPoint,enum CHESS);
    enum CHESS getStatus(OurPoint);
    void resetChess();
    OurPoint CurrentPoint;
    OurPoint TargetPoint;
    int chess_num;
    bool needupdate;
    bool toSee;
    OurPoint StartPoint;
    OurPoint EndPoint;
    bool checkVision;
private:
    enum CHESS chess_location[10][9];
};

#endif // CHESSSUBBOARD_H
