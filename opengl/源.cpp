#include<GL/glut.h>  
#include <windows.h>
#define WIDTH 800  
#define HEIGHT 800  

static GLfloat angle = 0.0f;

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//创建透视效果视图  
	glMatrixMode(GL_PROJECTION); //操作投影矩阵  
	glLoadIdentity();  //当前矩阵设置为单位矩阵  
	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);  //得到透视效果 （可视角，高宽比，最近可视距离，最远可视距离）
	glMatrixMode(GL_MODELVIEW); //操作“模型视图”矩阵  
	glLoadIdentity();
	gluLookAt(0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//定义太阳光源，它是一种白色光源  
	{
		GLfloat sun_light_position[] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat sun_light_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat sun_light_diffuse[] = { 0.0f,0.0f,0.0f,0.0f };
		GLfloat sun_light_specular[] = { 1.0f,1.0f,1.0f,1.0f };

		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}

	//定义太阳的材质并绘制太阳  
	{
		GLfloat sun_mat_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat sun_mat_diffuse[] = { 0.0f,0.0f,0.0f,1.0f };
		GLfloat sun_mat_specular[] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat sun_mat_emission[] = { 0.9f,0.9f,0.0f,1.0f };
		GLfloat sun_mat_shininess = 0.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient); //环境变量  
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse); //散射模式  
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular); //镜面反射  
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission); //发射，散发喷射  
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);

		glutSolidSphere(2.0, 40, 32);
	}

	//定义地球材质并绘制地球  
	{
		GLfloat earth_mat_ambient[] = { 0.0f,0.5f,0.9f,1.0f };
		GLfloat earth_mat_diffuse[] = { 0.0f,0.5f,0.5f,1.0f };
		GLfloat earth_mat_specular[] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat earth_mat_emission[] = {0.0f,0.0f,0.0f,1.0f };
		GLfloat earth_mat_shininess = 5.0f; //镜面指数 0~128 越小越接近镜面

		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient); //环境变量  
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse); //散射模式  
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular); //镜面反射  
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission); //发射，散发喷射  
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

		glRotatef(angle, 0.0f, -1.0f, 0.0f);
		glTranslatef(5.0f, 0.0f, 0.0f);
		glutSolidSphere(1.0, 1000, 1000);//半径为 2,40 条纬线,32 条经线
	}
	glutSwapBuffers();
}

void myIdle()
{
	angle += 1.0f;
	if (angle >= 360.0f)
		angle = 0.0f;
	myDisplay();
	Sleep(20);
}

/*
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(200, 20);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("opengl光照演示");
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle); //回调  
	glutMainLoop();
	return 0;
}*/