#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif


static int width, height; // OpenGL window size.


static float R[1000], G[1000], B[1000]; // color array
static float Size[1000]; // size array

static int B1 = 0; // border tool box
static int B2 = 0; // border color box
static int B3 = 0; // border storke box
static int cbc1 = 5; // tool box counter
static int cbc2 = 8; // color box counter
static int cbc5 = 5; // storke box counter
static int FILL = 1; // fill color object
static int CircleMode = 1; // cicle mode
static int SS = 0; // bg color tool box
static int sstemp = 0; // screen saver temp
static int sstemp2 = 0; // screen saver temp

static int pointCount = 0; // Number of  specified points
static int tempX, tempY, tempX1, tempY1; // Co-ordinates of clicked point

float t = 0; // Angle parameter.


#define PI 3.14159265358979324


using namespace std;






// Point class
class Point
{
public:
	Point(int x, int y)
	{
		xVal = x; yVal = y;
		int ssSize = Size[B3] + 15;
		xValRand = x + rand() % ssSize; yValRand = y + rand() % ssSize;
		rColor = R[B2]; gColor = G[B2]; bColor = B[B2];
		lSize = Size[B3];
		lSS = SS;
	}
	void drawPoint(void);
private:
	int xVal, yVal;
	int xValRand, yValRand;
	float rColor, gColor, bColor;
	float lSize;
	int lSS;
};

void Point::drawPoint(void)
{
	glPointSize(lSize);
	glColor3f(rColor, gColor, bColor);
	glBegin(GL_POINTS);
	if (lSS == 0)
	glVertex3f(xVal, yVal, 0.0);
	if (lSS == 1) {
		for (int i = 0; i < 15; i++)
			glVertex3f(xValRand, yValRand, 0.0);
	}
	glEnd();
}

vector<Point> points;
vector<Point>::iterator pointsIterator;








// Line class
class Line
{
public:
	Line(int x1Val, int y1Val, int x2Val, int y2Val)
	{
		x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
		rColor = R[B2]; gColor = G[B2]; bColor = B[B2];
		lSize = Size[B3];
	}
	void drawLine();
private:
	int x1, y1, x2, y2;
	float rColor, gColor, bColor;
	float lSize;
};


void Line::drawLine()
{
	glLineWidth(lSize);
	glColor3f(rColor, gColor, bColor);
	glBegin(GL_LINES);
	glVertex3f(x1, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glEnd();
}

vector<Line> lines;
vector<Line>::iterator linesIterator;










// Rectangle class
class Rect
{
public:
	Rect(int x1Val, int y1Val, int x2Val, int y2Val)
	{
		x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
		rColor = R[B2]; gColor = G[B2]; bColor = B[B2];
		lSize = Size[B3];
		fill = FILL;
	}
	void drawRectangle();
private:
	int x1, y1, x2, y2;
	float rColor, gColor, bColor;
	float lSize;
	int fill;
};

void Rect::drawRectangle()
{
	glLineWidth(lSize);
	glColor3f(rColor, gColor, bColor);
	if (fill == 1)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(x1, y1, x2, y2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

vector<Rect> rectangles;
vector<Rect>::iterator rectanglesIterator;







// Circle class
class Circle
{
public:
	Circle(int x1Val, int y1Val, int x2Val, int y2Val)
	{
		x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
		rColor = R[B2]; gColor = G[B2]; bColor = B[B2];
		lSize = Size[B3];
		RR = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));

		CM = CircleMode;
	}
	void drawCircle();
private:
	int x1, y1, x2, y2;
	float rColor, gColor, bColor;
	float lSize;
	int RR;
	int CM;
};


void Circle::drawCircle()
{
	glLineWidth(lSize);
	glColor3f(rColor, gColor, bColor);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 500; ++i)
	{
		if(CM == 1)
			glVertex3f(x1 + RR * cos(t), y1 + RR * sin(t), 0.0);
		else
			glVertex3f(x1 + ((x2 - x1)*1.4) * cos(t), y1 + ((y2 - y1)*1.4) * sin(t), 0.0);
		t += 2 * PI / 500;
	}
	glEnd();
}

vector<Circle> circles;
vector<Circle>::iterator circlesIterator;






