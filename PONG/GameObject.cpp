#include "GameObject.h"

void GameObject::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha)
{
	color[0] = r;
	color[1] = g;
	color[2] = b; 
	color[3] = alpha;
}

void GameObject::setColor(GLfloat newColor[])
{	
		*color = *newColor;
		*(color + 1) = *(newColor + 1);
		*(color + 2) = *(newColor + 2);
		*(color + 3) = *(newColor + 3);	
}


void  GameObject::setStartPos(GLfloat x, GLfloat y) { startPosX = x, startPosY = y; }

void  GameObject::setCurrPos(GLfloat x, GLfloat y) { currPosX = x, currPosY = y; }