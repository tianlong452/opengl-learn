#include "fun.h"
#define Pi 3.1415926
float STEP = 0.2,deg_step=0.5,view_dis = 5;
float a = 0, b = 0, c = 0;
double regx = 0, regy = 0,eyedeg=180;
CSkyBox m_SkyBox;

int loadimg(const string& filename) {
	cv::Mat img = cv::imread(filename, CV_LOAD_IMAGE_UNCHANGED);
	if (img.channels() != 3) {
		for (int i = 0; i < img.rows; ++i)
		{
			cout << i << "/" << img.rows << "\r";
			for (int j = 0; j < img.cols; ++j)
			{
				if (img.at<Vec4b>(i, j)[3] == 0)
				{
					img.at<Vec4b>(i, j)[1] = 0;
					img.at<Vec4b>(i, j)[2] = 0;
					img.at<Vec4b>(i, j)[0] = 0;
				}
			}
		}
	}
	else
	{
		cvtColor(img, img, CV_BGR2BGRA);
	}
	//resize(LandR, LandR, cv::Size(np2(LandR.cols), np2(LandR.rows)), 0, 0, cv::INTER_LINEAR);
	//cv::imwrite("..\\上前面.bmp", F);
	GLubyte* pixels;
	int pixellength = img.cols * img.rows * 4;
	pixels = new GLubyte[pixellength];
	memcpy(pixels, img.data, pixellength * sizeof(char));
	GLuint i;
	glGenTextures(1, &i);
	glBindTexture(GL_TEXTURE_2D, i);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, img.cols, img.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.cols,
		img.rows, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	img.release();
	return i;
}

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
void cube_tank_bottom(const GLuint &index, float x, float y, float z, float l, float w, float h) {
	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	//左面
	glColor4f(1.0f, 1.0, 1.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, loadimg("..//下侧面.bmp"));
	glTexCoord2f(1, 1); glVertex3f(x + l, y + 0, z + 0);
	glTexCoord2f(0.0f, 1); glVertex3f(x + l, y + w, z + 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + l, y + w, z + h);
	glTexCoord2f(1, 0.0f); glVertex3f(x + l, y + 0, z + h);
	//右面
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + 0, z + 0);
	glTexCoord2f(0.0f, 1); glVertex3f(x + 0, y + w, z + 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + 0, y + w, z + h);
	glTexCoord2f(1, 0.0f); glVertex3f(x + 0, y + 0, z + h);	
	//下面
/*
	glColor4f(0.0f, 1.0, 1.0, 0.0);
	 glVertex3f(x + 0, y + 0, z + 0);
	 glVertex3f(x + 0, y + 0, z + h);
	 glVertex3f(x + l, y + 0, z + h);
	 glVertex3f(x + l, y + 0, z + 0);*/
	//上面
	glBindTexture(GL_TEXTURE_2D, loadimg("..//下上面.bmp"));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + w, z + 0);
	glTexCoord2f(0, 1); glVertex3f(x + 0, y + w, z + h);
	glTexCoord2f(0, 0); glVertex3f(x + l, y + w, z + h);
	glTexCoord2f(1, 0); glVertex3f(x + l, y + w, z + 0);
	//背面
	glBindTexture(GL_TEXTURE_2D, loadimg("..//xia.png"));
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + 0, z + 0);
	glTexCoord2f(0, 1); glVertex3f(x + l, y + 0, z + 0);
	glTexCoord2f(0, 0); glVertex3f(x + l, y + w, z + 0);
	glTexCoord2f(1, 0); glVertex3f(x + 0, y + w, z + 0);
	glDisable(GL_BLEND);
	//前面
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + 0, z + h);
	glTexCoord2f(0, 1); glVertex3f(x + l, y + 0, z + h);
	glTexCoord2f(0, 0); glVertex3f(x + l, y + w, z + h);
	glTexCoord2f(1, 0); glVertex3f(x + 0, y + w, z + h);
	glEnd();
	glEndList();
}

