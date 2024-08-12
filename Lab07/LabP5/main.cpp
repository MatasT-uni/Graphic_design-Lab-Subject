#include <windows.h>
#include <GL/glut.h>
#include <cstdlib> //this is for randomization "rand"
#include <math.h> // math functions
const float Pi=3.14159265358979323846;//you can also use M_PI from math.h
GLint wx = 800, wy = 800;//initial size of the window
GLfloat r, g, b;
void MyInit(void)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0,wx,0.0,wy); // math coordinate system matches the window
glPointSize(4.0);
}

//***************************Replace this procedure***************************
void draw_Polygon(GLfloat xc, GLfloat yc,GLint N,GLfloat R) //draw the triangle
{
    GLfloat x, y;
    GLint i;
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    for (i=0; i<=N; i++)
    {
        x=xc+R*cos(2*Pi*i/N);
        y=yc+R*sin(2*Pi*i/N);
        glVertex2f(x,y);
    }
    glEnd();
    glFlush();
}

//***********************************************************
void myDrawing()
{
draw_Polygon(100,100,5,40);
}

void winReshapeFcn (GLint w, GLint h)
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
wx=w; wy=h; //the new window dimensions are sent to the main
}

int main(int argc, char** argv)
{ glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowPosition(50,50);
glutInitWindowSize (800, 800);
glutCreateWindow("problem 5");
MyInit();
glutDisplayFunc(myDrawing); //call the display function
glutReshapeFunc(winReshapeFcn); // call the reshape window function
glutMainLoop();
return 0;
}
