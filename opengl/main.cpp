#include "fun.h"
int init(GLFWwindow **windowp)
{
	/** �û��Զ���ĳ�ʼ������ */
	if (!glfwInit())
		exit(-1);
	int monitorCount;
	bool isFullScreen =true;
	GLFWmonitor** pMonitor = isFullScreen ? glfwGetMonitors(&monitorCount) : NULL;
	*windowp = glfwCreateWindow(1400, 850, "tank", pMonitor[1], nullptr);
	GLFWwindow *window = *windowp;
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); /*�Ե�ǰ���ڲ���*/

	int width, height;
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST); //������Ȳ���
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_2D); //��������ӳ��
	glEnable(GL_BLEND); //������ɫ���
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);

	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glfwSetCursorPosCallback(window, cursor_pos_callback);//����¼��ص�
	glfwSetKeyCallback(window, key_callback);//�����¼��ص�
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &width, &height);
	framebuffer_size_callback(window, width, height);
	return true;
}

int main(int argc, char* argv[])
{
	/*string filename = "../�ϲ���";
	Mat img = imread(filename+".png", CV_LOAD_IMAGE_UNCHANGED);
	flip(img, img, 1);
	/ *resize(img, img, cv::Size(np2(img.cols), np2(img.rows)), 0, 0, cv::INTER_LINEAR);
	cvtColor(img, img, CV_BGR2BGRA);
	for (int i=0;i<img.rows;++i)
	{
		cout << i <<"/"<< img.rows << "\r";
		for (int j=0;j<img.cols;++j)
		{
			if (img.at<Vec4b>(i,j)[1]>200 && img.at<Vec4b>(i, j)[2]>200)
			{
				img.at<Vec4b>(i, j)[3] = 0;
			}
		}
	}* /
	imwrite(filename+"1.png", img);
	getchar();
	exit(0);*/
	GLFWwindow *window;
	init(&window);

	GLuint index = glGenLists(5);
	ground(index + 1, 1024, 0, 100,"../c.jpg");
	//cube_tank_bottom(index, -0.5, 0, -1,   1, 0.5, 2);
	vector<string> bottom = { "../�²���.png","../�²���.png","../������.png","../��ǰ��.png","../��ǰ��.png" };
	creat_cube_list(index, -0.5, 0.0, -0.85,   1, 0.5, 1.7,   0.0, -0.15,bottom);
	vector<string> top = { "../������.png","../������.png","../������.png","../��ǰ��.png","../�ϱ���.png" };
	creat_cube_list(index + 2, -0.25, 0.5, -0.5, 0.5, 0.25, 1,0.1,0.1,top);
	creat_cube_list(index + 3, 0, 0.6, 0, 0.05, 0.05, 1.5,0,0,top);
	vector< string> jpgName = { "left.jpg","right.jpg","top.jpg","front.jpg","back.jpg","bottom.jpg"};
	vector< string> bmpName = { "../left.bmp","../right.bmp","../top.bmp","../front.bmp","../back.bmp","../bottom.bmp" };
	creat_cube_list(index + 4, -512, -512, -512, 1024, 1024, 1024, 0, 0, jpgName);
	mainloop(window);
	return 0;
}

