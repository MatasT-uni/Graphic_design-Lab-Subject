#include <windows.h>
#include<gl\glut.h>
void myDisplay (void)
{glClear(GL_COLOR_BUFFER_BIT);
glFlush( );//send the drawing to the screen
}
void Init(void)
{glClearColor(0.0, 0.0, 1.0, 0.0);//blue background
}
int main (int argc, char** argv)
{glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //Set a display mode
glutCreateWindow("Simple program"); // Create a window with a title
glutDisplayFunc(myDisplay); //callback redraw function
Init( ); // Initialize settings
glutMainLoop( ); // infinite loop
return 0;
}
