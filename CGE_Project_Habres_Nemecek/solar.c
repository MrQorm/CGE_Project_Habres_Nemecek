#include <stdlib.h> // for exit
#include "planet.h"
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#ifndef M_PI
#define M_PI 3.141592653
#endif

#define RAD(x) (((x)*M_PI)/180.)

int window; 

float hour = 0.0;
float day = 0.0;
float earthsize = 0.4;
float earthdist = 4.0;
float inc = 1.00;
float longestYear = 60148.0; //in earth days
float longestDay = 243 * 24; //in hours

int begin_x = 0;
int begin_y = 0;
GLfloat angle_x = 0.0;
GLfloat angle_y = 0.0;

GLfloat pos_x = 0.0;
GLfloat pos_y = 0.0;
GLfloat pos_z = 0.0;

int moving = 0;

void resize(int width, int height)
{
  // prevent division by zero
  if (height == 0) { height=1; }

  glViewport(0, 0, width, height);  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, (float)width/(float)height, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
}

void keyPressed(unsigned char key, int x, int y) 
{
	switch (key) 
	{
		case 27:
			glutDestroyWindow(window); 
			exit(0);
			break;
		case 'i':
			angle_x -= 1.0;
			break;
		case 'j':
			angle_y -= 1.0;
			break;
		case 'k':
			angle_x += 1.0;
			break;
		case 'l':
			angle_y += 1.0;
			break;
		case 'w':
			pos_x += -sinf(RAD(angle_y)) * 0.5;
			pos_y += sinf(RAD(angle_x)) * 0.5;
			pos_z += cosf(RAD(angle_y)) * 0.5;
			break;
		case 'a':
			angle_y -= 90;
			pos_x += -sinf(RAD(angle_y)) * 0.5;
			pos_y += sinf(RAD(angle_x)) * 0.5;
			pos_z += cosf(RAD(angle_y)) * 0.5;
			angle_y += 90;
			break;
		case 's':
			pos_x += sinf(RAD(angle_y)) * 0.5;
			pos_y += -sinf(RAD(angle_x)) * 0.5;
			pos_z += -cosf(RAD(angle_y)) * 0.5;
			break;
		case 'd':
			angle_y += 90;
			pos_x += -sinf(RAD(angle_y)) * 0.5;
			pos_y += sinf(RAD(angle_x)) * 0.5;
			pos_z += cosf(RAD(angle_y)) * 0.5;
			angle_y -= 90;
			break;
	}
	if (angle_x > 360.0) angle_x -= 360.0;
	else if (angle_x < -360.0) angle_x += 360.0;
	if (angle_y > 360.0) angle_y -= 360.0;
	else if (angle_y < -360.0) angle_y += 360.0;
}

static void specialKeyPressed(int key, int x, int y)
{
  switch (key) {
  case GLUT_KEY_UP:
    inc *= 1.5;
    break;
  case GLUT_KEY_DOWN:
    inc *= 0.75;
    break;
  }
}

void setMaterial(GLfloat spec[], GLfloat diff[], GLfloat shine[])
{
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}

void setLights()
{
	GLfloat light_position[] = { 0.0, 0.0, -50.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	gluLookAt(-sinf(RAD(angle_y)), sinf(RAD(angle_x)), cosf(RAD(angle_y)),
		0., 0., 0.,
		0., 1., 0.);

	glTranslatef(pos_x, pos_y, pos_z);

	glPushMatrix();

	setLights();

	hour += inc;
	day += inc/24.0;
	/*hour = hour - ((int)(hour/24))*24;
	day = day - ((int)(day/365))*365;*/
	hour = hour - ((int)(hour / longestDay)) * 24;
	day = day - ((int)(day / longestYear)) * 365;

	glTranslatef (0.0, 0.0, -50.0);

	glRotatef(360*day/365.0, 0.0, 1.0, 0.0);

	// ecliptic
	glRotatef(15.0, 1.0, 0.0, 0.0);

	// sun
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 0.0);
	glutWireSphere(2.5 * earthsize, 50, 50);
	glEnable(GL_LIGHTING);

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 100.0 };
	setMaterial(mat_specular, mat_diffuse, mat_shininess);

	//Merkur
	planet(0.3*earthdist, 0.38*earthsize, 88.0, 58.0 * 24.0, day, hour);
	//Venus
	planet(0.6*earthdist, 0.95*earthsize, 225.0, 243.0 * 24.0, day, hour);
	//Erde
	earth(day, hour);
	//Mars
	planet(1.5*earthdist, 0.53*earthsize, 687.0, 24.0, day, hour);
	//Jupiter
	planet(3.0*earthdist, 2.0*earthsize, 4329.0, 10.0, day, hour);
	//Saturn
	planet(4.0*earthdist, 2.0*earthsize, 10751.0, 10.0, day, hour);
	//Uranus
	planet(5.0*earthdist, 1.5*earthsize, 30664.0, 17.0, day, hour);
	//Neptun
	planet(6.0*earthdist, 1.5*earthsize, 60148.0, 15.0, day, hour);

	glPopMatrix();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
	switch (button) 
	{
		case GLUT_LEFT_BUTTON:    /* spin scene around */
			if (state == GLUT_DOWN) 
			{
				moving = 1;
				begin_x = x;
				begin_y = y;

			}
			else if (state == GLUT_UP) 
			{
				moving = 0;
			}
			break;

		default:
			break;
	}

	glutPostRedisplay();
}

void mouseMotion(int x, int y) {

	//if (moving) 
	//{ /* mouse button is pressed */

	//	/* calculate new modelview matrix values */
	//	angle_y = angle_y + (x - begin_x);
	//	angle_x = angle_x + (y - begin_y);
	//	if (angle_x > 360.0) angle_x -= 360.0;
	//	else if (angle_x < -360.0) angle_x += 360.0;
	//	if (angle_y > 360.0) angle_y -= 360.0;
	//	else if (angle_y < -360.0) angle_y += 360.0;

	//	begin_x = x;
	//	begin_y = y;
	//	glutPostRedisplay();
	//}
}


void init(int width, int height)  
{
	setLights();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	resize(width, height);
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60.0, &timer, 1);
}



int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(0, 0);
  window = glutCreateWindow("foo");
  glutDisplayFunc(&display);
  
  glutTimerFunc(1000 / 60.0, &timer, 1);

  glutReshapeFunc(&resize);
  glutKeyboardFunc(&keyPressed);
  glutSpecialFunc(&specialKeyPressed);
  
  init(640, 480);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  glutMainLoop();
  return 0;
}

