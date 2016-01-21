#ifndef __GAMEOBJECT_H_INCLUDED__
#define __GAMEOBJECT_H_INCLUDED__
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h

//abstract base class
class GameObject {
protected:
	GLfloat color[4];
	GLfloat velX, velY;
	GLfloat currPosX, currPosY;
	GLfloat startPosX, startPosY;

public:
	virtual void draw() const = 0;
	//virtual void move() const = 0;
	virtual void pause()  = 0;
	virtual void unpause() = 0;

	GLfloat getVelX() const { return velX; }
	GLfloat getVelY() const { return velY; }
	GLfloat getCurrX() const { return currPosX; }
	GLfloat getCurrY() const { return currPosY; }

	void setStartPos(GLfloat, GLfloat);
	void setCurrPos(GLfloat, GLfloat);
	void setColor(GLfloat, GLfloat, GLfloat, GLfloat);
	void setColor(GLfloat[]);


};

#endif 