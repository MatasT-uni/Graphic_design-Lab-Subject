#include <windows.h>
#include<GL/glut.h>
#include<stdio.h>
#define Sphere 1
#define Cone 2
#define Torus 3
#define Teapot 4
#define SnowMan 5
#define Red 1
#define Green 2
#define White 3
//use this for the solution
#define X_axis 1
#define Y_axis 2
#define Z_axis 3
#define Stop 1
#define Resume 2
float angle = 0.0, dangle=0.05;
int option_global=4;
int swidth=500,sheight=500;
int slices = 16;
int stacks = 16;
int red=1,green=1, blue=1;
float vx=1,vy=0,vz=0;
void Display_TeaPot()
{
glutWireTeapot(1.0); // the teapot
}
void Display_Cone()
{
glutWireCone(1,1,slices,stacks);
}
void Display_Sphere()
{ glutWireSphere(1,slices,stacks);
}
void Display_Torus()
{ glutWireTorus(0.5,0.5,slices,stacks);
}
void Display_SnowMan() //DOWNLOADABLE
{
glPushMatrix();
glColor3d(red, green, blue);
// Draw Body
glutWireSphere(0.75,20,20);
// Draw Head
glTranslatef(0.0, 1.0, 0.0);
glutWireSphere(0.25,20,20);
// Draw Eyes
glPushMatrix();
glColor3f(0.0,0.0,0.0);
glTranslatef(0.05, 0.10, 0.18);
glutSolidSphere(0.05,10,10);
glTranslatef(-0.1, 0.0, 0.0);
glutSolidSphere(0.05,10,10);
glPopMatrix();
// Draw Nose
glColor3f(1.0, 0.5 , 0.5);
glRotatef(0.0,1.0, 0.0, 0.0);
glutSolidCone(0.08,0.5,10,2);
glPopMatrix();
}
void init(void) {
glEnable(GL_DEPTH_TEST);//close objects obstruct far objects
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60,float(swidth)/float(sheight),0.1,1000);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(0.0,0.0,3.0,
0.0,0.0,0.0,
0.0,1.0,0.0);
}
void myDisplay(void) {
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glPushMatrix();
glRotated(angle,vx,vy,vz);
glColor3d(red,green,blue);
switch (option_global)
{
case Sphere :Display_Sphere() ; break;
case Cone : Display_Cone(); break;
case Torus : Display_Torus(); break;
case Teapot : Display_TeaPot();break;
case SnowMan: Display_SnowMan();break;
default :break;
}
angle+=dangle;
glPopMatrix();
glutSwapBuffers();
}
void processMenuShape(int option)
{
option_global=option;//this menu is executed in myDisplay
}
void Menu_Color(int option)
{
switch (option) {
case Red : red = 1.0; green = 0.0; blue = 0.0; break;
case Green : red = 0.0; green = 1.0; blue = 0.0; break;
case White : red = 1.0; green = 1.0; blue = 1.0; break;
default :break; }
}
void createGLUTMenus() {
int submenu1 = glutCreateMenu(Menu_Color);
glutAddMenuEntry("Red",Red);
glutAddMenuEntry("Green",Green);
glutAddMenuEntry("White", White);
int menu=glutCreateMenu(processMenuShape);
glutAddMenuEntry("Sphere",Sphere);
glutAddMenuEntry("Cone",Cone);
glutAddMenuEntry("Torus",Torus);
glutAddMenuEntry("Teapot",Teapot);
glutAddMenuEntry("SnowMan",SnowMan);
glutAddSubMenu("Color",submenu1);
glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char **argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(100,100);
glutInitWindowSize(swidth,sheight);
glutCreateWindow("Problem 1");
init();
glutDisplayFunc(myDisplay);
glutIdleFunc(myDisplay);
createGLUTMenus();
glutMainLoop();
return 0;
}
