#include<GL/glut.h>  
#include<math.h>  
#include<windows.h>  

#define WIDTH 400  
#define HEIGHT 400  

#define ColoredVertex(c,v) do{glColor3fv(c);glVertex3fv(v);}while(0)  

GLfloat angle = 0.0f;

void myDisplay()
{
	static int list = 0;
	if (list == 0)
	{
		GLfloat
			PointA[] = { 0.5f,-sqrt(6.0f) / 12,-sqrt(3.0f) / 6 },
			PointB[] = { -0.5f,-sqrt(6.0f) / 12,-sqrt(3.0f) / 6 },
			PointC[] = { 0.0f,-sqrt(6.0f) / 12,sqrt(3.0f) / 3 },
			PointD[] = { 0.0f,sqrt(6.0f) / 4,0 };
		GLfloat
			ColorR[] = { 1,0,0 ,0},
			ColorG[] = { 0,1,0 ,1},
			ColorB[] = { 0,0,1 ,1},
			ColorY[] = { 1,1,0 ,1};

		list = glGenLists(1); //申请1个显示列表名，并赋值给刚才创建的现实列表变量
		glEnable(GL_ALPHA_TEST);
		glNewList(list, GL_COMPILE);
		glBegin(GL_TRIANGLES);
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorB, PointC);

		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorB, PointC);
		ColoredVertex(ColorY, PointD);

		ColoredVertex(ColorB, PointC);
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorY, PointD);

		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorY, PointD);
		glEnd();
		glEndList();
		glEnable(GL_DEPTH_TEST);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(angle, 1, 0.5, 0);
	glCallList(list);
	glPopMatrix();
	glutSwapBuffers();
}

void myIdle()
{
	++angle;
	if (angle >= 360.0f)
		angle = 0.0f;
	Sleep(1000 / 10);
	myDisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(400, 400);
	glutCreateWindow("study");
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle);
	glutMainLoop();
	return 0;
}