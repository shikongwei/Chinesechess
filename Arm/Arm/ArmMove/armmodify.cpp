#include "armmodify.h"
#include "ui_armmodify.h"
#include <string>
#include <fstream>
#include <QString>
using namespace std;
ArmModify::ArmModify(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArmModify)
{

    ui->setupUi(this);
    theComm=new Comm_armMove();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeToStop()));
    //timer->start(120000);
    fstream posi;
    posi.open("position",fstream::in);
    for(int j=0;j<10;j++)
    {
        for(int i=0;i<9;i++)
        {
            double x,y,z;
            posi>>x;
            posi>>y;
            posi>>z;
            Position po(x,y,z);
            chessPosition[j][i]=po;
            //cout<<po.x<<" "<<po.y<<" "<<po.z<<endl;
        }
    }
    posi.close();

}

ArmModify::~ArmModify()
{
    delete ui;
}

void ArmModify::on_Move_clicked()
{
    string pwm1=ui->pwm1->text().toStdString();
    string pwm2=ui->pwm2->text().toStdString();
    string pwm3=ui->pwm3->text().toStdString();
    string pwm4=ui->pwm4->text().toStdString();
    theComm->Send(pwm1,pwm2,pwm3,pwm4);
}

void ArmModify::on_MoveAngle_clicked()
{
    int angle1=ui->angle1->text().toInt();
    int angle2=ui->angle2->text().toInt();
    int angle3=ui->angle3->text().toInt();
    int angle4=ui->angle4->text().toInt();
    theComm->SendAngle(angle1,angle2,angle3,angle4);
}

void ArmModify::on_pushButton_clicked()
{
    double x=ui->line->text().toDouble();
    double y=ui->road->text().toDouble();
    x=x*3.5+13;
    y=(y-5)*3.5-6;
    double z=0.5;
    cout<<"x "<<x<<" y "<<y<<" z "<<z<<endl;
    theComm->SendPosition(x,y,z);
}
void ArmModify::Move_Path(int from_line, int from_road, int to_line, int to_road,bool lift)
{
    double startx=0;
    double starty=0;
    double startz=0;
    double endx=0;
    double endy=0;
    double endz=0;
    bool from_rest=false;
    bool to_rest=false;
    theActionToSend.action_done=false;
    if(from_line==0&&from_road==0)//the rest position of arm
    {
        from_rest=true;
    }
    if(to_line==0&&to_road==0)
    {
        to_rest=true;
    }
    if(from_line<1)//1~10 line
        from_line=1;
    else if(from_line>10)
        from_line=10;
    if(from_road<1)//1~9 road
        from_road=1;
    else if(from_road>9)
        from_road=9;
    if(to_line<1)
        to_line=1;
    else if(to_line>10)
        to_line=10;
    if(to_road<1)
        to_road=1;
    else if(to_road>9)
        to_road=9;
    startx=chessPosition[from_line-1][from_road-1].x;
    starty=chessPosition[from_line-1][from_road-1].y;
    startz=chessPosition[from_line-1][from_road-1].z;
    endx=chessPosition[to_line-1][to_road-1].x;
    endy=chessPosition[to_line-1][to_road-1].y;
    endz=chessPosition[to_line-1][to_road-1].z;
    if(from_rest)
    {
        startx=17;
        starty=10;
        startz=0;
    }
    if(to_rest)
    {
        endx=17;
        endy=10;
        endz=0;
    }



    string dataToSend;
    double R=sqrt((startx-endx)*(startx-endx)+(starty-endy)*(starty-endy)+(startz-endz)*(startz-endz))/2;
    double centerx=(startx+endx)/2;
    double centery=(starty+endy)/2;
    double centerz=(startz+endz)/2;
    double theata=atan2(endy-starty,endx-startx);
    double beta=atan2((endz-startz),sqrt((startx-endx)*(startx-endx)+(starty-endy)*(starty-endy)));
    cout<<"center z "<<centerz<<endl;
    cout<<"beta "<<beta<<endl;
    for(int i=1;i<1000001;i++)
    {
        double alpha=3.14/1000000.0*i-beta;
        double x=centerx-R*cos(alpha)*cos(theata);
        double y=centery-R*cos(alpha)*sin(theata);
        double z=R*sin(3.14-alpha)+centerz;
        Angle angel =  calculateAngel(x,y,z);
        theAngle.angle1=angel.angle1*3.14/180;
        theAngle.angle2=angel.angle2*3.14/180;
        theAngle.angle3=angel.angle3*3.14/180;
        theAngle.angle4=angel.angle4*3.14/180;
        if(i%10000==0)//use 100 of all data
        {
            dataToSend+=" ";
            dataToSend+=std::to_string(static_cast<int>(((angel.angle1))*30/11+730));//change angle to pwm
            dataToSend+=" ";
            dataToSend+=std::to_string(static_cast<int>(((angel.angle2))*30/11+770));
            dataToSend+=" ";
            dataToSend+=std::to_string(static_cast<int>(-((angel.angle3))*390/90+260));
            dataToSend+=" ";
            dataToSend+=std::to_string(static_cast<int>(((angel.angle4))*260/90+950));
            ui->angle_cal1->setText(QString().setNum(angel.angle1));
            ui->angle_cal2->setText(QString().setNum(angel.angle2));
            ui->angle_cal3->setText(QString().setNum(angel.angle3));
            ui->angle_cal4->setText(QString().setNum(angel.angle4));
            ui->modify_x->setText(QString().setNum(x));
            ui->modify_y->setText(QString().setNum(y));
            ui->modify_z->setText(QString().setNum(z));


        }
    }
    dataToSend+=" ";
    theComm->lift=lift;
    theComm->SendPath(dataToSend);
    theActionToSend.action_done=true;

}

