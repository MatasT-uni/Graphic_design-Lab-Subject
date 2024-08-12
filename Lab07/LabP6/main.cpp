#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <cstdlib> //this is for randomization "rand"
#include <math.h> // math functions

const float Pi=3.14159265358979323846;
bool start = true;
GLint wx=500;
GLint wy=500;
GLfloat r, g, b;

//******************replace by a function to draw a Heptagon with a random color here***
void draw_Triangle(GLfloat cornerX, GLfloat cornerY, GLfloat size) {
glBegin(GL_POLYGON);
glColor3f(1,0,0); // Set the drawing color to red.
glVertex2f(cornerX, cornerY);
glVertex2f(cornerX+size, cornerY);
glVertex2f(cornerX+size/2, cornerY+size);
glEnd();
glFlush(); // Send to the screen
}

//Function for Heptagon picture//
void draw_Heptagon(GLfloat xc, GLfloat yc,GLfloat R) {
{
    GLfloat x, y;
    GLint i;
    GLfloat r, g, b;
    r = rand() %1000/1000.;
    g = rand() %1000/1000.;
    b = rand() %1000/1000.;
    glColor3f(r,g,b);
    glBegin(GL_POLYGON);
    for (i=0; i<=7; i++)
    {
        x=xc+R*cos(2*Pi*i/7);
        y=yc+R*sin(2*Pi*i/7);
        glVertex2f(x,y);
    }
    glEnd();
    glFlush();
}
}

void doNothing(void) {
if (start) {
start = false;
glClear(GL_COLOR_BUFFER_BIT); // Clear display window for the first time
}
glFlush();
}

void mouse(GLint button, GLint state, GLint x, GLint y) {
if (button ==GLUT_LEFT_BUTTON && state== GLUT_DOWN)
draw_Triangle(x, wy-y,30);// understand wy-y!

//********draw the Heptagon on the right mouse click here
if (button ==GLUT_RIGHT_BUTTON && state== GLUT_DOWN)
draw_Heptagon(x, wy-y,20);// understand wy-y!
}

// *******reshape function to adjust the view port and math coordinates here
void Reshape(int w, int h)
{
glMatrixMode(GL_PROJECTION);
glViewport(0, 0, w, h); //viewport matches the new window
glLoadIdentity();//identity matrix
gluOrtho2D(0.0, 1.0*w, 0.0, 1.0*h); //math coordinates to match the new window
r=rand()%1000/1000.;
g=rand()%1000/1000.;
b=rand()%1000/1000.; //change r,g,b randomly
glClearColor(r,g,b,0.0); //set up a new RGB background color
glClear (GL_COLOR_BUFFER_BIT);
}

void myInit(void) {
glClearColor(1, 1, 1, 0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity( );
gluOrtho2D(0.0, wx, 0.0, wy); // set the word coordinate system
}

int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition(50,50);
glutInitWindowSize (wx, wy);
glutCreateWindow("Ex_6");
myInit();
glutDisplayFunc(doNothing);

//**************callback Reshape
glutReshapeFunc(Reshape);
glutMouseFunc(mouse);
glutMainLoop();
}
