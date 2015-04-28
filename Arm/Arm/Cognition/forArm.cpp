#include "cognition.h"
#include "ui_cognition.h"
#include <fstream>
double Cognition::calcuH(double R, double G, double B)
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
double Cognition::calcuS(double R, double G, double B)
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
double Cognition::calcuV(double R, double G, double B)
{
    return std::max(std::max(R,G),B);
}

Cognition::MyPoint Cognition::locationCorrect(MyPoint point, double height)
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
void Cognition::locationTest()
{

    Mat src=imread(("img"+QString().setNum(imgNum-1)+".jpg").toStdString());

    for(int row=0;row<10;row++)
    {
        for(int col=-4;col<5;col++)
        {
            MyPoint temp(row,col);
            MyPoint tempRight(row,(col-0.4));
            MyPoint tempLeft(row,(col+0.4));
            MyPoint tempFront((row+0.4),col);
            MyPoint tempBehind((row-0.4),col);
            MyPoint tempo=locationCorrect(temp);
            MyPoint tempoR=locationCorrect(tempRight);
            MyPoint tempoL=locationCorrect(tempLeft);
            MyPoint tempoF=locationCorrect(tempFront);
            MyPoint tempoB=locationCorrect(tempBehind);
            Point center(tempo.y,tempo.x);
            double Rx=sqrt((tempoR.x-tempoL.x)*(tempoR.x-tempoL.x)+(tempoR.y-tempoL.y)*(tempoR.y-tempoL.y))/2 ;
            double Ry=sqrt((tempoF.x-tempoB.x)*(tempoF.x-tempoB.x)+(tempoF.y-tempoB.y)*(tempoF.y-tempoB.y))/2 ;
            double R=sqrt(Rx*Rx+Ry*Ry)/2;
            circle(src,center,R,Scalar(124,111,25), -1, 8, 0);
            rectangle( src,
                       Point( tempoR.y,tempoF.x ),
                       Point( tempoL.y,tempoB.x),
                       Scalar( 0, 255, 255 ),
                       -1,
                       8 );

            int i=0;
            int j=0;
            for(int pi=static_cast<int>(tempoF.x);pi<static_cast<int>(tempoB.x);pi++)
            {

                for(int pj=static_cast<int>(tempoL.y);pj<static_cast<int>(tempoR.y);pj++)
                {

                    if(static_cast<int>(imgAfterRecolor.at<uchar>(pi,pj*3+2))==0)
                    {
                        j++;
                        //
                    }
                    else if(static_cast<int>(imgAfterRecolor.at<uchar>(pi,pj*3+1))==0)
                    {
                        i++;
                    }

                }

            }
           // cout<<"red "<<i<<"black "<<j<<" ";

        }
       // cout<<endl;
    }
    imshow("location",src);
}
void Cognition::recolorDir()
{
    Mat src=img.clone();
    int srcRow=src.rows;
    int srcCol=src.cols;
    for(int pi=0;pi<srcRow;pi++)
    {
        for(int pj=0;pj<srcCol;pj++)
        {
            if(colorRecognitionHSV(static_cast<int>(src.at<uchar>(pi,pj*3+2)),static_cast<int>(img.at<uchar>(pi,pj*3+1)),static_cast<int>(img.at<uchar>(pi,pj*3)))==1)
            {
                src.at<uchar>(pi,pj*3+2)=255;
                src.at<uchar>(pi,pj*3+1)=0;
                src.at<uchar>(pi,pj*3)=0;
            }
            else if(colorRecognitionHSV(static_cast<int>(src.at<uchar>(pi,pj*3+2)),static_cast<int>(img.at<uchar>(pi,pj*3+1)),static_cast<int>(img.at<uchar>(pi,pj*3)))==-1)
            {
                src.at<uchar>(pi,pj*3+2)=0;
                src.at<uchar>(pi,pj*3+1)=0;
                src.at<uchar>(pi,pj*3)=0;
            }
            else
            {
                src.at<uchar>(pi,pj*3+2)=255;
                src.at<uchar>(pi,pj*3+1)=255;
                src.at<uchar>(pi,pj*3)=255;
            }
        }
    }
    imgAfterRecolor=src;
    //imshow("recolor",src);
}

