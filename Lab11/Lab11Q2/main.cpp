#include <windows.h>
#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#define TORUS_COLOR 1
#define SPHERE_SMALL_COLOR 2
#define SPHERE_BIG_COLOR 3

#define RED 1
#define GREEN 2
#define BLUE 3
#define BLACK 4
#define WHITE 5

#define XAXIS 1
#define YAXIS 2
#define ZAXIS 3
#define DIAGN 4

#define DIRECTIONAL 1
#define POSITIONAL  2

#define SPEC_ON  1
#define SPEC_OFF 2

int swidth=500,sheight=500;
float ax[3]={5,0,0}, ay[3]={0,5,0}, az[3]={0,0,5};
float angle=0, dangle=0.5;
int red=0, green=0, blue=0;
int tred=1, tgreen=1, tblue=1;
int ssred=0, ssgreen=1, ssblue=0;
int sbred=0, sbgreen=0, sbblue=1;
int Lred=1, Lgreen=1, Lblue=1;
int dir=0, cur_lightpos=ZAXIS, lp=1, shine=10;
bool spec=true;
GLfloat light_position[] = {0, 0, static_cast<GLfloat>(lp), static_cast<GLfloat>(dir)};
GLfloat light[] = {static_cast<GLfloat>(Lred), static_cast<GLfloat>(Lgreen), static_cast<GLfloat>(Lblue), 0};
GLfloat specularLight[] = {1, 1, 1, 0};

void output_text(float x, float y, char *text, int red, int green, int blue){
    int len,i;
    char W[7]=" White";
    glColor3f(red,green,blue);
    if((red==1)&&(green==1)&&(blue==1)){
        glColor3f(0,0,0);
    }
    glPushMatrix();
    glRotated(45,0,1,0);
    glRasterPos3f(x,y,0);
    len=(int)strlen(text);
    for(i=0;i<len;i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,text[i]);
    }
    if((red==1)&&(green==1)&&(blue==1)){
        for(i=0;i<6;i++){
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13,W[i]);
        }
    }
    glPopMatrix();
}

void plot_arrow(float v1[3],float v2[3]){
    glPointSize(10);
    glBegin(GL_LINES);
        glVertex3fv(v1);
        glVertex3fv(v2);
    glEnd();
}

void plot_vector(float v[3]){
    float zero[3]={0,0,0};
    plot_arrow(zero,v);
}

void plot_axis(){
    glColor3f(1,0,0);
    plot_vector(ax);
    glColor3f(0,1,0);
    plot_vector(ay);
    glColor3f(0,0,1);
    plot_vector(az);
}

void time_delay(int dur){
    clock_t start_time = clock();
    while(clock()-start_time<dur){}
}

void init(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,float(swidth)/float(sheight),0.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5,5,5,0,0,0,0,1,0);
}

