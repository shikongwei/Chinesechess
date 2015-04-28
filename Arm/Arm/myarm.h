/******************************************************************************
 * @file myarm.h
 * define a class represent the arm with the length of the arm and so on feature
 * funtion to calculate the angle of each link to make terminal get to a specified position
 *
 *
 * ***************************************************************************/
#ifndef MYARM_H
#define MYARM_H
#include <math.h>
#include "Representation/Blackboard.h"
class MyArm
{
private:
    double length1;
    double length2;
    double height1;
    double height2;
public:
    MyArm();
    MyArm(double l1,double l2,double h1,double h2);
    class Angel
    {
    public:
        double angle1;
        double angle2;
        double angle3;
        double angle4;
    };
    void setPara(double l1,double l2,double h1,double h2);
    Angel calculateAngel(double x,double y);
    Angel calculateAngel(double x,double y,double z);
};

#endif // MYARM_H
