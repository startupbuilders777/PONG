/*
* PONG
*/

#include <windows.h>  // for MS Windows
// #include <GLee.h>         // No need to link to GL/gl.h
#include <GL/glfw.h>      // Include OpenGL Framework library
#include <GL/freeglut.h>  // Include FreeGLUT so we can easily draw spheres 
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <Math.h>     // Needed for sin, cos
#include <iostream>
#include "ai.h"
#include "ball.h"
#include "paddle.h"

#define PI 3.14159265f

// Global variables

char title[] = "PONG";  // Windowed mode's title
int windowWidth = 640;     // Windowed mode's width
int windowHeight = 480;     // Windowed mode's height
int windowPosX = 50;      // Windowed mode's top-left corner x
int windowPosY = 50;      // Windowed mode's top-left corner y



Ball ball(0.03f,0.0f,0.0f);
Paddle paddleLeft;
Paddle paddleRight;
AI ai(&paddleLeft);
//AI ai2(&paddleRight);

int refreshMillis = 10;      // Refresh period in milliseconds

// Projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

bool fullScreenMode = true; // Full-screen or windowed mode?
bool paused = false;         // Movement paused or resumed
bool init = false;

int scoreLeft;
int scoreRight;

/* Initialize OpenGL Graphics */
void initGL() {
	    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
	    
	   GLfloat colorPaddle[4] = { 1.0f, 0.0f, 0.0f, 0.5f };

	    scoreLeft = 0;
	    scoreRight = 0;
	    ball.initBallSpeed(0.03, 0.0125);
		ball.setColor(1.0f, 1.0f, 0.0f, 0.0f);
		ball.setPaddleSpeedHitFactor(2.0);
	    paddleRight.setColor(colorPaddle);
	    paddleLeft.setColor(colorPaddle);
		paddleRight.setLength(0.3f);
		paddleRight.setWidth (0.1f);
		paddleLeft.setLength(0.3f);
	    paddleLeft.setWidth(0.1f);
		paddleRight.setSpeed(0.00f);
		paddleRight.setMaxSpeed(0.02f);
	    paddleLeft.setSpeed(0.02f);
		paddleLeft.setMaxSpeed(0.01f);
		paddleLeft.setStartPos(0, 0);
		paddleRight.setStartPos(0, 0);
}

void adjustPaddleAndBallCoordinates(){
	paddleLeft.setCurrPos(clipAreaXLeft + 0.2f, 0);
	paddleLeft.setYRestrictions(clipAreaYTop, clipAreaYBottom);
	paddleRight.setCurrPos(clipAreaXRight - 0.2f - paddleRight.getWidth(), 0);
	paddleRight.setYRestrictions(clipAreaYTop, clipAreaYBottom);
	paddleLeft.setContactSurfaceX(paddleLeft.getCurrX() + paddleLeft.getWidth());
	paddleRight.setContactSurfaceX(paddleRight.getCurrX());
	ball.setYRestrictions(clipAreaYTop, clipAreaYBottom);
	ball.setLoseBounds(paddleLeft.getCurrX(), paddleRight.getCurrX() + paddleRight.getWidth());
}

void field(){ // More Graphics




}

/* Callback handler for window re-paint event */
void display() {
	glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
	glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
	glLoadIdentity();              // Reset model-view matrix
	paddleRight.move();
	ball.draw();
	paddleRight.draw();
	paddleLeft.draw();

	glutSwapBuffers();  // Swap front and back buffers (of double buffered mode)

	// Animation Control - compute the location for the next refresh
 	ball.contactLeft(paddleLeft);
	ball.contactRight(paddleRight);
	ball.move();
	ai.AIPaddleMove(ball);
	//ai2.AIPaddleMove(ball);
	if (ball.didRoundEnd() == 'R'){
		++scoreRight;
		ball.resetBallPos();
	}
	else if (ball.didRoundEnd() == 'L'){
		++scoreLeft;
		ball.resetBallPos();
	}
	else
		return;


}


/* Call back when the windows is re-sized */
void reshape(GLsizei width, GLsizei height) {
	// Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix
	if (width >= height) {
		clipAreaXLeft = -1.0 * aspect;
		clipAreaXRight = 1.0 * aspect;
		clipAreaYBottom = -1.0;
		clipAreaYTop = 1.0;
	}
	else {
		clipAreaXLeft = -1.0;
		clipAreaXRight = 1.0;
		clipAreaYBottom = -1.0 / aspect;
		clipAreaYTop = 1.0 / aspect;
	}

	gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
	adjustPaddleAndBallCoordinates();
}

