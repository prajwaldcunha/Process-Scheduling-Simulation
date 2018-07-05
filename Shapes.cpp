#ifdef WIN32
#include<windows.h>
#endif
#include <iostream>
#include<math.h>
#include <iomanip>
#include <GL/glut.h>
#include "Shapes.h"
using namespace std;

void Shapes :: drawTriangleShape(GLint x1,GLint y1,GLint x2,GLint y2,GLint x3,GLint y3){


    glClearColor(1.0,1.0,1.0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_TRIANGLES);
    glVertex2i(x1,y1);
    glVertex2i(x2,y2);
    glVertex2i(x3,y3);
    glEnd();
    glFlush();
}

void Shapes :: headingText(char s[],float x,float y,float z,float sx,float sy,float sz){
    int i;
     glPushMatrix();
     glLineWidth(2.5);
     glTranslatef(x, y,z);
     glScalef(sx,sy,sz);
    // glColor3f(1.0, 0.25, 0);
    for (i=0;s[i]; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN , s[i]);
	}
    glPopMatrix();
}

void Shapes :: text(char s[],float x,float y,float z){
  int i;
	glRasterPos3f(x, y,z);
    for (i=0;s[i]; i++)	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
	}
}

void Shapes :: drawCircle(float x, float y, float radius) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);
    static const int circle_points = 100;
    static const float angle = 2.0f * 3.1416f / circle_points;
    glBegin(GL_POLYGON);
    double angle1=0.0;
    glVertex2d(radius * cos(0.0) , radius * sin(0.0));
    int i;
    for (i=0; i<circle_points; i++)
    {
        glVertex2d(radius * cos(angle1), radius *sin(angle1));
        angle1 += angle;
    }
    glEnd();
    glPopMatrix();
}

void Shapes :: drawSemiCircle(float x, float y, float radius,float rotateangle,float x1,float y1,float z1) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
  
    glTranslatef(x, y, 0.0f);
      glRotatef(rotateangle,0,0,1);
    static const int circle_points = 100;
    static const float angle =  3.1416f / circle_points;
    glBegin(GL_POLYGON);
    glColor3f(0.3,0.8,0.3);
    double angle1=0.0;
    glVertex2d(radius * cos(0.0) , radius * sin(0.0));
    int i;
    for (i=0; i<circle_points; i++)
    {
        glVertex2d(radius * cos(angle1), radius *sin(angle1));
        angle1 += angle;
    }
    glEnd();
    glPopMatrix();

}
//Scaling factor is included in this circle
void Shapes::drawCircle2(float x, float y, float radius) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glScalef(0.6,0.6,0.6);
    glTranslatef(x, y, 0.0f);
    static const int circle_points = 1000;
    static const float angle = 2.0f * 3.1416f / circle_points;
    glBegin(GL_POLYGON);
    double angle1=0.0;
    glVertex2d(radius * cos(0.0) , radius * sin(0.0));
    int i;
    for (i=0; i<circle_points; i++)
    {
        glVertex2d(radius * cos(angle1), radius *sin(angle1));
        angle1 += angle;
    }
    glEnd();
    glPopMatrix();
}

void Shapes :: drawLine(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2){
        glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
}

void Shapes:: bgComputer(){
    glClear(GL_COLOR_BUFFER_BIT); 
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0.8,0.8,0.8);
    glRectd(-1.2,-0.9,1.2,1.0);
    glClearColor(0.0, 0.9, 0.9, 0.0);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_QUADS);
    glVertex2d(-1.2,-0.90);
    glVertex2d(-1.2,1.0);
    glVertex2d(-1.15,1.0);
    glVertex2d(-1.15,-0.90);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(-1.2,1.0);
    glVertex2d(-1.2,0.95);
    glVertex2d(1.2,0.95);
    glVertex2d(1.2,1.0);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(-1.2,-0.90);
    glVertex2d(-1.2,-0.85);
    glVertex2d(1.2,-0.85);
    glVertex2d(1.2,-0.90);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(1.2,1.0);
    glVertex2d(1.2,-0.90);
    glVertex2d(1.15,-0.90);
    glVertex2d(1.15,1.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(-0.2,-0.95);
    glVertex2d(-0.15,-0.90);
    glVertex2d(0.15,-0.90);
    glVertex2d(0.2,-0.95);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(-0.3,-1.0);
    glVertex2d(-0.25,-0.95);
    glVertex2d(0.25,-0.95);
    glVertex2d(0.3,-1.0);
    glEnd();
    glColor3f(1,0,0);
    headingText("Press 'q' to quit",0.5,-0.95,0,0.0005f,0.0005f,0.0f);
    glPopMatrix();
    // end of bg computer
}

