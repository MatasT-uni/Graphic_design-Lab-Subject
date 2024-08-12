#include <windows.h>
#include <GL\glut.h>
#include <time.h>
GLfloat angle1=0,dangle1=1,angle2=0,dangle2=2.5;
//Define variables: your code here
void Draw_Origin()
{ glColor3f(0.0, 0.0, 1.0); // set the drawing color blue
glPointSize(6);
glBegin(GL_POINTS);
glVertex2i(0,0);
glEnd();
}
void myInit(void)
{
//your code
glClearColor(1.0, 1.0, 1.0, 0.0); // set white background color
    glColor3f(0.0, 0.0, 0.0); // set the drawing color
    glMatrixMode(GL_PROJECTION); //set some additional parameters
    glLoadIdentity();
    gluOrtho2D(-300, 300.0, -300, 300.0);//set your coordinate system
    glMatrixMode(GL_MODELVIEW); //set some additional parameters
    glLoadIdentity();
    angle1=0.0;
}
void Time_Delay(GLint dur) //time delay
{clock_t start_time;
start_time = clock();
while((clock() - start_time) < dur )
{ }
}
void Rotate_Rect1()
{
glPushMatrix(); // send the preceding transformation matrix to stack
Draw_Origin();//draw the origin
glTranslatef(100,100,0); // Translate to the center of rotation
glRotatef(angle1, 0.0, 0.0, 1.0); //Set angle-deg. rotation about the z axis.
Draw_Origin();//draw the new origin (the center of rotation)
glTranslatef(120,0,0);
glColor3f(1.0, 0.0, 0.0); // set the drawing color red
glRecti (-50,-50, 50, 50); // Display the rotated rectangle.
//Draw_Origin();//draw the new origin on the top of the rectangle
glPopMatrix(); // restore the transformation matrix
angle1+=dangle1;//increment the rotation angle
Time_Delay(100);
}
//your code declare Rotate_Rect2
void Rotate_Rect2()
{
glPushMatrix(); // send the preceding transformation matrix to stack
Draw_Origin();//draw the origin
glTranslatef(-100,-100,0); // Translate to the center of rotation
glRotatef(angle2, 0.0, 0.0, 1.0); //Set angle-deg. rotation about the z axis.
Draw_Origin();//draw the new origin (the center of rotation)
glTranslatef(120,0,0);
glColor3f(255.0,255.0,0.0); // set the drawing color red
glRecti (-50,-50, 50, 50); // Display the rotated rectangle.
//Draw_Origin();//draw the new origin on the top of the rectangle
glPopMatrix(); // restore the transformation matrix
angle2+=dangle2;//increment the rotation angle
Time_Delay(100);
}

void myDisplay(void)
{
glClear(GL_COLOR_BUFFER_BIT);
Rotate_Rect1();
// your code call Rotate_Rect2
Rotate_Rect2();
glutSwapBuffers();
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
int main(int argc, char** argv)
{
glutInit(&argc, argv); // initialize the
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
glutInitWindowPosition(0,0); // set window position on screen
glutInitWindowSize(600,600); // set window size
glutCreateWindow("problem 4"); // open the screen window
glutDisplayFunc(myDisplay); //register the display function
glutIdleFunc(myDisplay); // register idle display function
glutMouseFunc(mouse);
myInit(); //initialize settings
glutMainLoop(); // go into the perpetual loop
}
