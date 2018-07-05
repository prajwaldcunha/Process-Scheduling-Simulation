#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Shapes.h"
#include "Button.h"
#include "RRScene1.h"
using namespace std;
irrklang::ISoundEngine *engine;
Shapes sobj;
RRScene1 rrscene1;
int n = 4, time_quantum = 3, i, j, k, count, time1, remain = 4, flag = 0, wait_time = 0, turnaround_time = 0, rt[10], p[50], t[50];
int flagForRR = 0, flag5 = 0, flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flagForButton = 0, flagForRRComp = 0, f = 0, flagforNPP = 0,flagForP4=0;
int windowWidth = 800;  // Windowed mode's width
int windowHeight = 600; // Windowed mode's height
int windowPosX = 0;     // Windowed mode's top-left corner x
int windowPosY = 0;     // Windowed mode's top-left corner y
GLfloat radius = 0.8f;
GLfloat sdx = -1.0;
GLfloat xx = 0.0f;
GLfloat yy = -1.0f;
GLfloat XMax, XMin, YMax = 0.3, YMin; //  center (x, y) bounds
GLfloat xSpeed = 0.00f;               // speed in x and y directions
GLfloat ySpeed = 0.007f;
GLfloat fxRR, dx1RR, xRR = -0.8;
GLfloat xRex = 0.0f, yRex = 0.0f, xRex1 = 0.0f, yRex1 = 0.0f, xRex2 = 0.0f, yRex2 = 0.0f, xRex3 = 0.0f, yRex3 = 0.0f, xRex4 = 0.0f, yRex4 = 0.0f, xRex5 = 0.0f, yRex5 = 0.0f;
GLfloat xRex6 = 0.0f, yRex6 = 0.0f, xRex7 = 0.0f, yRex7 = 0.0f, xRex8 = 0.0f, yRex8 = 0.0f, xRex9 = 0.0f, yRex9 = 0.0f, xRex10 = 0.0f, yRex10 = 0.0f,yRex11=0.0f;
GLfloat xRex11=0.0f,yRex12=0.0f,xRex12=0.0f,yRex13=0.0f,xRex13=0.0f,yRex14=0.0f,xRex14=0.0f,yRex15=0.0f,yRex16=0.0f,yRex17=0.0f;
GLsizei width1 = 20, height1 = 20;
float count1;
bool isDone = false, isDone1 = false, isDone2 = false, isDone3 = false, isDone4 = false, isDone5 = false, isDone6 = false,isDone7 = false,isDone8=false,isDone9=false;
long delay = 500000;
int refreshMillis = 10; // Refresh period in milliseconds
char charTime_array2[10];
string strTime2;
char charTime_array3[10];
char process_names[10][10];
int process[4] = {1, 2, 3, 4};
string strTime3;

Button homeBtn(-1.13,0.8,0.9,0.928,"");

Button btnRR(0.8, -0.2, 1.0, -0.1, "Continue>>>");
Button btnegRR(0.8, -0.4, 1.0, -0.3, "Continue>>>");
Button btnP(0.8, -0.6, 1.0, -0.5, "Continue>>>");
Button btnPeg(0.8, -0.8, 1.0, -0.7, "Continue>>>");


//RR scheduling
Button btn4(-0.37, -0.10, -0.32, -0.05, "+");
Button btn5(-0.37, -0.17, -0.32, -0.12, "+");
Button btn6(0.03, -0.10, 0.08, -0.05, "+");
Button btn7(0.03, -0.17, 0.08, -0.12, "+");
Button btn8(0.42, -0.10, 0.47, -0.05, "+");
Button btn9(0.42, -0.17, 0.47, -0.12, "+");
Button btn10(0.84, -0.10, 0.89, -0.05, "+");
Button btn11(0.84, -0.17, 0.89, -0.12, "+");
Button btn12(-0.37, -0.40, -0.32, -0.35, "+");
Button btn13(-0.37, -0.47, -0.32, -0.42, "+");
Button btn14(0.03, -0.40, 0.08, -0.35, "+");
Button btn15(0.03, -0.47, 0.08, -0.42, "+");
Button btn16(0.42, -0.40, 0.47, -0.35, "+");
Button btn17(0.42, -0.47, 0.47, -0.42, "+");
Button btn18(0.84, -0.40, 0.89, -0.35, "+");
Button btn19(0.84, -0.47, 0.89, -0.42, "+");

//Arrival time and burst time for RR Scheduling
int at[4], bt[4];

void Torus2d(float inner, float outer, unsigned int pts)
{

    glScalef(0.05, 0.05, 0.05);
    glTranslatef(16, 9.5, 0);
    glColor3ub(0, 0, 255);
    glBegin(GL_QUAD_STRIP);
    for (unsigned int i = 0; i <= pts; ++i)
    {
        float angle = (i / (float)pts) * 3.14159f * 2.0f;
        glVertex2f(inner * cos(angle), inner * sin(angle));
        glVertex2f(outer * cos(angle), outer * sin(angle));
    }
    glEnd();
}

void drawCircle(float cx, float cy, float r, int num_segments)
{
    float theta = 2 * 3.1415926 / float(num_segments);
    float tangetial_factor = tanf(theta); //calculate the tangential factor

    float radial_factor = cosf(theta); //calculate the radial factor

    float x = r; //we start at angle = 0

    float y = 0;

    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)
    {
        glVertex2f(x + cx, y + cy); //output vertex

        //calculate the tangential vector
        //remember, the radial vector is (x, y)
        //to get the tangential vector we flip those coordinates and negate one of them

        float tx = -y;
        float ty = x;

        //add the tangential vector

        x += tx * tangetial_factor;
        y += ty * tangetial_factor;

        //correct using the radial factor

        x *= radial_factor;
        y *= radial_factor;
    }
    glEnd();
}