// Poly class
class Poly
{
public:
	Poly(int x1Val, int y1Val, int x2Val, int y2Val, int x3Val, int y3Val)
	{
		x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val; x3 = x3Val; y3 = y3Val;
		rColor = R[B2]; gColor = G[B2]; bColor = B[B2];
		lSize = Size[B3];
		fill = FILL;
	}
	void drawPoly();
private:
	int x1, y1, x2, y2, x3, y3;
	float rColor, gColor, bColor;
	float lSize;
	int fill;
};


void Poly::drawPoly()
{
	glLineWidth(lSize);
	glColor3f(rColor, gColor, bColor);
	if (fill == 1)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(x1, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glVertex3f(x3, y3, 0.0);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

vector<Poly> polys;
vector<Poly>::iterator polysIterator;









void writeBitmapString(void *font, char *string)
{
	char *c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void writeStrokeString(void *font, char *string)
{
	char *c;
	for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}









void drawScene(void)
{
   glClear(GL_COLOR_BUFFER_BIT);





   pointsIterator = points.begin();
   while (pointsIterator != points.end())
   {
	   pointsIterator->drawPoint();
	   pointsIterator++;
   }



   linesIterator = lines.begin();
   while (linesIterator != lines.end())
   {
	   linesIterator->drawLine();
	   linesIterator++;
   }



   rectanglesIterator = rectangles.begin();
   while (rectanglesIterator != rectangles.end())
   {
	   rectanglesIterator->drawRectangle();
	   rectanglesIterator++;
   }



   circlesIterator = circles.begin();
   while (circlesIterator != circles.end())
   {
	   circlesIterator->drawCircle();
	   circlesIterator++;
   }



   polysIterator = polys.begin();
   while (polysIterator != polys.end())
   {
	   polysIterator->drawPoly();
	   polysIterator++;
   }



   // BG tool box & color box
   glColor3f(0.90, 0.90, 0.90);
   glBegin(GL_POLYGON);
   glVertex3f(0.0, 0.0, 0.0);
   glVertex3f(1000.0, 0.0, 0.0);
   glVertex3f(1000.0, 60.0, 0.0);
   glVertex3f(100.0, 60.0, 0.0);
   glVertex3f(100.0, 600.0, 0.0);
   glVertex3f(0.0, 600.0, 0.0);
   glEnd();




   // BOX color in tool box
   glColor3f(0.95, 0.95, 0.95);
   glBegin(GL_POLYGON);
   glVertex3f(10.0, 590.0, 0.0);
   glVertex3f(90.0, 590.0, 0.0);
   glVertex3f(90.0, 510.0, 0.0);
   glVertex3f(10.0, 510.0, 0.0);
   glEnd();
   glBegin(GL_POLYGON);
   glVertex3f(10.0, 500.0, 0.0);
   glVertex3f(90.0, 500.0, 0.0);
   glVertex3f(90.0, 420.0, 0.0);
   glVertex3f(10.0, 420.0, 0.0);
   glEnd();
   glBegin(GL_POLYGON);
   glVertex3f(10.0, 410.0, 0.0);
   glVertex3f(90.0, 410.0, 0.0);
   glVertex3f(90.0, 330.0, 0.0);
   glVertex3f(10.0, 330.0, 0.0);
   glEnd();
   glBegin(GL_POLYGON);
   glVertex3f(10.0, 320.0, 0.0);
   glVertex3f(90.0, 320.0, 0.0);
   glVertex3f(90.0, 240.0, 0.0);
   glVertex3f(10.0, 240.0, 0.0);
   glEnd();
   glBegin(GL_POLYGON);
   glVertex3f(10.0, 230.0, 0.0);
   glVertex3f(90.0, 230.0, 0.0);
   glVertex3f(90.0, 150.0, 0.0);
   glVertex3f(10.0, 150.0, 0.0);
   glEnd();
   glBegin(GL_POLYGON);
   glColor3f(0.95, 0.95, 0.95);
   if (FILL == 1)
   glColor3f(0.8, 0.8, 0.8);
   glVertex3f(10.0, 140.0, 0.0);
   glVertex3f(45.0, 140.0, 0.0);
   glVertex3f(45.0, 105.0, 0.0);
   glVertex3f(10.0, 105.0, 0.0);
   glEnd();
   glBegin(GL_POLYGON);
   glColor3f(0.95, 0.95, 0.95);
   if (FILL == 0)
   glColor3f(0.8, 0.8, 0.8);
   glVertex3f(55.0, 140.0, 0.0);
   glVertex3f(90.0, 140.0, 0.0);
   glVertex3f(90.0, 105.0, 0.0);
   glVertex3f(55.0, 105.0, 0.0);
   glEnd();
   glColor3f(0.95, 0.95, 0.95);
   glBegin(GL_POLYGON);
   if (SS == 1)
   glColor3f(0.8, 0.8, 0.8);
   glVertex3f(10.0, 95.0, 0.0);
   glVertex3f(45.0, 95.0, 0.0);
   glVertex3f(45.0, 60.0, 0.0);
   glVertex3f(10.0, 60.0, 0.0);
   glEnd();
   glColor3f(0.95, 0.95, 0.95);
   glBegin(GL_POLYGON);
   if (CircleMode == 0)
   glColor3f(0.8, 0.8, 0.8);
   glVertex3f(55.0, 95.0, 0.0);
   glVertex3f(90.0, 95.0, 0.0);
   glVertex3f(90.0, 60.0, 0.0);
   glVertex3f(55.0, 60.0, 0.0);
   glEnd();




   glPointSize(4);
   glColor3f(0.15, 0.15, 0.15);
   glBegin(GL_POINTS);
   glVertex3f(50.0, 550.0, 0.0);
   glEnd();
   glLineWidth(2);
   glBegin(GL_LINES);
   glVertex3f(75.0, 485.0, 0.0);
   glVertex3f(25.0, 435.0, 0.0);
   glEnd();
   glLineWidth(2);
   glBegin(GL_LINE_LOOP);
   glVertex3f(25.0, 395.0, 0.0);
   glVertex3f(75.0, 395.0, 0.0);
   glVertex3f(75.0, 345.0, 0.0);
   glVertex3f(25.0, 345.0, 0.0);
   glEnd();

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glLineWidth(1);
   glColor3f(0.0, 0.0, 0.0);
   glRectf(20, 130, 35, 115);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(65, 130, 80, 115);
   glPointSize(2);
   glBegin(GL_POINTS);
   glVertex3f(17, 75, 0.0);
   glVertex3f(23, 69, 0.0);
   glVertex3f(29, 80, 0.0);
   glVertex3f(35, 88, 0.0);
   glVertex3f(36, 66, 0.0);
   glVertex3f(29, 73, 0.0);
   glVertex3f(35, 75, 0.0);
   glVertex3f(20, 80, 0.0);
   glEnd();

   glLineWidth(2);
   glBegin(GL_LINE_LOOP);
   for (int i = 0; i < 500; ++i)
   {
	   glVertex3f(50 + 25 * cos(t), 280 + 25 * sin(t), 0.0);
	   t += 2 * PI / 500;
   }
   glEnd();


   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
   glVertex3f(50.0, 215.0, 0.0);
   glVertex3f(25.0, 165.0, 0.0);
   glVertex3f(75.0, 165.0, 0.0);
   glEnd();
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);






   // border tool box
   glColor3f(0.5, 0.5, 0.5);
   glLineWidth(2);
   glBegin(GL_LINE_LOOP);
   glVertex3f(10.0 - 4, 590.0 - B1 + 4, 0.0);
   glVertex3f(90.0 + 4, 590.0 - B1 + 4, 0.0);
   glVertex3f(90.0 + 4, 510.0 - B1 - 4, 0.0);
   glVertex3f(10.0 - 4, 510.0 - B1 - 4, 0.0);
   glEnd();





   // BOX color in color box
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_POLYGON);
   glVertex3f(150.0, 50.0, 0.0);
   glVertex3f(110.0, 50.0, 0.0);
   glVertex3f(110.0, 10.0, 0.0);
   glVertex3f(150.0, 10.0, 0.0);
   glEnd();
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
   glVertex3f(200.0, 50.0, 0.0);
   glVertex3f(160.0, 50.0, 0.0);
   glVertex3f(160.0, 10.0, 0.0);
   glVertex3f(200.0, 10.0, 0.0);
   glEnd();
   glColor3f(0.0, 0.0, 1.0);
   glBegin(GL_POLYGON);
   glVertex3f(250.0, 50.0, 0.0);
   glVertex3f(210.0, 50.0, 0.0);
   glVertex3f(210.0, 10.0, 0.0);
   glVertex3f(250.0, 10.0, 0.0);
   glEnd();
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
   glVertex3f(300.0, 50.0, 0.0);
   glVertex3f(260.0, 50.0, 0.0);
   glVertex3f(260.0, 10.0, 0.0);
   glVertex3f(300.0, 10.0, 0.0);
   glEnd();
   glColor3f(0.0, 1.0, 1.0);
   glBegin(GL_POLYGON);
   glVertex3f(350.0, 50.0, 0.0);
   glVertex3f(310.0, 50.0, 0.0);
   glVertex3f(310.0, 10.0, 0.0);
   glVertex3f(350.0, 10.0, 0.0);
   glEnd();
   glColor3f(1.0, 0.0, 1.0);
   glBegin(GL_POLYGON);
   glVertex3f(400.0, 50.0, 0.0);
   glVertex3f(360.0, 50.0, 0.0);
   glVertex3f(360.0, 10.0, 0.0);
   glVertex3f(400.0, 10.0, 0.0);
   glEnd();
   glColor3f(0.0, 0.0, 0.0);
   glBegin(GL_POLYGON);
   glVertex3f(450.0, 50.0, 0.0);
   glVertex3f(410.0, 50.0, 0.0);
   glVertex3f(410.0, 10.0, 0.0);
   glVertex3f(450.0, 10.0, 0.0);
   glEnd();
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_POLYGON);
   glVertex3f(500.0, 50.0, 0.0);
   glVertex3f(460.0, 50.0, 0.0);
   glVertex3f(460.0, 10.0, 0.0);
   glVertex3f(500.0, 10.0, 0.0);
   glEnd();



   // border tool box
   glColor3f(0.5, 0.5, 0.5);
   glLineWidth(2);
   glBegin(GL_LINE_LOOP);
   glVertex3f(150.0 + B2 + 3, 50.0 + 3, 0.0);
   glVertex3f(110.0 + B2 - 3, 50.0 + 3, 0.0);
   glVertex3f(110.0 + B2 - 3, 10.0 - 3, 0.0);
   glVertex3f(150.0 + B2 + 3, 10.0 - 3, 0.0);
   glEnd();







   glColor3f(0.6, 0.6, 0.6);
   glLineWidth(2);
   glBegin(GL_LINES);
   glVertex3f(550.0, 50.0, 0.0);
   glVertex3f(550.0, 10.0, 0.0);
   glEnd();
   glColor3f(0.6, 0.6, 0.6);
   glLineWidth(4);
   glBegin(GL_LINES);
   glVertex3f(570.0, 50.0, 0.0);
   glVertex3f(570.0, 10.0, 0.0);
   glEnd();
   glColor3f(0.6, 0.6, 0.6);
   glLineWidth(6);
   glBegin(GL_LINES);
   glVertex3f(590.0, 50.0, 0.0);
   glVertex3f(590.0, 10.0, 0.0);
   glEnd();
   glColor3f(0.6, 0.6, 0.6);
   glLineWidth(8);
   glBegin(GL_LINES);
   glVertex3f(610.0, 50.0, 0.0);
   glVertex3f(610.0, 10.0, 0.0);
   glEnd();
   glColor3f(0.6, 0.6, 0.6);
   glLineWidth(10);
   glBegin(GL_LINES);
   glVertex3f(630.0, 50.0, 0.0);
   glVertex3f(630.0, 10.0, 0.0);
   glEnd();



   // border storke box
   glColor3f(0.0, 0.0, 0.0);
   glLineWidth(Size[B3]);
   glBegin(GL_LINES);
   glVertex3f(550.0 + B3, 50.0, 0.0);
   glVertex3f(550.0 + B3, 10.0, 0.0);
   glEnd();





   glRasterPos3f(59.0, 80.0, 0.0);
   writeBitmapString(GLUT_BITMAP_HELVETICA_10, "Circle");
   glRasterPos3f(59.0, 67.0, 0.0);
   writeBitmapString(GLUT_BITMAP_HELVETICA_10, "Mode");


   glRasterPos3f(12.0, 12.0, 0.0);
   writeBitmapString(GLUT_BITMAP_HELVETICA_10, "PAINT (graphic)");
   glRasterPos3f(830.0, 12.0, 0.0);
   writeBitmapString(GLUT_BITMAP_HELVETICA_10, "Powered by OmidHa & Morteza ");


   glRasterPos3f(700.0, 26.0, 0.0);
   writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Clear");

   glRasterPos3f(640.0, 26.0, 0.0);
   writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+");
   glRasterPos3f(530.0, 26.0, 0.0);
   writeBitmapString(GLUT_BITMAP_HELVETICA_18, "-");







   glFlush(); 
}







