#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define RED 1
#define BLACK 2
#define BLUE 3
#define TRANSPARENT 4
#define HIGH 1
#define MEDIUM 2
#define LOW 3
GLfloat ratio;
GLfloat x=0.0,y=0,z=3.0;//eye coordinates
int ni=25, nj=25;//number of points for discretizing the surface
float a1=-1, b1=1;
float a2=-1, b2=1;
float stepi=(b1-a1)/(ni-1);
float stepj=(b2-a2)/(nj-1); // step in the u and v direction.
GLfloat angle=0, inc_angle=0.01; //rotation angle
GLfloat red=0, green=0, blue=0;
GLfloat trans=1.0;//transparency of the surface 1-solid, 0- invisible
bool flag;
int menu1, menu2, cur_menu;
void output_Text(float x, float y, char *text)
{
glColor3f(1, 0, 0);//text color red
glRasterPos3f(x, y, 0);
int len, i;
len = (int)strlen(text);
for (i = 0; i < len; i++) {
glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
}
}
void Output_CurMenu(int menu)
{
if (menu==menu1) output_Text(-3.0,-1.2,"Color menu");
if (menu==menu2) output_Text(-3.0,-1.2,"Speed menu");
output_Text(-3.0,-1.0,"F1- switch the menu");
}
void changeSize(GLsizei w, GLsizei h)
{
// Prevent a divide by zero, when window is too short
// (you cant make a window of zero width).
if(h == 0)
h = 1;
ratio = 1.0f * w / h;
// Reset the coordinate system before modifying
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
// Set the viewport to be the entire window
glViewport(0, 0, w, h);
// Set the clipping volume
gluPerspective(60,ratio,1,1000);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(x, y, z,
x,y,z-1,
0.0,1.0,0.0);
}
float sx(float u,float v)
{
return u;
}
float sy(float u,float v)
{
return u*u-v*v;
}
float sz(float u,float v)
{
return v;
}
void displaySurface()
{int i, j;
float ui,vj,uip1,vjp1;
float xij,yij,zij;
float xip1j,yip1j,zip1j;
float xijp1,yijp1,zijp1;
float xip1jp1,yip1jp1,zip1jp1;
for (j = 0; j <= nj-1; j++) {
for (i = 0; i <= ni-1; i++) {
ui=a1+i*stepi;
vj=a2+j*stepj;
uip1=a1+(i+1)*stepi;
vjp1=a2+(j+1)*stepj;
xij=sx(ui,vj);
yij=sy(ui,vj);
zij=sz(ui,vj);
xip1j=sx(uip1,vj);
yip1j=sy(uip1,vj);
zip1j=sz(uip1,vj);
xip1jp1=sx(uip1,vjp1);
yip1jp1=sy(uip1,vjp1);
zip1jp1=sz(uip1,vjp1);
xijp1=sx(ui,vjp1);
yijp1=sy(ui,vjp1);
zijp1=sz(ui,vjp1);
glColor4f(red, green, blue, trans);
glBegin(GL_QUADS); //solid surface
glVertex3f(xij,yij,zij);
glVertex3f(xip1j,yip1j,zip1j);
glVertex3f(xip1jp1,yip1jp1,zip1jp1);
glVertex3f(xijp1,yijp1,zijp1);
glEnd();
glColor3f(1.0, 1.0, 1.0);//white wire
glBegin(GL_LINE_LOOP);
glVertex3f(xij,yij,zij);
glVertex3f(xip1j,yip1j,zip1j);
glVertex3f(xip1jp1,yip1jp1,zip1jp1);
glVertex3f(xijp1,yijp1,zijp1);
glEnd();
}
}
}
void display(void)
{
glClearColor(1,1,1,0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glPushMatrix();
glRotated(angle,0,1,0);
displaySurface();
glPopMatrix();
angle=angle+inc_angle;
Output_CurMenu(cur_menu);
glutSwapBuffers();
}
void Do_Nothing()
{
}
void processSpecialKeys(int c, int x, int y)
{
    if ((c == GLUT_KEY_F1)&&(!flag)) // F1 pressed and menu is not in use
{cur_menu = glutGetMenu();// which menu is in use ?
if (cur_menu==menu1) {glutSetMenu(menu2); cur_menu=menu2;} else
if (cur_menu==menu2) {glutSetMenu(menu1); cur_menu=menu1;}
glutAttachMenu(GLUT_RIGHT_BUTTON);// attach the menu to the mouse button

}
}

void process_Menu_Color(int option) {
switch (option) {
case RED : red = 1.0; green = 0.0; blue = 0.0; break;
case BLACK : red = 0.0; green = 0.0; blue = 0.0; break;
case BLUE : red = 0.0; green = 0.0; blue = 1.0; break;
case TRANSPARENT: if (trans==1.0) trans=0.5; else trans=1.0; break;
}

}
void process_Menu_Speed(int option) {
switch (option) {
case LOW : inc_angle=0.01; break;
case MEDIUM: inc_angle=0.05; break;
case HIGH : inc_angle=0.1; break;
}

}
void createGLUTMenus() {
menu1=glutCreateMenu(process_Menu_Color);
glutAddMenuEntry("Red",RED);
glutAddMenuEntry("Black",BLACK);
glutAddMenuEntry("Blue",BLUE);
glutAddMenuEntry("Transparent",TRANSPARENT);
menu2=glutCreateMenu(process_Menu_Speed);
glutAddMenuEntry("Low",LOW);
glutAddMenuEntry("Medium",MEDIUM);
glutAddMenuEntry("High",HIGH);
cur_menu=menu2;
glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void processMenuStatus(int status, int x, int y) {
if (status == GLUT_MENU_IN_USE)
flag = true; else flag = false; //check whether the menu is in use

// if it is in use you can not swap between them
}
int main(int argc, char **argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(100,100);
glutInitWindowSize(640,360);
glutCreateWindow("Problem 3");
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glEnable( GL_BLEND );
glutDisplayFunc(display);
glutIdleFunc(display);
glutReshapeFunc(changeSize);
glutMenuStatusFunc(processMenuStatus);
glutSpecialFunc(processSpecialKeys);
createGLUTMenus();
glutMainLoop();
return(0);
}
