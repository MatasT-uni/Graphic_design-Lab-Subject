#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
GLfloat ratio=1.33;
GLfloat x=-1.0,y=2.0,z=7.0;
GLfloat lx=0.0,ly=0.0,lz=-1.0,angle=0;
//position and orientation of the camera
GLfloat increment=0.1, angleincrement=0.01;
//increments for changing the camera position
GLfloat ang=0, sangleincrement=1;
//the angle and increment for revolving the sphere and the torus
GLfloat head_ang=0, head_anginc=0.5;
float angleh=0;//head rotation
float dh=0.005;//head rotation increment
float R=2;//-R is an x-offset of the reference point
void changeSize(GLint w, GLint h) //window resize
{
// Prevent a divide by zero, when window width=0
if(h == 0) h = 1;
ratio = 1.0 * w / h; // Reset the coordinate system before modifying
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
// Set the viewport to be the entire window
glViewport(0, 0, w, h);
// Set the clipping volume
gluPerspective(45,ratio,1,1000);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(x, y, z,
x + lx,y + ly,z + lz,
0.0,1.0,0.0);

}
void Time_Delay(int dur)
{clock_t start_time;
start_time = clock();
while((clock() - start_time) < dur )
{ }
}
void DrawPoint(GLfloat x, GLfloat y, GLfloat z)
{ glColor3d(1,0,0);
glPointSize(16);
glBegin(GL_POINTS);
glVertex3f(x,y,z);
glEnd();
}
void DrawDonut(void) //change the position and the rotation of the torus
{
glPushMatrix();
glTranslated(-2,0.5,0);//position of the torus
glRotated(ang,1,1,0); //revolve the torus
glColor3f(1,0,0);
glutWireTorus(0.2,0.8,20,20); //red wire torus
glColor3f(0,0,1);
glutSolidTorus(0.2,0.8,20,20);//blue solid torus
glPopMatrix();
}
void DrawBall()
{
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
   glRotated(ang,0,1,0);
   glTranslated(-R,0.5,0.0);
   glRotated(ang,1,0,0);
   glColor3f(1,1,0);
   glutWireSphere(0.5,50,50);
    glColor3f(0,1,0);
    glutSolidSphere(0.5,50,50);
    glPopMatrix();
}
void DrawSnowMan() {
int c;
glColor3f(1.0, 1.0, 1.0);
// Draw Body
glTranslatef(0.0f ,0.75, 0.0);
glutSolidSphere(0.75,20,20);
glPushMatrix();
glTranslatef(0.0, 1.0, 0.0);
//the head nodes (very simple solution)
if ((ang>0.5) || (ang<0)) ang=-ang;
glRotated(ang,1,0,0);
glutSolidSphere(0.25,20,20);
c=rand()%100; //blinking here (with the probability 1 from 100)
//if c=1 make the eyes or one eye blink –white color
// Draw Eyes
glColor3f(0,0,0);
glPushMatrix();
glTranslatef(0.05, 0.10, 0.18);
glutSolidSphere(0.05,10,10);
glTranslatef(-0.1, 0.0, 0.0);
glutSolidSphere(0.05,10,10);
glPopMatrix(); // Draw Nose
glColor3f(1.0, 0.5 , 0.5);
glRotatef(0.0,1.0, 0.0, 0.0);
glutSolidCone(0.08,0.5,10,2);
glPopMatrix();
}
void Draw36SnowMan(void)
{
for(int i = -3; i < 3; i++)
for(int j=-3; j < 3; j++) {
glPushMatrix();
glTranslatef(i*10.0,0,j * 10.0);
DrawSnowMan();
glPopMatrix();
}
}
void DrawWorld(void) {
glEnable(GL_DEPTH_TEST);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// Draw ground
glColor3f(0.9, 0.9, 0.9);
glBegin(GL_QUADS);
glVertex3f(-100.0, 0.0, -100.0);
glVertex3f(-100.0, 0.0, 100.0);
glVertex3f( 100.0, 0.0, 100.0);
glVertex3f( 100.0, 0.0, -100.0);
glEnd();
// Draw objects
DrawDonut();//in a different position
//DrawMagicBall() – rotating and rolling sphere here
Draw36SnowMan();
DrawBall();
DrawPoint(0,0,0);
DrawPoint(-R,0.5,0); //the reference point
Time_Delay(20);
ang=ang+sangleincrement;// this rotates the torus
glutSwapBuffers();
}
//------------------position of the camera here
void orientMe(float ang) {
lx = sin(ang);
lz = -cos(ang);
glLoadIdentity();
gluLookAt(x, y, z,
x+lx ,y+ly ,z+lz,
0.0,1.0,0.0);

}
void moveMeFlat(float increment) {
x = x + lx*increment;
z = z + lz*increment;
glLoadIdentity();
gluLookAt(x, y, z,
x + lx,y + ly,z + lz,
0.0,1.0,0.0);

}
void moveMeUp(float increment) {
y=y-increment;
glLoadIdentity();
gluLookAt(x, y, z,
x + lx,y+ly ,z + lz,
0.0,1,0.0);

}
//------------------control position of the camera by the special keys
void inputKey(int key, int x, int y) {
switch (key) {
case GLUT_KEY_LEFT :
angle -= angleincrement;
orientMe(angle);
break;
case GLUT_KEY_RIGHT :
angle +=angleincrement;
orientMe(angle);
break;
case GLUT_KEY_UP :
moveMeFlat(increment);break;
case GLUT_KEY_DOWN : moveMeFlat(-increment);break;
case GLUT_KEY_PAGE_UP: moveMeUp(increment);break;
case GLUT_KEY_PAGE_DOWN: moveMeUp(-increment);break;
}
}
int main(int argc, char **argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(0,0);
glutInitWindowSize(600,600);
glutCreateWindow("Problem 5: Nodding & blinking");
glutSpecialFunc(inputKey);
glutDisplayFunc(DrawWorld);
glutIdleFunc(DrawWorld);
glutReshapeFunc(changeSize);
glutMainLoop();
return(0);
}
