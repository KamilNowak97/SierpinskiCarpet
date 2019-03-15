
#include "pch.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

GLint level = 3;
GLfloat degree_of_deformation = 20;
GLfloat width = 120;

void draw_Carpet(GLfloat x, GLfloat y, GLfloat width, GLint level)
{
	if (level > 0)
	{
		width = width / 3;

		//Górna warstwa dywanu
		draw_Carpet(x, y, width, level - 1);
		draw_Carpet(x - width, y, width, level - 1);
		draw_Carpet(x - 2 * width, y, width, level - 1);

		//Œrodkowa warstwa dywanu, bez œrodkowego kwadratu
		draw_Carpet(x, y - width, width, level - 1);
		draw_Carpet(x - 2 * width, y - width, width, level - 1);

		//Dolna warstwa dywanu
		draw_Carpet(x, y - 2 * width, width, level - 1);
		draw_Carpet(x - width, y - 2 * width, width, level - 1);
		draw_Carpet(x - 2 * width, y - 2 * width, width, level - 1);
	}
	else
	{
		GLfloat deformation = (rand() % 75 + 14)*degree_of_deformation / 846;
		glBegin(GL_POLYGON);

		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
		glVertex2f(x + deformation, y + deformation);

		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
		glVertex2f(x + deformation - width, y + deformation);

		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
		glVertex2f(x + deformation - width, y + deformation - width);

		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
		glVertex2f(x + deformation, y + deformation - width);

		glEnd();
	}
}
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0f, 0.5f, 1.0f);
	draw_Carpet(50, 50, width, level);
	glFlush();
}

void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	GLfloat AspectRatio;
	if (vertical == 0)
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	if (horizontal <= vertical)
		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);  
	glLoadIdentity();
}
void main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Dywan Sierpiñskiego");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	MyInit();
	glutMainLoop();
}