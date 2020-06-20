#include "fractals.h"

bool t_cube = false, curve_Levy = false, mandelbrot = false, tree = false;
double xB, yB, b = 0.21; int r = 6, n = 8;

void Initialization()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Main fon collor;
	glPointSize(1.0f);
}

void ResizeWindow(GLsizei width, GLsizei height)
{
	WIDTH = width / 2; // Ortho x;
	HEIGTH = height / 2; // Orto y;

	cout << "Current Window Size is:" << width << "|" << height << endl;
	cout << "Ortho x is:" << -WIDTH << "|" << WIDTH << " y is:" << -HEIGTH << "|" << HEIGTH << endl;
	glViewport(0,0,width,height); // Wiew window;
	SelectOrto();
}

void Menu()
{
	int newMenu = glutCreateMenu(MenuAction);
	glutSetMenu(newMenu);
	glutAddMenuEntry("Create T-Cube Fractal",1);
	glutAddMenuEntry("Create Curve Levy", 2);
	glutAddMenuEntry("Create Fractal Mandelbrot", 3);
	glutAddMenuEntry("Create Tree", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void MenuAction(int value)
{
	switch (value)
	{
	case 1:
		t_cube = t_cube ? false : true; 
		curve_Levy = false;
		mandelbrot = false;
		tree = false;
		cout << "create fractal T cube" << endl;
		glutPostRedisplay();
	break;
	case 2:
		curve_Levy = curve_Levy ? false : true;
		t_cube = false;
		mandelbrot = false;
		tree = false;
		cout << "create Curve Levy" << endl;
		glutPostRedisplay();
		break;
	case 3:
		mandelbrot = mandelbrot ? false : true;
		t_cube = false;
		curve_Levy = false;
		tree = false;
		cout << "create Fractal Mandelbrot" << endl;
		glutPostRedisplay();
		break;
	case 4:
		tree = tree ? false : true;
		t_cube = false;
		curve_Levy = false;
		mandelbrot = false;
		cout << "create Treet" << endl;
		glutPostRedisplay();
		break;
	}
}

void SelectOrto()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (mandelbrot)
		gluOrtho2D(-2, 0.8f, -1.0f, 1.0f);
	else
		gluOrtho2D(-WIDTH, WIDTH, -HEIGTH, HEIGTH); // Cartesian coordinate system (default -400x400); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void DrawScene()
{
	SelectOrto();
	glClear(GL_COLOR_BUFFER_BIT);
	if (t_cube)
	{
		glBegin(GL_QUADS);
		glColor3ub(100, 100, 100);
		T_Cube(0,0,WIDTH);
		glEnd();
	}
	else if (curve_Levy)
	{
		glBegin(GL_LINES);
		glColor3ub(100, 100, 100);
		CurveLevy(-(float)WIDTH / 2.0f, (float)WIDTH / 2.0f);
		glEnd();
	}
	else if (mandelbrot)
	{
		glBegin(GL_POINTS);
		glColor3ub(0, 0, 0);
		Mandelbrot(100);
		glEnd();
	}
	if (tree) 
	{
		glColor3d(0.0, 1.0, 0.0);
		glLineWidth(2.0);
		glBegin(GL_LINES);
		glVertex2d(0.0, -1.0);
		glVertex2d(0.0, -0.1);
		Tree(0.0, 0.0, 0.65, WIDTH / 4 + 30.0f, 10);
		glVertex2d(0.0, 0.0);
		glVertex2d(0.0, -HEIGTH);
		glEnd();
	}

	glutSwapBuffers();
}

void T_Cube(float x_main, float y_main, int cube_size, int iteration)
{
	//cube_size /= 2;
	float x1 = x_main - (cube_size / 2) , x2 = x_main + (cube_size / 2); // Create x for cubes;
	float y1 = y_main - (cube_size / 2),  y2 = y_main + (cube_size / 2); // Create y for cubes; 

	glVertex2f(x1, y1); glVertex2f(x1, y2); glVertex2f(x2, y2); glVertex2f(x2, y1); // Draw cube;

	if (iteration) // is iter true;
	{
		iteration--; 
		cube_size /= 2; // new cube size;

		// Draw four cubes at end points (x,y);
		T_Cube( x1, y1, cube_size, iteration);
		T_Cube( x1, y2, cube_size, iteration);
		T_Cube( x2, y2, cube_size, iteration);
		T_Cube( x2, y1, cube_size, iteration);
	}

}

void CurveLevy(float x1, float x2, float y1, float y2, int iteration)
{
	if (iteration == 0)
	{
		// main line;
		glVertex2f(x1, y1); glVertex2f(x2, y2);
	}
	else
	{
		iteration--;
		float x_new = ( (x1 + x2)  - (y2 - y1) ) / 2;
		float y_new =  ( (y1 + y2)  + (x2 - x1) ) / 2;
		CurveLevy(x1, x_new, y1, y_new, iteration);
		CurveLevy(x_new, x2, y_new, y2, iteration);
	}
}

void Mandelbrot(int iteration)
{

	double x = 0.0, y = 0.0;
	double temp_x, temp_y;


	for (double x1 = -2.0f; x1 < 0.8f; x1 += 0.002) 	// flat passage;
	{
		for (double y1 = -1.0f; y1 < 1.0f; y1 += 0.002) 	// flat passage;
		{
			x = x1; y = y1;
			int current_iterator = 0;;
			while (current_iterator < iteration && (x * x  +  y * y) < 4) 
			{
			temp_x = x * x - y * y + x1;
			temp_y = 2 * x * y + y1;
			x = temp_x; 
			y = temp_y;
			current_iterator++;
			}
			if (current_iterator == iteration) // point goes to many;
				glVertex2f(x1, y1);
		}
	}
}

void Tree(double x0, double y0, double a,double L, int n)
{
	for (int i = 0; i <= 2 * r; i += r)
	{
		xB = x0 + cos(a + i * b) * L;
		yB = y0 + sin(a + i * b) * L;
		glVertex2d(x0, y0);
		glVertex2d(xB, yB);
		if (n > 0) Tree(xB, yB, a + (i - 1) * b, L / 2, n - 1);
	}
}