#include <windows.h>
#include <GL/glut.h>
#include <time.h>
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
float angle=0.0,dangle=1; //the rotation angle and increment
void Time_Delay(int dur) {
clock_t start_time;
start_time = clock();
while ((clock() - start_time) < dur) {
}
}
void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0); // set white background color
    glColor3f(0.0, 0.0, 0.0); // set the drawing color
    glMatrixMode(GL_PROJECTION); //set some additional parameters
    glLoadIdentity();
    gluOrtho2D(-300, 300.0, -300, 300.0);//set your coordinate system
    glMatrixMode(GL_MODELVIEW); //set some additional parameters
    glLoadIdentity();
    angle=0.0;
}
//<<<<<<<<<<<<<<<<<<<<<<<< my routines >>>>>>>>>>>>>>>>>
void Draw_Origin()
{
glPointSize(7.0);
glColor3f(0.0, 0.0, 0.0); //the origin, big, red point
glBegin(GL_POINTS);
glVertex2i(0,0);
glEnd();}
void Rotate_Rect( )
{
glColor3f(0.0, 1.0, 0.0); // rectangle drawing color green
glPushMatrix();
glRotatef(angle, 0.0, 0.0, 1.0);// Set angle-deg. rotation about the z axis.
glRecti(-50, -50, 50, 50); // Display green rectangle.
angle+=dangle;
glPopMatrix();
Draw_Origin();
Time_Delay(50);
glutSwapBuffers();
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void) {
glClear(GL_COLOR_BUFFER_BIT);
Rotate_Rect();
}
void Do_Nothing(void) {
}
void mouse(int button, int state, int x, int y)
{
switch (button) {

case GLUT_LEFT_BUTTON:
if (state == GLUT_DOWN)
glutIdleFunc(myDisplay);
break;
case GLUT_RIGHT_BUTTON:
if (state == GLUT_DOWN)
glutIdleFunc(Do_Nothing);
break;
default:
break;

}
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize (480, 480);
glutInitWindowPosition (100, 150);
glutCreateWindow ("problem 3");
glutDisplayFunc(myDisplay);
glutMouseFunc(mouse);
myInit();
glutMainLoop();
}
