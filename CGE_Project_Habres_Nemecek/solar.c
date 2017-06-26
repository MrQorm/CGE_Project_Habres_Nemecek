#include <stdlib.h> // for exit

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

int window; 

float hour = 0.0;
float day = 0.0;
float earthsize = 0.4;
float earthdist = 4.0;
float inc = 1.00;
float longestYear = 60148.0; //in earth days
float longestDay = 243 * 24; //in hours

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
  switch (key) {
  case 27:
    glutDestroyWindow(window); 
    exit(0);
    break;
  }
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

void planet(float dist, float size, float circTime, float dayLength)
{
	glPushMatrix();
	glRotatef(360.0*day / circTime, 0.0, 1.0, 0.0);
	glTranslatef(dist, 0.0, 0.0);

	glPushMatrix();
	// rotate the planet on its axis
	glRotatef(360.0*hour / dayLength, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.50, 0.50, 0.50);
	glutWireSphere(size, 10, 10);
	glPopMatrix();
	glPopMatrix();
}

void earth()
{
	glPushMatrix();
	// earth
	// position around the sun
	glRotatef(360.0*day / 365.0, 0.0, 1.0, 0.0);
	glTranslatef(earthdist, 0.0, 0.0);

	glPushMatrix();
	// rotate the earth on its axis
	glRotatef(360.0*hour / 24.0, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.50, 0.50, 0.50);
	glutWireSphere(earthsize, 10, 10);
	glPopMatrix();

	// moon
	glRotatef(360.0 * 4 * day / 365.0, 0.0, 1.0, 0.0);
	glTranslatef(0.7f, 0.0f, 0.0f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutWireSphere(0.1f, 10, 10);

	glPopMatrix();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

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
  glColor3f(1.0, 1.0, 0.0);
  glutWireSphere(1.0, 50, 50);

  //Merkur
  planet(0.3*earthdist, 0.38*earthsize, 88.0, 58.0 * 24.0);
  //Venus
  planet(0.6*earthdist, 0.95*earthsize, 225.0, 243.0 * 24.0);
  //Erde
  earth();
  //Mars
  planet(1.5*earthdist, 0.53*earthsize, 687.0, 24.0);
  //Jupiter
  planet(3.0*earthdist, 2.0*earthsize, 4329.0, 10.0);
  //Saturn
  planet(4.0*earthdist, 2.0*earthsize, 10751.0, 10.0);
  //Uranus
  planet(6.0*earthdist, 1.5*earthsize, 30664.0, 17.0);
  //Neptun
  planet(7.0*earthdist, 1.5*earthsize, 60148.0, 15.0);

  glutSwapBuffers();
}

void init(int width, int height)  
{
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
  glutMainLoop();
  return 0;
}

