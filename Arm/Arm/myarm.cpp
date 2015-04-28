#include "myarm.h"
#include <iostream>
MyArm::MyArm()
{
}
MyArm::MyArm(double l1,double l2,double h1,double h2)
{
    length1=l1;
    length2=l2;
    height1=h1;
    height2=h2;
}
void MyArm::setPara(double l1,double l2,double h1,double h2)
{
    length1=l1;
    length2=l2;
    height1=h1;
    height2=h2;
    theLength.length2=length1;
    theLength.length3=length2;
    theLength.length1=height1;
    theLength.length4=height2;
}
MyArm::Angel MyArm::calculateAngel(double x,double y)
{
    Angel angel;
    double distance_hori =sqrt(x*x+y*y);//x
    //std::cout<<distance_hori<<std::endl;
    double distance_vert=height2-height1;//y
    double distance=sqrt(distance_hori*distance_hori+distance_vert*distance_vert);
    //std::cout<<(distance*distance+length1*length1-length2*length2)/2*distance*length1<<std::endl;
//    std::cout<<"hori_dis:  "<<distance_hori<<"  hori_ver  "<<distance_vert<<" "<<std::endl;
//    std::cout<<"hori_dis:  "<<distance_hori<<"  hori_ver  "<<distance_vert<<" "<<std::endl;
    angel.angle1=atan(y/x);
    double alpha1=acos((distance*distance+length1*length1-length2*length2)/(2*distance*length1));
//    std::cout<<alpha1<<std::endl;
    double alpha2=acos((distance*distance+length2*length2-length1*length1)/(2*distance*length2));
    double theta =atan(distance_vert/distance_hori);
    angel.angle2=theta+alpha1;
    angel.angle3=-alpha1-alpha2;
    angel.angle4=(-angel.angle3-angel.angle2)-1.57;
    angel.angle2=angel.angle2-1.57;
    theAngle.angle1=angel.angle1;
    theAngle.angle2=angel.angle2;
    theAngle.angle3=angel.angle3;
    theAngle.angle4=angel.angle4;
    return angel;
}
MyArm::Angel MyArm::calculateAngel(double x,double y,double z)
{
    Angel angel;
    double distance_hori =sqrt(x*x+y*y);//x
    //std::cout<<distance_hori<<std::endl;
    double distance_vert=height2+z-height1;//y
    double distance=sqrt(distance_hori*distance_hori+distance_vert*distance_vert);
    //std::cout<<(distance*distance+length1*length1-length2*length2)/2*distance*length1<<std::endl;
//    std::cout<<"hori_dis:  "<<distance_hori<<"  hori_ver  "<<distance_vert<<" "<<std::endl;
//    std::cout<<"hori_dis:  "<<distance_hori<<"  hori_ver  "<<distance_vert<<" "<<std::endl;
    angel.angle1=atan2(y,x);
    double alpha1=acos((distance*distance+length1*length1-length2*length2)/(2*distance*length1));
//    std::cout<<alpha1<<std::endl;
    double alpha2=acos((distance*distance+length2*length2-length1*length1)/(2*distance*length2));
    double theta =atan2(distance_vert,distance_hori);
    angel.angle2=theta+alpha1;
    angel.angle3=-alpha1-alpha2;
    angel.angle4=(-angel.angle3-angel.angle2)-1.57;
    angel.angle2=angel.angle2-1.57;
    theAngle.angle1=angel.angle1;
    theAngle.angle2=angel.angle2;
    theAngle.angle3=angel.angle3;
    theAngle.angle4=angel.angle4;
    return angel;
}
