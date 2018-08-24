#include "fun.h"
#define Pi 3.1415926
float STEP = 0.2,deg_step=0.5,view_dis = 20;
float a = 0, b = 0, c = 0;
double regx = 0, regy = 0,eyedeg=0;
CSkyBox m_SkyBox;
void myDisplay(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(a, b, c);
	glCallList(5);
	glPopMatrix();
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
	glPopMatrix();
	glPushMatrix();
	glCallList(2);
	glPopMatrix(); 
	glLoadIdentity();
	gluLookAt(a+view_dis*sin(eyedeg*Pi/180), 5, c+view_dis*cos(eyedeg*Pi / 180),   a, 2, c,   0, 1, 0);
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
	CbmpLoader c;
	c.LoadBitmapa((string("E:\\cpp\\opengl\\") + "b.bmp").c_str());
	glGenTextures(1, &c.ID);                        /**< 生成一个纹理对象名称 */

	glBindTexture(GL_TEXTURE_2D, c.ID);             /**< 创建纹理对象 */
	/** 控制滤波: */
	/*
	其中GL_TEXTURE_WRAP_S，GL_TEXTURE_WRAP_T通常可设置为GL_REPEAT或GL_CLAMP两种方式。
	当待填充的多边形大于纹理的时候，GL_REPEAT表示多余的部分用重复的方式填充；GL_CLAMP表示多余的部分用相连边缘的相邻像素填充。
	在实际绘制中，我们一般采用GL_CLAMP_EDGE来处理，这就消除了接缝处的细线，增强了天空盒的真实感。
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/** 创建纹理 */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, c.imageWidth,
		c.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
		c.image);
	glNewList(index, GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, c.ID);
	glBegin(GL_QUADS);
	glTexCoord2f(h, h);glVertex3f(-l, y + 0, -l);
	glTexCoord2f(0.0f, h);glVertex3f(l, y + 0, -l);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(l, y + 0, l);
	glTexCoord2f(h, 0.0f);glVertex3f(-l, y + 0, l);
	glEnd();
	glEndList();
}
void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(view_dis, 5.0,view_dis, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
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
			regy += (xpos - xposp)/3;
			xposp = xpos;
			myDisplay(window);
		}
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		glfwGetCursorPos(window, &xposp, &yposp);
		while (GLFW_RELEASE != glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
		{
			double xpos, ypos;
			glfwPollEvents();
			glfwGetCursorPos(window, &xpos, &ypos);
			eyedeg += (xpos - xposp)/10;
			xposp = xpos;
			myDisplay(window);
		}
	}
}
void scroll_callback(GLFWwindow* window, double x, double y) {
	if (y == 1)
		view_dis += 0.1;
	if (y == -1)
		view_dis -= 0.1;
	view_dis = max(20, view_dis);
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
	if (key == GLFW_KEY_W || key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		STEP = action == GLFW_REPEAT ? STEP+0.1 : 0.2;
		STEP = min(STEP, 0.5);
		cout << STEP << endl;
		double reg = regx * Pi / 180;
		bool keyw = key == GLFW_KEY_W;
		a += (keyw ? sin(reg) : -sin(reg))*STEP;
		c += (keyw ? cos(reg) : -cos(reg))*STEP;
	}
	if ((key == GLFW_KEY_D || key == GLFW_KEY_A) && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		deg_step = ((action == GLFW_REPEAT) ? deg_step + 0.5 : 1);
		deg_step = min(deg_step, 5);
		regx -= key == GLFW_KEY_D ? deg_step: -deg_step;
	}
	
	myDisplay(window);
}