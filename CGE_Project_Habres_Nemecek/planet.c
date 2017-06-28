#include "planet.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include "glext.h"

#define _CRT_SECURE_NO_WARNINGS
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
	glutSolidSphere(size, 30, 30);
	glPopMatrix();
	glPopMatrix();
}

void earth(int day, int hour, GLuint texture )
{
	GLUquadricObj *sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, 1);
	gluQuadricNormals(sphere, GLU_FLAT);
	//gluQuadricOrientation(sphere, GLU_OUTSIDE);
	//Making a display list
	int mysphereID;
	mysphereID = glGenLists(1);
	glNewList(mysphereID, GL_COMPILE);
	gluSphere(sphere, 0.4, 20, 20);
	glEndList();
	gluDeleteQuadric(sphere);
	glPushMatrix();
	// earth
	// position around the sun
	glRotatef(360.0*day / 365.0, 0.0, 1.0, 0.0);
	glTranslatef(4.0, 0.0, 0.0);

	glPushMatrix();
	// rotate the earth on its axis
	//glRotatef(360.0*hour / 24.0, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.50, 0.50, 0.50);
	glEnable(GL_TEXTURE_2D);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//gluQuadricTexture(sphere, 1);
	//gluSphere(sphere, 2, 20, 20);
	glCallList(mysphereID);

	/*GLUquadricObj *sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, 1);
	gluQuadricNormals(sphere, GLU_FLAT);
	gluSphere(sphere, 0.4, 20, 20);*/
	//glutSolidSphere(0.4, 20, 20);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	// moon
	glRotatef(360.0 * 4 * day / 365.0, 0.0, 1.0, 0.0);
	glTranslatef(0.7f, 0.0f, 0.0f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutSolidSphere(0.1f, 10, 10);

	glPopMatrix();
}