void initlights(){
    glClearColor(1,1,1,0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT,GL_SPECULAR,specularLight);
    glMaterialf(GL_FRONT,GL_SHININESS,shine);
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glColorMaterial(GL_FRONT,GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void display_all(){
    glPushMatrix();
    plot_axis();
    glColor3f(tred,tgreen,tblue);
    glutSolidTorus(0.5,1,20,20);
    glColor3f(ssred,ssgreen,ssblue);
    glutSolidSphere(0.4,15,15);
    glColor3f(sbred,sbgreen,sbblue);
    glTranslated(0,2,0);
    glutSolidSphere(1,20,16);
    glPopMatrix();
}

void output_textall(){
    glDisable(GL_LIGHTING);
    if(spec){
        output_text(-5.8,-5.3,"Specular+",0,0,0);
    }else{
        output_text(-5.8,-5.3,"Specular-",0,0,0);
    }
    output_text(-6,-6,"Torus",tred,tgreen,tblue);
    output_text(-6.1,-6.6,"Big Sphere",sbred,sbgreen,sbblue);
    output_text(-6.35,-7.3,"Small Sphere",ssred,ssgreen,ssblue);
    if(dir==0){
        output_text(-6.55,-8.15,"Light-Dir",Lred,Lgreen,Lblue);
    }else{
        output_text(-6.55,-8.15,"Light-Pos",Lred,Lgreen,Lblue);
    }
    glEnable(GL_LIGHTING);
}

void display(){
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    display_all();
    output_textall();
    glFlush();
}

void color_torus(int option){
    switch(option){
        case RED:   tred=1;tgreen=0;tblue=0;break;
        case GREEN: tred=0;tgreen=1;tblue=0;break;
        case BLUE:  tred=0;tgreen=0;tblue=1;break;
        case BLACK: tred=0;tgreen=0;tblue=0;break;
        case WHITE: tred=1;tgreen=1;tblue=1;break;
        default: break;
    }
}

void color_smallSphere(int option){
        switch(option){
        case RED:   ssred=1;ssgreen=0;ssblue=0;break;
        case GREEN: ssred=0;ssgreen=1;ssblue=0;break;
        case BLUE:  ssred=0;ssgreen=0;ssblue=1;break;
        case BLACK: ssred=0;ssgreen=0;ssblue=0;break;
        case WHITE: ssred=1;ssgreen=1;ssblue=1;break;
        default: break;
    }
}

void color_bigSphere(int option){
        switch(option){
        case RED:   sbred=1;sbgreen=0;sbblue=0;break;
        case GREEN: sbred=0;sbgreen=1;sbblue=0;break;
        case BLUE:  sbred=0;sbgreen=0;sbblue=1;break;
        case BLACK: sbred=0;sbgreen=0;sbblue=0;break;
        case WHITE: sbred=1;sbgreen=1;sbblue=1;break;
        default: break;
    }
}

void light_color(int option){
    glDisable(GL_LIGHTING);
        switch(option){
        case RED:   Lred=1;Lgreen=0;Lblue=0;break;
        case GREEN: Lred=0;Lgreen=1;Lblue=0;break;
        case BLUE:  Lred=0;Lgreen=0;Lblue=1;break;
        case BLACK: Lred=0;Lgreen=0;Lblue=0;break;
        case WHITE: Lred=1;Lgreen=1;Lblue=1;break;
        default: break;
    }
    light[0]=Lred;light[1]=Lgreen;light[2]=Lblue;
    initlights();
}

void light_pos(int option){
    int i;
    cur_lightpos=option;
    glDisable(GL_LIGHTING);
    switch(option){
        case XAXIS:
            light_position[0]=lp;light_position[1]=0; light_position[2]=0; break;
        case YAXIS:
            light_position[0]=0; light_position[1]=lp;light_position[2]=0; break;
        case ZAXIS:
            light_position[0]=0; light_position[1]=0; light_position[2]=lp;break;
        case DIAGN:
            light_position[0]=lp;light_position[1]=lp;light_position[2]=lp;break;
        default: break;
    }
    light_position[3]=dir;
    initlights();
}

void light_type(int option){
    glDisable(GL_LIGHTING);
    switch(option){
        case DIRECTIONAL:lp=1;dir=0;break;
        case POSITIONAL: lp=5;dir=1;break;
        default: break;
    }
    light_pos(cur_lightpos);
}

void spec_light(int option){
    glDisable(GL_LIGHTING);
    switch(option){
        case SPEC_ON:
            for(int i=0;i<3;i++){
                specularLight[i]=1;
            }
            specularLight[3]=0;
            spec=true;
            break;
        case SPEC_OFF:
            for(int i=0;i<3;i++){
                specularLight[i]=0;
            }
            specularLight[3]=shine;
            spec=false;
            break;
        default: break;
    }
    initlights();
}

void dummy(int option){}

void createGLUTmenu(){
    int coltor_menu=glutCreateMenu(color_torus);
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("Black",BLACK);
    glutAddMenuEntry("White",WHITE);
    int colss_menu=glutCreateMenu(color_smallSphere); //SMALL Sphere
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("Black",BLACK);
    glutAddMenuEntry("White",WHITE);
    int colsb_menu=glutCreateMenu(color_bigSphere);   //BIG Sphere
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("Black",BLACK);
    glutAddMenuEntry("White",WHITE);
    int light_col_menu=glutCreateMenu(light_color);
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("Black",BLACK);
    glutAddMenuEntry("White",WHITE);
    int light_type_menu=glutCreateMenu(light_type);
    glutAddMenuEntry("Directional",DIRECTIONAL);
    glutAddMenuEntry("Positional",POSITIONAL);
    int light_pos_menu=glutCreateMenu(light_pos);
    glutAddMenuEntry("X-Axis",XAXIS);
    glutAddMenuEntry("Y-Axis",YAXIS);
    glutAddMenuEntry("Z-Axis",ZAXIS);
    glutAddMenuEntry("Diagonal",DIAGN);
    int spec_menu=glutCreateMenu(spec_light);
    glutAddMenuEntry("Specular Light On",SPEC_ON);
    glutAddMenuEntry("Specular Light Off",SPEC_OFF);
    int menu=glutCreateMenu(NULL);
    glutAddSubMenu("Torus Color",coltor_menu);
    glutAddSubMenu("Small Sphere Color",colss_menu);
    glutAddSubMenu("Big Sphere Color",colsb_menu);
    glutAddSubMenu("Light Color",light_col_menu);
    glutAddSubMenu("Light Type",light_type_menu);
    glutAddSubMenu("Light Position",light_pos_menu);
    glutAddSubMenu("Specular Light",spec_menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(swidth,sheight);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Problem 2. Lighting Menu Project");
    init();
    initlights();
    createGLUTmenu();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
