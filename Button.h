#ifndef BUTTON
#define BUTTON
#include <GL/gl.h>
#include<iostream>
using namespace std;
class Button{

public:
  	float btnx1,btny1,btnx2,btny2;
	int btnstate;
	char btnstr[10];

public:	
Button();
	Button(float x1,float y1,float x2,float y2,char* str1);
    void draw();
	void togglestate();
	int insidebutton(float x,float y,float x1,float x2,float y1,float y2);
};
#endif