/* Called back when the timer expired */
void Timer(int value) {
	glutPostRedisplay();    // Post a paint request to activate display()
	glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}


/*
We can register callback functions to handle keyboard inputs for normal and special keys, respectively.

glutKeyboardFunc: registers callback handler for keyboard event.

void glutKeyboardFunc (void (*func)(unsigned char key, int x, int y)
// key is the char pressed, e.g., 'a' or 27 for ESC
// (x, y) is the mouse location in Windows' coordinates

glutSpecialFunc: registers callback handler for special key (such as arrow keys and function keys).

void glutSpecialFunc (void (*func)(int specialKey, int x, int y)
// specialKey: GLUT_KEY_* (* for LEFT, RIGHT, UP, DOWN, HOME, END, PAGE_UP, PAGE_DOWN, F1,...F12).
// (x, y) is the mouse location in Windows' coordinates

Similarly, we can register callback function to handle mouse-click and mouse-motion.
glutMouseFunc: registers callback handler for mouse click.
void glutMouseFunc(void (*func)(int button, int state, int x, int y)
// (x, y) is the mouse-click location.
// button: GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, GLUT_MIDDLE_BUTTON
// state: GLUT_UP, GLUT_DOWN
glutMotionFunc: registers callback handler for mouse motion (when the mouse is clicked and moved).
void glutMotionFunc(void (*func)(int x, int y)
// where (x, y) is the mouse location in Window's coordinates


mouse(int button, int state, int x, int y)
{

if ((button == GLUT_LEFT_BUTTON ) && (state == GLUT_DOWN))
{
Do something when the left button is pressed!
called only on state change.
}

if ((button == GLUT_LEFT_BUTTON ) && (state == GLUT_UP))
{
Do something when the left button is released.
}
Hope this helps

*/

/* Callback handler for mouse event */
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { // Pause/resume
		paused = !paused;         // Toggle state
		if (paused) {
			ball.pause();
			paddleLeft.pause();
			paddleRight.pause();
		}
		else {
			ball.unpause();
			paddleLeft.unpause();
			paddleRight.unpause();
		}
	}
}


/* Callback handler for normal-key event */
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:     // ESC key
		exit(0);
		break;
	}
}


/* Callback handler for special-key event */
void specialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:    // F1: Toggle between full-screen and windowed mode
		fullScreenMode = !fullScreenMode;         // Toggle state
		if (fullScreenMode) {                     // Full-screen mode
			windowPosX = glutGet(GLUT_WINDOW_X); // Save parameters for restoring later
			windowPosY = glutGet(GLUT_WINDOW_Y);
			windowWidth = glutGet(GLUT_WINDOW_WIDTH);
			windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
			glutFullScreen();                      // Switch into full screen
		}
		else {                                         // Windowed mode
			glutReshapeWindow(windowWidth, windowHeight); // Switch into windowed mode
			glutPositionWindow(windowPosX, windowPosX);   // Position top-left corner
		}
		break;
	case GLUT_KEY_UP:       // Up: increase y speed
		paddleRight.setSpeed(paddleRight.getMaxSpeed());
		break;
	case GLUT_KEY_DOWN:     // Down: decrease y speed
		paddleRight.setSpeed(-paddleRight.getMaxSpeed()); 
		break;
	}
}

void specialKeysUp(int key, int x, int y){
	if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN)
		paddleRight.setSpeed(0);
	}



/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
	glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
	glutCreateWindow(title);      // Create window with given title
	glutDisplayFunc(display);     // Register callback handler for window re-paint
	glutReshapeFunc(reshape);     // Register callback handler for window re-shape
	glutTimerFunc(0, Timer, 0);   // First timer call immediately
	glutSpecialFunc(specialKeys); // Register callback handler for special-key event
	glutSpecialUpFunc(specialKeysUp);
	glutKeyboardFunc(keyboard);   // Register callback handler for NORMAL key event
	glutFullScreen();             // Put into full screen
	glutMouseFunc(mouse);   // Register callback handler for mouse event
	initGL();                     // Our own OpenGL initialization
	glutMainLoop();               // Enter event-processing loop
	return 0;
}