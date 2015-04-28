#include "ui_chess.h"
#include "chess.h"
#include <iostream>
Chess::Chess(QWidget* parent)
    :QWidget(parent),ui(new Ui::Chess)
{
    ui->setupUi(this);
     chessPixmap = QPixmap(":/img/chess/Chess/board.bmp");
     chess=QPixmap(":/img/chess/Chess/chessmen.png");
     //setGeometry(680-300,400-300,600,600);
     for(int i=0;i<14;i++)
     {
         chess_sub[i]=chess.copy(i*36,0,36,36);

     }
     play1=new PlayMp3();
     theBoard=&theChessBoard;
     get_flag=false;
     toMove_flag=false;
     //theVision=new Vision(1);
     theTimer=new QTimer(this);
     connect(theTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
     theTimer->start(ui->Delicacy->text().toInt());//every 500ms update chesstheBoard
     visionFlag=false;
     play1->sayHello();
     //resize(400,410);

}
void Chess::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,chessPixmap);
    for(int row=0;row<10;row++)
    {
        for(int col=0;col<9;col++)
        {
            switch(theBoard->getStatus(OurPoint(col,row)))
            {
                case B_CAR:
                    painter.drawPixmap(LEFT_WIDEH+col*GRID_WIDTH,TOP_HEIGHT+row*GRID_HEIGHT,chess_sub[1]);
                    break;
                case B_HORSE:
                    painter.drawPixmap(LEFT_WIDEH+col*GRID_WIDTH,TOP_HEIGHT+row*GRID_HEIGHT,chess_sub[2]);
                    break;
                case B_MINISTER:
                    painter.drawPixmap(LEFT_WIDEH+col*GRID_WIDTH,TOP_HEIGHT+row*GRID_HEIGHT,chess_sub[5]);
                    break;
                case B_IMPERIAL:
                    painter.drawPixmap(LEFT_WIDEH+col*GRID_WIDTH,TOP_HEIGHT+row*GRID_HEIGHT,chess_sub[4]);
                    break;
                case B_KING:
                    painter.drawPixmap(LEFT_WIDEH+col*GRID_WIDTH,TOP_HEIGHT+row*GRID_HEIGHT,chess_sub[0]);
                    break;
                case B_CANON:
                    painter.drawPixmap(LEFT_WIDEH+col*GRID_WIDTH,TOP_HEIGHT+row*GRID_HEIGHT,chess_sub[3]);
                    break;
                case B_PAWN:
                    painter.drawPixmap(LEFT_WIDEH+col*GRID_WIDTH,TOP_HEIGHT+row*GRID_HEIGHT,chess_sub[6]);
                    break;
                case R_CAR:
                    painter.drawPixmap(LEFT_WIDEH+col*GRID_WIDTH,TOP_HEIGHT+row*GRID_HEIGHT,chess_sub[8]);
                    break;
                case R_HORSE:
                    painter.drawPixmap(LEFT_WIDEH+col*GRID_WIDTH,TOP_HEIGHT+row*GRID_HEIGHT,chess_sub[9]);
                    break;
                case R_MINISTER:
                    painter.drawPixmap(LEFT_WIDEH+col*GRID_WIDTH,TOP_HEIGHT+row*GRID_HEIGHT,chess_sub[12]);
                    break;
                case R_IMPERIAL:
                    painter.drawPixmap(LEFT_WIDEH+col*GRID_WIDTH,TOP_HEIGHT+row*GRID_HEIGHT,chess_sub[11]);
                    break;
                case R_KING:
                    painter.drawPixmap(LEFT_WIDEH+col*GRID_WIDTH,TOP_HEIGHT+row*GRID_HEIGHT,chess_sub[7]);
                    break;
                case R_CANON:
                    painter.drawPixmap(LEFT_WIDEH+col*GRID_WIDTH,TOP_HEIGHT+row*GRID_HEIGHT,chess_sub[10]);
                    break;
                case R_PAWN:
                    painter.drawPixmap(LEFT_WIDEH+col*GRID_WIDTH,TOP_HEIGHT+row*GRID_HEIGHT,chess_sub[13]);
                    break;
                case NOCHESS:
                    //painter.drawPixmap(LEFT_WIDEH+col*GRID_WIDTH,TOP_HEIGHT+row*GRID_HEIGHT,chess_sub[13]);
                    break;
                default:
                    break;
            }
        }
    }
}
void Chess::mousePressEvent ( QMouseEvent * event)
{
    move(event->x(),event->y());
    //std::cout<<event->y()<<std::endl;
}
void Chess::move(int x,int y)
{

    int ncol =(x-33)/GRID_WIDTH, nrow=(y-35)/GRID_HEIGHT;
    double dcol = (x-33)/39.0, drow =(y-35)/39.0;
    std::cout<<"ncol  "<<ncol<<"  dcol  "<<dcol<<"  nrow   "<<nrow<<"  drow  "<<drow<<std::endl;

     if(dcol-ncol >0.3 && dcol-ncol <0.7)
         return;

     if(drow-nrow >0.3 && drow-nrow <0.7)
         return;


     if(dcol-ncol <= 0.3) x = ncol;
     if(dcol-ncol >= 0.7) x = ncol+1;

     if(drow-nrow <= 0.3) y = nrow ;
     if(drow-nrow >= 0.7) y = nrow+1;
     //std::cout<<"x  "<<x<<"   y  "<<y<<std::endl;
     if(theBoard->getStatus(OurPoint(x,y))!=NOCHESS&&get_flag==false)
     {
         theBoard->CurrentPoint=OurPoint(x,y);
         get_flag=true;
         //std::cout<<"get"<<std::endl;

     }
     else if(get_flag)
     {
         toMove_flag=true;
          //std::cout<<"tomove"<<std::endl;
     }
     else
     {
         theBoard->CurrentPoint=OurPoint(-1,-1);
         get_flag=false;
         //std::cout<<"nochess"<<std::endl;
     }
     if(toMove_flag)
     {
         theBoard->TargetPoint=OurPoint(x,y);
         if(theBoard->getStatus(OurPoint(x,y))!=NOCHESS)
         {
             //theMove.toEat=true;
             //std::cout<<"to eat"<<std::endl;
             theBoard->chess_num--;
             std::cout<<theBoard->chess_num<<std::endl;
         }
         else
         {
             //theMove.toEat=false;
         }

         play1->say(theBoard->CurrentPoint,theBoard->TargetPoint);

         theBoard->setChess(theBoard->TargetPoint,theBoard->getStatus(theBoard->CurrentPoint));
         theBoard->setChess(theBoard->CurrentPoint,NOCHESS);
         go(theBoard->CurrentPoint,theBoard->TargetPoint);

         get_flag=false;
         toMove_flag=false;
         theMove.startx=theBoard->CurrentPoint.x+1;//road
         theMove.starty=theBoard->CurrentPoint.y+1;//line
         theMove.endx=theBoard->TargetPoint.x+1;//road
         theMove.endy=theBoard->TargetPoint.y+1;//road
         theMove.toMove=true;
         theBoard->CurrentPoint=OurPoint(-1,-1);

     }
     else
         theMove.toMove=false;

     update();
}
Chess::~Chess()
{

}

//void ChessSubWindow::on_reset_clicked()
//{
//    board->resetChess();
//    update();
//}


void Chess::on_RESET_clicked()
{
        theBoard->resetChess();
        theBoard->chess_num=32;
        update();
}

void Chess::on_vision_clicked()
{
    visionFlag=true;

    //theVision->chessboardRecognition();
    theTimer->start(1000);
}
void Chess::myUpdate()
{
    if(theBoard->needupdate)
    {
        update();
        go(theBoard->StartPoint,theBoard->EndPoint);
        //PlayMp3 play1=PlayMp3();
        //play1.say(theBoard->StartPoint,theBoard->EndPoint);
    }
    theBoard->needupdate=false;

}
