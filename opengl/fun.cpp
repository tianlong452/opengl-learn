#include "fun.h"
#define Pi 3.1415926
float a = 0, b = 0, c = 0;
int regx = 0, regy = 0;
void myDisplay(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(a, b, c);
	glRotatef(regx + regy, 0, 1, 0);
	glCallList(4);
	glCallList(3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(a, b, c);			
	glRotatef(regx, 0, 1, 0);
	glCallList(1);
	gluLookAt(a-0.0, 5.0, c-10.0,   0.0, -1.0, 0.0,   0.0, 1.0, 0.0);
	glPopMatrix();
	glPushMatrix();
	glCallList(2);
	glPopMatrix();
	glfwSwapBuffers(window);
}
void cube(const GLuint &index, float x, float y, float z, float l, float w, float h) {
	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0, 0.0, 1.0);
	glVertex3f(x + 0, y + 0, z + 0);
	glVertex3f(x + l, y + 0, z + 0);
	glVertex3f(x + l, y + w, z + 0);
	glVertex3f(x + 0, y + w, z + 0);

	glColor4f(1.0f, 0.0, 0.0, 1.0);
	glVertex3f(x + l, y + 0, z + 0);
	glVertex3f(x + l, y + w, z + 0);
	glVertex3f(x + l, y + w, z + h);
	glVertex3f(x + l, y + 0, z + h);

	glColor4f(1.0f, 0.0, 0.0, 1.0);
	glVertex3f(x + 0, y + 0, z + 0);
	glVertex3f(x + 0, y + w, z + 0);
	glVertex3f(x + 0, y + w, z + h);
	glVertex3f(x + 0, y + 0, z + h);

	glColor4f(0.0f, 1.0, 0.0, 1.0);
	glVertex3f(x + 0, y + 0, z + 0);
	glVertex3f(x + 0, y + 0, z + h);
	glVertex3f(x + l, y + 0, z + h);
	glVertex3f(x + l, y + 0, z + 0);

	glColor4f(0.0f, 0.0, 1.0, 1.0);
	glVertex3f(x + 0, y + w, z + 0);
	glVertex3f(x + 0, y + w, z + h);
	glVertex3f(x + l, y + w, z + h);
	glVertex3f(x + l, y + w, z + 0);

	glColor4f(0.0f, 1.0, 1.0, 1.0);
	glVertex3f(x + 0, y + 0, z + h);
	glVertex3f(x + l, y + 0, z + h);
	glVertex3f(x + l, y + w, z + h);
	glVertex3f(x + 0, y + w, z + h);
	glEnd();
	glEndList();
}
void ground(const GLuint &index, float x, float y, float z, float l, float w, float h) {
	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	glColor4f(1.0f, 1.0, 0.0, 1.0);
	glVertex3f(-10, y + 0, -20);
	glColor4f(1.0f, 1.0, 0.0, 1.0);
	glVertex3f(10, y + 0, -20);
	glColor4f(1.0f, 1.0, 1.0, 1.0);
	glVertex3f(10, y + 0, 10);
	glColor4f(1.0f, 1.0, 1.0, 1.0);
	glVertex3f(-10, y + 0, 10);
	glEnd();
	glEndList();
}
void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0,-10.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	double xposp, yposp;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		glfwGetCursorPos(window, &xposp, &yposp);
		while (GLFW_RELEASE != glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
		{
			double xpos, ypos;
			glfwPollEvents();
			glfwGetCursorPos(window, &xpos, &ypos);
			regy += (xpos - xposp);
			regy %= 360;
			xposp = xpos;
			myDisplay(window);
		}
	}
}
void scroll_callback(GLFWwindow* window, double x, double y) {
	if (y == 1)
		c += 0.01;
	if (y == -1)
		c -= 0.01;
	myDisplay(window);
}
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {

}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
	// 关闭应用程序
	glfwPollEvents();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		exit(0);
	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		double reg = regx * Pi / 180;
		a += sin(reg)*0.1;
		c += cos(reg)*0.1;
		myDisplay(window);
	}
	if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		double reg = regx * Pi / 180;
		a -= sin(reg)*0.1;
		c -= cos(reg)*0.1;
		myDisplay(window);
	}
	if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		regx -= 5;
		myDisplay(window);
	}
	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		regx += 5;
		myDisplay(window);
	}
}