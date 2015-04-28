#ifndef COGNITION_H
#define COGNITION_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QString>
#include <iostream>
#include "QuickSort.h"
#include "../Representation/Blackboard.h"
#include "Audio/playmp3.h"
#include "QTimer"
using namespace std;
using namespace  cv;
namespace Ui {
class Cognition;
}

class Cognition : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cognition(QWidget *parent = 0);
    ~Cognition();

private slots:
    void on_openCamera_clicked();

    void on_stopCamera_clicked();

    void on_Pause_clicked();

    void on_start_clicked();

    void on_Catch_clicked();

    void on_Histogram_clicked();

    void on_threshold_clicked();

    void on_pushButton_clicked();

    void on_remap_clicked();

    void on_Eroded_clicked();

    void on_Dialated_clicked();

    void on_Location_clicked();

    void on_Recolor_clicked();

    void on_pushButton_2_clicked();

    void on_ChessPosition_clicked();

    void on_chessColor_clicked();

    void on_ChessMark_clicked();
    void chessChange();
private:
    Ui::Cognition *ui;
    VideoCapture capture;
    Mat img;
    Mat imgAfterRecolor;
    Mat imgAfterEroded;
    Mat imgAfterThreshold;
    QTimer *timer;
    int chess_num;
    int red_num;
    int black_num;
    bool chess_exist[10][9];
    int chess_color[10][9];//1 is red -1 is black
    int chess_color_count[10][9];//1 is red -1 is black
    int chess_change[10][9];//0 keep -1 disappear 1 appear 2 color chang
    void showImg();
    bool showFlag;
    int imgNum;
    void myRemap(Mat &img);
    bool remapFlag;
    class MyPoint
    {
    public:
        double x;
        double y;
        MyPoint(double xt,double yt)
        {
            x=xt;
            y=yt;
        }
        MyPoint()
        {

        }
    };
    MyPoint locationCorrect(MyPoint point,double height=0.1/3.5);
    void recolorDir();
    void erodeDir();
    void threshDir();
    void locationTest();
    void reColor();
    void chessPosition();
    void chessColor();
    void chessColorFinal();
    //void chessChange();
    void chessMark();
    void markMove();
    int colorRecognition(int R,int G,int B);
    int colorRecognitionHSV(int R, int G, int B);
    int colorRecognitionHSVWhenThre(int R, int G, int B);
    double calcuH(double R,double G,double B);
    double calcuS(double R,double G,double B);
    double calcuV(double R,double G,double B);
    void chessboardRecognition();
    //enum CHESS_STATE{NONE,RED,BLACK};
    //enum CHESS_CHANGE{STILL,DISAPPEAR,CHANGECOLOR,APPEAR};
    //enum CHESS_STATE chess_state[10][9];
    //enum CHESS_CHANGE chess_change[10][9];
public slots:

};

#endif // COGNITION_H
