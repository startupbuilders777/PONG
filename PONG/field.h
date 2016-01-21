
#ifndef FIELD_H
#define FIELD_H



#include "ball.h"
#include "paddle.h"


class Field {
public:
	Field(){
	


	}
	
	void display();
	void keyboard();


private:
	Ball * ball;
	Paddle * leftPaddle;
	Paddle * rightPaddle;






};

#endif