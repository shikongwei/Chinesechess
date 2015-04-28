#include "simarm.h"


SimArm::SimArm():MyArm(1,1.5,0.5,0.2)
{
    chessBoardWidth=3.5;
    chessBoardLength=3.5;
    chessBoardHeight=0.3;
    armWidth=0.1;
}
SimArm::SimArm(double width,double length,double height,double l1,double l2,double h1,double h2,double armwidth):MyArm(l1,l2,h1,h2)
{

    chessBoardWidth=width;
    chessBoardLength=length;
    chessBoardHeight=height;
    armWidth=armwidth;

}
void SimArm::draw()
{
    int argc; char *argv[2];
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE| GLUT_DEPTH  );// add it to make the front can not diseapper the behind// ignore what I said just now

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("OpenGL");
    init();
    glutReshapeFunc( reshape );
    glutDisplayFunc(display);
    glutIdleFunc(display);  //设置不断调用显示函数
    glutMouseFunc(Mouse);
    glutMotionFunc(onMouseMove);
    glutMainLoop();

}
void SimArm::setAngel(double angel1,double angel2,double angle3,double angle4)
{
    angel.angle1=angel1;
    angel.angle2=angel2;
    angel.angle3=angle3;
    angel.angle4=angle4;
}
MyArm::Angel SimArm::getAngel()
{
    return angel;
}


