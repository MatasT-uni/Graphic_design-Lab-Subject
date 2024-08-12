#include <windows.h>
#include <math.h>
#include <gl/glut.h>

GLint screenWidth = 640; GLint screenHeight = 480; // width and height of the window
GLfloat r=1,g=1,b=1;
void myInit(void)
{
glClearColor(1.0,1.0,1.0,0.0); // background color is white
glColor3f(1.0, 0.0, 0.0); // drawing color is blac
glPointSize(2.0); // a 'dot' is 2 by 2 pixels
glMatrixMode(GL_PROJECTION); // set some other parameters
glLoadIdentity(); // set some other parameters
gluOrtho2D(1,1.0,1,1.2); // set the coordinates
glClear (GL_COLOR_BUFFER_BIT);//clear the screen
glClearColor(r,g,b,0.0); //set up an RGB background color
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClearColor(r,g,b,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);

    for(double t = 0; t < 10.0; t += 0.005)
    {
        GLdouble    funcx = sin(2*t);
        GLdouble    funcy = sin(3*t);
        glVertex2d(funcx,funcy);
    }
//your code here (L9)
glEnd();
glFlush(); // send all output to display
}
int main(int argc, char** argv)
{ glutInit(&argc, argv); // initialize the toolkit
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
glutInitWindowSize(screenWidth, screenHeight); // set window size
glutInitWindowPosition(100, 150); // set window position on screen
glutCreateWindow("Dot Plot of a Function"); // open the screen window
glutDisplayFunc(myDisplay); // register the redraw function
myInit();
glutMainLoop();
return 0;
}
