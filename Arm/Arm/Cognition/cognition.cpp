#include "cognition.h"
#include <iostream>
#include <vector>
#include "ui_cognition.h"

Cognition::Cognition(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Cognition)
{
    ui->setupUi(this);
    timer=new QTimer(this);
    //connect(timer,SIGNAL(timeout()),this,SLOT(chessChange()));
    //timer->start(3000);
    showFlag=false;
    imgNum=0;
    remapFlag=false;
    chess_num=32;
    red_num=16;
    black_num=16;
    ui->hold->setText("0");
    ui->positionHold->setText("60");
    ui->ColorHold->setText("1");
    ui->colorCount->setText("5");
   // ui->Eroded->setText("4");
    //ui->cErode->setCurrentIndex(3);
    ui->ErodeSize->setValue(1);
    for(int row=0;row<10;row++)
    {
        for(int col=-4;col<5;col++)
        {
            chess_color_count[row][col+4]=0;
        }
    }

}

Cognition::~Cognition()
{
    delete ui;
}

void Cognition::on_openCamera_clicked()
{
    capture.open(1);
    showFlag=true;
    showImg();
}

void Cognition::on_stopCamera_clicked()
{
    showFlag=false;
    capture.release();



}
void Cognition::showImg()
{
    while(showFlag)
    {
        capture>>img;
        if(remapFlag)
        {
            myRemap(img);
        }
        recolorDir();
        erodeDir();
        threshDir();
        chessPosition();
        chessColor();
        chessColorFinal();
        chessMark();
//        chessChange(); //call by chess ColorFinal
//        markMove();
        imshow("source_pic",img);



    }
}

void Cognition::on_Pause_clicked()
{
    showFlag=false;
}

void Cognition::on_start_clicked()
{
    showFlag=true;
    showImg();
}

void Cognition::on_Catch_clicked()
{

    imwrite(("img"+QString().setNum(imgNum)+".jpg").toStdString(),img);
    Mat temp=imread(("img"+QString().setNum(imgNum)+".jpg").toStdString());
    imshow(("img"+QString().setNum(imgNum)).toStdString(),temp);
    ui->Catch->setText(QString().setNum(imgNum));
    imgNum++;
}

void Cognition::on_Histogram_clicked()
{

   Mat src=imread(("img"+QString().setNum(imgNum-1)+".jpg").toStdString(),0);

   //cvtColor(src,hsv,CV_BGR2HSV);
   int gbins = 256;
       int histSize[] = {gbins};
       // hue varies from 0 to 179, see cvtColor
       float granges[] = { 0, 255 };

       const float* ranges[] = { granges };
       MatND hist;
       // we compute the histogram from the 0-th and 1-st channels
       int channels[] = {0};

       calcHist( &src, 1, channels, Mat(), // do not use mask
                hist, 1, histSize, ranges,
                true, // the histogram is uniform
                false );

        double maxValue=0,minValue=0;
        minMaxLoc(hist,&minValue,&maxValue,0,0);
        cout<<maxValue<<" "<<minValue<<endl;
        Mat histImg(histSize[0],histSize[0],CV_8U,Scalar(255));
        int hpt =static_cast<int>(0.9*histSize[0]);
        for(int h=0;h<histSize[0];h++)
        {
            float binVal =hist.at<float>(h);
            int intensity=static_cast<int>(binVal*hpt/maxValue);
            line(histImg,Point(h,histSize[0]),Point(h,histSize[0]-intensity),Scalar::all(0));
        }
       namedWindow( "Source", 1 );
       imshow( "Source", src );

       namedWindow( "hist", 1 );
       imshow("hist",histImg);
       waitKey();
}

void Cognition::threshDir()
{
    Mat src=imgAfterEroded;
    Mat gra;
    cvtColor(src,gra,CV_BGR2GRAY);
    Mat thresho;
    threshold(gra,thresho,ui->hold->text().toInt(),255,THRESH_BINARY);
    imwrite(("imgthreshold"+QString().setNum(imgNum-1)+".jpg").toStdString(),thresho);
    //imshow("threshold",thresho);
    imgAfterThreshold=thresho;
}