void Cognition::reColor()
{
    Mat src;
    if(ui->comboBox->currentIndex()==0)
    {
        src=imread(("img"+QString().setNum(imgNum-1)+".jpg").toStdString());
    }
    else if(ui->comboBox->currentIndex()==1)
    {
        src=imread(("imgEroded"+QString().setNum(imgNum-1)+".jpg").toStdString());
    }
    else
    {
        src=imread(("imgDilated"+QString().setNum(imgNum-1)+".jpg").toStdString());
    }

    int srcRow=src.rows;
    int srcCol=src.cols;
    for(int pi=0;pi<srcRow;pi++)
    {
        for(int pj=0;pj<srcCol;pj++)
        {
            if(colorRecognitionHSV(static_cast<int>(src.at<uchar>(pi,pj*3+2)),static_cast<int>(img.at<uchar>(pi,pj*3+1)),static_cast<int>(img.at<uchar>(pi,pj*3)))==1)
            {
                src.at<uchar>(pi,pj*3+2)=255;
                src.at<uchar>(pi,pj*3+1)=0;
                src.at<uchar>(pi,pj*3)=0;
            }
            else if(colorRecognitionHSV(static_cast<int>(src.at<uchar>(pi,pj*3+2)),static_cast<int>(img.at<uchar>(pi,pj*3+1)),static_cast<int>(img.at<uchar>(pi,pj*3)))==-1)
            {
                src.at<uchar>(pi,pj*3+2)=0;
                src.at<uchar>(pi,pj*3+1)=0;
                src.at<uchar>(pi,pj*3)=0;
            }
            else
            {
                src.at<uchar>(pi,pj*3+2)=255;
                src.at<uchar>(pi,pj*3+1)=255;
                src.at<uchar>(pi,pj*3)=255;
            }
        }
    }
    imgAfterRecolor=src;
    imshow("recolor",src);
    imwrite(("imgRecolored"+QString().setNum(imgNum-1)+".jpg").toStdString(),src);
}

int Cognition::colorRecognitionHSVWhenThre(int R, int G, int B)
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

