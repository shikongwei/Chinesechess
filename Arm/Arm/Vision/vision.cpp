#include "vision.h"
Vision::Vision()
{
    capture = new VideoCapture(1);
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<9;j++)
        {
            grid_state[i][j]=0;
        }
    }

}
Vision::Vision(int i)
{
    capture =new VideoCapture(i);
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<9;j++)
        {
            grid_state[i][j]=0;
        }
    }


}
double Vision::calcuH(double R, double G, double B)
{

    if(R==G&&R==B)
    {
        return 0;
    }
    else if(R>G&&R>B)
    {
        if(B>G)
            return 60*(G-B)/(R-G);
        else
           return 60*(G-B)/(R-B);
    }
    else if(G>B&&G>R)
    {
        if(B>R)
            return 60*(B-R)/(G-R)+120;
        else
            return 60*(B-R)/(G-B)+120;
    }
    else
    {
        if(G>R)
            return 60*(R-G)/(B-R)+240;
        else
            return 60*(R-G)/(B-G)+240;
    }
}
double Vision::calcuS(double R, double G, double B)
{
    if(R==0&&G==0&&B==0)
    {
        return 0;
    }
    else
    {
       double max=std::max(std::max(R,G),B);
       double min =std::min(std::min(R,G),B);
       return (1-min/max)*255;
    }
}
double Vision::calcuV(double R, double G, double B)
{
    return std::max(std::max(R,G),B);
}
void Vision::myRemap(Mat &img)
{
    FileStorage readfs("camera.yml",FileStorage::READ);
    if(readfs.isOpened())
    {
        Mat cameraMatrix, distCoeffs;
        readfs["camera_matrix"]>>cameraMatrix;
        readfs["distortion_coefficients"]>>distCoeffs;
        Mat temp=img.clone();
        undistort(temp,img,cameraMatrix,distCoeffs);


    }
}
Vision::MyPoint Vision::locationCorrect(MyPoint point, double height)
{
    MyPoint returnPoint;
    fstream Lfile;
    Lfile.open("L",ios::in);
    vector<double> L;
    for(int i=0;i<11;i++)
    {
        double temp;
        Lfile>>temp;
        L.push_back(temp);
    }
    double x=point.x;
    double y=point.y;
    double z=height;
    double u=(L[0]*x+L[1]*y+L[2]*z+L[3])/(L[8]*x+L[9]*y+L[10]*z+1);
    double v=(L[4]*x+L[5]*y+L[6]*z+L[7])/(L[8]*x+L[9]*y+L[10]*z+1);
    returnPoint.x=u;
    returnPoint.y=v;
    return returnPoint;
}
int Vision::colorRecognitionHSVWhenThre(int R, int G, int B)
{
    double H=calcuH(R,G,B);
    double S=calcuS(R,G,B);
    double V=calcuV(R,G,B);
    if(H<30)
        return 1;
    else if(H<50)
    {
        if(V>50)
            return 1;
        else return -1;
    }
    else
            return -1;
}

