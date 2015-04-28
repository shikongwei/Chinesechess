#ifndef VISION_H
#define VISION_H
#include <opencv2/opencv.hpp>
#include <fstream>
#include <QTimer>
#include <vector>
#include <iostream>
#include <QObject>
#include<math.h>
#include "Representation/Blackboard.h"
#include "Audio/playmp3.h"
using namespace std;
using namespace cv;
class Vision
{
private:
    VideoCapture *capture;
    Mat img;
     int grid_state[10][9];
public:
    Vision();
    Vision(int i);
    void myRemap(Mat &img);
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
    int colorRecognition(int R,int G,int B);
    int colorRecognitionHSV(int R, int G, int B);
    int colorRecognitionHSVWhenThre(int R, int G, int B);
    double calcuH(double R,double G,double B);
    double calcuS(double R,double G,double B);
    double calcuV(double R,double G,double B);
    void chessboardRecognition();
    Mat myThreshold(Mat img);
    Mat Contour(Mat img);
    enum CHESS_STATE{NONE,RED,BLACK};
    enum CHESS_CHANGE{STILL,DISAPPEAR,CHANGECOLOR,APPEAR};
    enum CHESS_STATE chess_state[10][9];
    enum CHESS_CHANGE chess_change[10][9];
public slots:
    void getChessChange();
    void getChessState();
    void changeChessBoard();
};

#endif // VISION_H