int Cognition::colorRecognitionHSV(int R, int G, int B)
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
        if(S>100)
             return 1;
        else
             return 0;
    }
    else if(H<=60&&H>=-60)
    {
        if(V>50)
        {
            if(S>100)
                return 1;
            else
                return 0;
        }
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
void Cognition::chessPosition()
{


    for(int row=0;row<10;row++)
    {
        for(int col=-4;col<5;col++)
        {
            MyPoint tempRight(row,(col-0.4));
            MyPoint tempLeft(row,(col+0.4));
            MyPoint tempFront((row+0.4),col);
            MyPoint tempBehind((row-0.4),col);
            MyPoint tempoR=locationCorrect(tempRight);
            MyPoint tempoL=locationCorrect(tempLeft);
            MyPoint tempoF=locationCorrect(tempFront);
            MyPoint tempoB=locationCorrect(tempBehind);
            int j=0;
            for(int pi=static_cast<int>(tempoF.x);pi<static_cast<int>(tempoB.x);pi++)
            {

                for(int pj=static_cast<int>(tempoL.y);pj<static_cast<int>(tempoR.y);pj++)
                {

                    if(static_cast<int>(imgAfterThreshold.at<uchar>(pi,pj))==0)
                    {
                        j++;

                    }

                }

            }
           // cout<<j*100/((tempoB.x-tempoF.x)*(tempoR.y-tempoL.y))<<" ";//if j>40 there is chess
            if(row==9&&col==4)
            {
                if(j*100/((tempoB.x-tempoF.x)*(tempoR.y-tempoL.y))>ui->positionHold->text().toInt()-30)
                    chess_exist[row][col+4]=true;
                else
                    chess_exist[row][col+4]=false;
            }
            else
            {
                if(j*100/((tempoB.x-tempoF.x)*(tempoR.y-tempoL.y))>ui->positionHold->text().toInt())
                    chess_exist[row][col+4]=true;
                else
                    chess_exist[row][col+4]=false;
            }
            //cout<<chess_exist[row][col+4]<<" ";

        }
       // cout<<endl;
    }
}
void Cognition::chessColor()
{
    float chess_credibility[10][9];
    float chess_credibility_line[90];
    for(int row=0;row<10;row++)
    {
        for(int col=-4;col<5;col++)
        {
            //chess_color_count[row][col+4]=0;
            MyPoint tempRight(row,(col-0.4));
            MyPoint tempLeft(row,(col+0.4));
            MyPoint tempFront((row+0.4),col);
            MyPoint tempBehind((row-0.4),col);
            MyPoint tempoR=locationCorrect(tempRight);
            MyPoint tempoL=locationCorrect(tempLeft);
            MyPoint tempoF=locationCorrect(tempFront);
            MyPoint tempoB=locationCorrect(tempBehind);
            int j=0,i=0;
            if(chess_exist[row][col+4])
            {
                for(int pi=static_cast<int>(tempoF.x);pi<static_cast<int>(tempoB.x);pi++)
                {

                    for(int pj=static_cast<int>(tempoL.y);pj<static_cast<int>(tempoR.y);pj++)
                    {

                        if(static_cast<int>(imgAfterRecolor.at<uchar>(pi,pj*3+2))==0)
                        {
                            j++;
                        }
                        else if(static_cast<int>(imgAfterRecolor.at<uchar>(pi,pj*3+1))==0)
                        {
                            i++;
                        }

                    }

                }

                chess_credibility[row][col+4]=double(j)/double(i);
                chess_credibility_line[row*9+col+4]=double(j)/double(i);
                if(chess_credibility[row][col+4]<ui->ColorHold->text().toFloat()&&chess_credibility[row][col+4]!=0)//if it is zero,it is too perfect to be true
                    chess_color_count[row][col+4]++;
                else if(chess_credibility[row][col+4]>(1/ui->ColorHold->text().toFloat()))
                    chess_color_count[row][col+4]--;
                else
                {
                    chess_color_count[row][col+4]+=0;
                }
                if(row>4)
                {
                       chess_color_count[row][col+4]=12;
                }
            }
            else
            {
                chess_color_count[row][col+4]+=0;
                chess_credibility[row][col+4]=0;
                chess_credibility_line[row*9+col+4]=0;
            }
           // cout<<chess_credibility[row][col+4]<<" ";
            //cout<<chess_color[row][col+4]<<" ";


        }
       // cout<<endl;

    }
//    quickSort(chess_credibility_line,0,89);
//    int left=90-chess_num;
//    int right=89;
//    for(int i=90-chess_num;i<90;i++)
//    {

//    }
}
void Cognition::chessColorFinal()
{
    static int myTimer=0;
    if(myTimer>10)
    {
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<9;j++)
            {
                cout<<chess_color_count[i][j]<<" ";
                if(chess_color_count[i][j]>ui->colorCount->text().toInt())
                {
                    chess_color[i][j]=1;
                }
                else if(chess_color_count[i][j]<-ui->colorCount->text().toInt())
                {
                    chess_color[i][j]=-1;
                }
                else
                {
                    chess_color[i][j]=0;
                }

                chess_color_count[i][j]=0;
            }
            cout<<endl;
        }
        myTimer=0;
        chessChange();
        markMove();

    }
    else
    {
        myTimer++;
    }
}