void clearAll(void)
{
	points.clear();
	lines.clear();
	rectangles.clear();
	circles.clear();
	polys.clear();

	B1 = 0;
	B2 = 0;
	B3 = 0;
	FILL = 1;
	SS = 0;
}





void main_menu(int id)
{
	if (id == 1) clearAll();
	if (id == 2) exit(0);

	glutPostRedisplay();
}

// The sub-menu callback function.
void storke_menu(int id)
{
	if (id == 3)
	{
		if (B3 >= 0 && B3 < (cbc5 * 20) - 20)
			B3 += 20;
	}
	if (id == 4)
	{
		if (B3 >= 20 && B3 < (cbc5 * 20))
			B3 -= 20;
	}
	
	glutPostRedisplay();
}


void makeMenu(void)
{
	int sub_menu;
	sub_menu = glutCreateMenu(storke_menu);
	glutAddMenuEntry("Storke +", 3);
	glutAddMenuEntry("Storke -", 4);

	glutCreateMenu(main_menu);
	glutAddSubMenu("Storke", sub_menu);
	glutAddMenuEntry("Clear", 1);
	glutAddMenuEntry("Quit", 2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}










void setup(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0); 

   R[0] = 1.0; G[0] = 0.0; B[0] = 0.0;
   R[50] = 0.0; G[50] = 1.0; B[50] = 0.0;
   R[100] = 0.0; G[100] = 0.0; B[100] = 1.0;
   R[150] = 1.0; G[150] = 1.0; B[150] = 0.0;
   R[200] = 0.0; G[200] = 1.0; B[200] = 1.0;
   R[250] = 1.0; G[250] = 0.0; B[250] = 1.0;
   R[300] = 0.0; G[300] = 0.0; B[300] = 0.0;
   R[350] = 1.0; G[350] = 1.0; B[350] = 1.0;

   Size[0] = 2.0;
   Size[20] = 4.0;
   Size[40] = 6.0;
   Size[60] = 8.0;
   Size[80] = 10.0;

   makeMenu();
}