void cube_tank_top(const GLuint &index, float x, float y, float z, float l, float w, float h) {
	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);

	//左面
	glColor4f(1.0f, 1.0, 1.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, loadimg("..\\上侧面.bmp"));
	glTexCoord2f(1, 1); glVertex3f(x + l, y + 0, z + 0);
	glTexCoord2f(0.0f, 1); glVertex3f(x + l, y + w, z + 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + l, y + w, z + h);
	glTexCoord2f(1, 0.0f); glVertex3f(x + l, y + 0, z + h);
	//右面
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + 0, z + 0);
	glTexCoord2f(0.0f, 1); glVertex3f(x + 0, y + w, z + 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + 0, y + w, z + h);
	glTexCoord2f(1, 0.0f); glVertex3f(x + 0, y + 0, z + h);
	//下面
	glVertex3f(x + 0, y + 0, z + 0);
	glVertex3f(x + 0, y + 0, z + h);
	glVertex3f(x + l, y + 0, z + h);
	glVertex3f(x + l, y + 0, z + 0);
	//上面
	glBindTexture(GL_TEXTURE_2D, loadimg("..\\上上面.bmp"));
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + w, z + 0);
	glTexCoord2f(0, 1); glVertex3f(x + 0, y + w, z + h);
	glTexCoord2f(0, 0); glVertex3f(x + l, y + w, z + h);
	glTexCoord2f(1, 0); glVertex3f(x + l, y + w, z + 0);
	//背面
	glBindTexture(GL_TEXTURE_2D, loadimg("..\\上背面.bmp"));
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + 0, z + 0);
	glTexCoord2f(0, 1); glVertex3f(x + l, y + 0, z + 0);
	glTexCoord2f(0, 0); glVertex3f(x + l, y + w, z + 0);
	glTexCoord2f(1, 0); glVertex3f(x + 0, y + w, z + 0);
	//前面
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + 0, z + h);
	glTexCoord2f(0, 1); glVertex3f(x + l, y + 0, z + h);
	glTexCoord2f(0, 0); glVertex3f(x + l, y + w, z + h);
	glTexCoord2f(1, 0); glVertex3f(x + 0, y + w, z + h);
	glEnd();
	glEndList();
}
void ground(const GLuint &index, float x, float y, float z, float l, float w, float h) {

	//OpenCV读取图像
	cv::Mat I = cv::imread("E:\\cpp\\opengl\\b.bmp");
	//resize(I, I, cv::Size(1024, 1024), 0, 0, cv::INTER_LINEAR);
	cvtColor(I, I, CV_BGR2BGRA);
	//设置长宽
	int width = I.cols;
	int height = I.rows;
	GLubyte* pixels;
	//设置指针长度
	int pixellength = width * height * 4;
	//开辟指针空间
	pixels = new GLubyte[pixellength];
	//图像指针复制
	memcpy(pixels, I.data, pixellength * sizeof(char));
	GLuint i;
	glGenTextures(1, &i);                        /**< 生成一个纹理对象名称 */

	glBindTexture(GL_TEXTURE_2D, i);             /**< 创建纹理对象 */
	/** 控制滤波: */
	/*
	其中GL_TEXTURE_WRAP_S，GL_TEXTURE_WRAP_T通常可设置为GL_REPEAT或GL_CLAMP两种方式。
	当待填充的多边形大于纹理的时候，GL_REPEAT表示多余的部分用重复的方式填充；GL_CLAMP表示多余的部分用相连边缘的相邻像素填充。
	在实际绘制中，我们一般采用GL_CLAMP_EDGE来处理，这就消除了接缝处的细线，增强了天空盒的真实感。
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/** 创建纹理 */
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, I.cols,
		I.rows, GL_RGBA, GL_UNSIGNED_BYTE,pixels);
	glNewList(index, GL_COMPILE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, i);
	glBegin(GL_QUADS);
	glTexCoord2f(h, h);glVertex3f(-l, y + 0, -l);
	glTexCoord2f(0.0f, h);glVertex3f(l, y + 0, -l);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(l, y + 0, l);
	glTexCoord2f(h, 0.0f);glVertex3f(-l, y + 0, l);
	glEnd();
	glDisable(GL_BLEND);
	glEndList();
	delete pixels;
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
	view_dis = 5>view_dis?5:view_dis;
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
		STEP = STEP>0.5?0.5:STEP;
		double reg = regx * Pi / 180;
		bool keyw = key == GLFW_KEY_W;
		a += (keyw ? sin(reg) : -sin(reg))*STEP;
		c += (keyw ? cos(reg) : -cos(reg))*STEP;
	}
	if ((key == GLFW_KEY_D || key == GLFW_KEY_A) && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		deg_step = ((action == GLFW_REPEAT) ? deg_step + 0.5 : 1);
		deg_step = deg_step>5?5:deg_step;
		regx -= key == GLFW_KEY_D ? deg_step: -deg_step;
	}
	
	myDisplay(window);
}

int np2(int v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v++;
	v += (v == 0); // handle v == 0 edge case
	return v;
}