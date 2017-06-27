#include "planet.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void planet(float dist, float size, float circTime, float dayLength, int day, int hour)
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

void earth(int day, int hour)
{
	glPushMatrix();
	// earth
	// position around the sun
	glRotatef(360.0*day / 365.0, 0.0, 1.0, 0.0);
	glTranslatef(4.0, 0.0, 0.0);

	glPushMatrix();
	// rotate the earth on its axis
	glRotatef(360.0*hour / 24.0, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.50, 0.50, 0.50);
	glutWireSphere(0.4, 10, 10);
	glPopMatrix();

	// moon
	glRotatef(360.0 * 4 * day / 365.0, 0.0, 1.0, 0.0);
	glTranslatef(0.7f, 0.0f, 0.0f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutWireSphere(0.1f, 10, 10);

	glPopMatrix();
}