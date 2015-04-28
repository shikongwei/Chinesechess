#include "comm_armMove.h"
#include <string>
#include <QString>
#include <iostream>
#include <math.h>
using namespace std;
Comm_armMove::Comm_armMove()
{
    python=new pyinit();
    lift=false;

}
void Comm_armMove::Send(string pwm1,string pwm2,string pwm3,string pwm4)
{
    object main_ns=import("__main__").attr("__dict__");//import dictionary of python
        try
        {
            object result=exec_file("../Arm/python/SerialW.py",main_ns,main_ns);//relative path
            object send=main_ns["send"];
            object rece=main_ns["rece"];
            string  data;
            data="65535";
            for(unsigned int num=0;num<10;num++)
            {
                data+=" ";
                data+=pwm1;
                data+=" ";
                data+=pwm2;
                data+=" ";
                data+=pwm3;
                data+=" ";
                data+=pwm4;
            }
            data+=" ";
            if(lift)
                data+="1";
            else
                data+="0";
            send(data);
            while(1)
            {
                cout<<"waiting rece"<<endl;
                object recedata=rece(1);
                string receData=extract<string>(recedata);
                cout<<receData<<endl;
                if(receData[0]=='1')
                {

                    cout<<"action_done "<<endl;
                    break;
                }
            }
       }
       catch(...)
       {
           pyinit::err_print();
       }
}
void Comm_armMove::SendAngle(int angle1, int angle2, int angle3, int angle4)
{
    string pwm1=std::to_string((30*angle1/11)+730);
    string pwm2=std::to_string((30*angle2/11)+770);
    string pwm3=std::to_string(-(angle3*390/90)+260);
    string pwm4=std::to_string((angle4*260/90)+950);
    Send(pwm1,pwm2,pwm3,pwm4);
}
void Comm_armMove::SendPosition(double x, double y, double z)
{
    double length1=22.8;
    double length2=24.2;
    double height1=19.9;
    double height2=24.5;
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
    std::cout<<angle1<<" "<<angle2<<" "<<angle3<<" "<<angle4<<std::endl;
    SendAngle(angle1,angle2,angle3,angle4);
}
void Comm_armMove::SendPath(string theActionToSendData)
{
    object main_ns=import("__main__").attr("__dict__");//import dictionary of python
    object result=exec_file("../Arm/python/SerialW.py",main_ns,main_ns);//relative path
    object send=main_ns["send"];
    object rece=main_ns["rece"];
    for(unsigned int num=0;num<10;num++)
    {
        string data="65535";
        for(unsigned int i=0;i<40;i++)
        {
            data+=" ";
            theActionToSendData=theActionToSendData.substr(1);
            data+=theActionToSendData.substr(0,theActionToSendData.find_first_of(' '));
            theActionToSendData=theActionToSendData.substr(theActionToSendData.find_first_of(' '));
        }
        data+=" ";
        if(lift)
            data+="1";
        else
            data+="0";

        send(data);
        while(1)
        {
            cout<<"waiting rece"<<endl;
            object recedata=rece(1);
            string receData=extract<string>(recedata);
            cout<<receData<<endl;
            if(receData[0]=='1')
            {

                cout<<"action_done "<<num<<endl;
                break;
            }
        }
    }
}



void Comm_armMove::Communicate()
{
    object main_ns=import("__main__").attr("__dict__");//import dictionary of python
        try
        {
            object result=exec_file("../Arm/python/SerialW.py",main_ns,main_ns);//relative path
            object send=main_ns["send"];
            object rece=main_ns["rece"];
            string  data;
            data="65535";
            for(unsigned int num=0;num<10;num++)
            {

            }
            while(1)
            {
                cout<<"waiting rece"<<endl;
                object recedata=rece(1);
                string receData=extract<string>(recedata);
                cout<<receData<<endl;
                if(receData[0]=='1')
                {

                    cout<<"action_done "<<endl;
                    break;
                }
            }
       }
       catch(...)
       {
           pyinit::err_print();
       }
}
Comm_armMove::~Comm_armMove()
{

}

