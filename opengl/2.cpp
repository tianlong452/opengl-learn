#include<GL/glut.h>  
#include <glfw/glfw3.h>
#include <glad/glad.h>
#include <iostream>
using namespace std;

float a = 0, b = 0 , c = 0;
int regx = 0,regy=0;

void cube(const GLuint &index, float x, float y, float z, float l, float w, float h);

void myDisplay(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//gluLookAt(10, 10, 100, 0, 0, 0, 0, 1, 0);
	glPushMatrix();
	glTranslatef(a, b, c);				//移动，参数含义(x轴位移,y轴位移,z轴位移)
	glRotatef(regx, 1, 0, 0);				//旋转，参数含义(旋转量,x轴,y轴,z轴)
	glRotatef(regy, 0, 1, 0);
	glBegin(GL_QUADS);
	glCallList(1);
	glEnd();
	glPopMatrix();
	glfwSwapBuffers(window);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double x, double y);
void framebuffer_size_callback(GLFWwindow* window, int w, int h);
int main(int argc, char* argv[])
{
		if (!glfwInit())
			exit(-1);
		GLFWwindow* window = glfwCreateWindow(700, 700, "tank", nullptr, nullptr);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window); /*对当前窗口操作*/

		//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		// glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}
	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 1.0f, 0.3f, 1.0f);
	//鼠标事件回调
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	//键盘事件回调
	glfwSetKeyCallback(window, key_callback);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &width, &height);
	framebuffer_size_callback(window, width, height);


	GLuint index = glGenLists(1);
	glColor4f(1.0f, 0.0, 0.0, 1.0);
	cube(index, -0.5, -0.5, -0.5, 1, 1, 1);
	while (!glfwWindowShouldClose(window))
	{
		myDisplay(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;

}

void cube(const GLuint &index,float x,float y,float z,float l ,float w,float h) {
	glNewList(index, GL_COMPILE);
	glVertex3f(x + 0,y + 0,z + 0);
	glVertex3f(x + l, y + 0, z + 0);
	glVertex3f(x + l, y + w, z + 0);
	glVertex3f(x + 0, y + w, z + 0);

	glVertex3f(x + l, y + 0, z + 0);
	glVertex3f(x + l, y + w, z + 0);
	glVertex3f(x + l, y + w, z + h);
	glVertex3f(x + l, y + 0, z + h);

	glVertex3f(x + 0, y + 0, z + 0);
	glVertex3f(x + 0, y + w, z + 0);
	glVertex3f(x + 0, y + w, z + h);
	glVertex3f(x + 0, y + 0, z + h);

	glVertex3f(x + 0, y + 0, z + 0);
	glVertex3f(x + 0, y + 0, z + h);
	glVertex3f(x + l, y + 0, z + h);
	glVertex3f(x + l, y + 0, z + 0);

	glVertex3f(x + 0, y + w, z + 0);
	glVertex3f(x + 0, y + w, z + h);
	glVertex3f(x + l, y + w, z + h);
	glVertex3f(x + l, y + w, z + 0);

	glVertex3f(x + 0, y + 0, z + h);
	glVertex3f(x + l, y + 0, z + h);
	glVertex3f(x + l, y + w, z + h);
	glVertex3f(x + 0, y + w, z + h);
	glEndList();
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h); // Setup viewport
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){}
void scroll_callback(GLFWwindow* window, double x, double y){
	if (y == 1)
		c += 0.01;
	if (y == -1)
		c -= 0.01;
	myDisplay(window);
}
static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	cout << xpos << " , " << ypos << endl;
	regx = xpos/4;
	regy = ypos/4;
	myDisplay(window);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
	// 关闭应用程序
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		b += 0.01;
		myDisplay(window);
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		b -= 0.01;
		myDisplay(window);
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		a += 0.01;
		myDisplay(window);
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		a -= 0.01;
		myDisplay(window);
	}
}