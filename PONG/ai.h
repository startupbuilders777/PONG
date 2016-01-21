#ifndef AI_H
#define AI_H
#include "paddle.h"
#include "ball.h"


class AI {
public:
	AI():targetLocY(0.0f), initSrand(false){};

	AI(Paddle * paddle){
		pad = paddle; 
	}

	void setAIpaddle(Paddle * paddle){ pad = paddle;}
	
	void AIPaddleMove(const Ball&);

private:
	Paddle * pad; 
	GLfloat targetLocY;
	GLfloat hitLocation;
	bool initSrand;


	void calculateTargetLocation(const Ball&);
	GLfloat paddleHitLocation(const Ball&);
};

#endif
