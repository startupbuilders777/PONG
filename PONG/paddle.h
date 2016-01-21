#ifndef __PADDLE_H_INCLUDED__
#define __PADDLE_H_INCLUDED__
#include "GameObject.h"

class Paddle : public GameObject
{
public:
	Paddle() : length(0), width(0){
		startPosX = 0;
		startPosY = 0;
		currPosX = 0;
		currPosY = 0;
		velY = 0;
		maxSpeed = 0;
		velX = 0;
		ymax = 0;
		ymin = 0;

	}

	Paddle(GLfloat len, GLfloat wid, GLfloat x, GLfloat y, GLfloat vy = 0)
		: length(len), width(wid) 
	{
		currPosX = x;
		currPosY = y;
		startPosX = x;
		startPosY = y;
		velY = vy;
		maxSpeed = vy;
		velX = 0;
		setColor(0.0f, 0.0f, 0.0f, 0.0f);
	}

	void  draw() const;
	void  moveUp();
	void  moveDown();
	void  move();
	void setSpeed(GLfloat);
	void setMaxSpeed(GLfloat);

	void  setWidth(GLfloat wid) {width = wid;}
	void  setLength(GLfloat len) { length = len; }
	void  setYRestrictions(GLfloat ymax, GLfloat ymin) { this->ymax = ymax, this->ymin = ymin;}
	void  setContactSurfaceX(GLfloat x) { contactSurfaceX = x;}

	GLfloat getWidth() const { return width; }
	GLfloat getLength ()  const { return length; }
	GLfloat getContactSurfaceX() const { return contactSurfaceX; }
	GLfloat getMaxSpeed() const { return maxSpeed; }
	void pause();
	void unpause();

private:
	GLfloat length;
	GLfloat width;
	GLfloat ymax, ymin;
	GLfloat contactSurfaceX;
	GLfloat savedSpeedY;
	GLfloat maxSpeed;
	
};

#endif
