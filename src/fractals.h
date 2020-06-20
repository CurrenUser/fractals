#pragma once
#include <GL/glut.h>
#include <iostream>
using namespace std;

static int WIDTH = 600, HEIGTH = 600;


// all function;
void Initialization(); // default parametrs Opengl;
void DrawScene(); // function for draw cube; 
void ResizeWindow(GLsizei width, GLsizei height); // Resize window;
void T_Cube(float x_main = 0, float y_main = 0, int cube_size = 400 , int iteration = 8); // Draw fractal T-Cube;
void CurveLevy(float x1, float x2, float y1 = 0, float y2 = 0, int iteration = 20); // Draw Curve Levy;
void Mandelbrot(int iteration = 600); // Draw fractal Mandelbrot;
void Tree(double x0, double y0, double a,double L, int n);
void SelectOrto(); // Set / cartesian coordinate system;
void Menu(); // Set menu options;
void MenuAction( int value); // User of actions;