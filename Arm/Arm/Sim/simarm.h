#ifndef SIMARM_H
#define SIMARM_H
#include "myarm.h"
#include "drawTool.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "Representation/Blackboard.h"
class SimArm : public MyArm
{
private:
    double chessBoardWidth;
    double chessBoardLength;
    double chessBoardHeight;
    double armWidth;
    Angel angel;
public:
    SimArm();
    SimArm(double width,double length,double height,double l1,double l2,double h1,double h2,double armwidth);
    void draw();
    void setAngel(double angel1,double angel2,double angle3,double angle4);
    Angel getAngel();

};

#endif // SIMARM_H
