#include "planet.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include "glext.h"

#define _CRT_SECURE_NO_WARNINGS
void planet(float dist, float size, float circTime, float dayLength, int day, int hour,int planetID)
{
	glPushMatrix();
	glRotatef(360.0*day / circTime, 0.0, 1.0, 0.0);
	glTranslatef(dist, 0.0, 0.0);

	glPushMatrix();
	// rotate the planet on its axis
	glRotatef(360.0*hour / dayLength, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.50, 0.50, 0.50);
	GLUquadricObj *qObj = gluNewQuadric();

	gluQuadricNormals(qObj, GLU_SMOOTH);
	gluQuadricTexture(qObj, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, planetID);    // texID is the texture ID of a

										// previously generated texture



	gluSphere(qObj, size, 50, 50);

	glDisable(GL_TEXTURE_2D);
	//glutSolidSphere(size, 30, 30);
	glPopMatrix();
	glPopMatrix();
}

void earth(int day, int hour, GLuint texture)
{


	glPushMatrix();
	// earth
	// position around the sun
	glRotatef(360.0*day / 365.0, 0.0, 1.0, 0.0);
	glTranslatef(4.0, 0.0, 0.0);

	glPushMatrix();
	// rotate the earth on its axis
	glRotatef(360.0*hour / 24.0, 0.0, 1.0, 0.0);
	//glColor3f(1.0, 1.0, 1.0);
	glScalef(0.50, 0.50, 0.50);
	GLUquadricObj *qObj = gluNewQuadric();

	gluQuadricNormals(qObj, GLU_SMOOTH);
	gluQuadricTexture(qObj, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,2);    



	gluSphere(qObj, 0.4f, 20, 20);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	// moon
	glRotatef(360.0 * 4 * day / 365.0, 0.0, 1.0, 0.0);
	glTranslatef(0.7f, 0.0f, 0.0f);

	GLUquadricObj *qObj2 = gluNewQuadric();

	gluQuadricNormals(qObj2, GLU_SMOOTH);
	gluQuadricTexture(qObj2, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 11);    



	gluSphere(qObj2, 0.1f, 10, 10);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

