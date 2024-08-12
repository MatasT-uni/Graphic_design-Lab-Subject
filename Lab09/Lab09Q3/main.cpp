#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
GLfloat mat_specular1[] = { 0.0, 0.1, 0.3, 1.0 };//blue for the Earth
GLfloat mat_specular2[] = { 0.3, 0.3, 0.0, 1.0 };//yellow for the Sun
GLfloat mat_specular3[] = { 0.2, 0.2, 0.2, 1.0 };//grey for the Moon
GLint year_Earth = 0, day_Earth = 0;//rotation angles, Earth
GLint year_Moon=0, day_Moon=0; //rotation angles, Moon
GLint dyearE=1, ddayE=0.5; //increments
GLint dyearM=2, ddayM=0.25;
int slices=25, stacks=25;
void Time_Delay(int dur) {
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur) {
    }
}
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.3);
    glShadeModel (GL_FLAT);//you may change delete this line to change to
    glEnable(GL_LIGHTING);//enable lighting
    glEnable(GL_LIGHT0); //enable light 0 by default it is white
    glEnable(GL_DEPTH_TEST);//close objects obstruct far objects
}
void drawplanet(GLfloat rad)
{
    glutSolidSphere(rad, slices, stacks);
    glColor3f(0,0,0);//black wire
    glutWireSphere(rad,slices, stacks);
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glPushMatrix();
    glRotatef (year_Earth, 0.0, 1.0, 0.0);//rotate the Earth
    glTranslatef (2.0, 0.0, 0.0); //shift the Earth by 2
    glRotatef (day_Earth, 0.0, 1.0, 0.0);//revolve the Earth
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);//reflection light,
    //the Earth
    drawplanet(0.5);

    // Draw moon
    glRotatef (year_Moon, 0.0, 1.0, 0.0);//rotate the Earth
    glTranslatef (1.0, 0.0, 0.0); //shift the Earth by 2
    glRotatef (day_Moon, 0.0, 1.0, 0.0);//revolve the Earth
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);//reflection light,
    drawplanet(0.2);


    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);//reflection light
    //the Sun
    drawplanet(1);//draw the motionless Sun
    year_Earth=year_Earth+dyearE; //increment rotations of the Earth
    //around the sun
    day_Earth=day_Earth+ddayE;//increment rotations of the Earth around


    //Moon setting
    year_Moon=year_Moon+dyearM; //increment rotations of the Moon
    //around the Earth
    day_Moon=day_Moon+ddayM;//increment rotations of the Moon around
    //itself


    glutSwapBuffers();
    Time_Delay(50);//depends on your computer
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);// convert w and h to
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(void)
{
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("problem 3 Sun-Earth-Moon");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