void schedulingDiagram()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2d(-0.3, 0.6);
    glVertex2d(-0.3, 0.9);
    glVertex2d(-0.1, 0.9);
    glVertex2d(-0.1, 0.6);
    glEnd();


    //lines on white board
    glColor3f(0.8, 0.1, 0.0);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2d(-0.26, 0.85);
    glVertex2d(-0.14, 0.85);

    glVertex2d(-0.26, 0.8);
    glVertex2d(-0.14, 0.8);

    glVertex2d(-0.26, 0.75);
    glVertex2d(-0.14, 0.75);

    glVertex2d(-0.26, 0.7);
    glVertex2d(-0.14, 0.7);

    glVertex2d(-0.26, 0.65);
    glVertex2d(-0.14, 0.65);
    glEnd();

    glColor3f(0.1, 0.1, 1);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex2d(-0.3, 0.6);
    glVertex2d(-0.3, 0.9);
    glVertex2d(-0.1, 0.9);
    glVertex2d(-0.1, 0.6);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex2d(-0.22, 0.91);
    glVertex2d(-0.22, 0.94);
    glVertex2d(-0.18, 0.94);
    glVertex2d(-0.18, 0.91);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.8, 0.8, 0.8);
    glVertex2d(-0.22, 0.933);
    glVertex2d(-0.22, 0.94);
    glVertex2d(-0.215, 0.94);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.8, 0.8, 0.8);
    glVertex2d(-0.18, 0.933);
    glVertex2d(-0.18, 0.94);
    glVertex2d(-0.185, 0.94);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.8, 0.3);
    glVertex2d(-0.23, 0.86);
    glVertex2d(-0.23, 0.91);
    glVertex2d(-0.17, 0.91);
    glVertex2d(-0.17, 0.86);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 1);
    glVertex2d(-0.23, 0.86);
    glVertex2d(-0.23, 0.87);
    glVertex2d(-0.225, 0.86);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 1);
    glVertex2d(-0.17, 0.86);
    glVertex2d(-0.17, 0.87);
    glVertex2d(-0.175, 0.86);
    glEnd();

    //calendar
    glColor3f(0.3, 0.8, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(-0.15, 0.75);
    glVertex2f(0.05, 0.75);
    glVertex2f(0.06, 0.74);
    glVertex2f(0.06, 0.65);
    glVertex2f(-0.155, 0.65);
    glVertex2f(-0.155, 0.74);
    glEnd();
    glColor3f(1.0, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2f(0.06, 0.47);
    glVertex2f(0.06, 0.65);
    glVertex2f(-0.155, 0.65);
    glVertex2f(-0.155, 0.47);
    glEnd();
    glColor3f(0, 0, 0);
     glBegin(GL_LINES);
     glVertex2f(-0.01, 0.75);
     glVertex2f(-0.01, 0.775);

     glVertex2f(-0.085, 0.75);
     glVertex2f(-0.085, 0.775);
     glEnd();

    glColor3f(0.9, 0.8, 0.3);
    sobj.text("18", -0.08, 0.55, 0);

    // clock
    glPushMatrix();
    glTranslatef(-.65, -0.08, 0);
    Torus2d(2.3, 2.8, 30);
    glColor3f(1, 1, 1);
    sobj.drawCircle(0.15, 0.3956, .111);

    glPopMatrix();
    glColor3f(0.3, 0.3, 0.3);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2d(0.15, 0.5);
    glVertex2d(0.15, 0.46);
    glVertex2d(0.15, 0.29);
    glVertex2d(0.15, 0.33);

    glVertex2d(0.03, 0.39);
    glVertex2d(0.07, 0.39);
    glVertex2d(0.215, 0.39);
    glVertex2d(0.255, 0.39);

    glColor3f(0.9, 0.05, 0.05);
    glVertex2d(0.15, .39);
    glVertex2d(0.22, 0.45);

    glVertex2d(0.15, .39);
    glVertex2d(0.21, 0.39);

    glEnd();
    sobj.drawSemiCircle(0.065, 0.520, .061, 40, 1, 0, 1);
    sobj.drawSemiCircle(0.238, 0.52, .061, -39, 1, 0, 1);
    glPopMatrix();
}

void first_display(){
    glPushMatrix();
    glClearColor(.92, 0.92, 0.92, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sobj.bgComputer();
    glPopMatrix();
    glutSwapBuffers();
}
// Projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

void initial_display()
{
    glPushMatrix();
    glClearColor(.92, 0.92, 0.92, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sobj.bgComputer();
    schedulingDiagram();
    glColor3f(1.0, 0.0, 0.2);
    sobj.headingText("PROCESS SCHEDULING ALGORITHM", 28, 270, 0, 0.2f, 0.2f, 0.0f);
    glColor3f(0.1, 0.1, 0.8);
    sobj.headingText("1) Round Robin Scheduling Algorithm", 15, 200, 0, 0.13f, 0.13f, 0.0f);
    sobj.headingText("2) Round Robin Scheduling Algorithm Example", 15, 150, 0, 0.13f, 0.13f, 0.0f);
    sobj.headingText("3) Priority Scheduling Algorithm", 15, 100, 0, 0.13f, 0.13f, 0.0f);
    sobj.headingText("4) Priority Scheduling Algorithm Example", 15, 50, 0, 0.13f, 0.13f, 0.0f);
    glPopMatrix();
    glPushMatrix();
    btnRR.draw();
    btnegRR.draw();
    btnP.draw();
    btnPeg.draw();
    glPopMatrix();
    glColor3f(1.0, 1.0, 1.0);
    sobj.headingText(">>", 470, 208, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText(">>", 470, 160, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText(">>", 470, 108, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText(">>", 470, 58, 0.0, 0.1f, 0.1f, 0.0f);

    glutSwapBuffers();
}

void display()
{

    glClearColor(.92, 0.92, 0.92, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //background
    sobj.bgComputer();

    flagForRR = 1;
    flagForButton = 1;
    
    glMatrixMode(GL_MODELVIEW); // -0.4f,0.5f,0.1f
    glPushMatrix();
    glLoadIdentity();

   // homeBtn.draw();

    //home button 
    glPushMatrix();
    glTranslatef(-1.0,0.75,0);
    sobj.home();
    glPopMatrix();


    //Word
    sobj.drawWord();
    //Calculator
    glPushMatrix();
    glLoadIdentity();
    sobj.drawCalculator();
    glPopMatrix();
    //Chrome
    sobj.drawChrome();

    sobj.drawMxPlayer();
    glPopMatrix();
    glPushMatrix();
    btn4.draw();
    btn5.draw();
    btn6.draw();
    btn7.draw();
    btn8.draw();
    btn9.draw();
    btn10.draw();
    btn11.draw();
    btn12.draw();
    btn13.draw();
    btn14.draw();
    btn15.draw();
    btn16.draw();
    btn17.draw();
    btn18.draw();
    btn19.draw();
    glPopMatrix();
    glColor3f(1.0, 1.0, 1);
    sobj.headingText("+", 158, 227, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 158, 210, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("+", 258, 227, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 258, 210, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("+", 357, 227, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 357, 210, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("+", 459, 227, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 459, 210, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("+", 158, 152, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 158, 135, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("+", 258, 152, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 258, 135, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("+", 357, 152, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 357, 135, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("+", 459, 152, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 459, 135, 0.0, 0.1f, 0.1f, 0.0f);

    glColor3f(0.35, 0.35, 0.67);
    sobj.headingText({"ROUND ROBIN SCHEDULING"}, 120, 450, 0, 0.18f, 0.18f, 0.0f);
    glColor3f(0.0, 0.0, 0.0);
    sobj.text({"Process Name:"}, 12, 300, 0);
    sobj.text({"Arrival Time:"}, 11, 220, 0);
    sobj.text({"Burst Time:"}, 12, 140, 0);
    sobj.text({"Quantum time : 3"}, 11, 60, 0);
    sobj.text({"P1"}, 140, 300, 0);
    sobj.text({"P2"}, 239, 300, 0);
    sobj.text({"P3"}, 340, 300, 0);
    sobj.text({"P4"}, 445, 300, 0);

    string s1 = to_string(at[0]);
    int n = s1.length();
    char char_array1[n + 1];
    strcpy(char_array1, s1.c_str());
    sobj.text(char_array1, 140, 220, 0);

    string s2 = to_string(at[1]);
    char char_array2[n + 1];
    strcpy(char_array2, s2.c_str());
    sobj.text(char_array2, 239, 220, 0);

    string s3 = to_string(at[2]);
    char char_array3[n + 1];
    strcpy(char_array3, s3.c_str());
    sobj.text(char_array3, 340, 220, 0);

    string s4 = to_string(at[3]);
    char char_array4[n + 1];
    strcpy(char_array4, s4.c_str());
    sobj.text(char_array4, 445, 220, 0);

    //burst time
    string bs1 = to_string(bt[0]);
    n = bs1.length();
    char bchar_array1[n + 1];
    strcpy(bchar_array1, bs1.c_str());
    sobj.text(bchar_array1, 140, 140, 0);

    string bs2 = to_string(bt[1]);
    char bchar_array2[n + 1];
    strcpy(bchar_array2, bs2.c_str());
    sobj.text(bchar_array2, 239, 140, 0);

    string bs3 = to_string(bt[2]);
    char bchar_array3[n + 1];
    strcpy(bchar_array3, bs3.c_str());
    sobj.text(bchar_array3, 340, 140, 0);

    string bs4 = to_string(bt[3]);
    char bchar_array4[n + 1];
    strcpy(bchar_array4, bs4.c_str());
    sobj.text(bchar_array4, 445, 140, 0);
    sobj.text({"Press Enter to view Gantt chart"}, 190, 50, 0);
    glEnd();
    glutSwapBuffers();
}

void display2()
{

    glClearColor(.92, 0.92, 0.92, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    flagForRR = 0;
    sobj.bgComputer();
    glColor3f(0.5, 0, 1.0);
    sobj.headingText("GANTT CHART CONSTRUCTION", 70, 450, 0, 0.2, 0.2, 0.0); //Not Working
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW); // To operate on the model-view matrix
    glLoadIdentity();           // Reset model-view matrix
    glColor3f(0,0,0);
    sobj.text("Time Qauntum:3ms",0.7,-0.7,0);
    //home button 
    glPushMatrix();
    glTranslatef(-1.0,0.75,0);
    sobj.home();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(xx, yy, 0.0f); // Translate to (xPos, yPos)
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f); // Blue
    glVertex2f(-0.8f, 0.0f);
    glVertex2f(-0.8f, 0.2f);
    glVertex2f(0.8f, 0.2f);
    glVertex2f(0.8f, 0.0f);
    glEnd();
    glPopMatrix();
    // Swap front and back buffers (of double buffered mode)
    // Animation Control - compute the location for the next refresh
    if (yy < YMax)
    {
        yy += ySpeed;
        glutSwapBuffers();
    }
    else
    {
        yy = YMax;
        glPushMatrix();
        glMatrixMode(GL_MODELVIEW); // To operate on the model-view matrix
        glLoadIdentity();
        glColor3f(0, 0, 0);
        sobj.text({"0"}, -0.8, 0.1, 0);
        sobj.text({"Time:"}, -1.0, 0.1, 0);
        if (flagForRRComp == 0)
        {
            int temp;
            char temp1[10];
            i = 0;
            t[0] = 0;
            for (int p = 1; p < 4; p++)
                for (int q = 0; q < 4 - p; q++)
                {
                    if (at[q] > at[q + 1])
                    {
                        temp = at[q];
                        at[q] = at[q + 1];
                        at[q + 1] = temp;
                        temp = bt[q];
                        bt[q] = bt[q + 1];
                        bt[q + 1] = temp;
                        for (int l = 0; l < 2; l++)
                        {
                            temp1[l] = process_names[q][l];
                            process_names[q][l] = process_names[q + 1][l];
                            process_names[q + 1][l] = temp1[l];
                        }
                    }
                }

            for (i = 0; i < n; i++)
            {
                rt[i] = bt[i];
            }
            for (int l = 0; l < 4; l++)
            {
                printf("Arrival time P%d %d\n", l + 1, at[l]);
                printf("Burst time P%d %d\n", l + 1, bt[l]);
            }
            //RR Scheduling Algorithm
            for (time1 = 0, count = 0; remain != 0;)
            {

                if (rt[count] <= time_quantum && rt[count] > 0)
                {
                    time1 += rt[count];
                    rt[count] = 0;
                    flag = 1;
                    p[i] = count + 1;
                    t[++i] = time1;
                    printf("Process:%d   time: %d\n", count + 1, time1);
                }
                else if (rt[count] > 0)
                {
                    rt[count] -= time_quantum;
                    time1 += time_quantum;
                    p[i] = count + 1;
                    t[++i] = time1;
                    printf("Process:%d   time: %d\n", count + 1, time1);
                }
                if (rt[count] == 0 && flag == 1)
                {
                    remain--;
                    printf("P[%d]\t|\t%d\t|\t%d\n", count + 1, time1 - at[count], time1 - at[count] - bt[count]);
                    wait_time += time1 - at[count] - bt[count];
                    turnaround_time += time1 - at[count];
                    flag = 0;
                }
                if (count == n - 1)
                    count = 0;
                else if (at[count + 1] <= time1)
                {
                    count++;
                }
                else
                    count = 0;
            }
            // for(k=0;k<i;k++){

            // }
            fxRR = 1.6 / time1; //width of the box for each unit for time(0.8+0.8=1.6)
            flagForRRComp = 1;
            t[i + 1] = time1 + 1;
        }

        //Process blocks in the top
        glColor3f(1, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(-0.6, 0.6);
        glVertex2f(-0.6, 0.7);
        glVertex2f(-0.4, 0.7);
        glVertex2f(-0.4, 0.6);
        glEnd();
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2f(-0.3, 0.6);
        glVertex2f(-0.3, 0.7);
        glVertex2f(-0.1, 0.7);
        glVertex2f(-0.1, 0.6);
        glEnd();
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POLYGON);
        glVertex2f(0.0, 0.6);
        glVertex2f(0.0, 0.7);
        glVertex2f(0.2, 0.7);
        glVertex2f(0.2, 0.6);
        glEnd();
        glColor3f(0.647059, 0.164706, 0.164706);
        glBegin(GL_POLYGON);
        glVertex2f(0.3, 0.6);
        glVertex2f(0.3, 0.7);
        glVertex2f(0.5, 0.7);
        glVertex2f(0.5, 0.6);
        glEnd();

        //Print process names
        glColor3f(1.0, 1.0, 1.0);
        sobj.text(process_names[0], -0.53, 0.62, 0);
        sobj.text(process_names[1], -0.23, 0.62, 0);
        sobj.text(process_names[2], 0.07, 0.62, 0);
        sobj.text(process_names[3], 0.37, 0.62, 0);

        glColor3f(0.0, 0.0, 0.0);
        sobj.text({"Arrival Time"}, -0.6, -0.3, 0);
        sobj.text({"Burst Time"}, -0.1, -0.3, 0);
        sobj.text(process_names[0], -0.8, -0.40, 0);
        sobj.text(process_names[1], -0.8, -0.48, 0);
        sobj.text(process_names[2], -0.8, -0.56, 0);
        sobj.text(process_names[3], -0.8, -0.64, 0);

        //Print Arrival Time
        strTime3 = to_string(at[0]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, -0.5, -0.40, 0);
        strTime3 = to_string(at[1]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, -0.5, -0.48, 0);
        strTime3 = to_string(at[2]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, -0.5, -0.56, 0);
        strTime3 = to_string(at[3]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, -0.5, -0.64, 0);

        //Print Burst Time
        strTime3 = to_string(bt[0]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, 0.0, -0.40, 0);
        strTime3 = to_string(bt[1]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, 0.0, -0.48, 0);
        strTime3 = to_string(bt[2]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, 0.0, -0.56, 0);
        strTime3 = to_string(bt[3]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, 0.0, -0.64, 0);

        //Gantt Chart
        for (j = 1; t[j] <= time1; j++)
        {
            if (p[j - 1] == 1) //P1
            {
                glColor3f(1.0, 0.0, 0.0);
                if ((t[j] - t[j - 1]) == 1)
                    dx1RR = fxRR;
                else if ((t[j] - t[j - 1]) == 2)
                    dx1RR = fxRR * 2;
                else if ((t[j] - t[j - 1]) == 3)
                    dx1RR = fxRR * 3;
                glBegin(GL_POLYGON);
                glVertex2d(xRR, 0.2);
                glVertex2d(xRR, 0.4);
                glVertex2d(xRR + dx1RR, 0.4);
                glVertex2d(xRR + dx1RR, 0.2);
                glEnd();

                glColor3f(1, 1, 1);
                sobj.text(process_names[0], xRR + dx1RR / 2 - 0.03, 0.3, 0);
                glColor3f(0, 0, 0);
                glLineWidth(3);
                glBegin(GL_LINES);
                glVertex2d(xRR + dx1RR, 0.2);
                glVertex2d(xRR + dx1RR, 0.4);
                glEnd();
                string strTime = to_string(t[j]);
                char charTime_array[n + 1];
                strcpy(charTime_array, strTime.c_str());
                sobj.text(charTime_array, xRR + dx1RR, 0.1, 0);
                xRR += dx1RR;
                if (isDone == false)
                {
                    for (long ccc = 0; ccc < delay; ccc++)
                    {
                        std::cout << "Delay" << std::endl;
                    }
                    glutSwapBuffers();
                }
            }
            else if (p[j - 1] == 2) //P2
            {
                glColor3f(0.0, 1.0, 0.0);
                if ((t[j] - t[j - 1]) == 1)
                    dx1RR = fxRR;
                else if ((t[j] - t[j - 1]) == 2)
                    dx1RR = fxRR * 2;
                else if ((t[j] - t[j - 1]) == 3)
                    dx1RR = fxRR * 3;
                glBegin(GL_POLYGON);
                glVertex2d(xRR, 0.2);
                glVertex2d(xRR, 0.4);
                glVertex2d(xRR + dx1RR, 0.4);
                glVertex2d(xRR + dx1RR, 0.2);
                glEnd();
                glColor3f(1, 1, 1);
                sobj.text(process_names[1], xRR + dx1RR / 2 - 0.03, 0.3, 0);
                glColor3f(0, 0, 0);
                glLineWidth(3);
                glBegin(GL_LINES);
                glVertex2d(xRR + dx1RR, 0.2);
                glVertex2d(xRR + dx1RR, 0.4);
                glEnd();
                string strTime1 = to_string(t[j]);
                char charTime_array1[n + 1];
                strcpy(charTime_array1, strTime1.c_str());
                sobj.text(charTime_array1, xRR + dx1RR, 0.1, 0);
                xRR += dx1RR;
                if (isDone == false)
                {
                    for (long ccc = 0; ccc < delay; ccc++)
                    {
                        std::cout << "Delay" << std::endl;
                    }
                    glutSwapBuffers();
                }
            }
            else if (p[j - 1] == 3) //P3
            {
                glColor3f(0.0, 0.0, 1.0);
                if ((t[j] - t[j - 1]) == 1)
                    dx1RR = fxRR;
                else if ((t[j] - t[j - 1]) == 2)
                    dx1RR = fxRR * 2;
                else if ((t[j] - t[j - 1]) == 3)
                    dx1RR = fxRR * 3;
                glBegin(GL_POLYGON);
                glVertex2d(xRR, 0.2);
                glVertex2d(xRR, 0.4);
                glVertex2d(xRR + dx1RR, 0.4);
                glVertex2d(xRR + dx1RR, 0.2);
                glEnd();
                glColor3f(1, 1, 1);
                sobj.text(process_names[2], xRR + dx1RR / 2 - 0.03, 0.3, 0);
                glColor3f(0, 0, 0);
                glLineWidth(3);
                glBegin(GL_LINES);
                glVertex2d(xRR + dx1RR, 0.2);
                glVertex2d(xRR + dx1RR, 0.4);
                glEnd();
                strTime2 = to_string(t[j]);
                strcpy(charTime_array2, strTime2.c_str());
                sobj.text(charTime_array2, xRR + dx1RR, 0.1, 0);
                xRR += dx1RR;
                if (isDone == false)
                {
                    for (long ccc = 0; ccc < delay; ccc++)
                    {
                        std::cout << "Delay" << std::endl;
                    }
                    glutSwapBuffers();
                }
            }
            else if (p[j - 1] == 4) //P4
            {
                glColor3f(0.647059, 0.164706, 0.164706);
                if ((t[j] - t[j - 1]) == 1)
                    dx1RR = fxRR;
                else if ((t[j] - t[j - 1]) == 2)
                    dx1RR = fxRR * 2;
                else if ((t[j] - t[j - 1]) == 3)
                    dx1RR = fxRR * 3;
                glBegin(GL_POLYGON);
                glVertex2d(xRR, 0.2);
                glVertex2d(xRR, 0.4);
                glVertex2d(xRR + dx1RR, 0.4);
                glVertex2d(xRR + dx1RR, 0.2);
                glEnd();
                glColor3f(1, 1, 1);
                sobj.text(process_names[3], xRR + dx1RR / 2 - 0.03, 0.3, 0);
                glColor3f(0, 0, 0);
                glLineWidth(3);
                glBegin(GL_LINES);
                glVertex2d(xRR + dx1RR, 0.2);
                glVertex2d(xRR + dx1RR, 0.4);
                glEnd();
                strTime3 = to_string(t[j]);
                strcpy(charTime_array3, strTime3.c_str());
                sobj.text(charTime_array3, xRR + dx1RR, 0.1, 0);
                xRR += dx1RR;
                if (isDone == false)
                {
                    for (long ccc = 0; ccc < delay; ccc++)
                    {
                        std::cout << "Delay" << std::endl;
                    }
                    glutSwapBuffers();
                }
            }
        }
        xRR = -0.8;
        f = 1;
        if (isDone == false)
        {
            for (long ccc = 0; ccc < delay; ccc++)
            {
                std::cout << "Delay" << std::endl;
            }
            glutSwapBuffers();
        }
        isDone = true;
        //glutSwapBuffers();
        glPopMatrix();
        glutSwapBuffers();
    }
    glPopMatrix();
}

void displayRREx()
{

    
    glClearColor(.92, 0.92, 0.92, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sobj.bgComputer();
    glColor3f(1.0, 0.2, 0.5);
    sobj.headingText("QUEUE", 423, 40, 0, 0.15f, 0.15f, 0.0f);
    sobj.headingText("CPU", 230, 40, 0, 0.15f, 0.15f, 0.0f);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //home button 
    glPushMatrix();
    glTranslatef(-1.0,0.75,0);
    sobj.home();
    glPopMatrix();


    glColor3f(0.5, 0, 0.9);
    sobj.drawCircle(-0.8, 0.3, 0.10);
    sobj.drawCircle(-0.8, -0.1, 0.10);
    sobj.drawCircle(-0.8, -0.5, 0.10);

    glColor3f(0, 0, 0);
    sobj.text({"Time Quantum: 3ms"}, -0.95, -0.75, 0);
    glColor3f(1.0, 1.0, 1.0);
    sobj.text({"P2"}, -0.83, 0.30, 0);
    sobj.text({"3ms"}, -0.86, 0.23, 0);
    sobj.text({"P3"}, -0.83, -0.10, 0);
    sobj.text({"2ms"}, -0.86, -0.17, 0);
    sobj.text({"P4"}, -0.83, -0.50, 0);
    sobj.text({"7ms"}, -0.86, -0.57, 0);

    //CPU
    glPushMatrix();
    glScalef(1.25, 1.5, 0);
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_POLYGON);
    glVertex2d(-0.15, -0.5);
    glVertex2d(-0.15, 0.0);
    glVertex2d(0.15, 0.0);
    glVertex2d(0.15, -0.5);
    glEnd();
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2d(-0.10, -0.45);
    glVertex2d(-0.10, -0.05);
    glVertex2d(0.10, -0.05);
    glVertex2d(0.10, -0.45);
    glEnd();
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_POLYGON);
    glVertex2d(-0.085, -0.15);
    glVertex2d(-0.085, -0.10);
    glVertex2d(0.085, -0.10);
    glVertex2d(0.085, -0.15);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(-0.085, -0.25);
    glVertex2d(-0.085, -0.28);
    glVertex2d(-0.065, -0.28);
    glVertex2d(-0.065, -0.25);
    glEnd();
    glPopMatrix();

    //Ready Queue
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2d(0.7, -0.65);
    glVertex2d(0.95, -0.65);
    glVertex2d(0.7, -0.65);
    glVertex2d(0.7, 0.3);
    glVertex2d(0.95, -0.65);
    glVertex2d(0.95, 0.3);
    glEnd();
    if (xRex < 0.8f)
    { //P1
        glPushMatrix();
        glTranslated(xRex, 0, 0);
        glColor3f(0.5, 0, 0.9);
        sobj.drawCircle(-0.8 + xRex, 0.7, 0.10);
        glColor3f(1, 1, 1);
        sobj.text({"P1"}, -0.83, 0.70, 0);
        sobj.text({"4ms"}, -0.85, 0.63, 0);
        glPopMatrix();
        glColor3f(0,0,0);
        sobj.text({"Time:0ms"}, 0.75, 0.80, 0);
        xRex += 0.015f;
    }
    else
    {
        xRex = 0.8f;
        if (yRex > -1.05f)
        {
            glPushMatrix();
            glTranslated(0, yRex, 0);
            glColor3f(0.5, 0, 0.9);
            sobj.drawCircle(0, 0.7 + yRex, 0.10);
            glColor3f(1, 1, 1);
            sobj.text({"P1"}, -0.03, 0.70, 0);
            sobj.text({"4ms"}, -0.05, 0.64, 0);
            glPopMatrix();
            glColor3f(0,0,0);
            sobj.text({"Time:0ms"}, 0.75, 0.80, 0);
            yRex -= 0.01f;
        }
        else
        {
            yRex = -1.05f;
            if (isDone1 == false)
            {
                for (long ccc = 0; ccc < delay; ccc++)
                {
                    std::cout << "Delay" << std::endl;
                }
            }
            isDone1 = true;
            if (yRex1 < 1.04)
            {
                glColor3f(0,0,0);
                sobj.text({"Time:3ms"}, 0.75, 0.8, 0);
                glPushMatrix();
                glTranslated(xRex1, yRex1 + yRex, 0);
                glColor3f(0.5, 0, 0.9);
                sobj.drawCircle(0 + xRex1, 0.7 + yRex1 + yRex, 0.10);
                glColor3f(1, 1, 1);
                sobj.text({"P1"}, -0.03, 0.70, 0);
                sobj.text({"1ms"}, -0.05, 0.63, 0);
                glPopMatrix();
                yRex1 += 0.005f;
                xRex1 += 0.004f;
            }
            else
            {
                yRex1 = 1.05;
                xRex1 = 0.83;
                if (yRex2 > -1.23)
                {
                    glColor3f(0,0,0);
                    sobj.text({"Time:3ms"}, 0.75, 0.8, 0);
                    glPushMatrix();
                    glTranslated(xRex1, yRex2, 0);
                    glColor3f(0.5, 0, 0.9);
                    sobj.drawCircle(0 + xRex1, 0.7 + yRex1 + yRex + yRex2, 0.10);
                    glColor3f(1, 1, 1);
                    sobj.text({"P1"}, -0.03, 0.70, 0);
                    sobj.text({"1ms"}, -0.05, 0.63, 0);
                    glPopMatrix();
                    yRex2 -= 0.01f;
                }
                else
                {
                    yRex2 = -1.23;
                    glPushMatrix();
                    glTranslated(xRex1, yRex2, 0);
                    glColor3f(0.5, 0, 0.9);
                    sobj.drawCircle(0 + xRex1, 0.7 + yRex1 + yRex + yRex2, 0.10);
                    glColor3f(1, 1, 1);
                    sobj.text({"P1"}, -0.03, 0.70, 0);
                    sobj.text({"1ms"}, -0.05, 0.63, 0);
                    glPopMatrix();
                    glColor3f(0.8, 0.8, 0.8);
                    sobj.drawCircle(-0.8, 0.3, 0.10);
                    if (xRex2 < 0.8f)
                    { //P2
                        glColor3f(0,0,0);
                        sobj.text({"Time:3ms"}, 0.75, 0.8, 0);
                        glPushMatrix();
                        glTranslated(xRex2, 0, 0);
                        glColor3f(0.5, 0, 0.9);
                        sobj.drawCircle(-0.8 + xRex2, 0.3, 0.10);
                        glColor3f(1, 1, 1);
                        sobj.text({"P2"}, -0.83, 0.30, 0);
                        sobj.text({"3ms"}, -0.85, 0.23, 0);
                        glPopMatrix();
                        xRex2 += 0.015f;
                    }
                    else
                    {
                        xRex2 = 0.8f;
                        if (yRex3 > -0.8f)
                        {
                            glColor3f(0,0,0);
                            sobj.text({"Time:3ms"}, 0.75, 0.8, 0);
                            glPushMatrix();
                            glTranslated(xRex2, yRex3, 0);
                            glColor3f(0.5, 0, 0.9);
                            sobj.drawCircle(0, 0.3 + yRex3, 0.10);
                            glColor3f(1, 1, 1);
                            sobj.text({"P2"}, -0.83, 0.30, 0);
                            sobj.text({"3ms"}, -0.85, 0.23, 0);
                            glPopMatrix();
                            yRex3 -= 0.009f;
                        }
                        else
                        {
                            yRex3 = -0.8f;
                            if (isDone2 == false)
                            {
                                for (long ccc = 0; ccc < delay; ccc++)
                                {
                                    std::cout << "Delay" << std::endl;
                                }
                            }
                            isDone2 = true;
                            glColor3f(0.8, 0.8, 0.8);
                            sobj.drawCircle(-0.8, -0.1, 0.10);
                            glColor3f(1,0.2,0.2);
                            sobj.text({"P2 completed executing!"},-0.4,0.8,0);
                            if (xRex3 < 0.8f)
                            { //P3
                                glColor3f(0,0,0);
                                sobj.text({"Time:6ms"}, 0.75, 0.8, 0);
                                glPushMatrix();
                                glTranslated(xRex3, 0 + yRex9, 0);
                                glColor3f(0.5, 0, 0.9);
                                sobj.drawCircle(-0.8 + xRex3, -0.1 + yRex9, 0.10);
                                glColor3f(1, 1, 1);
                                sobj.text({"P3"}, -0.83, -0.10, 0);
                                sobj.text({"2ms"}, -0.85, -0.17, 0);
                                glPopMatrix();
                                xRex3 += 0.015f;
                                yRex9 += 0.005f;
                            }
                            else
                            {
                                xRex3 = 0.8f;
                                if (yRex4 > -0.65f)
                                {
                                    glColor3f(0,0,0);
                                    sobj.text({"Time:6ms"}, 0.75, 0.8, 0);
                                    glPushMatrix();
                                    glTranslated(xRex3, yRex4 + yRex9, 0);
                                    glColor3f(0.5, 0, 0.9);
                                    sobj.drawCircle(0, -0.1 + yRex4 + yRex9, 0.10);
                                    glColor3f(1, 1, 1);
                                    sobj.text({"P3"}, -0.83, -0.10, 0);
                                    sobj.text({"2ms"}, -0.85, -0.17, 0);
                                    glPopMatrix();
                                    yRex4 -= 0.01f;
                                }
                                else
                                {
                                    yRex4 = -0.65f;
                                    if (isDone3 == false)
                                    {
                                        for (long ccc = 0; ccc < delay; ccc++)
                                        {
                                            std::cout << "Delay" << std::endl;
                                        }
                                    }
                                    isDone3 = true;
                                    glColor3f(0.8, 0.8, 0.8);
                                    sobj.drawCircle(-0.8, -0.5, 0.10);
                                    glColor3f(1,0.2,0.2);
                                    sobj.text({"P3 completed executing!"},-0.4,0.7,0);
                                    if (xRex4 < 0.8f)
                                    { //P4
                                        glColor3f(0,0,0);
                                        sobj.text({"Time:8ms"}, 0.75, 0.8, 0);
                                        glPushMatrix();
                                        glTranslated(xRex4, yRex5, 0);
                                        glColor3f(0.5, 0, 0.9);
                                        sobj.drawCircle(-0.8 + xRex4, -0.5 + yRex5, 0.10);
                                        glColor3f(1, 1, 1);
                                        sobj.text({"P4"}, -0.83, -0.50, 0);
                                        sobj.text({"7ms"}, -0.85, -0.57, 0);
                                        glPopMatrix();
                                        xRex4 += 0.009f;
                                        yRex5 += 0.007f;
                                    }
                                    else
                                    {
                                        xRex4 = 0.8f;
                                        if (yRex6 > -0.65f)
                                        {
                                            glColor3f(0,0,0);
                                            sobj.text({"Time:8ms"}, 0.75, 0.8, 0);
                                            glPushMatrix();
                                            glTranslated(xRex4, yRex5 + yRex6, 0);
                                            glColor3f(0.5, 0, 0.9);
                                            sobj.drawCircle(0, -0.5 + yRex5 + yRex6, 0.10);
                                            glColor3f(1, 1, 1);
                                            sobj.text({"P4"}, -0.83, -0.50, 0);
                                            sobj.text({"7ms"}, -0.85, -0.57, 0);
                                            glPopMatrix();
                                            yRex6 -= 0.01f;
                                        }
                                        else
                                        {
                                            yRex6 = -0.65f;
                                            if (isDone4 == false)
                                            {
                                                for (long ccc = 0; ccc < delay; ccc++)
                                                {
                                                    std::cout << "Delay" << std::endl;
                                                }
                                            }
                                            isDone4 = true;
                                            if (yRex7 < 1.1)
                                            {
                                                glColor3f(0,0,0);
                                                sobj.text({"Time:11ms"}, 0.75, 0.8, 0);
                                                glPushMatrix();
                                                glTranslated(xRex5, yRex7, 0);
                                                glColor3f(0.5, 0, 0.9);
                                                sobj.drawCircle(0 + xRex5, 0.75 + yRex7 + yRex6 - yRex5, 0.10);
                                                glColor3f(1, 1, 1);
                                                sobj.text({"P4"}, -0.03, -0.50, 0);
                                                sobj.text({"4ms"}, -0.05, -0.57, 0);
                                                glPopMatrix();
                                                yRex7 += 0.007f;
                                                xRex5 += 0.00525f;
                                            }
                                            else
                                            {
                                                yRex7 = 1.1;
                                                //xRex5 = 0.83;
                                                if (yRex8 > -0.9)
                                                {
                                                    glColor3f(0,0,0);
                                                    sobj.text({"Time:11ms"}, 0.75, 0.8, 0);
                                                    glPushMatrix();
                                                    glTranslated(xRex5, yRex8 + yRex7, 0);
                                                    glColor3f(0.5, 0, 0.9);
                                                    sobj.drawCircle(0 + xRex5, 0.75 + yRex8 + yRex7 + yRex6 - yRex5, 0.10);
                                                    glColor3f(1, 1, 1);
                                                    sobj.text({"P4"}, -0.03, -0.50, 0);
                                                    sobj.text({"4ms"}, -0.05, -0.57, 0);
                                                    glPopMatrix();
                                                    yRex8 -= 0.01f;
                                                }
                                                else
                                                {
                                                    yRex8 = -0.91;
                                                    glColor3f(0.5, 0, 0.9);
                                                    sobj.drawCircle(0 + xRex5, 0.75 + yRex8 + yRex7 + yRex6 - yRex5, 0.10);
                                                    glColor3f(1, 1, 1);
                                                    sobj.text({"P4"}, xRex5 - 0.03, yRex8 + yRex7 - 0.50, 0);
                                                    sobj.text({"4ms"}, xRex5 - 0.05, yRex8 + yRex7 - 0.57, 0);
                                                    if (isDone5 == false)
                                                    {
                                                        for (long ccc = 0; ccc < delay; ccc++)
                                                        {
                                                            std::cout << "Delay" << std::endl;
                                                        }
                                                    }
                                                    isDone5 = true;
                                                    glColor3f(0.8, 0.8, 0.8);
                                                    sobj.drawCircle(0 + xRex5, 0.75 + yRex8 + yRex7 + yRex6 - yRex5, 0.10);
                                                    sobj.drawCircle(0 + xRex5, 0.55 + yRex8 + yRex7 + yRex6 - yRex5, 0.11);
                                                    glColor3f(0.5, 0.0, 0.9);
                                                    sobj.drawCircle(-0.8, 0.3, 0.10);
                                                    glColor3f(1, 1, 1);
                                                    sobj.text({"P4"}, -0.83, 0.30, 0);
                                                    sobj.text({"4ms"}, -0.86, 0.23, 0);

                                                    if (xRex7 < 0.8f)
                                                    { //P1
                                                        glColor3f(0,0,0);
                                                        sobj.text({"Time:11ms"}, 0.75, 0.8, 0);
                                                        glPushMatrix();
                                                        glTranslated(xRex7, 0, 0);
                                                        glColor3f(0.5, 0, 0.9);
                                                        sobj.drawCircle(-0.8 + xRex7, 0.7, 0.10);
                                                        glColor3f(1, 1, 1);
                                                        sobj.text({"P1"}, -0.83, 0.70, 0);
                                                        sobj.text({"1ms"}, -0.85, 0.63, 0);
                                                        glPopMatrix();
                                                        xRex7 += 0.015f;
                                                    }
                                                    else
                                                    {
                                                        xRex7 = 0.8f;
                                                        if (yRex10 > -1.25f)
                                                        {
                                                            glColor3f(0,0,0);
                                                            sobj.text({"Time:11ms"}, 0.75, 0.8, 0);
                                                            glPushMatrix();
                                                            glTranslated(0, yRex10, 0);
                                                            glColor3f(0.5, 0, 0.9);
                                                            sobj.drawCircle(0, 0.7 + yRex10, 0.10);
                                                            glColor3f(1, 1, 1);
                                                            sobj.text({"P1"}, -0.03, 0.70, 0);
                                                            sobj.text({"1ms"}, -0.05, 0.64, 0);
                                                            glPopMatrix();
                                                            yRex10 -= 0.01f;
                                                        }
                                                        else
                                                        {
                                                            yRex10 = -1.25f;
                                                            if (isDone6 == false)
                                                            {
                                                                for (long ccc = 0; ccc < delay; ccc++)
                                                                {
                                                                    std::cout << "Delay" << std::endl;
                                                                }
                                                            }
                                                            isDone6 = true;
                                                            flagForP4=1;
                                                            glColor3f(0.8, 0.8, 0.8);
                                                            sobj.drawCircle(-0.8, 0.3, 0.10);
                                                            glColor3f(1,0.2,0.2);
                                                            sobj.text({"P1 completed executing!"},-0.4,0.6,0);

                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(flagForP4==1)
    {
        if (xRex10 < 0.8f)
        { //P4
            glColor3f(0,0,0);
            sobj.text({"Time:12ms"}, 0.75, 0.8, 0);
            glPushMatrix();
            glTranslated(xRex10, 0, 0);
            glColor3f(0.5, 0, 0.9);
            sobj.drawCircle(-0.8 + xRex10, 0.3, 0.10);
            glColor3f(1, 1, 1);
            sobj.text({"P4"}, -0.83, 0.30, 0);
            sobj.text({"4ms"}, -0.85, 0.23, 0);
            glPopMatrix();
            xRex10 += 0.015f;
            }
            else
            {
                xRex10 = 0.8f;
                if (yRex11 > -0.85f)
                {
                    glColor3f(0,0,0);
                    sobj.text({"Time:12ms"}, 0.75, 0.8, 0);
                    glPushMatrix();
                    glTranslated(xRex10, yRex11, 0);
                    glColor3f(0.5, 0, 0.9);
                    sobj.drawCircle(0, 0.3 + yRex11, 0.10);
                    glColor3f(1, 1, 1);
                    sobj.text({"P4"}, -0.83, 0.30, 0);
                    sobj.text({"4ms"}, -0.85, 0.23, 0);
                    glPopMatrix();
                    yRex11 -= 0.009f;
                }
                else
                {
                    yRex11 = -0.85f;
                    if (isDone7 == false)
                    {
                        for (long ccc = 0; ccc < delay; ccc++)
                        {
                            std::cout << "Delay" << std::endl;
                        }
                    }
                    isDone7 = true;
                    if (yRex12 < 1.04)
                    {
                        glColor3f(0,0,0);
                        sobj.text({"Time:15ms"}, 0.75, 0.8, 0);
                        glPushMatrix();
                        glTranslated(xRex11, yRex12 + yRex11, 0);
                        glColor3f(0.5, 0, 0.9);
                        sobj.drawCircle(0 + xRex11, 0.3 + yRex12 + yRex11, 0.10);
                        glColor3f(1, 1, 1);
                        sobj.text({"P4"}, -0.03, 0.30, 0);
                        sobj.text({"1ms"}, -0.05, 0.23, 0);
                        glPopMatrix();
                        yRex12 += 0.005f;
                        xRex11 += 0.004f;
                    }
                    else
                    {
                        yRex12 = 1.05;
                        xRex11 = 0.83;
                        if (yRex13 > -0.95)
                        {
                            glColor3f(0,0,0);
                            sobj.text({"Time:15ms"}, 0.75, 0.8, 0);
                            glPushMatrix();
                            glTranslated(xRex11, yRex13 + yRex12 + yRex11, 0);
                            glColor3f(0.5, 0, 0.9);
                            sobj.drawCircle(0 + xRex11, 0.3 + yRex12 + yRex11 + yRex13, 0.10);
                            glColor3f(1, 1, 1);
                            sobj.text({"P4"}, -0.03, 0.30, 0);
                            sobj.text({"1ms"}, -0.05, 0.23, 0);
                            glPopMatrix();
                            yRex13 -= 0.01f;
                        }
                        else
                        {
                            yRex13 = -0.96;
                            if (isDone8 == false)
                            {
                                glPushMatrix();
                                glTranslated(xRex11, yRex13 + yRex12 + yRex11, 0);
                                glColor3f(0.5, 0, 0.9);
                                sobj.drawCircle(0 + xRex11, 0.3 + yRex12 + yRex11 + yRex13, 0.10);
                                glColor3f(1, 1, 1);
                                sobj.text({"P4"}, -0.03, 0.30, 0);
                                sobj.text({"1ms"}, -0.05, 0.23, 0);
                                glPopMatrix();
                            
                                for (long ccc = 0; ccc < delay; ccc++)
                                {
                                    std::cout << "Delay" << std::endl;
                                }
                            }
                            isDone8 = true;
                            glColor3f(0.8, 0.8, 0.8);
                            sobj.drawCircle(0 + xRex11, 0.3 + yRex12 + yRex11 + yRex13, 0.10);
                            /*glColor3f(0.5, 0.0, 0.9);
                            sobj.drawCircle(-0.8, 0.7, 0.10);
                            glColor3f(1, 1, 1);
                            sobj.text({"P4"}, -0.83, 0.70, 0);
                            sobj.text({"1ms"}, -0.86, 0.63, 0);
                        */
                            flagForP4=2;
                        }
                    }
                }
            }
    }
    if(flagForP4==2){
        if (xRex12 < 0.8f)
        { //P4
            glColor3f(0,0,0);
            sobj.text({"Time:15ms"}, 0.75, 0.8, 0);
            glPushMatrix();
            glTranslated(xRex12, 0, 0);
            glColor3f(0.5, 0, 0.9);
            sobj.drawCircle(-0.8 + xRex12, 0.7, 0.10);
            glColor3f(1, 1, 1);
            sobj.text({"P4"}, -0.83, 0.70, 0);
            sobj.text({"1ms"}, -0.85, 0.63, 0);
            glPopMatrix();
            xRex12 += 0.015f;
            }
            else
            {
                xRex12 = 0.8f;
                if (yRex14 > -1.25f) 
                {
                    glColor3f(0,0,0);
                    sobj.text({"Time:15ms"}, 0.75, 0.8, 0);
                    glPushMatrix();
                    glTranslated(xRex12, yRex14, 0);
                    glColor3f(0.5, 0, 0.9);
                    sobj.drawCircle(0, 0.7 + yRex14, 0.10);
                    glColor3f(1, 1, 1);
                    sobj.text({"P4"}, -0.83, 0.70, 0);
                    sobj.text({"1ms"}, -0.85, 0.63, 0);
                    glPopMatrix();
                    yRex14 -= 0.009f;
                }
                else
                {
                    yRex14 = -1.25f;
                    if (isDone9 == false)
                    {
                        for (long ccc = 0; ccc < delay; ccc++)
                        {
                            std::cout << "Delay" << std::endl;
                        }
                    }
                    isDone9 = true;
                    glColor3f(0,0,0);
                    sobj.text({"Time:16ms"}, 0.75, 0.8, 0);
                    glColor3f(1,0.2,0.2);
                    sobj.text({"P4 completed executing!"},-0.4,0.5,0);
                }
            }
        }

    glPopMatrix();
    glutSwapBuffers();
}

void np_priority_display()
{

    glClearColor(.92, 0.92, 0.92, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //background
    sobj.bgComputer();

    flagforNPP = 1;
    flagForButton = 1;

    //std::cout<<"flag for npp and fr button set"<<std::endl;
    glMatrixMode(GL_MODELVIEW); // -0.4f,0.5f,0.1f
    glPushMatrix();
    glLoadIdentity();

     //home button 
    glPushMatrix();
    glTranslatef(-1.0,0.75,0);
    sobj.home();
    glPopMatrix();


    //Word
    sobj.drawWord();
    //Calculator
    glPushMatrix();
    glLoadIdentity();
    sobj.drawCalculator();
    glPopMatrix();
    //Chrome
    sobj.drawChrome();

    sobj.drawMxPlayer();
    glPopMatrix();
    glPushMatrix();
    btn4.draw();
    btn5.draw();
    btn6.draw();
    btn7.draw();
    btn8.draw();
    btn9.draw();
    btn10.draw();
    btn11.draw();
    btn12.draw();
    btn13.draw();
    btn14.draw();
    btn15.draw();
    btn16.draw();
    btn17.draw();
    btn18.draw();
    btn19.draw();
    glPopMatrix();
    glColor3f(1.0, 1.0, 1);
    sobj.headingText("+", 158, 227, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 158, 210, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("+", 258, 227, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 258, 210, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("+", 357, 227, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 357, 210, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("+", 459, 227, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 459, 210, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("+", 158, 152, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 158, 135, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("+", 258, 152, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 258, 135, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("+", 357, 152, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 357, 135, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("+", 459, 152, 0.0, 0.1f, 0.1f, 0.0f);
    sobj.headingText("-", 459, 135, 0.0, 0.1f, 0.1f, 0.0f);

    glColor3f(0.35, 0.35, 0.67);
    sobj.headingText({"PRIORITY SCHEDULING"}, 150, 450, 0, 0.18f, 0.18f, 0.0f);
    glColor3f(0.0, 0.0, 0.0);
    sobj.text({"Process Name:"}, 12, 300, 0);
    sobj.text({"Priority:"}, 11, 220, 0);
    sobj.text({"Burst Time:"}, 12, 140, 0);
    sobj.text({"P1"}, 140, 300, 0);
    sobj.text({"P2"}, 239, 300, 0);
    sobj.text({"P3"}, 340, 300, 0);
    sobj.text({"P4"}, 445, 300, 0);

    string s1 = to_string(at[0]);
    int n = s1.length();
    char char_array1[n + 1];
    strcpy(char_array1, s1.c_str());
    sobj.text(char_array1, 140, 220, 0);

    string s2 = to_string(at[1]);
    char char_array2[n + 1];
    strcpy(char_array2, s2.c_str());
    sobj.text(char_array2, 239, 220, 0);

    string s3 = to_string(at[2]);
    char char_array3[n + 1];
    strcpy(char_array3, s3.c_str());
    sobj.text(char_array3, 340, 220, 0);

    string s4 = to_string(at[3]);
    char char_array4[n + 1];
    strcpy(char_array4, s4.c_str());
    sobj.text(char_array4, 445, 220, 0);

    //burst time
    string bs1 = to_string(bt[0]);
    n = bs1.length();
    char bchar_array1[n + 1];
    strcpy(bchar_array1, bs1.c_str());
    sobj.text(bchar_array1, 140, 140, 0);

    string bs2 = to_string(bt[1]);
    char bchar_array2[n + 1];
    strcpy(bchar_array2, bs2.c_str());
    sobj.text(bchar_array2, 239, 140, 0);

    string bs3 = to_string(bt[2]);
    char bchar_array3[n + 1];
    strcpy(bchar_array3, bs3.c_str());
    sobj.text(bchar_array3, 340, 140, 0);

    string bs4 = to_string(bt[3]);
    char bchar_array4[n + 1];
    strcpy(bchar_array4, bs4.c_str());
    sobj.text(bchar_array4, 445, 140, 0);
    sobj.text({"*Lower number is HIGHER priority"}, 20, 83, 0);
    sobj.text({"Press Enter to view Gantt chart"}, 250, 45, 0);
    glEnd();
    glutSwapBuffers();
}
//Added
void np_priority_display2()
{

    int time_sum = 0, burst_sum = 0.0;

    glClearColor(.92, 0.92, 0.92, 0.0);

    glClear(GL_COLOR_BUFFER_BIT);
    flagforNPP = 0;
    sobj.bgComputer();
    glColor3f(0.5, 0, 1.0);
    sobj.headingText("GANTT CHART CONSTRUCTION", 70, 450, 0, 0.2, 0.2, 0.0); //Not Working
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW); // To operate on the model-view matrix
    glLoadIdentity();           // Reset model-view matrix

    //home button 
    glPushMatrix();
    glTranslatef(-1.0,0.75,0);
    sobj.home();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(xx, yy, 0.0f); // Translate to (xPos, yPos)
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f); // Blue
    glVertex2f(-0.8f, 0.0f);
    glVertex2f(-0.8f, 0.2f);
    glVertex2f(0.8f, 0.2f);
    glVertex2f(0.8f, 0.0f);
    glEnd();
    glPopMatrix();

    // glutSwapBuffers();

    // Swap front and back buffers (of double buffered mode)
    // Animation Control - compute the location for the next refresh
    if (yy < YMax)
    {
        yy += ySpeed;
        glutSwapBuffers();
    }
    else
    {
        yy = YMax;
        glPushMatrix();
        glMatrixMode(GL_MODELVIEW); // To operate on the model-view matrix
        glLoadIdentity();
        glColor3f(0, 0, 0);
        sobj.text({"0"}, -0.8, 0.1, 0);
        sobj.text({"Time:"}, -1.1, 0.1, 0);
        glPopMatrix();
        if (flagForRRComp == 0)
        {
            for (i = 0; i < n; i++)
            {
                rt[i] = bt[i];
            }
            for (int l = 0; l < 4; l++)
            {
                printf("Priority  P%d %d\n", l + 1, at[l]);
                printf("Burst time P%d %d\n", l + 1, bt[l]);
                burst_sum += bt[l];
            }
            std::cout << "\n burst sum =" << burst_sum << std::endl;

            //non premptive priority Scheduling Algorithm
            int position, temp;
            char temp1;
            for (i = 0; i < 4; i++)
            {
                position = i;
                for (j = i + 1; j < 4; j++)
                {
                    if (at[j] < at[position])
                    {
                        position = j;
                    }
                }
                temp = at[i];
                at[i] = at[position];
                at[position] = temp;
                temp = bt[i];
                bt[i] = bt[position];
                bt[position] = temp;
                temp1 = process[i];
                process[i] = process[position];
                process[position] = temp1;
            }

            //wait time

            //wait_time[0] = 0;
            //   for(i = 1; i < 4; i++)
            //   {
            //     //    wait_time[i] = 0;
            //         for(j = 0; j < i; j++)
            //         {
            //               wait_time[i] = wait_time[i] + bt[j];
            //         }
            //         sum = sum + wait_time[i];
            //   }
            //   average_wait_time = sum / 4;
            // sum = 0;
            //printf("\nProcess ID\t\tBurst Time\t Waiting Time\t Turnaround Time\n");

            printf("\nProcess ID\t\tBurst Time\n");

            for (i = 0; i < 4; i++)
            {
                //turnaround_time[i] = bt[i] + wait_time[i];
                //sum = sum + turnaround_time[i];
                // printf("\nProcess[%d]\t\t%d\t\t %d\t\t %d\n", process[i], bt[i], wait_time[i], turnaround_time[i]);
                printf("\nProcess[%d]\t\t%d\t\t \n", process[i], bt[i]);
            }
            //   average_turnaround_time = sum / 4;
            //   printf("\nAverage Waiting Time:\t%f", average_wait_time);
            //   printf("\nAverage Turnaround Time:\t%f\n", average_turnaround_time);

            flagForRRComp = 1;
        } // complete solvinhg

        //Process blocks in the top
        glColor3f(1, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(-0.6, 0.6);
        glVertex2f(-0.6, 0.7);
        glVertex2f(-0.4, 0.7);
        glVertex2f(-0.4, 0.6);
        glEnd();
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2f(-0.3, 0.6);
        glVertex2f(-0.3, 0.7);
        glVertex2f(-0.1, 0.7);
        glVertex2f(-0.1, 0.6);
        glEnd();
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POLYGON);
        glVertex2f(0.0, 0.6);
        glVertex2f(0.0, 0.7);
        glVertex2f(0.2, 0.7);
        glVertex2f(0.2, 0.6);
        glEnd();
        glColor3f(0.647059, 0.164706, 0.164706);
        glBegin(GL_POLYGON);
        glVertex2f(0.3, 0.6);
        glVertex2f(0.3, 0.7);
        glVertex2f(0.5, 0.7);
        glVertex2f(0.5, 0.6);
        glEnd();

        //Print process names
        glColor3f(1, 1, 1);
        sobj.text("P1", -0.53, 0.62, 0);
        sobj.text("P2", -0.23, 0.62, 0);
        sobj.text("P3", 0.07, 0.62, 0);
        sobj.text("P4", 0.37, 0.62, 0);

        glColor3f(0.0, 0.0, 0.0);
        sobj.text({"Priority"}, -0.6, -0.3, 0);
        sobj.text({"Burst Time"}, -0.1, -0.3, 0);

        strTime3 = to_string(process[0]);
        strTime3.insert(0, 1, 'P');
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, -0.8, -0.40, 0);

        strTime3 = to_string(process[1]);
        strTime3.insert(0, 1, 'P');
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, -0.8, -0.48, 0);

        strTime3 = to_string(process[2]);
        strTime3.insert(0, 1, 'P');
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, -0.8, -0.56, 0);

        strTime3 = to_string(process[3]);
        strTime3.insert(0, 1, 'P');
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, -0.8, -0.64, 0);

        //Print Arrival Time
        strTime3 = to_string(at[0]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, -0.5, -0.40, 0);
        strTime3 = to_string(at[1]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, -0.5, -0.48, 0);
        strTime3 = to_string(at[2]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, -0.5, -0.56, 0);
        strTime3 = to_string(at[3]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, -0.5, -0.64, 0);

        //Print Burst Time
        strTime3 = to_string(bt[0]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, 0.0, -0.40, 0);
        strTime3 = to_string(bt[1]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, 0.0, -0.48, 0);
        strTime3 = to_string(bt[2]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, 0.0, -0.56, 0);
        strTime3 = to_string(bt[3]);
        strcpy(charTime_array3, strTime3.c_str());
        sobj.text(charTime_array3, 0.0, -0.64, 0);

        xRR = -0.798;

        if (flagForRRComp == 1)
        {
            for (i = 0; i < 4; i++)
            {
                dx1RR = 1.596 * bt[i] / burst_sum;
                std::cout << "dx rr" << dx1RR << std::endl;
                if (process[i] == 1)
                    glColor3f(1.0, 0.0, 0.0);
                else if (process[i] == 2)
                    glColor3f(0, 1, 0);
                else if (process[i] == 3)
                    glColor3f(0.0, 0.0, 1);
                else
                    glColor3f(0.647059, 0.164706, 0.164706);
                glBegin(GL_POLYGON);
                glVertex2d(xRR, 0.205);
                glVertex2d(xRR, 0.4);
                glVertex2d(xRR + dx1RR, 0.4);
                glVertex2d(xRR + dx1RR, 0.205);
                glEnd();

                glColor3f(1, 1, 1);
                strTime3 = to_string(process[i]);
                strTime3.insert(0, 1, 'P');
                strcpy(charTime_array3, strTime3.c_str());

                sobj.text(charTime_array3, xRR + dx1RR / 2 - 0.03, 0.3, 0);

                glColor3f(0, 0, 0);
                glLineWidth(3);
                glBegin(GL_LINES);
                glVertex2d(xRR + dx1RR, 0.2);
                glVertex2d(xRR + dx1RR, 0.4);
                glEnd();
                time_sum += bt[i];
                string strTime = to_string(time_sum);
                char charTime_array[n + 1];
                strcpy(charTime_array, strTime.c_str());
                sobj.text(charTime_array, xRR + dx1RR - .02, 0.1, 0);
                xRR += dx1RR;
                if (isDone == false)
                {
                    for (long ccc = 0; ccc < delay; ccc++)
                    {
                        std::cout << "Delay" << std::endl;
                    }
                    glutSwapBuffers();
                }
                if (i == 3)
                {
                    flagForRRComp = 2;
                    glutSwapBuffers();
                }
            }

            glutSwapBuffers();
        }
    }
    glPopMatrix();
}

void displayPEx(){

    glClearColor(.92, 0.92, 0.92, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sobj.bgComputer();
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

 //home button 
    glPushMatrix();
    glTranslatef(-1.0,0.75,0);
    sobj.home();
    glPopMatrix();



    //CPU
    glPushMatrix();
    glScalef(1.25, 1.5, 0);
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_POLYGON);
    glVertex2d(-0.15, -0.5);
    glVertex2d(-0.15, 0.0);
    glVertex2d(0.15, 0.0);
    glVertex2d(0.15, -0.5);
    glEnd();
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2d(-0.10, -0.45);
    glVertex2d(-0.10, -0.05);
    glVertex2d(0.10, -0.05);
    glVertex2d(0.10, -0.45);
    glEnd();
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_POLYGON);
    glVertex2d(-0.085, -0.15);
    glVertex2d(-0.085, -0.10);
    glVertex2d(0.085, -0.10);
    glVertex2d(0.085, -0.15);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(-0.085, -0.25);
    glVertex2d(-0.085, -0.28);
    glVertex2d(-0.065, -0.28);
    glVertex2d(-0.065, -0.25);
    glEnd();
    glPopMatrix();


    glColor3f(0.5, 0, 0.9);

     glPushMatrix();
        glTranslated(xRex, yRex, 0);
        glColor3f(0.5, 0, 0.9);
        sobj.drawCircle(-0.8+xRex , 0.7+yRex, 0.10);
        glColor3f(1, 1, 1);
        sobj.text({"P1"}, -0.83, 0.70, 0);
        sobj.text({"4ms"}, -0.85, 0.63, 0);
        glPopMatrix();

//chnge below
    
     glPushMatrix();
        glTranslated(xRex1, yRex1, 0);
        glColor3f(0.5, 0, 0.9);
    sobj.drawCircle(-0.8+xRex1, 0.55+yRex1, 0.10);
      glColor3f(1, 1, 1);
    sobj.text({"P2"}, -0.84, 0.58, 0);
    sobj.text({"3ms"}, -0.855, 0.5, 0);
    glPopMatrix();


    
     glPushMatrix();
        glTranslated(xRex2, yRex2, 0);
        glColor3f(0.5, 0, 0.9);
     sobj.drawCircle(-0.8+xRex2, 0.3+yRex2, 0.10);
      glColor3f(1, 1, 1);
    sobj.text({"P3"}, -0.84, 0.33, 0);
    sobj.text({"2ms"}, -0.855,0.25, 0);
    glPopMatrix();


 
     glPushMatrix();
        glTranslated(xRex3, yRex3, 0);
        glColor3f(0.5, 0, 0.9);
    sobj.drawCircle(-0.8+xRex3, 0.05+yRex3, 0.10);
    glColor3f(1.0, 1.0, 1.0);
    sobj.text({"P4"}, -0.84, 0.054, 0);
    sobj.text({"7ms"}, -0.855,-0.01, 0);
glPopMatrix();

  glPushMatrix();
         glColor3f(1,0,0);
    sobj.text({"Priority:"}, 0.58, 0.4, 0);
    sobj.text({"P1 > P2 > P4 > P3"}, 0.50,0.3, 0);
glPopMatrix();


    if (xRex < 0.8f)
    {
       
        xRex += 0.01;
    }
    else
    {
        xRex = 0.8f;
        if (yRex > -1.2f)
        {
            yRex -= 0.005f;
           
        }
        else
        {
           
            if(yRex>=-1.205){
                std::cout << "Delay" << std::endl;
                for (long ccc = 0; ccc < delay; ccc++)
                {
                    std::cout << "Delay" << std::endl;
                }
                yRex-=1;
            }
            yRex = -2.0f;

          
            if (xRex1 < 0.8f)
            {
                xRex1 += 0.010f;
            }
            else
            {
                xRex1 = 0.8;
                if (yRex1 > -1.080f)
                {
                     
                    yRex1 -= 0.005f;
                }
                else
                {
                    
                    if(yRex1>=-1.085){
                    for (long ccc = 0; ccc < delay; ccc++)
                    {
                   std::cout << "Delay" << std::endl;
                    }
                    yRex1 -= -1.0f;
                    }
                    yRex1 = -2.0f;

                    //4th process
                    if (xRex3 < 0.8f)
                    {
       
                       xRex3 += 0.01;
                    }
                    else
                    {
                         xRex3 = 0.8f;
                         if (yRex3 > -0.605f)
                         {
                            yRex3 -= 0.005f;
                            std::cout << "XREX3" <<yRex3<< std::endl;
                         }
                         else
                        {
           
                        if(yRex3>=-0.610){
                                std::cout << "Delay" << std::endl;
                        for (long ccc = 0; ccc < delay; ccc++)
                        {
                              std::cout << "Delay" << std::endl;
                        }
                       yRex3-=1;
                       }
                        yRex3 = -2.0f;
                         //3rd process
                         if (xRex2 < 0.8f)
                         {
       
                            xRex2 += 0.01;
                        }
                        else{
                             xRex2 = 0.8f;
                         if (yRex2 > -0.805f)
                         {
                            yRex2 -= 0.005f;
                            std::cout << "XREX3" <<yRex2<< std::endl;
                         }
                         else
                        {
           
                        if(yRex2>=-0.810){
                                std::cout << "Delay" << std::endl;
                        for (long ccc = 0; ccc < delay; ccc++)
                        {
                              std::cout << "Delay" << std::endl;
                        }
                       yRex2-=1;
                       }
                        yRex2 = -2.0f;
                         }
                        }
                         }

                        

                    }

                }

            }
         }
    }
    glPopMatrix();
    glutSwapBuffers();


}


void init_variable(){

     n = 4; time_quantum = 3  ; remain = 4  ; flag = 0  ; wait_time = 0  ; turnaround_time = 0;
 flagForRR = 0  ; flag5 = 0  ; flag1 = 0  ; flag2 = 0  ; flag3 = 0  ; flag4 = 0  ; flagForButton = 0  ; flagForRRComp = 0  ; f = 0  ; flagforNPP = 0  ;flagForP4=0;

 radius = 0.8f;
   sdx = -1.0;
  xx = 0.0f;
  yy = -1.0f;
  YMax = 0.2  ;  //  center (x  ; y) bounds
 xSpeed = 0.00f;               // speed in x and y directions
  ySpeed = 0.007f;
   xRR = -0.8;
   xRex = 0.0f  ; yRex = 0.0f  ; xRex1 = 0.0f  ; yRex1 = 0.0f  ; xRex2 = 0.0f  ; yRex2 = 0.0f  ; xRex3 = 0.0f  ; yRex3 = 0.0f  ; xRex4 = 0.0f  ; yRex4 = 0.0f  ; xRex5 = 0.0f  ; yRex5 = 0.0f;
   xRex6 = 0.0f  ; yRex6 = 0.0f  ; xRex7 = 0.0f  ; yRex7 = 0.0f  ; xRex8 = 0.0f  ; yRex8 = 0.0f  ; xRex9 = 0.0f  ; yRex9 = 0.0f  ; xRex10 = 0.0f  ; yRex10 = 0.0f  ;yRex11=0.0f;
   xRex11=0.0f  ;yRex12=0.0f  ;xRex12=0.0f  ;yRex13=0.0f  ;xRex13=0.0f  ;yRex14=0.0f  ;xRex14=0.0f  ;yRex15=0.0f  ;yRex16=0.0f  ;yRex17=0.0f;
width1 = 20  ; height1 = 20;

 isDone = false  ; isDone1 = false  ; isDone2 = false  ; isDone3 = false  ; isDone4 = false  ; isDone5 = false  ; isDone6 = false  ;isDone7 = false  ;isDone8=false  ;isDone9=false;
 delay = 500000;
refreshMillis = 10; // Refresh period in milliseconds
int i_counter=0;
for(i_counter=0;i_counter<4;i_counter++)
{
     process[i_counter] =i_counter;
     bt[i_counter]=1;
     at[i_counter]=0;
     rt[i_counter]=0;

}

}

void reshape(GLsizei width, GLsizei height)
{
    // Compute aspect ratio of the new window
    if (height == 0)
        height = 1; // To prevent divide by 0
    windowWidth = width;
    windowHeight = height;

    std::cout << "window height reshape:   " << windowHeight << endl;
    std::cout << "indow width reshape:   " << windowWidth << endl
              << endl;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);
    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity();            // Reset the projection matrix
    if (width >= height)
    {
        clipAreaXLeft = -1.0 * aspect;
        clipAreaXRight = 1.0 * aspect;
        clipAreaYBottom = -1.0;
        clipAreaYTop = 1.0;
    }
    else
    {
        clipAreaXLeft = -1.0;
        clipAreaXRight = 1.0;
        clipAreaYBottom = -1.0 / aspect;
        clipAreaYTop = 1.0 / aspect;
    }
    gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
    XMin = clipAreaXLeft + radius;
    XMax = (clipAreaXRight - radius);
    YMin = clipAreaYBottom + radius;
    YMax = (clipAreaYTop - radius);
}

void Timer(int value)
{
    if (flag1 == 0)
    {
        glutPostRedisplay();                    // Post a paint request to activate display()
        glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 13: // ENTER key
            if (flagForRR == 1)
                glutDisplayFunc(display2);
            else if (flagforNPP == 1)
            {
                std::cout << "insde entr fg npp";
                glutDisplayFunc(np_priority_display2);
            }
            break;
        case 'q':exit(0);
    }
    glutPostRedisplay();
}

void myInit()
{
    int i;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    for (i = 0; i < 4; i++)
    {
        at[i] = 0;
        bt[i] = 1;
    }
    process_names[0][0] = 'P';
    process_names[1][0] = 'P';
    process_names[2][0] = 'P';
    process_names[3][0] = 'P';
    process_names[0][1] = '1';
    process_names[1][1] = '2';
    process_names[2][1] = '3';
    process_names[3][1] = '4';
}

void mouse(int btn, int state, int x, int y)
{
    y = windowHeight - y;
    std::cout << "x:   " << x << endl;
    std::cout << "y  :   " << y << endl;

    float x1 = x / (float)windowWidth;
    float y1 = y / (float)windowHeight;
    std::cout << "x1:   " << x1 << endl;
    std::cout << "y 1 :   " << y1 << endl;

    std::cout << "window height :   " << windowHeight << endl;
    std::cout << "window width :   " << windowWidth << endl
              << endl;


    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (homeBtn.insidebutton(x1, y1,0.07,0.30,0.855,0.965))
        {
            std::cout << "insde homeBtn............." << endl;
           // homeBtn.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (homeBtn.insidebutton(x1, y1, 0.07,0.30,0.855,0.965))
        {
            std::cout << "idsdsdnsde homeBtn........." << endl;
            //homeBtn.togglestate();
            init_variable();
            glutDisplayFunc(initial_display);
        }
    }

     // 1st page4 option selection
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 0 && btnRR.insidebutton(x1, y1, 0.71, 0.88, 0.4, 0.5))
        {
            std::cout << "insde btnRR" << endl;
            btnRR.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 0 && btnRR.insidebutton(x1, y1, 0.71, 0.88, 0.4, 0.5))
        {
            std::cout << "idsdsdnsde btnegRR" << endl;
            btnRR.togglestate();
            glutDisplayFunc(display);
        }
    }

    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 0 && btnegRR.insidebutton(x1, y1, 0.71, 0.88, 0.3, 0.4))
        {
            std::cout << "inside btnegRR" << endl;
            btnegRR.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 0 && btnegRR.insidebutton(x1, y1, 0.71, 0.88, 0.3, 0.4))
        {
            std::cout << "inside btn1" << endl;
            btnegRR.togglestate();
            glutDisplayFunc(displayRREx);
        }
    }

   if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 0 && btnP.insidebutton(x1, y1, 0.71, 0.88, 0.2, 0.3))
        {
            std::cout << "inside btnP" << endl;
            btnP.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 0 && btnP.insidebutton(x1, y1, 0.71, 0.88, 0.2, 0.3))
        {
            std::cout << "inside btnP" << endl;
            btnP.togglestate();
            glutDisplayFunc(np_priority_display);
        }
    }

    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 0 && btnPeg.insidebutton(x1, y1, 0.71, 0.88, 0.1, 0.2))
        {
            std::cout << "inside btnPeg" << endl;
            btnPeg.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 0 && btnPeg.insidebutton(x1, y1, 0.71, 0.88, 0.1, 0.2))
        {
            std::cout << "inside btnPeg" << endl;
            btnPeg.togglestate();
            glutDisplayFunc(displayPEx);
        }
    }
    

    //P1 arrival time
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn4.insidebutton(x1, y1, 0.365, 0.417, 0.45, 0.473))
        {
            std::cout << "inside btn4" << endl;
            btn4.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn4.insidebutton(x1, y1, 0.365, 0.417, 0.45, 0.473))
        {
            std::cout << "inside btn4" << endl;
            btn4.togglestate();
            if (at[0] < 5)
                at[0]++;
            std::cout << "at[0]: " << at[0] << endl;
        }
    }

    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn5.insidebutton(x1, y1, 0.365, 0.417, 0.417, 0.437))
        {
            std::cout << "inside btn5" << endl;
            btn5.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn5.insidebutton(x1, y1, 0.365, 0.417, 0.417, 0.437))
        {
            std::cout << "inside btn5" << endl;
            btn5.togglestate();
            if (at[0] > 0)
                at[0]--;
            std::cout << "at[0]: " << at[0] << endl;
        }
    }

    //P2 arrival time
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn6.insidebutton(x1, y1, 0.50, 0.52, 0.45, 0.473))
        {
            std::cout << "inside btn6" << endl;
            btn6.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn6.insidebutton(x1, y1, 0.50, 0.52, 0.45, 0.473))
        {
            std::cout << "inside btn5" << endl;
            btn6.togglestate();
            if (at[1] < 5)
                at[1]++;
            std::cout << "at[1]: " << at[1] << endl;
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn7.insidebutton(x1, y1, 0.50, 0.52, 0.417, 0.437))
        {
            std::cout << "inside btn7" << endl;
            btn7.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn7.insidebutton(x1, y1, 0.50, 0.52, 0.417, 0.437))
        {
            std::cout << "inside btn7" << endl;
            btn7.togglestate();
            if (at[1] > 0)
                at[1]--;
            std::cout << "at[1]: " << at[1] << endl;
        }
    }

    //Arrival time for Process3
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn8.insidebutton(x1, y1, 0.61, 0.673, 0.45, 0.473))
        {
            std::cout << "inside btn8" << endl;
            btn8.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn8.insidebutton(x1, y1, 0.61, 0.673, 0.45, 0.473))
        {
            std::cout << "inside btn8" << endl;
            btn8.togglestate();
            if (at[2] < 5)
                at[2]++;
            std::cout << "at[2]: " << at[2] << endl;
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn9.insidebutton(x1, y1, 0.61, 0.673, 0.417, 0.437))
        {
            std::cout << "inside btn9" << endl;
            btn9.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn9.insidebutton(x1, y1, 0.61, 0.673, 0.417, 0.437))
        {
            std::cout << "inside btn9" << endl;
            btn9.togglestate();
            if (at[2] > 0)
                at[2]--;
            std::cout << "at[2]: " << at[2] << endl;
        }
    }

    //Arrival time for Process4
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn10.insidebutton(x1, y1, 0.719, 0.8275, 0.45, 0.473))
        {
            std::cout << "inside btn10" << endl;
            btn10.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn10.insidebutton(x1, y1, 0.719, 0.8275, 0.45, 0.473))
        {
            std::cout << "inside btn10" << endl;
            btn10.togglestate();
            if (at[3] < 5)
                at[3]++;
            std::cout << "at[3]: " << at[3] << endl;
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn11.insidebutton(x1, y1, 0.719, 0.8275, 0.417, 0.437))
        {
            std::cout << "inside btn11" << endl;
            btn11.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn11.insidebutton(x1, y1, 0.719, 0.8275, 0.417, 0.437))
        {
            std::cout << "inside btn11" << endl;
            btn11.togglestate();
            if (at[3] > 0)
                at[3]--;
            std::cout << "at[3]: " << at[3] << endl;
        }
    }

    //burst time for Process1
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn12.insidebutton(x1, y1, 0.365, 0.417, 0.297, 0.325))
        {
            std::cout << "inside btn12" << endl;
            btn12.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn12.insidebutton(x1, y1, 0.365, 0.417, 0.297, 0.325))
        {
            std::cout << "inside btn12" << endl;
            btn12.togglestate();
            if (bt[0] < 6)
                bt[0]++;
            std::cout << "bt[0]: " << bt[0] << endl;
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn13.insidebutton(x1, y1, 0.365, 0.417, 0.27, 0.285))
        {
            std::cout << "inside btn13" << endl;
            btn13.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn13.insidebutton(x1, y1, 0.365, 0.417, 0.27, 0.285))
        {
            std::cout << "inside btn13" << endl;
            btn13.togglestate();
            if (bt[0] > 1)
                bt[0]--;
            std::cout << "bt[0]: " << bt[0] << endl;
        }
    }
    //P2 burst time
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn14.insidebutton(x1, y1, 0.50, 0.525, 0.295, 0.325))
        {
            std::cout << "inside btn14" << endl;
            btn14.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn14.insidebutton(x1, y1, 0.50, 0.525, 0.295, 0.325))
        {
            std::cout << "inside btn14" << endl;
            btn14.togglestate();
            if (bt[1] < 6)
                bt[1]++;
            std::cout << "bt[1]: " << bt[1] << endl;
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn15.insidebutton(x1, y1, 0.50, 0.52, 0.268, 0.288))
        {
            std::cout << "inside btn15" << endl;
            btn15.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn15.insidebutton(x1, y1, 0.50, 0.52, 0.268, 0.288))
        {
            std::cout << "inside btn15" << endl;
            btn15.togglestate();
            if (bt[1] > 1)
                bt[1]--;
            std::cout << "bt[1]: " << bt[1] << endl;
        }
    }

    //burst time for Process3
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn16.insidebutton(x1, y1, 0.61, 0.673, 0.305, 0.325))
        {
            std::cout << "inside btn16" << endl;
            btn16.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn16.insidebutton(x1, y1, 0.61, 0.673, 0.305, 0.325))
        {
            std::cout << "inside btn16" << endl;
            btn16.togglestate();
            if (bt[2] < 6)
                bt[2]++;
            std::cout << "bt[2]: " << bt[2] << endl;
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn17.insidebutton(x1, y1, 0.61, 0.673, 0.27, 0.287))
        {
            std::cout << "inside btn17" << endl;
            btn17.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn17.insidebutton(x1, y1, 0.61, 0.673, 0.27, 0.287))
        {
            std::cout << "inside btn17" << endl;
            btn17.togglestate();
            if (bt[2] > 1)
                bt[2]--;
            std::cout << "bt[2]: " << bt[2] << endl;
        }
    }

    //burst time for Process4
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn18.insidebutton(x1, y1, 0.719, 0.8275, 0.31, 0.329))
        {
            std::cout << "inside btn18" << endl;
            btn18.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn18.insidebutton(x1, y1, 0.719, 0.8275, 0.31, 0.329))
        {
            std::cout << "inside btn18" << endl;
            btn18.togglestate();
            if (bt[3] < 6)
                bt[3]++;
            std::cout << "bt[3]: " << bt[3] << endl;
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (flagForButton == 1 && btn19.insidebutton(x1, y1, 0.719, 0.8275, 0.269, 0.29))
        {
            std::cout << "inside btn19" << endl;
            btn19.togglestate();
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (flagForButton == 1 && btn19.insidebutton(x1, y1, 0.719, 0.8275, 0.269, 0.29))
        {
            std::cout << "inside btn19" << endl;
            btn19.togglestate();
            if (bt[3] > 1)
                bt[3]--;
            std::cout << "bt[3]: " << bt[3] << endl;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glEnable(GL_NORMALIZE);
    glutCreateWindow("Process Selection");
    glutFullScreen();
    glutDisplayFunc(initial_display);
   // glutDisplayFunc(first_display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, Timer, 0);
    glutKeyboardFunc(keyboard);
    myInit();
    //engine = irrklang::createIrrKlangDevice();
  //  engine->play2D("abc.wav",false);              
    //  engine = irrklang::createIrrKlangDevice();
    // engine->play2D("0998.wav",false);

    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
