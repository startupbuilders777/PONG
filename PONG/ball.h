#ifndef __BALL_H_INCLUDED__
#define __BALL_H_INCLUDED__
#include "GameObject.h"
#include "paddle.h"

class Ball : public GameObject {
public: 
	
	Ball(){
	initSrand = false;
	}

	Ball(GLfloat rad, GLfloat x, GLfloat y, GLfloat vx = 0, GLfloat vy = 0)
		: radius(rad)
	{
		currPosX = x;
		currPosY = y;
		startPosX = x;
		startPosY = y;
		setSpeed(vx, vy);
		setColor(0.0f, 0.0f, 0.0f, 0.0f);
		initSrand = false;
	}

	void draw() const;
	void move(); 
	void contactRight(const Paddle& z);
	void contactLeft(const Paddle& z);

	void setMaxAndMinRandSpeed(GLfloat, GLfloat);
	void setSpeed(GLfloat, GLfloat);
	void initBallSpeed(GLfloat, GLfloat);
	void setRadius(GLfloat rad) {radius = rad;}
	void setYRestrictions(GLfloat ymax, GLfloat ymin) { this->ymax = ymax, this->ymin = ymin; }
	void setLoseBounds(GLfloat left, GLfloat right) { this->xLoseLeft = left, this->xLoseRight = right;}
	void setPaddleSpeedHitFactor(double factor) { paddleHitSpeedFactor = factor; }
	char didRoundEnd();
	void resetBallPos();

	GLfloat getRadius()  const { return radius ; }
	GLfloat getTopBoundY() const { return ymax; }
	GLfloat getBotBoundY() const { return ymin;}

	void pause();
	void unpause();

private:
	GLfloat radius;
	GLfloat savedSpeedX, savedSpeedY;
	GLfloat ymax, ymin;
	GLfloat xLoseLeft, xLoseRight;
	double paddleHitSpeedFactor;
	GLfloat initVelX, initVelY; 
	GLfloat speedRandMax, speedRandMin;

	bool initSrand;

	void paddleHitVelChange(GLfloat, GLfloat);
	void randomizeSpeedandPos();


};

#endif 

