#include "fun.h"
#define Pi 3.1415926
const int timer = 1000 / frame;
const double d2r = Pi / 180;
float STEP = 0.2,deg_step=0.5,view_dis = 10;
float a = 0, b = 0, c = 0;
double regx = 0, regy = 0, eyedegv = 180 ,eyedegh = 20;
int key1 = 0, key2 = 0 ,mkey=8;

int loadimg(const string& filename) {
	cv::Mat img = cv::imread(filename, CV_LOAD_IMAGE_UNCHANGED);
	bool b = img.channels() == 3;
	if(b)
		cvtColor(img, img, CV_BGR2RGB);
	else
		cvtColor(img, img, CV_BGRA2RGBA);
	GLuint i;
	glGenTextures(1, &i);
	glBindTexture(GL_TEXTURE_2D, i);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, b? GL_RGB:GL_RGBA, img.cols,
		img.rows, b ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, img.data);
	img.release();
	return i;
}

void myDisplay(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(a, b, c);
	glCallList(5); // sky box
	glPopMatrix();
	
	glPushMatrix();
	glCallList(2); //ground
	glPopMatrix(); 
	glPushMatrix();
	glTranslatef(a, b, c);			
	glRotatef(regx, 0, 1, 0);
	glCallList(1); //tank bottom
	glPopMatrix();
	glPushMatrix();
	glTranslatef(a, b, c);
	glRotatef(regx + regy, 0, 1, 0);
	glCallList(4);
	glCallList(3); // tank top
	glPopMatrix();
	glLoadIdentity();
	double sv = sin(eyedegv*d2r), cv = cos(eyedegv*d2r), sh = sin(eyedegh*d2r), ch = cos(eyedegh*d2r);
	gluLookAt(a + view_dis * sv * ch,  view_dis*sh  , c + view_dis * cv * ch		  ,a, 2, c,	      0, ch>0?1:-1, 0);
	glfwSwapBuffers(window);
	//glfwSwapBuffers(window);
}

