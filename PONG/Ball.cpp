#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <Math.h>     // Needed for sin, cos
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

#define PI 3.14159265f

#include "ball.h"
#include <iostream>

void  Ball::draw() const {

	glPushMatrix();
	glTranslatef(currPosX, currPosY, 0.0f);  // Translate to (xPos, yPos)
	// Use triangular segments to form a circle
	glBegin(GL_TRIANGLE_FAN);
	glColor4fv(color);  // Blue
	glVertex2f(startPosX, startPosY);       // Center of circle
	int numSegments = 100;
	GLfloat angle;
	for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
		angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
		glVertex2f(cos(angle) * radius, sin(angle) * radius);
	}
	glEnd();
	glPopMatrix();
}


void  Ball::move() 
{
	if ((currPosY + radius >= ymax) || (currPosY - radius <= ymin))
		velY = -velY;
	currPosX += velX;
	currPosY += velY;
}

char Ball::didRoundEnd(){

	if (currPosX + radius >= xLoseRight){ //Right Side Won
		return 'R';
	}
	else if (currPosX - radius <= xLoseLeft){ //Left Side Won
		return 'L'; 
	}
	else
		return 'F'; //No one won or lost
}

void Ball::resetBallPos(){
	randomizeSpeedandPos();
}

void Ball::contactRight(const Paddle& z){

	if (currPosX + radius >= z.getContactSurfaceX() && (currPosY >= z.getCurrY()) && (currPosY <= z.getCurrY() + z.getLength())){
		GLfloat middleOfPaddleYCoord = z.getCurrY() + z.getLength()/ 2;
		paddleHitVelChange(middleOfPaddleYCoord, z.getLength());
	}
}

void Ball::contactLeft(const Paddle& z){

	if (currPosX - radius <= z.getContactSurfaceX() && (currPosY >= z.getCurrY()) && (currPosY <= z.getCurrY() + z.getLength())){
		GLfloat middleOfPaddleYCoord = z.getCurrY() + z.getLength()/ 2;
		
		paddleHitVelChange(middleOfPaddleYCoord, z.getLength());
		velX = -velX;
	}
	}

void Ball::setMaxAndMinRandSpeed(GLfloat max, GLfloat min)
{
	speedRandMax = max;
	speedRandMin = min;
}

void Ball::initBallSpeed(GLfloat max, GLfloat min)
{
	setMaxAndMinRandSpeed(max, min);
	randomizeSpeedandPos();
}



void Ball::randomizeSpeedandPos(){
	if (initSrand == false){
		srand(time(NULL));
		initSrand = true;
	}

	double num = (rand() % 1000) / (double)1000; //generates a number between 1 and 1000
	std::cout << num << std::endl;
	velX = num*(speedRandMax - speedRandMin) + speedRandMin;

	num = (rand() % 1000) / (double)1000; //generates a number between 1 and 1000
	std::cout << num << std::endl;
	std::cout << speedRandMin << "," << speedRandMax << std::endl;

	velY = num*(speedRandMax - speedRandMin) + speedRandMin;

	int randUpAndDownDirection = (rand() % 2);
	randUpAndDownDirection == 1 ? velX = -velX : velX = velX;

	currPosX = 0;
	int randTopOrBot = (rand() % 2);
	randTopOrBot == 1 ? currPosY = ymax - 4*radius : currPosY = ymin + 4*radius;
}

	void Ball::paddleHitVelChange(GLfloat midOfPaddleYCoord, GLfloat paddleLength){

		GLfloat velTot = pow(pow(velX, 2) + pow(velY, 2), 0.5);

	//	if (currPosY <= (midOfPaddleYCoord + paddleLength / 4) && currPosY >= (midOfPaddleYCoord - paddleLength / 4)){
		
	//		if (velX > initVelX || velY > initVelY)	
	//			velTot /= paddleHitSpeedFactor;
		

		velY = (abs(currPosY - midOfPaddleYCoord) / (paddleLength / 2)) * velTot;
		velX = -pow(pow(velTot, 2) - pow(velY, 2), 0.5f);
	//	}
	//	else
//	{
//			velTot = velTot * (abs(currPosY - midOfPaddleYCoord) / (paddleLength / 2)) * paddleHitSpeedFactor;
//		if (abs(currPosY - midOfPaddleYCoord) / (paddleLength / 2) >= 0.80)
//		velY = 0.8 * velTot;
//		else
//			velY = (abs(currPosY - midOfPaddleYCoord) / (paddleLength / 2)) * velTot;

//		velX = -pow(pow(velTot, 2) - pow(velY, 2), 0.5f);
//		}
	}




void  Ball::setSpeed(GLfloat vx, GLfloat vy) { velX = vx, velY = vy; initVelX = vx, initVelY = vy; }



void Ball::pause(){
	savedSpeedX = velX;
	savedSpeedY = velY;
	velX = 0;
	velY = 0;
}

void Ball::unpause(){
	velX = savedSpeedX;
	velY = savedSpeedY;
}