void Shapes::drawSegment(float cx,float cy,float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float radius1,float radius2,double angle1,double angle2,double angle3,double angle4) {
    glMatrixMode(GL_MODELVIEW);

    
    glPushMatrix();
    glLoadIdentity();
    glScalef(0.6,0.6,0.6);
    glTranslatef(cx, cy, 0.0f);
    glBegin(GL_POLYGON);
    double angle=0.00001;
    glVertex2d(x1,y1);
    glVertex2d(x2,y2);
    float x=x3;
    float y=y3;
    while(angle1>angle3)
    {
        x=radius1 * cos(angle1);
        y=radius1 *sin(angle1);
        glVertex2d(x,y);
        angle1 -= angle;
    } 
    glVertex2d(x4,y4);
    x=x4;
    y=y4;
    while(angle2<=angle4)
    {
        x=radius2 * cos(angle2);
        y=radius2 *sin(angle2);
        glVertex2d(x,y);
        angle2 += angle;
    }
    glEnd();
    glPopMatrix();
}

void Shapes::drawSegment2(float cx,float cy,float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float radius1,float radius2,double angle1,double angle2,double angle3,double angle4) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glScalef(0.6,0.6,0.6);
    glTranslatef(cx, cy, 0.0f);
    float x,y;
    double angle=0.0001;
   glBegin(GL_POLYGON);
    glVertex2d(x1,y1);
    glVertex2d(x2,y2);
    while(angle1<4.71238)  //4.71238
    {
        x=radius1 * cos(angle1);
        y=radius1 * sin(angle1);
        glVertex2d(x,y);
        angle1 += angle;
    }
   glVertex2d(x4,y4);
   while(angle2>=angle4)
    {
        x=radius2 * cos(angle2);
        y=radius2 *sin(angle2);
        glVertex2d(x,y);
        angle2 -= angle;
    }
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(0.0,-0.14);
    double angle5=4.71238;
    angle=0.00001;
    while(angle5<=angle3) {
        x=radius1 * cos(angle5);
        y=radius1 * sin(angle5);
        glVertex2d(x,y);
        angle5 += angle;
    }
    glVertex2d(x4,y4);
    glEnd();
    glPopMatrix();
}

void Shapes::drawSegment3(float cx,float cy,float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float radius1,float radius2,double angle1,double angle2,double angle3,double angle4) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glScalef(0.6,0.6,0.6);
    glTranslatef(cx, cy, 0.0f);
    glBegin(GL_POLYGON);
    double angle=0.00001;
    glVertex2d(x4,y4);
    glVertex2d(x1,y1);
    float x=x3;
    float y=y3;
    while(angle1>angle3)
    {
        x=radius1 * cos(angle1);
        y=radius1 *sin(angle1);
        glVertex2d(x,y);
        angle1 -= angle;
    }
    glVertex2d(x3,y3);
    x=x4;
    y=y4;
    while(angle2<angle4)
    {
        x=radius2 * cos(angle2);
        y=radius2 *sin(angle2);
        glVertex2d(x,y);
        angle2 += angle;
    }
    glEnd();
    glPopMatrix();
}

void Shapes::drawWord(){
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.55,0.35);
    glVertex2f(-0.55,0.60);
    glVertex2f(-0.35,0.65);
    glVertex2f(-0.35,0.30);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.35,0.30);
    glVertex2f(-0.35,0.65);
    glVertex2f(-0.33,0.65);
    glVertex2f(-0.33,0.30);
    glEnd();
    glColor3f(1.0,1.0,1.0);
    text("W",-0.47,0.45,0.0);
    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,1);
    glVertex2f(-0.35,0.6);
    glVertex2f(-0.35,0.35);
    glVertex2f(-0.20,0.35);
    glVertex2f(-0.20,0.6);	//glClearColor(0.8,0.8,0.8,1);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-0.35,0.55);
    glVertex2f(-0.23,0.55);
    glVertex2f(-0.35,0.52);
    glVertex2f(-0.23,0.52);
    glVertex2f(-0.35,0.49);
    glVertex2f(-0.23,0.49);
    glVertex2f(-0.35,0.46);
    glVertex2f(-0.23,0.46);
    glVertex2f(-0.35,0.43);
    glVertex2f(-0.23,0.43);
    glVertex2f(-0.35,0.40);
    glVertex2f(-0.23,0.40);
    glEnd();
    glPopMatrix();
}

