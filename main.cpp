Added one line-Sample Jenkins
#include <stdlib.h>
#include <GL/glut.h>
#include<stdio.h>
#include<string.h>
#include <math.h>
//#include<iostream>

//using namespace std;
int score = 0;
GLfloat treasure_color_array[][3] = {1,0,0};

//The grid parameters for the bricks
int rows = 3;
int columns = 10;

// Structure to store the coordinates of each brick
struct treasure_coords{

	GLfloat x;
	GLfloat y;

};

//Array to store the bricks
treasure_coords treasure_array[50][50];
treasure_coords water_array[50][50];
GLfloat px,bx = 0,by = -11 ,speed = 0,dirx=0,diry=0,start = 0;

// Function to draw the paddle
void draw_boat()
{
	glDisable(GL_LIGHTING);
	glColor3f(1.0f,0.0f,0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-2+px,3-15,0);
	glVertex3f(2+px,3-15,0);
	glVertex3f(6+px,5-15,0);
	glVertex3f(-6+px,5-15,0);
	glEnd();
	glEnable(GL_LIGHTING);
}

//Function to draw a single brick
void treasure(GLfloat x,GLfloat y, GLfloat z)
{

	glDisable(GL_LIGHTING);
	glColor3f(1.0f,0.5f,0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(x,y,z);
	glVertex3f(x+3,y,z);
	glVertex3f(x+3,y+1,z);
	glVertex3f(x,y+1,z);
	glEnd();
	glColor3f(1.0f,1.0f,0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(x,y+1,z);
	glVertex3f(x+3,y+1,z);
	glVertex3f(x+2,y+2,z);
	glVertex3f(x+1,y+2,z);
	glEnd();
	glEnable(GL_LIGHTING);
}

// Function to draw the grid of bricks
void draw_treasures()
{

	int i,j;
	if(start == 0)
	{
		for(i = 1;i<=rows;i++)
		{
			for(j = 1;j<=columns;j++)
			{

				treasure_array[i][j].x = (GLfloat)(j*4*0.84);
				treasure_array[i][j].y = (GLfloat)(i*4*0.6) ;
			}
		}
	}


	glPushMatrix();
	glTranslatef(-19.5,3,0);

	for(i = 1;i<=rows;i+=1)
	{
		for(j = 1;j<=columns;j+=1)
		{

			if(treasure_array[i][j].x==0 || treasure_array[i][j].y ==0)
			{
				continue;
			}
			treasure(treasure_array[i][j].x,treasure_array[i][j].y,0);
		}
	}
	glPopMatrix();

}

//Function to print the score on the screen
void text( int sc)
{
	glDisable(GL_LIGHTING);
	char text[40];
	if(sc <40)
	sprintf(text,"SCORE: %d", sc);
	else
	{
	  sprintf(text,"You have won !!");
	  start = 0;
	  by = -11;
	  bx = 0;
	  dirx = 0;
	  diry = 0;
	  px = 0;

	}
	// The color
	glColor4f(1.0f,0.0f,0.0f,1.0f);
	// Position of the text to be printer
	glPushMatrix();
	glTranslatef(-3.25,2.50,0);
	glRasterPos3f(0, 0, 20);
	for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

//function for water
void water()
{
	glDisable(GL_LIGHTING);
	glColor3f(0.0f,0.0f,1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-20,-15,0);
	glVertex3f(20,-15,0);
	glVertex3f(20,-12,0);
	glVertex3f(-20,-12,0);
	glEnd();
	glEnable(GL_LIGHTING);
}

//The main display function
void display (void) {
	glClearColor (0.0,0.0,0.0,0.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0,0,0,0,0,-25,0,1,0);
	glTranslatef(0,0,-25);
	draw_boat();
	draw_treasures();
	water();
	text(score);
	glutSwapBuffers();
}

//function to take in keyboard entries
void keyboard (unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'd': px+=1; break;
		case 'a': px-=1; break;
		case 'q': exit(0); break;
		case 's':
		if(!start)
		{
			dirx = diry= 1;
			start = 1;
			score = 0;
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		break;
	}
	if(px>15)
	{
		px=15;
	}
	if(px<-15)
	{
		px=-15;
	}
	if(start== 0)
	{
		px=0;
	}
	glutPostRedisplay();
}

//function to turn on lights
void lightsOn()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

//fuction for reshape
void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
	glMatrixMode (GL_MODELVIEW);
}

//function for main
int main (int argc,char **argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (900, 900);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Treasure Hunt");
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	glEnable(GL_DEPTH_TEST);
    glutKeyboardFunc(keyboard);
	lightsOn();
	glutMainLoop ();
	return 0;
}
