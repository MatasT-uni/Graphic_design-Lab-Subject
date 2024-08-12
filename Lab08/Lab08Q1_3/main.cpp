#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
int menu1;
double angle=0;
bool origin=false;
void Time_Delay(int dur) {
clock_t start_time;
start_time = clock();
while ((clock() - start_time) < dur) {
}
}
float ax[3]={25,0,0}; float ay[3]={0,25,0}; float az[3]={0,0,25};//axes
void plot_Arrow(float v1[3], float v2[3]) //plot arrow
{
glBegin(GL_LINES);
glVertex3fv(v1);
glVertex3fv(v2);
glEnd();
}
void plot_Vector(float v[3]) //plot vector
{
float zero[3]={0,0,0};
plot_Arrow(zero,v);
}
void plot_Axis()
{
glColor3f(0,0,0);
plot_Vector(ax);
plot_Vector(ay);
plot_Vector(az);
}
void output_Text(float x, float y, char *text) //output a text at x,y
{
int len, i;
glColor3f(1, 0, 0); //red text
glRasterPos3f(x, y, 0);
len = (int)strlen(text);
for (i = 0; i < len; i++) {
glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
}
}
void output_Number(float x, float y, double v) //output a number at x,y
{
int len, i;
char text [20]={'\0'};
sprintf(text, "%lf", v); //converts v to the string
output_Text(x,y,text);
}
void myInit2d(void)
{
glClearColor(1.0,1.0,1.0,0.0); // set white background color
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0, 0.0, 0.0); // set the drawing color red
glMatrixMode(GL_PROJECTION);
glLoadIdentity(); // reset the projection matrix
gluOrtho2D(-50.0, 50.0, -50.0, 50.0);//set the math coordinates
//the coordinate system and window may be different
glMatrixMode(GL_MODELVIEW); //will be explained later
glLoadIdentity();//reset the modelview matrix to be explained
}
void myInit3d(void)
{
glClearColor(1,1,1,0);
glColor3f(1.0, 0.0, 0.0); // set the drawing color red
glClear(GL_COLOR_BUFFER_BIT); // clear the screen
glMatrixMode(GL_PROJECTION);
glLoadIdentity(); // reset the projection matrix
gluPerspective(45, 1.33, .01, 1000);
//the coordinate system, the window and glLookAt in this assignment
//can be different
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(30.0, 30.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//reset the modelview matrix to be explained
}
void draw_Origin()
{
glColor3f(1,0,1);
glPointSize(20);
glBegin(GL_POINTS);
glVertex3f(0,0,0);
glEnd();
}
void draw_triangle()
{
    glBegin(GL_TRIANGLES);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f( 0.0f, 15.0f, 0.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(20.0f,25.0f, 0.0f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 0.0f,25.0f, 15.0f);
	glEnd();
}
void myDisplay(void)
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//implement this part to draw objects..
glColor3f(1.0, 0.0, 0.0); // the drawing color red
glRecti(10,10,20,20);//draw a red rectangle
glPushMatrix();
glRotated(angle,1,0,0);
glColor3f(0.9, 0.9, 0.9);
glutSolidTeapot(15.0); //draw the teapot
glColor3f(0.0, 0.0, 1.0); //the drawing color blue
glutWireTeapot(15.0); //draw the teapot on the top as the wireframe
glPopMatrix();
angle++;
draw_triangle();
if (origin) draw_Origin();
plot_Axis();// coordinate axes
output_Text(-30,-60,"Right click for the menu...");
//will be introduced later
glutSwapBuffers();
Time_Delay(50);
}
void doNothing(void)
{
}
// implement this reshape callback if needed...
void myReshape (int w, int h)
{
}
// implement this mouse callback if needed...
void myMouse(int button, int state, int x, int y)
{

}
// implement this keyboard callback if needed...
void myKeyboard(unsigned char key, int x, int y)
{
}
// implement this motion callback if needed...
void myMotion(int x, int y)//will be explained later
{
}
void Menu_1(int option)//will be explained later
{
origin=option;
}
void createGLUTMenus() {
int menu = glutCreateMenu(Menu_1);
glutAddMenuEntry("Menu option 1",0);
glutAddMenuEntry("Menu option 2",1);
glutAttachMenu(GLUT_RIGHT_BUTTON);
} //will be explained later
int main(int argc, char **argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize (500, 500);
glutInitWindowPosition (100, 100);
glutCreateWindow ("Template 1.1");
/* Use myInit2d() or myInit3d() for initialization */
//myInit2d();
myInit3d();
glutDisplayFunc(myDisplay);
glutReshapeFunc(myReshape);
glutIdleFunc(myDisplay);
glutMouseFunc(myMouse);
glutKeyboardFunc(myKeyboard);
glutMotionFunc(myMotion);
createGLUTMenus();//will be explained later
glutMainLoop();
}