void Shapes::drawCalculator() {
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.12,0.3);
    glVertex2f(-0.12,0.6);
    glVertex2f(-0.09,0.6);
    glVertex2f(-0.09,0.3);
    glEnd();
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.09,0.305);
    glVertex2f(-0.09,0.595);
    glVertex2f(0.14,0.595);
    glVertex2f(0.14,0.305);
    glEnd();
    glLineWidth(7.0);
    glBegin(GL_LINES);
    glVertex2f(-0.05,0.49);
    glVertex2f(-0.03,0.49);
    glVertex2f(0.01,0.49);
    glVertex2f(0.03,0.49);
    glVertex2f(0.07,0.49);
    glVertex2f(0.09,0.49);
    glVertex2f(-0.05,0.42);
    glVertex2f(-0.03,0.42);
    glVertex2f(0.01,0.42);
    glVertex2f(0.03,0.42);
    glVertex2f(0.07,0.42);
    glVertex2f(0.09,0.42);
    glVertex2f(-0.05,0.35);
    glVertex2f(-0.03,0.35);
    glVertex2f(0.01,0.35);
    glVertex2f(0.03,0.35);
    glVertex2f(0.07,0.35);
    glVertex2f(0.09,0.35);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.05,0.53);
    glVertex2f(-0.05,0.56);
    glVertex2f(0.09,0.56);
    glVertex2f(0.09,0.53);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.17,0.3);
    glVertex2f(0.17,0.6);
    glVertex2f(0.14,0.6);
    glVertex2f(0.14,0.3);
    glEnd();
}
void Shapes::drawChrome() {
    glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0.0,1.0,0.0);
    drawSegment2(0.70,0.80,-0.2248,0.10937,-0.12124,-0.07,0.12124,-0.07,0.017682,-0.24937,0.14,0.25,3.66519,4.78318,5.7596,2.6888);
    glColor3f(1.0,0.0,0.0);
    drawSegment(0.70,0.80,-0.2248,0.10937,-0.12124,-0.07,0.0,0.14,0.20712,0.14,0.14,0.25,3.66519,0.5944,1.570796,2.6888);
    glColor3f(1.0,1.0,0.0);
    drawSegment3(0.70,0.80,0.0,0.14,0.12124,-0.07,0.017682,-0.24937,0.20712,0.14,0.14,0.25,7.85398,4.78318,5.7596,6.8776);
    glColor3f(1.0,1.0,1.0);
    glScalef(0.6,0.6,0.6);
    drawCircle2(0.70,0.80,0.14);
    glColor3f(0.0,0.2,1.0);
    drawCircle2(0.70,0.80,0.1);
    glPopMatrix();
}
 

 void  Shapes::Torus2d( float inner, float outer, unsigned int pts )
{

    glScalef(0.05,0.05,0.05);
    glTranslatef(16,9.5,0);
      glColor3ub( 0, 0, 255);
    glBegin( GL_QUAD_STRIP );
    for( unsigned int i = 0; i <= pts; ++i )
    {
        float angle = ( i / (float)pts ) * 3.14159f * 2.0f;
        glVertex2f( inner * cos( angle ), inner * sin( angle ) );
        glVertex2f( outer * cos( angle ), outer * sin( angle ) );
    }
       glEnd();
}


 void Shapes:: drawMxPlayer(){
     glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3ub( 0, 0, 255);
    Torus2d( 2, 3, 30 );
    glColor3ub( 255, 255, 255 );
    glScalef(0.5,0.50,.5);
    glColor3f(0,0,1);
    glBegin(GL_TRIANGLES);
    glVertex2f(-1,1.4);
    glVertex2f(-1,-1.5);
    glVertex2f(1.5,-0.15);
    glEnd();
    glPopMatrix();
 }


void Shapes::home(){
     // home
    //sides
    glPushMatrix();
    
    glScalef(0.22,0.22,0);
    glColor3f(0.0,0.0,1.0);
    drawCircle2(-1.67,1.35,0.21);
    glColor3f(0,0,0.8);
    drawCircle2(-1.67,1.35,0.18);
    glColor3f(0.2,0.5,1.0);
    drawCircle2(-1.67,1.35,0.155);
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);

    glVertex2f(0.1, 0.0);
    glVertex2f(0.08, 0.02);
    glVertex2f(0.08, 0.3);
    glVertex2f(0.21, 0.3);
    glVertex2f(0.21, 0.02);
    glVertex2f(0.2, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.2, 0.0);
    glVertex2f(-0.21, 0.02);
    glVertex2f(-0.21, 0.3);
    glVertex2f(-0.08, 0.3);
    glVertex2f(-0.08, 0.02);
    glVertex2f(-0.1, 0);
    glEnd();

    //mid block
    glBegin(GL_POLYGON);
    glVertex2f(0.1, 0.15);
    glVertex2f(0.1, 0.3);
    glVertex2f(-0.1, 0.3);
    glVertex2f(-0.1, 0.15);
    glEnd();

    // top
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.21, 0.3);
    glVertex2f(0, 0.45);
    glVertex2f(0.21, 0.3);
    glEnd();

    //top inverted V
    glBegin(GL_POLYGON);
    glVertex2f(-0.24, 0.3);
    glVertex2f(-0.28, 0.3);
    glVertex2f(-0.3, 0.32);
    glVertex2f(0, 0.53);
    glVertex2f(0, 0.48);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.24, 0.3);
    glVertex2f(0.28, 0.3);
    glVertex2f(0.3, 0.32);
    glVertex2f(0, 0.53);
    glVertex2f(0, 0.48);
    glEnd();

    glLineWidth(15);
    glBegin(GL_LINES);
    glVertex2f(0.17, 0.48);
    glVertex2f(0.17, 0.40);
    glVertex2f(0.16, 0.48);
    glVertex2f(0.16, 0.40);
    glEnd();

    glPopMatrix();
}