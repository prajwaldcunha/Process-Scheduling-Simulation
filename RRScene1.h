#ifndef RRSCENE1
#define RRSCENE1
#include <GL/gl.h>
class RRScene1 {

private:	
GLfloat radius = 0.8f;
GLfloat xx = 0.0f;
GLfloat xx1 = 0.0f;
GLfloat xx2 = 0.0f;
GLfloat xx3 = 0.0f;
GLfloat xx4 = 0.0f;
GLfloat xx5 = 0.0f;
GLfloat xx6 = 0.0f;
GLfloat xx7 = 0.0f;
GLfloat yy = -1.0f;
GLfloat yy1 = -1.0f;
GLfloat yy2 = -1.0f;
GLfloat yy3 = -1.0f;
GLfloat yy4 = -1.0f;
GLfloat yy5 = -1.0f;
GLfloat yy6 = -1.0f;
GLfloat yy7 = -1.0f;
GLfloat XMax, XMin, YMax=0.3, YMin; //  center (x, y) bounds
GLfloat xSpeed = 0.00f;      // speed in x and y directions
GLfloat ySpeed = 0.007f;

public:	
    void dispRR1();


};
#endif