#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4
GLfloat x=4,y=4.0,z=4.0;//camera position
GLfloat lx=0.0,ly=0.0,lz=0.0; //look at point
GLfloat ratio=1;
int Lred=1, Lgreen=1, Lblue=1;
bool rotate=false;
GLfloat t=0; //parameter along the trajectory of the light
GLfloat dt=0.0001; //increment of t

GLfloat Mred=0,Mgreen=0, Mblue=1;//material color = blue
GLfloat diffuseMaterial[4] = {Mred, Mgreen, Mblue, 1.0 };//material color
GLfloat light_position[] = {0.0, 0.5, 0.0, 1.0 };//initial light position
GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };//spot direction
GLfloat Light[] = {1.0, 1.0, 1.0, 0.0};//white
GLfloat light[] = {static_cast<GLfloat>(Lred), static_cast<GLfloat>(Lgreen), static_cast<GLfloat>(Lblue), 0};
float ax[3]={5,0,0}; float ay[3]={0,5,0}; float az[3]={0,0,5};//coordinate axes


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
glColor3f(1,0,0);
plot_Vector(ax);
glColor3f(0,1,0);
plot_Vector(ay);
glColor3f(0,0,1);
plot_Vector(az);
}
void initlights(void)
{
glClearColor (1.0, 1.0, 1.0, 0.0);
glShadeModel (GL_SMOOTH);
glLightfv(GL_LIGHT0, GL_POSITION, light_position); //set up the light position
glLightfv(GL_LIGHT0, GL_DIFFUSE, Light);//this sets the diffuse light
glLightfv(GL_LIGHT0, GL_AMBIENT, Light);//this sets the ambient light
glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);//30 degree light cone
glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);//sets the spot light direction
glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1);//concentration at the center of the spot
glEnable(GL_LIGHTING);//enable lighting
glEnable(GL_LIGHT0); //enable light 0
glEnable(GL_DEPTH_TEST);//enables the depth buffer: closer objects will obstruct objects located farther
glColorMaterial(GL_FRONT, GL_DIFFUSE);//diffuse light is reflected by the front face
glEnable(GL_COLOR_MATERIAL);//enable reflection by material
glShadeModel(GL_SMOOTH);//smooth shades
}
void init()
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60,1,0.1,1000);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(x, y, z,
lx,ly,lz,
0.0,1.0,0.0);

}
float sx(float u,float v) //surface =plane
{return u;}
float sy(float u,float v)
{return 0;}
float sz(float u,float v)
{return v;}
float nx(float u,float v) //normals along the y-axis
{return 0;}
float ny(float u,float v)
{return 1;}
float nz(float u,float v)
{return 0;}
void initScene() {
glEnable(GL_DEPTH_TEST);
glShadeModel (GL_FLAT);
}
int ni=50, nj=50;
float a1=-2, b1=2;
float a2=-2, b2=2;
float stepi=(b1-a1)/(ni-1);
float stepj=(b2-a2)/(nj-1); // step in the u and v direction.
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
vj=a1+j*stepj;
uip1=a1+(i+1)*stepi;
vjp1=a1+(j+1)*stepj;
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
//draw quads


glColor4fv(diffuseMaterial);
glBegin(GL_QUADS);
glNormal3f(nx(ui,vj),ny(ui,vj),nz(ui,vj));
glVertex3f(xij,yij,zij);
glNormal3f(nx(uip1,vj),ny(uip1,vj),nz(uip1,vj));
glVertex3f(xip1j,yip1j,zip1j);
glNormal3f(nx(uip1,vjp1),ny(uip1,vjp1),nz(uip1,vjp1));
glVertex3f(xip1jp1,yip1jp1,zip1jp1);
glNormal3f(nx(ui,vjp1),ny(ui,vjp1),nz(ui,vjp1));
glVertex3f(xijp1,yijp1,zijp1);
glEnd();
glColor3f(1,1,1);
glBegin(GL_LINE_LOOP);
glVertex3f(xij,yij+0.01,zij);
glVertex3f(xip1j,yip1j+0.01,zip1j);
glVertex3f(xip1jp1,yip1jp1+0.01,zip1jp1);
glVertex3f(xijp1,yijp1+0.01,zijp1);
glEnd();
}
}
}


GLfloat trajx(GLfloat t)
{
    return 2*cos(3*t);
}
GLfloat trajy(GLfloat t)
{
    return 0.5;
}
GLfloat trajz(GLfloat t)
{
    return 2*sin(2*t);
}


void plot_trajectory()
{
glDisable(GL_LIGHTING);
GLfloat xt,yt,zt,t,dt;
dt=0.01;
glColor3d(1,0,1);
glBegin(GL_LINE_STRIP);
for (t=0;t<=2*M_PI+dt;t=t+dt)
{
xt=trajx(t);
yt=0.5;
zt=trajz(t);
glVertex3d(xt,yt,zt);}
glEnd();
glEnable(GL_LIGHTING);
}


void move_light()
{
glPushMatrix();
glTranslated(trajx(t),trajy(t),trajz(t));
initlights();
glPopMatrix();
}

void move_point(float x, float y, float z)
{
glDisable(GL_LIGHTING);
glColor4fv(diffuseMaterial);
glPointSize(5);
glBegin(GL_POINTS);
glVertex3d(x,y,z);
glEnd();
glEnable(GL_LIGHTING);
}
void display(void)
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
displaySurface();
plot_trajectory();
plot_Axis();
move_light();
move_point(trajx(t),trajy(t),trajz(t));

t+=dt;
glutSwapBuffers();
}
void Menu(int option)
{
switch(option)
{

case RED: diffuseMaterial[0] = 1;diffuseMaterial[1] = 0;diffuseMaterial[2] = 0; break;
case BLUE:  diffuseMaterial[0] = 0;diffuseMaterial[1] = 0;diffuseMaterial[2] = 1; break;
case GREEN:  diffuseMaterial[0] = 0;diffuseMaterial[1] = 1;diffuseMaterial[2] = 0; break;
case WHITE:  diffuseMaterial[0] = 1;diffuseMaterial[1] = 1;diffuseMaterial[2] = 1; break;

}
light[0]=Lred;light[1]=Lgreen;light[2]=Lblue;
    initlights();
}
void createGLUTMenus() //create menus
{
int menu=glutCreateMenu(Menu);//call processMenuEvents on the menu click
glutAddMenuEntry("Red",RED);
glutAddMenuEntry("Blue",BLUE);
glutAddMenuEntry("Green",GREEN);
glutAddMenuEntry("White",WHITE);
glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char **argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(100,100);
glutInitWindowSize(700,700);
glutCreateWindow("Problem 3. Bonus. Basic code");
createGLUTMenus();
init();
initlights();
glutDisplayFunc(display);
glutIdleFunc(display);
glutMainLoop();

return(0);
}
