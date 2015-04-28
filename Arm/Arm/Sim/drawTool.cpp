#include "drawTool.h"
static float c=M_PI/180.0f; //弧度和角度转换参数
static int du=90,oldmy=-1,oldmx=-1; //du是视点绕y轴的角度,opengl里默认y轴是上方向
static float r=1.5f,h=0.0f; //r是视点绕y轴的半径,h是视点高度即在y轴上的坐标

void drawCube(float x,float y,float z, float length,float height,float width)
{    //glRotatef(90.0,0.5,0.5,0.0);
    glBegin(GL_QUADS);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(x-length/2,y-height/2,z-width/2);
    glVertex3f(x-length/2,y+height/2,z-width/2);
    glVertex3f(x+length/2,y+height/2,z-width/2);
    glVertex3f(x+length/2,y-height/2,z-width/2);
    glColor3f(0.1,0.2,1);
    glVertex3f(x-length/2,y-height/2,z-width/2);
    glVertex3f(x-length/2,y+height/2,z-width/2);
    glVertex3f(x-length/2,y+height/2,z+width/2);
    glVertex3f(x-length/2,y-height/2,z+width/2);
    glColor3f(0.1,1,1);
    glVertex3f(x+length/2,y-height/2,z-width/2);
    glVertex3f(x+length/2,y+height/2,z-width/2);
    glVertex3f(x+length/2,y+height/2,z+width/2);
    glVertex3f(x+length/2,y-height/2,z+width/2);
    glColor3f(1.0,1.0,0.0);
    glVertex3f(x-length/2,y-height/2,z+width/2);
    glVertex3f(x-length/2,y+height/2,z+width/2);
    glVertex3f(x+length/2,y+height/2,z+width/2);
    glVertex3f(x+length/2,y-height/2,z+width/2);
    glColor3f(1.0,0.5,0.5);
    glVertex3f(x-length/2,y+height/2,z-width/2);
    glVertex3f(x-length/2,y+height/2,z+width/2);
    glVertex3f(x+length/2,y+height/2,z+width/2);
    glVertex3f(x+length/2,y+height/2,z-width/2);
    glColor3f(0.2,0.5,0.2);
    glVertex3f(x-length/2,y-height/2,z-width/2);
    glVertex3f(x-length/2,y-height/2,z+width/2);
    glVertex3f(x+length/2,y-height/2,z+width/2);
    glVertex3f(x+length/2,y-height/2,z-width/2);

    glEnd();
     //glutWireTeapot(3);


}
void drawCubeWithAngel(float x, float y, float z, float length, float height, float width,float angle,char d)
{

    float theata1=-angle;
    float tempx;
    float tempy;
    float tempz;
    float movex;
    float movey;
    float movez;
    switch (d) {
    case 'z':
        glRotatef(angle/3.14*180,0.0,0.0,1.0);
        tempx=(x-length/2)*cos(theata1)-(y-height/2)*sin(theata1);
        tempy=(x-length/2)*sin(theata1)+(y-height/2)*cos(theata1);
        tempz=z-width/2;
        movex=tempx-(x-length/2);
        movey=tempy-(y-height/2);
        movez=tempz-(z-width/2);
        glTranslatef(movex,movey,movez);
        drawCube(x,y,z, length,height,width);
        break;
    case 'y':
        glRotatef(angle/3.14*180,0.0,1.0,0.0);
        tempx=(x-length/2)*cos(theata1)+(z-width/2)*sin(theata1);
        tempy=y-height/2;
        tempz=-(x-length/2)*sin(theata1)+(z-width/2)*cos(theata1);
        movex=tempx-(x-length/2);
        movey=tempy-(y-height/2);
        movez=tempz-(z-width/2);

        glTranslatef(movex,movey,movez);
        drawCube(x,y,z, length,height,width);
        break;
    case 'x':
//        tempx=(x-length/2);
//        tempy=(y-height/2)*cos(theata1)-(z-width/2)*sin(theata1);
//        tempz=-(y-length/2)*sin(theata1)+(z-width/2)*cos(theata1);
//        movex=tempx-(x-length/2);
//        movey=tempy-(y-height/2);
//        movez=tempz-(z-width/2);
//        std::cout<<tempx<<" "<<tempy<<" "<<std::endl;
//        glTranslatef(movex,movey,movez);
//        drawCube(x,y,z, length,height,width);
//        break;
    default:
        break;
    }

}
void display(void)
{
    float height1=theLength.length1;
    float height2=theLength.length4;
    float length1=theLength.length2;
    float length2=theLength.length3;
    float armwidth=0.1;
    float chesswidth =3.5;
    float chesslength =3.5;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //printf("At:%.2f %.2f %.2f\n",r*cos(c*du),h,r*sin(c*du)); //这就是视点的坐标
    glLoadIdentity();
    glTranslatef(0,-2,-3);
    gluLookAt(r*cos(c*du), h, r*sin(c*du), 0, 0, 0, 0, 1, 0); //从视点看远点,y轴方向(0,1,0)是上方向

    glColor3f(1.0f, 0.0f, 0.0f);
    //glutWireTeapot(0.5f);
    drawCubeWithAngel(0,0,0,chesslength,0.2,chesswidth,0,'y');//chessboard
    //drawCube(-chesslength/2+armwidth/2,height1/2,armwidth/2,armwidth,height1,armwidth);
    drawCubeWithAngel(-chesslength/2+armwidth/2,height1/2,armwidth/2,armwidth,height1,armwidth,theAngle.angle1,'y');//part one of arm
    drawCubeWithAngel(-chesslength/2+armwidth/2,height1+length1/2,armwidth/2,armwidth,length1,armwidth,theAngle.angle2,'z');
    drawCubeWithAngel(-chesslength/2+armwidth/2,height1+length1+length2/2,armwidth/2,armwidth,length2,armwidth,theAngle.angle3,'z');
    drawCubeWithAngel(-chesslength/2+armwidth/2,height1+length1+length2+height2/2,armwidth/2,armwidth,height2,armwidth,theAngle.angle4,'z');
    glFlush();
    glutSwapBuffers();
}
void Mouse(int button, int state, int x, int y) //处理鼠标点击
{
    if(state==GLUT_DOWN) //第一次鼠标按下时,记录鼠标在窗口中的初始坐标
        oldmx=x,oldmy=y;
}
void onMouseMove(int x,int y) //处理鼠标拖动
{
    //printf("%d\n",du);
    du+=x-oldmx; //鼠标在窗口x轴方向上的增量加到视点绕y轴的角度上，这样就左右转了
    h +=0.03f*(y-oldmy); //鼠标在窗口y轴方向上的改变加到视点的y坐标上，就上下转了
    if(h>1.0f) h=1.0f; //视点y坐标作一些限制，不会使视点太奇怪
    else if(h<-1.0f) h=-1.0f;
    oldmx=x,oldmy=y; //把此时的鼠标坐标作为旧值，为下一次计算增量做准备
}
void init()
{
    glEnable(GL_DEPTH_TEST);
}
void reshape(int w,int h)
{
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(75.0f, (float)w/h, 1.0f, 1000.0f);
    glMatrixMode( GL_MODELVIEW );
}