void ArmModify::on_move_path_clicked()
{
    double startx=0;
    double starty=0;
    double startz=0;
    double endx=0;
    double endy=0;
    double endz=0;
    int from_line=ui->fromline->text().toInt();
    if(from_line<1)
        from_line=1;
    else if(from_line>10)
        from_line=10;
    int from_road=ui->fromRoad->text().toInt();
    if(from_road<1)
        from_road=1;
    else if(from_road>9)
        from_road=9;
    int to_line=ui->toline->text().toInt();
    if(to_line<1)
        to_line=1;
    else if(to_line>10)
        to_line=10;
    int to_road=ui->toroad->text().toInt();
    if(to_road<1)
        to_road=1;
    else if(to_road>9)
        to_road=9;
    if(!ui->useDafault->isChecked())
    {
        startx=chessPosition[from_line-1][from_road-1].x;
        starty=chessPosition[from_line-1][from_road-1].y;
        startz=chessPosition[from_line-1][from_road-1].z;
        endx=chessPosition[to_line-1][to_road-1].x;
        endy=chessPosition[to_line-1][to_road-1].y;
        endz=chessPosition[to_line-1][to_road-1].z;
        if(ui->from_rest->isChecked())
        {
            startx=17;
            starty=10;
            startz=0;
        }
        if(ui->to_rest->isChecked())
        {
            endx=17;
            endy=10;
            endz=0;
        }
        cout<<"not default"<<endl;
    }
    else
    {
        startx=(ui->fromline->text().toDouble()-1)*3.5+13;
        starty=(ui->fromRoad->text().toDouble()-5)*3.5-6;
        endx=(ui->toline->text().toDouble()-1)*3.5+13;
        endy=(ui->toroad->text().toDouble()-5)*3.5-6;
        cout<<"default"<<endl;
    }

    string dataToSend;
    double R=sqrt((startx-endx)*(startx-endx)+(starty-endy)*(starty-endy)+(startz-endz)*(startz-endz))/2;
    double centerx=(startx+endx)/2;
    double centery=(starty+endy)/2;
    double centerz=(startz+endz)/2;
    double theata=atan2(endy-starty,endx-startx);
    double beta=atan2((endz-startz),sqrt((startx-endx)*(startx-endx)+(starty-endy)*(starty-endy)));
    cout<<"center z "<<centerz<<endl;
    cout<<"beta "<<beta<<endl;
    for(int i=1;i<1000001;i++)
    {
        double alpha=3.14/1000000.0*i-beta;
        double x=centerx-R*cos(alpha)*cos(theata);
        double y=centery-R*cos(alpha)*sin(theata);
        double z=R*sin(3.14-alpha)+centerz;
        Angle angel =  calculateAngel(x,y,z);
        if(i%10000==0)//use 100 of all data
        {
            dataToSend+=" ";
            dataToSend+=std::to_string(static_cast<int>(((angel.angle1))*30/11+730));//change angle to pwm
            dataToSend+=" ";
            dataToSend+=std::to_string(static_cast<int>(((angel.angle2))*30/11+770));
            dataToSend+=" ";
            dataToSend+=std::to_string(static_cast<int>(-((angel.angle3))*390/90+260));
            dataToSend+=" ";
            dataToSend+=std::to_string(static_cast<int>(((angel.angle4))*260/90+950));
            ui->angle_cal1->setText(QString().setNum(angel.angle1));
            ui->angle_cal2->setText(QString().setNum(angel.angle2));
            ui->angle_cal3->setText(QString().setNum(angel.angle3));
            ui->angle_cal4->setText(QString().setNum(angel.angle4));
            ui->modify_x->setText(QString().setNum(x));
            ui->modify_y->setText(QString().setNum(y));
            ui->modify_z->setText(QString().setNum(z));


        }
    }
    dataToSend+=" ";
    theComm->SendPath(dataToSend);
}
ArmModify:: Angle ArmModify::calculateAngel(double x, double y, double z)
{
    double length1=22.8;
    double length2=24.2;
    double height1=19.9;
    double height2=24.8;
    double distance_hori =sqrt(x*x+y*y);//x
    double distance_vert=height2+z-height1;//y
    double distance=sqrt(distance_hori*distance_hori+distance_vert*distance_vert);
    double angle1=atan2(y,x);
    double alpha1=acos((distance*distance+length1*length1-length2*length2)/(2*distance*length1));
    double alpha2=acos((distance*distance+length2*length2-length1*length1)/(2*distance*length2));
    double theta =atan2(distance_vert,distance_hori);
    double angle2=theta+alpha1;
    double angle3=-alpha1-alpha2;
    double angle4=(-angle3-angle2)-1.57;
    angle2=angle2-1.57;
    angle1=angle1*180/3.1415926;
    angle2=angle2*180/3.1415926;
    angle3=angle3*180/3.1415926;
    angle4=angle4*180/3.1415926;
    Angle reAngle;
    reAngle.angle1=angle1;
    reAngle.angle2=angle2;
    reAngle.angle3=angle3;
    reAngle.angle4=angle4;
    return reAngle;
    //SendAngle(angle1,angle2,angle3,angle4);
}