void Cognition::chessMark()
{
   // Mat src=imread(("img"+QString().setNum(imgNum-1)+".jpg").toStdString());
    Mat src=img.clone();
    for(int row=0;row<10;row++)
    {
        for(int col=-4;col<5;col++)
        {
            MyPoint temp(row,col);
            MyPoint tempRight(row,(col-0.4));
            MyPoint tempLeft(row,(col+0.4));
            MyPoint tempFront((row+0.4),col);
            MyPoint tempBehind((row-0.4),col);
            MyPoint tempo=locationCorrect(temp);
            MyPoint tempoR=locationCorrect(tempRight);
            MyPoint tempoL=locationCorrect(tempLeft);
            MyPoint tempoF=locationCorrect(tempFront);
            MyPoint tempoB=locationCorrect(tempBehind);
            Point center(tempo.y,tempo.x);
            double Rx=sqrt((tempoR.x-tempoL.x)*(tempoR.x-tempoL.x)+(tempoR.y-tempoL.y)*(tempoR.y-tempoL.y))/2 ;
            double Ry=sqrt((tempoF.x-tempoB.x)*(tempoF.x-tempoB.x)+(tempoF.y-tempoB.y)*(tempoF.y-tempoB.y))/2 ;
            double R=sqrt(Rx*Rx+Ry*Ry)/2;
            if(chess_color[row][col+4]==1)
            {
                circle(src,center,R,Scalar(124,111,25), -1, 8, 0);
            }
            else if(chess_color[row][col+4]==-1)
            {
                circle(src,center,R,Scalar(255,0,0), -1, 8, 0);
            }

            rectangle( src,
                       Point( tempoR.y,tempoF.x ),
                       Point( tempoL.y,tempoB.x),
                       Scalar( 0, 255, 255 ),
                       1,
                       8 );




        }

    }
    imshow("location",src);
}
void Cognition::chessChange()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(chess_color[i][j]==0)//no chess
            {
                if(theChessBoard.getStatus(OurPoint(j,i))!=NOCHESS)
                {
                    chess_change[i][j]=-1;
                }
                else
                {
                    chess_change[i][j]=0;
                }
            }
            else if(chess_color[i][j]==1)//red
            {
                if(theChessBoard.getStatus(OurPoint(j,i))==NOCHESS)
                {
                    chess_change[i][j]=1;
                }
                else if(theChessBoard.getStatus(OurPoint(j,i))<7)
                {
                    chess_change[i][j]=2;
                }
                else
                {
                    chess_change[i][j]=0;
                }
            }
            else
            {
                if(theChessBoard.getStatus(OurPoint(j,i))==NOCHESS)
                {
                    chess_change[i][j]=1;
                }
                else if(theChessBoard.getStatus(OurPoint(j,i))>6)
                {
                    chess_change[i][j]=2;
                }
                else
                {
                    chess_change[i][j]=0;
                }
            }
            //cout<<chess_change[i][j]<<" ";
        }
       // cout<<endl;
    }
}
void Cognition::markMove()
{
    Mat src=img.clone();
    OurPoint startPoint(-1,-1);
    OurPoint endPoint(-1,-1);
    int count_from=0;
    int count_to=0;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(chess_change[i][j]==-1&&theChessBoard.getStatus(OurPoint(j,i))>6)//to do
            {
                startPoint.x=j;
                startPoint.y=i;
                count_from++;
            }
            else if(chess_change[i][j]==1||chess_change[i][j]==2)
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
    //cout<<count_from<<" "<<count_to<<endl;
    if(count_from==1&&count_to==1&&theChessBoard.toSee)
    {

        PlayMp3 play1=PlayMp3();
        play1.say(startPoint,endPoint);
        //cout<<"move from ("<<startPoint.y<<","<<startPoint.x<<") to ("<<endPoint.y<<","<<endPoint.x<<")"<<endl;
        theChessBoard.setChess(endPoint,theChessBoard.getStatus(startPoint));
        theChessBoard.setChess(startPoint,NOCHESS);
        theChessBoard.StartPoint=startPoint;
        theChessBoard.EndPoint=endPoint;
        theChessBoard.needupdate=true;//update chessboard
        //theChessBoard.toSee=false;

//        MyPoint starto=locationCorrect(MyPoint(startPoint.x,startPoint.y));
//        MyPoint endo=locationCorrect(MyPoint(endPoint.x,endPoint.y));
//        rectangle( src,
//                   Point( starto.y,starto.x ),
//                   Point( endo.y,endo.x+3),
//                   Scalar( 0, 255, 255 ),
//                   1,
//                   8 );
    }
    else
    {
        //cout<<"do nothing"<<endl;
    }
    //imshow("move",src);
}

int Cognition::colorRecognition(int R, int G, int B)
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