void creat_cube_list(const GLuint &index, float x, float y, float z, float l, float w, float h, 
	float dx, float dz,vector<string> files) {
	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	//左面
	glColor4f(1.0f, 1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, loadimg(files[0]));
	glTexCoord2f(1, 1.0f); glVertex3f(x + l, y + 0, z + 0);
	glTexCoord2f(1, 0); glVertex3f(x + l - dx, y + w, z + 0 + dz);
	glTexCoord2f(0, 0); glVertex3f(x + l - dx, y + w, z + h - dz);
	glTexCoord2f(0, 1.0f); glVertex3f(x + l, y + 0, z + h);
	//右面
	if(files[0]!=files[1])
		glBindTexture(GL_TEXTURE_2D, loadimg(files[1]));
	glTexCoord2f(0, 1); glVertex3f(x + 0, y + 0, z + 0);
	glTexCoord2f(0, 0); glVertex3f(x + 0 + dx, y + w, z + 0 + dz);
	glTexCoord2f(1, 0); glVertex3f(x + 0 + dx, y + w, z + h - dz);
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + 0, z + h);
	//上面
	glBindTexture(GL_TEXTURE_2D, loadimg(files[2]));
	glTexCoord2f(1, 1); glVertex3f(x + 0 + dx, y + w, z + 0 + dz);
	glTexCoord2f(0, 1); glVertex3f(x + 0 + dx, y + w, z + h - dz);
	glTexCoord2f(0, 0); glVertex3f(x + l - dx, y + w, z + h - dz);
	glTexCoord2f(1, 0); glVertex3f(x + l- dx, y + w, z + 0 + dz);
	//前面
	glBindTexture(GL_TEXTURE_2D, loadimg(files[3]));
	glTexCoord2f(0, 1); glVertex3f(x + 0, y + 0, z + h );
	glTexCoord2f(1, 1); glVertex3f(x + l , y + 0, z + h );
	glTexCoord2f(1, 0); glVertex3f(x + l - dx, y + w, z + h - dz);
	glTexCoord2f(0, 0); glVertex3f(x + 0 + dx, y + w, z + h - dz);
	//背面
	if (files[3] != files[4])
	glBindTexture(GL_TEXTURE_2D, loadimg(files[4]));
	glTexCoord2f(1, 1); glVertex3f(x + 0, y + 0, z + 0);
	glTexCoord2f(0, 1); glVertex3f(x + l, y + 0, z + 0);
	glTexCoord2f(0, 0); glVertex3f(x + l - dx, y + w, z + 0 + dz);
	glTexCoord2f(1, 0); glVertex3f(x + 0 + dx, y + w, z + 0+ dz) ;
	//下面
	/*glVertex3f(x + 0, y + 0, z + 0);
	glVertex3f(x + 0, y + 0, z + h);
	glVertex3f(x + l, y + 0, z + h);
	glVertex3f(x + l, y + 0, z + 0);*/
	glEnd();
	glEndList();
}
void ground(const GLuint &index, float l, float y, float n,string filename) {
	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, loadimg(filename));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glColor4f(1.0f, 1.0, 1.0, 1.0);
	glTexCoord2f(n, n);glVertex3f(-l, y + 0, -l);
	glTexCoord2f(0.0f, n);glVertex3f(l, y + 0, -l);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(l, y + 0, l);
	glTexCoord2f(n, 0.0f);glVertex3f(-l, y + 0, l);
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
}
void mouse_button_callback1(GLFWwindow* window, int button, int action, int mods) {
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
			Sleep(timer);
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
			eyedegv += (xpos - xposp)/10;
			xposp = xpos;
			Sleep(timer);
			myDisplay(window);
		}
	}
}
void do_mouse(GLFWwindow* window,int mkey, int dx, int dy) {
	if (mkey == GLFW_MOUSE_BUTTON_LEFT)
	{
		regy += dx / 3;
	}
	if (mkey == GLFW_MOUSE_BUTTON_RIGHT)
	{
			eyedegv += (dx) / 3;
			eyedegh += dy / 6;
			eyedegh = eyedegh > 10 ? eyedegh : 10;
			eyedegh = eyedegh < 170 ? eyedegh : 170;
			//eyedegh = static_cast<int>(eyedegh)%180;
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS)
		mkey = button;
		if (action == GLFW_RELEASE)
		mkey = 8;
}
void scroll_callback(GLFWwindow* window, double x, double y) {
	if (y == 1)
		view_dis += 0.5;
	if (y == -1)
		view_dis -= 0.5;
	view_dis = 5>view_dis?5:view_dis;
}
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {

}
void key_callback1(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
	// 关闭应用程序
	glfwPollEvents();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		exit(0);
	if (key == GLFW_KEY_W || key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		STEP = action == GLFW_REPEAT ? STEP+0.1 : 0.2;
		STEP = STEP>0.4?0.4:STEP;
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
}
void dokey(int key) {
	if (key == GLFW_KEY_W || key == GLFW_KEY_S )
	{
		STEP = 0.8/*action == GLFW_REPEAT ? STEP + 0.1 :*/ ;
		STEP = STEP > 0.8 ? 0.8 : STEP;
		double reg = regx * Pi / 180;
		bool keyw = key == GLFW_KEY_W;
		a += (keyw ? sin(reg) : -sin(reg))*STEP;
		c += (keyw ? cos(reg) : -cos(reg))*STEP;
	}
	if ((key == GLFW_KEY_D || key == GLFW_KEY_A))
	{
		deg_step = (/*(action == GLFW_REPEAT) ? deg_step + 0.5 : */1);
		deg_step = deg_step > 5 ? 5 : deg_step;
		regx -= key == GLFW_KEY_D ? deg_step : -deg_step;
		eyedegv -= key== GLFW_KEY_D ? deg_step : -deg_step;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		exit(0);
	if (action == GLFW_PRESS)
		if (key1 == 0)
			key1 = key;
		else
			key2 = key;

	if (GLFW_RELEASE == action) {
		if (key1 == key) {
			key1 = key2, key2 = 0;
		}
		if (key2==key)
			key2 = 0;
	}
}

void mainloop(GLFWwindow *window)
{
	while (!glfwWindowShouldClose(window))
	{
		myDisplay(window);
		double xpos, ypos, xposp, yposp;
		glfwGetCursorPos(window, &xposp, &yposp);
		Sleep(timer);
		glfwGetCursorPos(window, &xpos, &ypos);
		do_mouse(window, mkey, xpos - xposp, ypos - yposp);
		if (key1) dokey(key1);
		if (key2)  dokey(key2);
		glfwPollEvents();
	}
	glfwTerminate();
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