#include "paddle.h"
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <Math.h>     // Needed for sin, cos
#define PI 3.14159265f

void  Paddle::draw() const {

	glPushMatrix();
	glTranslatef(currPosX, currPosY, 0);
	glBegin(GL_QUADS);
	glColor4fv(color);
	glVertex2f(startPosX, startPosY);
	glVertex2f(startPosX + width, startPosY);
	glVertex2f(startPosX + width, startPosY + length);
	glVertex2f(startPosX, startPosY + length);
	glEnd();
	glPopMatrix();
}

void Paddle::move(){

	if (currPosY + length > ymax)
		currPosY = ymax - length;
	else if (currPosY < ymin)
		currPosY = ymin;
	else
		currPosY += velY;
}

void  Paddle::moveUp()
{
	if (currPosY + length >= ymax)
		currPosY = ymax - length;
	else 
		currPosY += velY;
}

void Paddle::moveDown()
{
	if (currPosY <= ymin)
		currPosY = ymin;
	else 
	    currPosY -= velY;
}
void Paddle::setMaxSpeed(GLfloat vy){ maxSpeed = vy; }

void  Paddle::setSpeed(GLfloat vy) { velY = vy; }

void Paddle::pause(){
	savedSpeedY = velY;
	velY = 0;
}

void Paddle::unpause(){
	velY = savedSpeedY;
}








