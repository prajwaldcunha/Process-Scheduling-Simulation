#ifdef WIN32
#include<windows.h>
#endif
#include <iostream>
#include<math.h>
#include <iomanip>
#include <GL/glut.h>
#include<string.h>
#include<stdlib.h>
#include "Button.h"
#include "Shapes.h"
using namespace std;

Shapes sobj1;

Button::Button()
	{

	}

Button::Button(float x0,float y1,float x2,float y2,char *str1){
    	btnx1=x0;
		btny1=y1;
		btnx2=x2;
		btny2=y2;
		btnstate=1;
		strcpy(btnstr,str1);
}

void Button::draw(){

	/*setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(1.0,1.0,1.0);
	drawstring(btnx1+10,btny1+10,btnstr);
	*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0.1,0.9,0.1);
	glBegin(GL_POLYGON);
	glVertex2f(btnx1,btny1);
	glVertex2f(btnx1,btny2);
	glVertex2f(btnx2,btny2);
	glVertex2f(btnx2,btny1);
	glEnd();
	
	if(btnstate==0)
	{
		glColor3f(0.13,0.47,0.31);
		glLineWidth(5);
		glBegin(GL_LINES);
		glVertex2f(btnx1,btny1);
		glVertex2f(btnx2,btny1);
		glVertex2f(btnx2,btny1);
		glVertex2f(btnx2,btny2);
		glEnd();
	}
	else if(btnstate==1)
	{
		glColor3f(0.5,0.5,0.5);
		glLineWidth(5);
		glBegin(GL_LINES);
		glVertex2f(btnx1,btny1);
		glVertex2f(btnx1,btny2);
		glVertex2f(btnx1,btny2);
		glVertex2f(btnx2,btny2);
		glEnd();
	}
}


void Button::togglestate(void)
{
	btnstate=(btnstate==1)?0:1;
}
int Button::insidebutton(float x,float y,float x1,float x2,float y1,float y2)
{
	if(x>x1 &&  x<x2 && y>y1 && y<y2)
		return 1;
	else return 0;
}