int Vision::colorRecognitionHSV(int R, int G, int B)
{
    double H=calcuH(R,G,B);
    double S=calcuS(R,G,B);
    double V=calcuV(R,G,B);
    if(H>180)
    {
        if(S<40)
        return 0;
        else
            return -1;
    }
    else if(H>140)
    {
        return 0;
    }
    else if(H<=40&&H>=-40)
    {
        return 1;
    }
    else if(H<=60&&H>=-60)
    {
        if(V>50)
            return 1;
        else
            return -1;
    }
    else if(V<50)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int Vision::colorRecognition(int R, int G, int B)
{
//    if((R-G<10||R-G>-10)&&R>120&&G>120&&B>120&&B>R&&B>G)
//        return 0;
//    else if(R<50&&G<120&&B<120&&(G>(R*1.3)||B>(R*1.3)||(R<50&&G<50&&B<50&&R<G&&R<B)))
//        return -1;
//    else if(R>G&&R>B)
//        return 1;
//    else
//        return 0;
    /*the method below is great to cogn black*/
    if(R<50&&G<50&&B<50)
    {
        return -1;
    }
    else if(R>B+G)
    {
        return 1;
    }
    else if(R>140&&G>140&&B>140)
    {
        if(R>G&&R>B)
            return 1;
        else if(B>G&&B>R)
            return 0;
    }
    else if(R<140&&G<140&&B<140)
    {
        if(R>0.6*(B+G)&&R>B&&R>G)
            return 1;
    }
    else if(R<100&&G<100&&B<100&&R<0.6*(B+G))
        return -1;

     return 0;
}
/*******************************************************************
 * use to recognition where is red and where is black
 * it need a remaped img and the location correct function
 * it will show the result
 * ********************************************************************/
void Vision::chessboardRecognition()
{
    float grid_state_c[10][9];
    float grid_state_l[10][9];
    float grid_state_gray[10][9];
    while(1)
    {
        *capture>>img;
        myRemap(img);
        namedWindow("chessboard",1);
        Mat gray;
        cvtColor(img,gray,CV_BGR2GRAY);
        Mat thresh=myThreshold(gray);
        imshow("threshold",thresh);
        Mat couto=Contour(gray);
        imshow("contour",couto);
        for(int row=0;row<10;row++)
        {
            for(int col=-4;col<5;col++)
            {
                grid_state_l[row][col+4]=0;
                grid_state_c[row][col+4]=0;
                grid_state_gray[row][col+4]=0;
                MyPoint temp(row,col);
                MyPoint tempRight(row,(col-0.5));
                MyPoint tempLeft(row,(col+0.5));
                MyPoint tempFront((row+0.5),col);
                MyPoint tempBehind((row-0.5),col);
                MyPoint tempo=locationCorrect(temp);
                MyPoint tempoR=locationCorrect(tempRight);
                MyPoint tempoL=locationCorrect(tempLeft);
                MyPoint tempoF=locationCorrect(tempFront);
                MyPoint tempoB=locationCorrect(tempBehind);
                Point center(tempo.y,tempo.x);
                double Rx=sqrt((tempoR.x-tempoL.x)*(tempoR.x-tempoL.x)+(tempoR.y-tempoL.y)*(tempoR.y-tempoL.y))/2 ;
                double Ry=sqrt((tempoF.x-tempoB.x)*(tempoF.x-tempoB.x)+(tempoF.y-tempoB.y)*(tempoF.y-tempoB.y))/2 ;
                double R=sqrt(Rx*Rx+Ry*Ry)/2;
                circle(thresh,center,3,Scalar(124,111,25), -1, 8, 0);
                for(int pi=static_cast<int>(center.y-R);pi<static_cast<int>(center.y+R);pi++)
                {
                    for(int pj=static_cast<int>(center.x-R);pj<static_cast<int>(center.x+R);pj++)
                    {
                        grid_state_c[row][col+4]+=1;
                        //grid_state_gray[row][col+4]+=(255-static_cast<int>( thresh.at<uchar>(pi,pj)))/255;
                        grid_state_gray[row][col+4]+=(static_cast<int>( couto.at<uchar>(pi,pj)))/255;
                        if(static_cast<int>( thresh.at<uchar>(pi,pj))<125)
                        {
                            grid_state_l[row][col+4]+=colorRecognitionHSV(static_cast<int>(img.at<uchar>(pi,pj*3+2)),static_cast<int>(img.at<uchar>(pi,pj*3+1)),static_cast<int>(img.at<uchar>(pi,pj*3)));
                        }
                    }
                }
               grid_state_l[row][col+4]=grid_state_l[row][col+4]*1000/grid_state_c[row][col+4];
               grid_state_gray[row][col+4]=grid_state_gray[row][col+4]*1000/grid_state_c[row][col+4];
               cout<<grid_state_gray[row][col+4]<<" ";
               if(grid_state_gray[row][col+4]>150)
               {
                   if(grid_state_l[row][col+4]<-20)
                   {
                       circle(img,center,5,Scalar(124,111,25), -1, 8, 0);
                       grid_state[row][col+4]--;
                   }
                   else if(grid_state_l[row][col+4]>20)
                   {
                       circle(img,center,5,Scalar(0,0,255), -1, 8, 0);
                       grid_state[row][col+4]++;

                   }
               }
               else
               {

               }
            }
            cout<<endl;
            getChessState();
        }
        cout<<endl;
        char c =waitKey(100);
        if(c==49)
            break;
        imshow("chessboard",img);
    }
}
void Vision::getChessState()
{
    static int myTimer=0;
    if(myTimer>100)
    {
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<9;j++)
            {
                cout<<grid_state[i][j]<<" ";
                if(grid_state[i][j]>5)
                {
                    chess_state[i][j]=Vision::RED;
                }
                else if(grid_state[i][j]<-5)
                {
                    chess_state[i][j]=Vision::BLACK;
                }
                else
                {
                    chess_state[i][j]=Vision::NONE;
                }
                grid_state[i][j]=0;
            }
            cout<<endl;
        }
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<9;j++)
            {
                cout<<chess_state[i][j]<<" ";
            }
            cout<<endl;
        }
        myTimer=0;
        getChessChange();
    }
    else
    {
        myTimer++;
    }
}
void Vision::getChessChange()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(chess_state[i][j]==Vision::NONE)
            {
                if(theChessBoard.getStatus(OurPoint(j,i))!=NOCHESS)
                {
                    chess_change[i][j]=Vision::DISAPPEAR;
                }
                else
                {
                    chess_change[i][j]=Vision::STILL;
                }
            }
            else if(chess_state[i][j]==Vision::RED)
            {
                if(theChessBoard.getStatus(OurPoint(j,i))==NOCHESS)
                {
                    chess_change[i][j]=Vision::APPEAR;
                }
                else if(theChessBoard.getStatus(OurPoint(j,i))<7)
                {
                    chess_change[i][j]=Vision::CHANGECOLOR;
                }
                else
                {
                    chess_change[i][j]=Vision::STILL;
                }
            }
            else
            {
                if(theChessBoard.getStatus(OurPoint(j,i))==NOCHESS)
                {
                    chess_change[i][j]=Vision::APPEAR;
                }
                else if(theChessBoard.getStatus(OurPoint(j,i))>7)
                {
                    chess_change[i][j]=Vision::CHANGECOLOR;
                }
                else
                {
                    chess_change[i][j]=Vision::STILL;
                }
            }
            cout<<chess_change[i][j]<<" ";
        }
        cout<<endl;
    }
    changeChessBoard();
}
void Vision::changeChessBoard()
{
    OurPoint startPoint(-1,-1);
    OurPoint endPoint(-1,-1);
    int count_from=0;
    int count_to=0;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(chess_change[i][j]==Vision::DISAPPEAR&&chess_state[i][j]==1)//to do
            {
                startPoint.x=j;
                startPoint.y=i;
                count_from++;
            }
            else if(chess_change[i][j]==Vision::APPEAR||chess_change[i][j]==Vision::CHANGECOLOR)
            {
                endPoint.x=j;
                endPoint.y=i;
                count_to++;
            }
            else
            {

            }
        }
    }
    if(count_from==1&&count_to==1)
    {
        PlayMp3 play1=PlayMp3();
        play1.say(startPoint,endPoint);
        cout<<"move from ("<<startPoint.y<<","<<startPoint.x<<") to ("<<endPoint.y<<","<<endPoint.x<<")"<<endl;
        theChessBoard.setChess(endPoint,theChessBoard.getStatus(startPoint));
        theChessBoard.setChess(startPoint,NOCHESS);
        theChessBoard.StartPoint=startPoint;
        theChessBoard.EndPoint=endPoint;
        theChessBoard.needupdate=true;//update chessboard
    }
    else
    {
        cout<<"do nothing"<<endl;
    }
}
Mat Vision::myThreshold(Mat img)
{
    Mat thresho;
    threshold(img,thresho,100,255,THRESH_BINARY);
    return thresho;
}
Mat Vision::Contour(Mat img)
{
    Mat edge;
    Canny(img,edge,100,350);
    return edge;
}
