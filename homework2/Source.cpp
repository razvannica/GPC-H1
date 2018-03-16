#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>



// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display1() {
	double xmax, ymax, xmin, ymin;
	double a = 1, b = 2;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t;

	// calculul valorilor maxime/minime ptr. x si y
	// aceste valori vor fi folosite ulterior la scalare
	xmax = a - b - 1;
	xmin = a + b + 1;
	ymax = ymin = 0;
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = a + b * cos(t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		x2 = a - b * cos(t);
		xmax = (xmax < x2) ? x2 : xmax;
		xmin = (xmin > x2) ? x2 : xmin;

		y1 = a * tan(t) + b * sin(t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;

		y2 = a * tan(t) - b * sin(t);
		ymax = (ymax < y2) ? y2 : ymax;
		ymin = (ymin > y2) ? y2 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x2, y2);
	}
	glEnd();
}

// graficul functiei
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$,
void Display2() {
	double pi = 4 * atan(1.0);
	double xmax = 8 * pi;
	double ymax = exp(1.1);
	double ratia = 0.05;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double x = 0; x < xmax; x += ratia) {
		double x1, y1;
		x1 = x / xmax;
		y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();
}

void Display3() {
	double xmin = 0, xmax = 100;
	double ymin = 100000, ymax = 0;
	double ratia = 0.05;
	for (double t = xmin; t <= xmax; t += ratia) {
		double y;
		if (t == 0)
			y = 1;
		else y = (fabs(t - round(t))) / t;
		if (y < ymin)
			ymin = y;
		if (y > ymax)
			ymax = y;
	}

	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (double t = xmin; t <= xmax; t += ratia) {
		double x, y;
		x = t / (xmax + 10);
		y = ((fabs(t - round(t))) / t) / (ymax + 0.1);
		glVertex2f(x, y);
	}
	glEnd();
}

void Display4() {
	double a = 0.3, b = 0.2;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double xmin = 100, xmax = -100;
	double ymin = 100, ymax = -100;
	for (double t = -pi + ratia; t < pi; t += ratia) {
		double x, y;
		x = 2 * (a * cos(t) + b) * cos(t);
		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;
		y = 2 * (a * cos(t) + b) * sin(t);
		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;
	}
	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (double t = -pi + ratia; t < pi; t += ratia) {
		double x, y;
		x = (2 * (a * cos(t) + b) * cos(t)) / (xmax + 0.1);
		y = (2 * (a * cos(t) + b) * sin(t));
		glVertex2f(x, y);
	}
	glEnd();
}

void Display5() {
	double xmax, ymax;
	double xmin, ymin;
	double pi = 4 * atan(1);
	double ratia = 0.01;
	double a = 0.2;
	double t;
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < -pi / 6; t += ratia) {
		double x;
		double y;

		if (t != -pi / 6) {
			x = (a / (4 * cos(t)*cos(t) - 3));
			y = ((a*tan(t)) / (4 * cos(t) * cos(t) - 3));
			glVertex2f(x, y);
		}
	}
	glEnd();

	glPolygonMode(GL_FRONT, GL_FILL);
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_TRIANGLES);
	for (t = -pi / 2 + ratia; t < -pi / 6; t += ratia) {
		double x;
		double y;
		x = a / (4 * pow(cos(t), 2) - 3);
		y = (a * tan(t)) / (4 * pow(cos(t), 2) - 3);

		glVertex2f(x, y);
		glVertex2f(-1, 1);
	}
	glEnd();
}

void Display6() {
	double a = 0.1, b = 0.2;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (double t = -9.5; t < 9.5; t += ratia) {
		double x, y;
		x = a * t - b * sin(t);
		y = a - b * cos(t);
		glVertex2f(x, y);
	}
	glEnd();
}

void Display7() {
	double R = 0.1, r = 0.3;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 2 * pi; t += ratia) {
		double x, y;
		x = (R + r) * cos(r / R * t) - r * cos(t + r / R * t);
		y = (R + r) * sin(r / R * t) - r * sin(t + r / R * t);
		glVertex2f(x, y);
	}
	glEnd();
}

void Display8() {
	double R = 0.1, r = 0.3;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 2 * pi; t += ratia) {
		double x, y;
		x = (R - r) * cos(r / R * t) - r * cos(t - r / R * t);
		y = (R - r) * sin(r / R * t) - r * sin(t - r / R * t);
		glVertex2f(x, y);
	}
	glEnd();
}

void Display9() {
	double a = 0.4;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (double t = -pi / 4; t < pi / 4; t += ratia) {
		double r, x, y;
		r = a * sqrt(2 * cos(2 * t));
		x = r * cos(t);
		y = r * sin(t);
		glVertex2f(x, y);
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (double t = -pi / 4; t < pi / 4; t += ratia) {
		double r, x, y;
		r = -a * sqrt(2 * cos(2 * t));
		x = r * cos(t);
		y = r * sin(t);
		glVertex2f(x, y);
	}
	glEnd();
}

void Display0() {
	double a = 0.02;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (double t = ratia; t < 10; t += ratia) {
		double r, x, y;
		r = a * exp(1 + t);
		x = r * cos(t);
		y = r * sin(t);
		glVertex2f(x, y);
	}
	glEnd();
}

void Init(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	//   glPointSize(4);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (prevKey) {
	case '1':
		Display1();
		break;
	case '2':
		Display2();
		break;
	case '3':
		Display3();
		break;
	case '4':
		Display4();
		break;
	case '5':
		Display5();
		break;
	case '6':
		Display6();
		break;
	case '7':
		Display7();
		break;
	case '8':
		Display8();
		break;
	case '9':
		Display9();
		break;
	case '0':
		Display0();
		break;
	default:
		break;
	}

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}
