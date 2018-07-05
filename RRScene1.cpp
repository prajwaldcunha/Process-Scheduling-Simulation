#ifdef WIN32
#include<windows.h>
#endif
#include <iostream>
#include<math.h>
#include <iomanip>
#include <GL/glut.h>
#include<string.h>
#include<stdlib.h>
#include "RRScene1.h"
#include "Shapes.h"
using namespace std;


void RRScene1 :: dispRR1(){
    Shapes sobj;
   glClear(GL_COLOR_BUFFER_BIT);// Clear the color buffer


// bg computer
    sobj.bgComputer();
    // end of bg computer


   //Process details
   glColor3f(1,0,0);
   glBegin(GL_POLYGON);
   glVertex2f(-0.6,0.7);
   glVertex2f(-0.6,0.8);
   glVertex2f(-0.4,0.8);
   glVertex2f(-0.4,0.7);
   glEnd();
   glColor3f(1.0,1.0,1.0);
   sobj.text({"P1"},-0.53,0.72,0);
   glColor3f(1.0,1.0,0.0);
   glBegin(GL_POLYGON);
   glVertex2f(-0.3,0.7);
   glVertex2f(-0.3,0.8);
   glVertex2f(-0.1,0.8);
   glVertex2f(-0.1,0.7);
   glEnd();
   glColor3f(1.0,1.0,1.0);
   sobj.text({"P2"},-0.23,0.72,0);
   glColor3f(0.0,0.0,1.0);
   glBegin(GL_POLYGON);
   glVertex2f(0.0,0.7);
   glVertex2f(0.0,0.8);
   glVertex2f(0.2,0.8);
   glVertex2f(0.2,0.7);
   glEnd();
   glColor3f(1.0,1.0,1.0);
    sobj.text({"P3"},0.07,0.72,0);
   glColor3f(0.647059,0.164706,0.164706);
   glBegin(GL_POLYGON);
   glVertex2f(0.3,0.7);
   glVertex2f(0.3,0.8);
   glVertex2f(0.5,0.8);
   glVertex2f(0.5,0.7);
   glEnd();
   glColor3f(1.0,1.0,1.0);
    sobj.text({"P4"},0.37,0.72,0);

   glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
   glLoadIdentity();              // Reset model-view matrix
   glPushMatrix();
   glTranslatef(xx, yy, 0.0f);  // Translate to (xPos, yPos)
   glLineWidth(3.0);
   glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);  // Blue
    glVertex2f(-0.8f, 0.0f);
    glVertex2f(-0.8f, 0.2f);
    glVertex2f(0.75f, 0.2f);
    glVertex2f(0.75f, 0.0f);
   glEnd();
   glPopMatrix();
   // Swap front and back buffers (of double buffered mode)
   // Animation Control - compute the location for the next refresh
    if (yy < YMax) {
        yy += ySpeed;
        glutSwapBuffers();
    }
    else {
        yy = YMax;
        glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
        glLoadIdentity();
        sobj.text({"0"},-0.8,0.2,0);              // Reset model-view matrix
        glPushMatrix();
        glTranslatef(xx1-0.45, yy1-0.177, 0.0f);
        /*glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex2f(-0.8f,0.0f);
        glVertex2f(-0.8f,0.2f);
        glVertex2f(-0.55f,0.2f);
        glVertex2f(-0.55f,0.0f);
        glEnd();*/
        glScalef(0.6,0.6,0);
        sobj.drawWord();
        glPopMatrix();
        if (yy1 < YMax) {
            yy1 += ySpeed;
            glutSwapBuffers();
        }
        else {
            yy1 = YMax;
            glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
            glLoadIdentity();
             sobj.text({"3"},-0.55,0.2,0);             // Reset model-view matrix
            glPushMatrix();
            glTranslatef(xx2-0.43, yy2-0.17, 0.0f);
            glScalef(0.6,0.6,0);
            sobj.drawCalculator();
            glPopMatrix();
            if (yy2 < YMax) {
                yy2 += ySpeed;
                glutSwapBuffers();
        }
        else {
            yy2 = YMax;
            glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
            glLoadIdentity();              // Reset model-view matrix
            sobj.text({"6"},-0.30,0.2,0);
            glPushMatrix();
            glTranslatef(xx3, yy3, 0.0f);
            glColor3f(0.0f, 0.0f, 1.0f);
            glBegin(GL_POLYGON);
            glVertex2f(-0.3f,0.0f);
            glVertex2f(-0.3f,0.2f);
            glVertex2f(-0.05f,0.2f);
            glVertex2f(-0.05f,0.0f);
            glEnd();
            glPopMatrix();
            if (yy3 < YMax) {
                yy3 += ySpeed;
                glutSwapBuffers();
        }
        else {
            yy3 = YMax;
            glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
            glLoadIdentity();              // Reset model-view matrix
            sobj.text({"9"},-0.05,0.2,0);
            glPushMatrix();
            glTranslatef(xx4, yy4, 0.0f);
            glColor3f(0.647059,0.164706,0.164706);
            glBegin(GL_POLYGON);
            glVertex2f(-0.05f,0.0f);
            glVertex2f(-0.05f,0.2f);
            glVertex2f(0.20f,0.2f);
            glVertex2f(0.20f,0.0f);
            glEnd();
            glPopMatrix();
            if (yy4 < YMax) {
                yy4 += ySpeed;
                glutSwapBuffers();
        }
        else {
            yy4 = YMax;
            glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
            glLoadIdentity();              // Reset model-view matrix
             sobj.text({"12"},0.2,0.2,0);
            glPushMatrix();
            glTranslatef(xx5+0.55, yy5-0.177, 0.0f);
            glScalef(0.6,0.6,0);
            sobj.drawWord();
            glPopMatrix();
            if (yy5 < YMax) {
                yy5 += ySpeed;
                glutSwapBuffers();
        }
        else {
            yy5 = YMax;
            glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
            glLoadIdentity();              // Reset model-view matrix
            sobj.text({"15"},0.45,0.2,0);
            glPushMatrix();
            glTranslatef(xx6+0.53, yy6-0.13, 0.0f);
            glScalef(0.4,0.5,0);
            sobj.drawCalculator();
            glPopMatrix();
            if (yy6 < YMax) {
                yy6 += ySpeed;
                glutSwapBuffers();
        }
        else {
            yy6 = YMax;
            glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
            glLoadIdentity();              // Reset model-view matrix
             sobj.text({"17"},0.60,0.2,0);
            glPushMatrix();
            // glTranslatef(xx7, yy7, 0.0f);
            // glColor3f(0.647059,0.164706,0.164706);
            // glBegin(GL_POLYGON);
            // glVertex2f(0.60,0.0f);
            // glVertex2f(0.60f,0.2f);
            // glVertex2f(0.75f,0.2f);
            // glVertex2f(0.75f,0.0f);
            // glEnd(,;
            glScalef(0.5,0.5,0);
            sobj.drawMxPlayer();
            glPopMatrix();
            if (yy7 < YMax) {
                yy7 += ySpeed;
                glutSwapBuffers();
        }
        else {
            yy7 = YMax;
            sobj.text({"19"},0.75,0.2,0);
            glutSwapBuffers();
        }

        }
        }
        }
    }
    }
    }
    }
}