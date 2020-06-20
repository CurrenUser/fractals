#pragma once
#include "fractals.h"

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGTH);
	glutCreateWindow("Draw cube");
	Initialization();
	Menu();
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(ResizeWindow);
	glutMainLoop();
}