void resize(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

   width = w;
   height = h;

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}




void mouseControl(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		if (B1 == 0 && x > 100 && y < 540)
			points.push_back(Point(x, height - y));

		if (B1 == 90 && x > 100 && y < 540) {
			if (pointCount == 0)
			{
				tempX = x; tempY = height - y;
				pointCount++;
			}
			else
			{
				lines.push_back(Line(tempX, tempY, x, height - y));
				pointCount = 0;
			}
		}

		if (B1 == 180 && x > 100 && y < 540) {
			if (pointCount == 0)
			{
				tempX = x; tempY = height - y;
				pointCount++;
			}
			else
			{
				rectangles.push_back(Rect(tempX, tempY, x, height - y));
				pointCount = 0;
			}
		}

		if (B1 == 270 && x > 100 && y < 540) {
			if (pointCount == 0)
			{
				tempX = x; tempY = height - y;
				pointCount++;
			}
			else
			{
				circles.push_back(Circle(tempX, tempY, x, height - y));
				pointCount = 0;
			}
		}

		if (B1 == 360 && x > 100 && y < 540) {
			if (pointCount == 0)
			{
				tempX = x; tempY = height - y;
				pointCount++;
				cout << "1\n";
			}
			else if (pointCount == 1)
			{
				tempX1 = x; tempY1 = height - y;
				pointCount++;
			}
			else if (pointCount == 2)
			{
				polys.push_back(Poly(tempX, tempY, tempX1, tempY1, x, height - y));
				pointCount = 0;
			}
		}

		if (x > 690 && x < 740 && y > 550 && y < 585) {
			clearAll();
			glutPostRedisplay();
		}

		if (x > 10 && x < 45 && y > 460 && y < 495) {
			FILL = 1;
			glutPostRedisplay();
		}

		if (x > 55 && x < 90 && y > 460 && y < 495) {
			FILL = 0;
			glutPostRedisplay();
		}

		if (x > 10 && x < 90 && y > 10 && y < 90) {
			B1 = 0;
			glutPostRedisplay();
		}

		if (x > 10 && x < 90 && y > 100 && y < 180) {
			B1 = 90;
			glutPostRedisplay();
		}

		if (x > 10 && x < 90 && y > 190 && y < 270) {
			B1 = 180;
			glutPostRedisplay();
		}

		if (x > 10 && x < 90 && y > 280 && y < 360) {
			B1 = 270;
			glutPostRedisplay();
		}

		if (x > 10 && x < 90 && y > 370 && y < 450) {
			B1 = 360;
			glutPostRedisplay();
		}

		if (x > 110 && x < 150 && y > 550 && y < 590) {
			B2 = 0;
			glutPostRedisplay();
		}

		if (x > 160 && x < 200 && y > 550 && y < 590) {
			B2 = 50;
			glutPostRedisplay();
		}

		if (x > 210 && x < 250 && y > 550 && y < 590) {
			B2 = 100;
			glutPostRedisplay();
		}

		if (x > 260 && x < 300 && y > 550 && y < 590) {
			B2 = 150;
			glutPostRedisplay();
		}

		if (x > 310 && x < 350 && y > 550 && y < 590) {
			B2 = 200;
			glutPostRedisplay();
		}

		if (x > 360 && x < 400 && y > 550 && y < 590) {
			B2 = 250;
			glutPostRedisplay();
		}

		if (x > 410 && x < 450 && y > 550 && y < 590) {
			B2 = 300;
			glutPostRedisplay();
		}

		if (x > 460 && x < 500 && y > 550 && y < 590) {
			B2 = 350;
			glutPostRedisplay();
		}

		if (x > 630 && x < 660 && y > 550 && y < 590) {
			if (B3 >= 0 && B3 < (cbc5 * 20) - 20)
				B3 += 20;
			glutPostRedisplay();
		}

		if (x > 520 && x < 550 && y > 550 && y < 590) {
			if (B3 >= 20 && B3 < (cbc5 * 20))
				B3 -= 20;
			glutPostRedisplay();
		}

		if (x > 10 && x < 45 && y > 505 && y < 540) {
			if (sstemp == 0) {
				SS = 1;
				B1 = 0;
				sstemp++;
			}
			else {
				SS = 0;
				sstemp--;
			}
			glutPostRedisplay();
		}

		if (x > 55 && x < 90 && y > 505 && y < 540) {
			if (sstemp2 == 0) {
				CircleMode = 0;
				B1 = 270;
				sstemp2++;
			}
			else {
				CircleMode = 1;
				sstemp2--;
			}
			glutPostRedisplay();
		}

	}

}









