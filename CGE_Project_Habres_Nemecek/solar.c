#include <stdlib.h> // for exit
#include "planet.h"

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
  glutWireSphere(2.5 * earthsize, 50, 50);

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

