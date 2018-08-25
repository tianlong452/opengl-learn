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
	//cv::imwrite("..\\��ǰ��.bmp", F);
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
	//����
	glColor4f(1.0f, 1.0, 1.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, loadimg("..//�²���.bmp"));
	glTexCoord2f(1, 1); glVertex3f(x + l, y + 0, z + 0);
	glTexCoord2f(0.0f, 1); glVertex3f(x + l, y + w, z + 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + l, y + w, z + h);
	glTexCoord2f(1, 0.0f); glVertex3f(x + l, y + 0, z + h);
	//����
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + 0, z + 0);
	glTexCoord2f(0.0f, 1); glVertex3f(x + 0, y + w, z + 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + 0, y + w, z + h);
	glTexCoord2f(1, 0.0f); glVertex3f(x + 0, y + 0, z + h);	
	//����
/*
	glColor4f(0.0f, 1.0, 1.0, 0.0);
	 glVertex3f(x + 0, y + 0, z + 0);
	 glVertex3f(x + 0, y + 0, z + h);
	 glVertex3f(x + l, y + 0, z + h);
	 glVertex3f(x + l, y + 0, z + 0);*/
	//����
	glBindTexture(GL_TEXTURE_2D, loadimg("..//������.bmp"));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + w, z + 0);
	glTexCoord2f(0, 1); glVertex3f(x + 0, y + w, z + h);
	glTexCoord2f(0, 0); glVertex3f(x + l, y + w, z + h);
	glTexCoord2f(1, 0); glVertex3f(x + l, y + w, z + 0);
	//����
	glBindTexture(GL_TEXTURE_2D, loadimg("..//xia.png"));
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + 0, z + 0);
	glTexCoord2f(0, 1); glVertex3f(x + l, y + 0, z + 0);
	glTexCoord2f(0, 0); glVertex3f(x + l, y + w, z + 0);
	glTexCoord2f(1, 0); glVertex3f(x + 0, y + w, z + 0);
	glDisable(GL_BLEND);
	//ǰ��
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

	//����
	glColor4f(1.0f, 1.0, 1.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, loadimg("..\\�ϲ���.bmp"));
	glTexCoord2f(1, 1); glVertex3f(x + l, y + 0, z + 0);
	glTexCoord2f(0.0f, 1); glVertex3f(x + l, y + w, z + 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + l, y + w, z + h);
	glTexCoord2f(1, 0.0f); glVertex3f(x + l, y + 0, z + h);
	//����
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + 0, z + 0);
	glTexCoord2f(0.0f, 1); glVertex3f(x + 0, y + w, z + 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + 0, y + w, z + h);
	glTexCoord2f(1, 0.0f); glVertex3f(x + 0, y + 0, z + h);
	//����
	glVertex3f(x + 0, y + 0, z + 0);
	glVertex3f(x + 0, y + 0, z + h);
	glVertex3f(x + l, y + 0, z + h);
	glVertex3f(x + l, y + 0, z + 0);
	//����
	glBindTexture(GL_TEXTURE_2D, loadimg("..\\������.bmp"));
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + w, z + 0);
	glTexCoord2f(0, 1); glVertex3f(x + 0, y + w, z + h);
	glTexCoord2f(0, 0); glVertex3f(x + l, y + w, z + h);
	glTexCoord2f(1, 0); glVertex3f(x + l, y + w, z + 0);
	//����
	glBindTexture(GL_TEXTURE_2D, loadimg("..\\�ϱ���.bmp"));
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + 0, z + 0);
	glTexCoord2f(0, 1); glVertex3f(x + l, y + 0, z + 0);
	glTexCoord2f(0, 0); glVertex3f(x + l, y + w, z + 0);
	glTexCoord2f(1, 0); glVertex3f(x + 0, y + w, z + 0);
	//ǰ��
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + 0, z + h);
	glTexCoord2f(0, 1); glVertex3f(x + l, y + 0, z + h);
	glTexCoord2f(0, 0); glVertex3f(x + l, y + w, z + h);
	glTexCoord2f(1, 0); glVertex3f(x + 0, y + w, z + h);
	glEnd();
	glEndList();
}
void ground(const GLuint &index, float x, float y, float z, float l, float w, float h) {

	//OpenCV��ȡͼ��
	cv::Mat I = cv::imread("E:\\cpp\\opengl\\b.bmp");
	//resize(I, I, cv::Size(1024, 1024), 0, 0, cv::INTER_LINEAR);
	cvtColor(I, I, CV_BGR2BGRA);
	//���ó���
	int width = I.cols;
	int height = I.rows;
	GLubyte* pixels;
	//����ָ�볤��
	int pixellength = width * height * 4;
	//����ָ��ռ�
	pixels = new GLubyte[pixellength];
	//ͼ��ָ�븴��
	memcpy(pixels, I.data, pixellength * sizeof(char));
	GLuint i;
	glGenTextures(1, &i);                        /**< ����һ������������� */

	glBindTexture(GL_TEXTURE_2D, i);             /**< ����������� */
	/** �����˲�: */
	/*
	����GL_TEXTURE_WRAP_S��GL_TEXTURE_WRAP_Tͨ��������ΪGL_REPEAT��GL_CLAMP���ַ�ʽ��
	�������Ķ���δ��������ʱ��GL_REPEAT��ʾ����Ĳ������ظ��ķ�ʽ��䣻GL_CLAMP��ʾ����Ĳ�����������Ե������������䡣
	��ʵ�ʻ����У�����һ�����GL_CLAMP_EDGE��������������˽ӷ촦��ϸ�ߣ���ǿ����պе���ʵ�С�
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/** �������� */
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
	// ���û�����ESC��,��������window���ڵ�WindowShouldClose����Ϊtrue
	// �ر�Ӧ�ó���
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