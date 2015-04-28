#ifndef DRAWTOOL_H
#define DRAWTOOL_H

#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include "Representation/Blackboard.h"
using namespace std;
void drawCube(float x, float y, float z, float length, float height, float width);
void drawCubeWithAngel(float x, float y, float z, float length, float height, float width, float angle, char d);
void reshape(int w,int h);
void init();
void onMouseMove(int x,int y);
void Mouse(int button, int state, int x, int y);
void display(void);
#endif // DRAWTOOL_H
