#ifndef SHAPES_H_INCLUDED
#define SheadingTextHAPES_H_INCLUDED
class Shapes{

     public :
          void drawTriangleShape(GLint x1,GLint y1,GLint x2,GLint y2,GLint x3,GLint y3);
          void text(char s[],float x,float y,float z);
          void headingText(char s[],float x,float y,float z,float sx,float sy,float sz);
          void drawCircle(float x, float y, float radius) ;
          void drawLine(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2);
          void drawMxPlayer();
          void bgComputer();
          void drawWord();
          void drawCalculator();
          void drawChrome();
          void drawSegment2(float cx,float cy,float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float radius1,float radius2,double angle1,double angle2,double angle3,double angle4);
          void drawSegment3(float cx,float cy,float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float radius1,float radius2,double angle1,double angle2,double angle3,double angle4);
          void drawSegment(float cx,float cy,float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float radius1,float radius2,double angle1,double angle2,double angle3,double angle4);
          void drawCircle2(float x, float y, float radius);
          void drawSemiCircle(float x, float y, float radius,float rotateangle,float x1,float y1,float z1) ;
           void Torus2d( float inner, float outer, unsigned int pts );
           void home();
};


#endif // SHAPES_H_INCLUDED