void ArmModify::on_pushButton_2_clicked()
{
    int tempr=ui->fromRoad->text().toInt();
    int templ=ui->fromline->text().toInt();
    ui->fromRoad->setValue(ui->toroad->text().toInt());
    ui->fromline->setValue(ui->toline->text().toInt());
    ui->toroad->setValue(tempr);
    ui->toline->setValue(templ);
}

void ArmModify::on_pushButton_3_clicked()
{
    double x=ui->modify_x->text().toDouble();
    double y=ui->modify_y->text().toDouble();
    double z=ui->modify_z->text().toDouble();
    theComm->SendPosition(x,y,z);
    Angle angel =  calculateAngel(x,y,z);
    ui->angle_cal1->setText(QString().setNum(angel.angle1));
    ui->angle_cal2->setText(QString().setNum(angel.angle2));
    ui->angle_cal3->setText(QString().setNum(angel.angle3));
    ui->angle_cal4->setText(QString().setNum(angel.angle4));
    if(ui->checkBox->isChecked())
    {
        Position po(x,y,z);
        chessPosition[ui->toline->text().toInt()-1][ui->toroad->text().toInt()-1]=po;
        cout<<"po: "<<ui->toline->text().toInt()<<" "<<ui->toroad->text().toInt()<<" "<<x<<" "<<y<<" "<<z<<endl;
    }
}

void ArmModify::on_pushButton_4_clicked()
{
    fstream positi;
    positi.open("position",fstream::out);
    for(int j=0;j<10;j++)
    {
        for(int i=0;i<9;i++)
        {

            positi<<chessPosition[j][i].x<<" "<<chessPosition[j][i].y<<" "<<chessPosition[j][i].z<<endl;
        }
    }
    positi.close();

}

void ArmModify::timeToStop()
{

    QMessageBox::about(this,tr("Note!"),tr("steer need rest"));
}

void ArmModify::on_Lift_clicked()
{
    cout<<ui->Lift->isChecked()<<endl;

    theComm->lift=ui->Lift->isChecked();
}
