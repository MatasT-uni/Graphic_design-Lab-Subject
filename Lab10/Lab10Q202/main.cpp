# include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#define Red 1
#define Green 2
#define Blue 3
#define Black 4
#define Stop 2
#define Resume 1
#define Small 1
#define Medium 2
#define Large 3
// Global variables
int windowWidth = 500; // Windowed mode's width
int windowHeight = 500; // Windowed mode's height
int windowPosX = 50; // Windowed mode's top-left corner x
int windowPosY = 50; // Windowed mode's top-left corner y

int red=0,green=0, blue=1;

GLfloat ballRadius = 0.5; // Radius of the bouncing ball
GLfloat xPos = 0.0; // Ball's (x, y) position
GLfloat yPos = 0.0;
GLfloat xPosMax, xPosMin, yPosMax, yPosMin; // Ball's (x, y) -limits
GLdouble xLeft=-1, xRight=1, yBottom=-1, yTop=1; // The box limits
GLfloat xSpeed = 0.02; // Ball's speed in x and y directions
GLfloat ySpeed = 0.007;
void output_Text(float x, float y, char *text) //output a text at x,y, z=0 DOWNLOADABLE
{ int len, i;
glColor3f(1, 0, 0); //red text
glRasterPos3f(x, y, 0);
len = (int)strlen(text);
for (i = 0; i < len; i++) {
glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
}
}
void output_Number(float x, float y, double v) //output a number at x,y
{ int len, i;
char text [20]={'\0'};
sprintf(text, "%lf", v); //converts v to the string "text"
output_Text(x,y,text);
}
//these functions are simplified versions of the text outputs from L12. Here we set z=0
void initGL() {
glClearColor(1.0, 1.0, 1.0, 1.0); // Set the clear color to white
glMatrixMode(GL_PROJECTION); // Select the Projection matrix
glLoadIdentity(); // Reset
gluOrtho2D(xLeft, xRight, yBottom, yTop);
xPosMin = xLeft + ballRadius;
xPosMax = xRight - ballRadius;
yPosMin = yBottom + ballRadius;
yPosMax = yTop - ballRadius;
glMatrixMode(GL_MODELVIEW); // Select the model-view matrix
glLoadIdentity(); // Reset
}
void Time_Delay(int dur) {
clock_t start_time;
start_time = clock();
while ((clock() - start_time) < dur) {
}
}
void display_Ball()
{
//output text
output_Text(xLeft+0.05,yBottom+0.1,"bouncing ball size=");
output_Number(xLeft+0.7,yBottom+0.1,ballRadius);
//set the position of the ball
glTranslatef(xPos, yPos, 0.0); // Translate to (xPos, yPos)
// Use triangular segments to draw the circle
glBegin(GL_TRIANGLE_FAN);
glColor3f(red, green, blue); // Blue
glVertex2f(0.0, 0.0); // Center of the circle
int numSegments = 100;
GLfloat angle;
for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
angle = i * 2.0 * M_PI / numSegments; // 360 deg for all segments
glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
}
}
//M_PI is a constant pi from math.h
void display() {
glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
glLoadIdentity(); // Reset model-view matrix
display_Ball();
glEnd();
glutSwapBuffers(); // Swap front and back buffers (of double buffered mode)
// Animation Control - compute the location for the next refresh
xPos += xSpeed;//increment x
yPos += ySpeed;//increment y
// Check if the ball exceeds the edges
if (xPos > xPosMax) {
xPos = xPosMax;
xSpeed = -xSpeed;
} else if (xPos < xPosMin) {
xPos = xPosMin;
xSpeed = -xSpeed;
}
if (yPos > yPosMax) {
yPos = yPosMax;
ySpeed = -ySpeed;
} else if (yPos < yPosMin) {
yPos = yPosMin;
ySpeed = -ySpeed;
}
Time_Delay(10);
}

void Menu_Color(int option)
{
switch (option) {
case Red : red = 1.0; green = 0.0; blue = 0.0; break;
case Green : red = 0.0; green = 1.0; blue = 0.0; break;
case Blue : red = 0.0; green = 0.0; blue = 1.0; break;
case Black : red = 0.0; green = 0.0; blue = 0.0; break;
default :break; }
}

void Menu_Size(int option)
{
switch (option) {
case Small : ballRadius = 0.1; break;
case Medium : ballRadius = 0.3; break;
case Large : ballRadius = 0.5; break;
default :break; }
xPosMin = xLeft + ballRadius;
xPosMax = xRight - ballRadius;
yPosMin = yBottom + ballRadius;
yPosMax = yTop - ballRadius;
}

void do_nothing()
{

}

void Stop_Resume(int option)
{
    switch(option){
    case Resume : glutIdleFunc(display); break;
    case Stop : glutIdleFunc(do_nothing); break;
    default : break;
    }
}

void createGLUTMenus() {
int submenu1 = glutCreateMenu(Menu_Color);
glutAddMenuEntry("Red",Red);
glutAddMenuEntry("Green",Green);
glutAddMenuEntry("Blue", Blue);
glutAddMenuEntry("Black", Black);
int submenu2 = glutCreateMenu(Menu_Size);
glutAddMenuEntry("Small",Small);
glutAddMenuEntry("Medium",Medium);
glutAddMenuEntry("Large ", Large);
int menu=glutCreateMenu(Stop_Resume);
glutAddSubMenu("Color",submenu1);
glutAddSubMenu("Size",submenu2);
glutAddMenuEntry("Stop",Stop);
glutAddMenuEntry("Resume",Resume);
glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
glutInit(&argc, argv); // Initialize GLUT
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); // Enable double buffered mode
glutInitWindowSize(windowWidth, windowHeight); // Initial window width and height
glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
glutCreateWindow("Problem 2");
glutDisplayFunc(display);
glutIdleFunc(display);
createGLUTMenus();
initGL(); // Our OpenGL initialization
glutMainLoop(); // The event-processing loop
return 0;
}
