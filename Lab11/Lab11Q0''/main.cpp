#include <windows.h>
#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#define NMAX 8

#define TRIANGLE 1
#define SQUARE 2
#define PENTAGON 3

#define HEXAGON 4
#define HEPTAGON 5
#define OCTAGON 6

int n_use=3;
int menu_use=1;
bool flag;
float r[NMAX],g[NMAX],b[NMAX];

GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
GLfloat light_position[] = {1.0,1.0,1.0,1.0};
GLfloat DiffuseLight[4] = {1,1,1,0};
GLfloat ang=0,dang=1;

void time_delay(int dur){
    clock_t start_time = clock();
    while(clock()-start_time<dur){}
}

float ax[3]={25,0,0};
float ay[3]={0,25,0};
float az[3]={0,0,25};

void plot_arrow(float v1[3],float v2[3])
{
    glBegin(GL_LINES);
        glVertex3fv(v1);
        glVertex3fv(v2);
    glEnd();
}

void plot_vector(float v[3])
{
    float zero[3] = {0,0,0};
    plot_arrow(zero,v);
}

void plot_color_axes()
{
    glColor3f(1,0,0);
    plot_vector(ax);
    glColor3f(0,1,0);
    plot_vector(ay);
    glColor3f(0,0,1);
    plot_vector(az);
}

void plot_black_axes()
{
    glColor3f(0,0,0);
    plot_vector(ax);
    plot_vector(ay);
    plot_vector(az);
}

void output_text(float x,float y,float z,char *text)
{
    int len,i;
    //glColor3f(0,0,0);
    glRasterPos3f(x,y,z);
    len = (int)strlen(text);
    for(i=0;i<len;i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,text[i]);
    }
}

void initlights()
{
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialf(GL_FRONT,GL_SHININESS,125.0);
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,DiffuseLight);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT,GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void draw_polygon(GLfloat R,GLint N)
{
    GLfloat x,y;
    GLint i;
    glPushMatrix();
    glRotatef(ang,0,0,1);
    glBegin(GL_POLYGON);
        for(i=0;i<N;i++){
            x=R*cos(2*M_PI*i/N);
            y=R*sin(2*M_PI*i/N);
            glColor3f(r[i],g[i],b[i]);
            glVertex3f(x,y,0);
        }
    glEnd();
    glPopMatrix();
}

void myinit3d()
{
    glClearColor(1,1,1,0);
    glColor3f(1,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1.33,.01,1000);
    gluLookAt(30,30,30,0,0,0,0,1,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3f(0,0,1);
    if(menu_use==1){
        output_text(7,1,21,"Menu 1");
    }else{
        output_text(7,1,21,"Menu 2");
    }
    glColor3f(0,0,0);
    output_text(5,0,20,"Left click-color, right-menu 1,2-menu 1 or 2");
    ang+=dang;
    draw_polygon(15,n_use);
    glutSwapBuffers();
    time_delay(10);
}

void processMenu(int option)
{
    switch(option){
        case TRIANGLE:n_use=3; break;
        case SQUARE:n_use=4; break;
        case PENTAGON:n_use=5; break;
        case HEXAGON:n_use=6; break;
        case HEPTAGON:n_use=7; break;
        case OCTAGON:n_use=8; break;
    }
}

void createGLUTmenu()
{
    int menu = glutCreateMenu(processMenu);
    glutAddMenuEntry("Triangle",TRIANGLE);
    glutAddMenuEntry("Square",SQUARE);
    glutAddMenuEntry("Pentagon",PENTAGON);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void processMenuStatus(int status,int x,int y)
{
    if(status==GLUT_MENU_IN_USE){
        flag=true;
    }else{
        flag=false;
    }
}

void myMouse(int button,int state,int x,int y)
{
    int i;
    if(button==GLUT_LEFT_BUTTON && state== GLUT_DOWN){
        for(i=0;i<NMAX;i++){
            r[i]=rand()%1000/1000.0;
            g[i]=rand()%1000/1000.0;
            b[i]=rand()%1000/1000.0;
        }
    }
}

void processNormalKey(unsigned char key,int x,int y)
{
    if(!flag){
        switch(key){
            case '1':
                glutChangeToMenuEntry(1,"Triangle",TRIANGLE);
                glutChangeToMenuEntry(2,"Square",SQUARE);
                glutChangeToMenuEntry(3,"Pentagon",PENTAGON);
                while(glutGet(GLUT_MENU_NUM_ITEMS)>3){
                    glutRemoveMenuItem(4);
                }
                menu_use=1;
            break;
            case '2':
                glutChangeToMenuEntry(1,"Hexagon",HEXAGON);
                glutChangeToMenuEntry(2,"Heptagon",HEPTAGON);
                glutChangeToMenuEntry(3,"Octagon",OCTAGON);
                while(glutGet(GLUT_MENU_NUM_ITEMS)>3){
                    glutRemoveMenuItem(4);
                }
                menu_use=2;
            break;
            default: break;
        }
    }
}

int main(int argc,char **argv)
{
    srand(time(0));
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Problem 0''");
    myinit3d();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(processNormalKey);
    glutMenuStatusFunc(processMenuStatus);
    createGLUTmenu();
    glutMainLoop();
}
