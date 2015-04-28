#include "arm.h"
#include "ui_arm.h"
#include <iostream>
#include <string>
#include <math.h>
Arm::Arm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Arm)
{
    ui->setupUi(this);
    setGeometry(680-300,400-300,600,600);
    td=new Thread();
    td_send=new ThreadToSend();
    td_auto= new ThreadAuto();
}

Arm::~Arm()
{
    delete ui;
}

void Arm::on_Config_clicked()
{
    double length1=ui->length1->text().toDouble();
    double length2=ui->length2->text().toDouble();
    double height1=ui->height3->text().toDouble();
    double height2=ui->height4->text().toDouble();
    myarm.setPara(length1,length2,height1,height2);
}

void Arm::on_Calculate_clicked()
{
    double targetx= ui->TargetX->text().toDouble();
    double targety=ui->TargetY->text().toDouble();
    double targetz=ui->TargetZ->text().toDouble();
    std::cout<<targetx<<" "<<targety<<std::endl;
    MyArm::Angel angel= myarm.calculateAngel(targetx,targety,targetz);
    std::cout<<theAngle.angle1<<" "<<theAngle.angle2<<" "<<theAngle.angle3<<" "<<theAngle.angle4<<std::endl;
    return;


}

void Arm::on_Sim_clicked()
{
    td->start();
    //td_send->start();
}

void Arm::on_DrawCircle_clicked()
{
    double R;
    if(!ui->R->text().toStdString().empty())
        R=ui->R->text().toDouble();
    else
        R=1;

    for(int i=0;i<10000000;i++)
    {
        double theata=3.14/10000000.0*i;
        double x=R*cos(theata);
        double y=R*sin(theata);
        myarm.calculateAngel(x,y);
    }
}

void Arm::on_Move_clicked()
{
    double startx=ui->startx->text().toDouble();
    double starty=ui->starty->text().toDouble();
    double endx  =ui->endx->text().toDouble();
    double endy  =ui->endy->text().toDouble();
//    if(theMove.toMove)
//    {
//        startx=(theMove.startx-4)*0.35;
//        starty=(theMove.starty)*0.35;
//        endx=(theMove.endx-4)*0.35;
//        endy=(theMove.endy)*0.35;
//    }
    std::cout<<" sx: "<<startx<<" sy: "<<starty<<" endx: "<<endx<<" endy: "<<endy<<std::endl;
    double R=sqrt((startx-endx)*(startx-endx)+(starty-endy)*(starty-endy))/2;
    double centerx=(startx+endx)/2;
    double centery=(starty+endy)/2;
    double theata=atan2(endy-starty,endx-startx);
    std::cout<<"R:  "<<R<<"  theata:  "<<theata<<" center: "<<centerx<<","<<centery<<std::endl;
    theActionToSend.data="65535";
    for(int i=1;i<1000001;i++)
    {
        double alpha=3.14/1000000.0*i;

        double x=centerx-R*cos(alpha)*cos(theata);
        double y=centery-R*cos(alpha)*sin(theata);
        double z=R*sin(alpha);
        MyArm::Angel angel =  myarm.calculateAngel(x,y,z);

        if(i%100000==0)
        {
            vector<int> temp;
            temp.push_back(angel.angle1);
            temp.push_back(angel.angle2);
            temp.push_back(angel.angle3);
            temp.push_back(angel.angle4);
            theActionToSend.action.push_back(temp);
            theActionToSend.data+=" ";
            theActionToSend.data+=std::to_string(static_cast<int>(((angel.angle1*180/3.14))*2.77+748));//change angle to pwm
            theActionToSend.data+=" ";
            theActionToSend.data+=std::to_string(static_cast<int>(((angel.angle2*180/3.14))*2.77+749));
            theActionToSend.data+=" ";
            theActionToSend.data+=std::to_string(static_cast<int>(-((angel.angle3*180/3.14)+165)*2.84+912));
            theActionToSend.data+=" ";
            theActionToSend.data+=std::to_string(static_cast<int>(((angel.angle4*180/3.14)+130)*2.83+576));

            temp.clear();
        }
    }
     theActionToSend.action_ready=true;

    std::cout<<"data  "<<theActionToSend.data.size()<<std::endl;
}

void Arm::on_Auto_clicked()
{
    if(ui->ifAuto->isChecked())
    {
        td_auto->start();
    }
    else
    {
        td_auto->terminate();
    }
}