void mouseMotion(int x, int y)
{
	if (SS == 1 && B1 == 0 && x > 100 && y < 540)
		points.push_back(Point(x, height - y));

	glutPostRedisplay();
}











void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
	  case '2':
		  if (B1 >= 0 && B1 < (cbc1 * 90) - 90)
			  B1 += 90;
		  glutPostRedisplay();
		  break;
	  case '8':
		  if (B1 >= 90 && B1 < (cbc1 * 90))
			  B1 -= 90;
		  glutPostRedisplay();
		  break;
	  case '6':
		  if (B2 >= 0 && B2 < (cbc2 * 50) - 50)
			  B2 += 50; cout << B2;
		  glutPostRedisplay();
		  break;
	  case '4':
		  if (B2 >= 50 && B2 < (cbc2 * 50))
			  B2 -= 50; cout << B2;
		  glutPostRedisplay();
		  break;
	  case '+':
		  if (B3 >= 0 && B3 < (cbc5 * 20) - 20)
			  B3 += 20;
		  glutPostRedisplay();
		  break;
	  case '-':
		  if (B3 >= 20 && B3 < (cbc5 * 20))
			  B3 -= 20;
		  glutPostRedisplay();
		  break;
	  case '0':
		  clearAll();
		  glutPostRedisplay();
		  break;


      case 27:
         exit(0);
         break;
      default:
         break;
   }
}




int main(int argc, char **argv) 
{
   glutInit(&argc, argv);

   glutInitContextVersion(4, 3);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
   glutInitWindowSize(1000, 600);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("square.cpp");
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutMouseFunc(mouseControl);
   glutMotionFunc(mouseMotion);

   glewExperimental = GL_TRUE;
   glewInit();

   setup(); 
   
   glutMainLoop(); 
}