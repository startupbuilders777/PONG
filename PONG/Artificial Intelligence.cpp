#include "ai.h"
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>


void AI::AIPaddleMove(const Ball& ball){
	calculateTargetLocation(ball);
	//if (targetLocY = 0)
		//pad->setCurrPos(0, 0);
	if (pad->getCurrY() < targetLocY){
		pad->moveUp();
		if (pad->getCurrY() > targetLocY)
			pad->setCurrPos(pad->getCurrX(), targetLocY);
	}
	else if (pad->getCurrY() > targetLocY){
		pad->moveDown();
		if (pad->getCurrY() < targetLocY)
			pad->setCurrPos(pad->getCurrX(), targetLocY);
	}
	else return;

}

GLfloat AI::paddleHitLocation(const Ball& ball){

	if (initSrand == false){
		srand(time(NULL));
		initSrand = true;
	}

	double randFrac = (rand() % 1000) / (double)1000; // random decimal number between 0 and 1
	std::cout << randFrac << ",";
	std::cout << randFrac*ball.getRadius() << std::endl;
	return randFrac*pad->getLength();

}

void AI::calculateTargetLocation(const Ball& ball) {

	GLfloat distanceX = abs(ball.getCurrX() - pad->getCurrX());
	double time = distanceX / ball.getVelX();
	GLfloat displacementY = time*ball.getVelY();

	if (pad->getCurrX() >= ball.getCurrX() && ball.getVelX() <= 0){
		targetLocY = 0.0f;
		hitLocation = paddleHitLocation(ball);
	}
	else if (pad->getCurrX() <= ball.getCurrX() && ball.getVelX() >= 0){
		targetLocY = 0.0f;
		hitLocation = paddleHitLocation(ball);
	}
	else if (displacementY >= ball.getTopBoundY() || displacementY <= ball.getBotBoundY()){
		targetLocY = 0.0f; //change this for better approximations
		hitLocation = paddleHitLocation(ball);
	}
	else {
		targetLocY = ball.getCurrY() - hitLocation;
		std::cout << "The hit location is " << hitLocation << " and " << ball.getCurrY() - hitLocation << std::endl;
	}

}