void Cognition::on_threshold_clicked()
{
    Mat src;
    if(ui->cthre->currentIndex()==0)
    {
        src=imread(("img"+QString().setNum(imgNum-1)+".jpg").toStdString(),0);
    }
    else if(ui->cthre->currentIndex()==1)
    {
        src=imread(("imgEroded"+QString().setNum(imgNum-1)+".jpg").toStdString(),0);
    }
    else
    {
        src=imread(("imgDilated"+QString().setNum(imgNum-1)+".jpg").toStdString(),0);
    }
    Mat thresho;
    //
    threshold(src,thresho,ui->hold->text().toInt(),255,THRESH_BINARY);
    imwrite(("imgthreshold"+QString().setNum(imgNum-1)+".jpg").toStdString(),thresho);
    imshow("threshold",thresho);
    imgAfterThreshold=thresho;
}

void Cognition::on_pushButton_clicked()
{
    Mat src=imread(("img"+QString().setNum(imgNum-1)+".jpg").toStdString(),0);
    Mat edge;
    Canny(src,edge,ui->edgeHoldlow->text().toInt(),ui->edgeHoldhigh->text().toInt());
    imwrite(("imgContour"+QString().setNum(imgNum-1)+".jpg").toStdString(),edge);
    imshow("Contours",edge);

}
void Cognition::myRemap(Mat &img)
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

void Cognition::on_remap_clicked()
{
    remapFlag=!remapFlag;
}

void Cognition::erodeDir()
{
    Mat src=img.clone();
    int erosion_type=MORPH_RECT;
    int erosion_size=ui->ErodeSize->text().toInt();
    //if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
    //else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
    //else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

    Mat element = getStructuringElement( erosion_type,
                                         Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                         Point( erosion_size, erosion_size ) );
    Mat erosion_dst;
    erode( src, erosion_dst, element );
    imgAfterEroded=erosion_dst;
    //imshow( "Erosion Demo", erosion_dst );
}

void Cognition::on_Eroded_clicked()
{
    Mat src;
        if(ui->cErode->currentIndex()==0)
        {
            src=imread(("img"+QString().setNum(imgNum-1)+".jpg").toStdString());
        }
        else if(ui->cErode->currentIndex()==1)
        {
            src=imread(("imgRecolored"+QString().setNum(imgNum-1)+".jpg").toStdString());
        }

      int erosion_type=MORPH_RECT;
      int erosion_size=ui->ErodeSize->text().toInt();
      //if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
      //else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
      //else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

      Mat element = getStructuringElement( erosion_type,
                                           Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                           Point( erosion_size, erosion_size ) );
      Mat erosion_dst;
      erode( src, erosion_dst, element );
      imshow( "Erosion Demo", erosion_dst );
      imwrite(("imgEroded"+QString().setNum(imgNum-1)+".jpg").toStdString(),erosion_dst);
}

void Cognition::on_Dialated_clicked()
{
    Mat src;
        if(ui->cDilate->currentIndex()==0)
        {
            src=imread(("img"+QString().setNum(imgNum-1)+".jpg").toStdString());
        }
        else if(ui->cDilate->currentIndex()==1)
        {
            src=imread(("imgRecolored"+QString().setNum(imgNum-1)+".jpg").toStdString());
        }

       int dilation_type=MORPH_RECT;
       int dilation_size=ui->DilateSize->text().toInt();
//      if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
//      else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
//      else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

      Mat element = getStructuringElement( dilation_type,
                                           Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                           Point( dilation_size, dilation_size ) );
      Mat dilation_dst;
      ///膨胀操作
      dilate( src, dilation_dst, element );
      imshow( "Dilation Demo", dilation_dst );
      imwrite(("imgDilated"+QString().setNum(imgNum-1)+".jpg").toStdString(),dilation_dst);
}

void Cognition::on_Location_clicked()
{
    locationTest();
}

void Cognition::on_Recolor_clicked()
{
    reColor();

}

void Cognition::on_pushButton_2_clicked()
{
    Mat src;
        if(ui->Cblur->currentIndex()==0)
        {
            src=imread(("img"+QString().setNum(imgNum-1)+".jpg").toStdString());
        }
        else if(ui->Cblur->currentIndex()==1)
        {
            src=imread(("imgRecolored"+QString().setNum(imgNum-1)+".jpg").toStdString());
        }
    Mat result;
    blur(src,result,Size(5,5));
    imgAfterRecolor=src.clone();
    imshow("blur",result);
}

void Cognition::on_ChessPosition_clicked()
{
    chessPosition();
}

void Cognition::on_chessColor_clicked()
{
    chessColor();
}

void Cognition::on_ChessMark_clicked()
{
    chessMark();
}
