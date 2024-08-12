 #include <windows.h>
 #include<GL/glut.h>
 #include<math.h>
 #include <cstdlib>
  #include <stdlib.h>
  #include <stdio.h>
  #include <time.h>
  #define ROTATE_ALL 1
  #define MOVE_BALL 2
  #define BALL_COLOR 3
  #define ROTATE_CUBE 4

  double angle=0, dangle=0.01;
  double cangle=0, dcangle=0.1;
  bool gray=true;
  bool move=false, rotate=false;
  bool cube=false;
  bool colorchange=true;
  double t=0, dt=0.001;
  double r=0.6;

  void Time_Delay(int dur)
  {
  clock_t start_time;
  start_time = clock();
  while ((clock() - start_time) < dur)
  {
  }
  }

  void output_Text(float x, float y, char *text)
  {
  int len, i;
  glColor3f(1, 0, 0); //red text
  glRasterPos3f(x, y, 0);
  len = (int)strlen(text);
  for (i = 0; i < len; i++)
  {
  glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
  }
  }

  void display_Small_Sphere(double R)
  {
  glColor3d(r,r,r);
  glutSolidSphere(R,10,10);
  glColor3d(1,1,0);
  glutWireSphere(R,10,10);
  }

  void draw_1Point(double x, double y, double z)
  {
  glColor3d(1,1,0);
  glPointSize(10);
  glBegin(GL_POINTS);
  glVertex3d(x,y,z);
  glEnd();
  }

  double shiftx,shifty,shiftz,shift;//function Trajectory() changes
  // these global variables
  //piecewise linear interpolation points
  double xp[]={0,0,0,0,0,0,5,5,6};
  double yp[]={-1,-1,1,1,-1,-1,-1,1,2};
  double zp[]={0,-1,-1,1,1,0,0,0,0};
  //double xp[]={1.0,1.0,1.0,1.0,1.0,1.0,3.5,3.5,4.0};
  //double yp[]={1.0,1.0,2.0,2.0,1.0,1.0,1.0,2.0,2.5};
  //double zp[]={1.5,2.0,2.0,1.0,1.0,1.5,1.5,1.5,1.5};
  int n=(int)sizeof(xp)/sizeof(double);//number of points

  //--------------interpolation-------------------

  void draw_big_Cube()
  {
  glColor3f(0,0,0);
  if (cube) glColor3f(1,0,0);
  glPushMatrix();
  glTranslated(6,2,0);
  glRotated(cangle,0,1,0);
  glutWireCube(2);
  glPopMatrix();
  }

  double f(double *p,double t)
  {
  int i;
  double returnf;
  for (i=1;i<=n-1;i++)
  if ((t<=i)&&(t>=i-1))
  {
  returnf=p[i]*(t-i+1)+p[i-1]*(i-t);
  break;
  }
  return returnf;
  }

  double x(double t)
  {
  return f(xp,t);
 }

 double y(double t)
 {
 return f(yp,t);
 }

 double z(double t)
 {
 return f(zp,t);
 }

 //----------------------------------------------
 void Trajectory()//changes global variables shiftx, shifty, shiftz
 {
 shiftx=x(t);
 shifty=y(t);
 shiftz=z(t);
 }

 void DrawTrajectory()
 {
 double t,dt=0.5;//local t and dt
 double xx,yy,zz;
 int i;
 glColor3d(0,0,1);
 glBegin(GL_LINE_STRIP);
 for (t=0;t<=n-1;t=t+dt)
 {
 xx=x(t);
 yy=y(t);
 zz=z(t);
 glVertex3d(x(t),y(t),z(t));
 }
 glEnd();
 }

 void draw_Points()
 {
 int i;
 glColor3d(0,0,0);
 glPointSize(5);
 glBegin(GL_POINTS);
 for (i=0;i<=n-1;i++)
 {
 glVertex3d(xp[i],yp[i],zp[i]);
 }
 glEnd();
 }

 void myInit()
 {
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glMatrixMode(GL_PROJECTION); //set the projection matrix
 glLoadIdentity();
 gluPerspective(30, 1.0, .01, 10000);
 gluLookAt(18.0,18.0,18.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
 glMatrixMode(GL_MODELVIEW); // set the modelview matrix
 glLoadIdentity();//ready to apply translations and rotations
 glEnable(GL_DEPTH_TEST);//
 }

 void display_Move()
 {
 glPushMatrix();
 glRotated(angle,0,1,0);
 draw_Points();
 DrawTrajectory();
 draw_big_Cube();
 Trajectory();
 glTranslated(shiftx,shifty,shiftz);
 display_Small_Sphere(0.5);
 glPopMatrix();
 draw_1Point(0,0,0);
 output_Text(-3,-10,"Right click-menu");
 }

 void myDisplay(void)
 {
 glClearColor(1,1,1,0);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 display_Move();
 if (move) t+=dt;//increment if move=true
 if (rotate) angle+=dangle;
 if (cube) cangle+=dcangle;
 if ((fabs(t)>=n-1) || (t<0) ) dt=-dt;//turn back
 if (colorchange)
 {
 if (dt>0) r=0.8; else r=0;
 };
 glutSwapBuffers();
 }

 void process_Menu(int option)
 {
 switch (option)
 {
 case ROTATE_ALL : if (rotate) rotate=false; else rotate=true;
 break;
 case MOVE_BALL:if (move) move=false; else move=true;
 break;
 case BALL_COLOR :if (colorchange) colorchange=false; else colorchange=true;
 break;
 case ROTATE_CUBE :if (cube) cube=false; else cube=true;
 break;
 }
 }

 void createGLUTMenus()
 {
 int menu=glutCreateMenu(process_Menu);
 glutAddMenuEntry("Rotate All/Stop",ROTATE_ALL);
 glutAddMenuEntry("Move Ball/Stop",MOVE_BALL);
 glutAddMenuEntry("Change/Do not Change the Ball Color",BALL_COLOR);
 glutAddMenuEntry("Rotate the Cube/Stop",ROTATE_CUBE);
 glutAttachMenu(GLUT_RIGHT_BUTTON);
 }

 int main(int argc, char **argv)
 {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE| GLUT_RGBA);
 glutInitWindowPosition(100,100);
 glutInitWindowSize(500,500);
 glutCreateWindow("Problem 4. Solution");
 myInit();
 glutDisplayFunc(myDisplay);
 glutIdleFunc(myDisplay);
 createGLUTMenus();
 glutMainLoop();
 return 0;
 }
