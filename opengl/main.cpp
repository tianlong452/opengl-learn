#include "fun.h"
#include   <time.h>
void init(void)
{
	/** 用户自定义的初始化过程 */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	/** 启用纹理 */
	glEnable(GL_TEXTURE_2D);

	/** 初始化天空 */
	if (!m_SkyBox.Init())
	{
		exit(0);
	}
}

int main(int argc, char* argv[])
{
/*
	Mat img = imread(".\\下前面.bmp");
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
	}
	imwrite("xia.png", img);
	getchar();
	exit(0);*/
		if (!glfwInit())
			exit(-1);
		GLFWwindow* window = glfwCreateWindow(1440, 900, "tank", nullptr, nullptr);
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
	glEnable(GL_ALPHA_TEST);
	glClearColor(0.0f, 0.8f, 1.0f, 0.8f);
	init();
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
	GLuint index = glGenLists(5);
	ground(index + 1, -0.5, 0.0, -0.5, 1024, 1, 100);
	cube_tank_bottom(index, -0.5, 0, -1, 1, 0.5, 2);
	cube_tank_top(index + 2, -0.25, 0.5, -0.5, 0.5, 0.25, 1);
	cube_tank_top(index + 3, 0, 0.6, 0, 0.05, 0.05, 1.5);
	m_SkyBox.CreateSkyBox(0, 0, 0, 1, 1, 1);
	while (!glfwWindowShouldClose(window))
	{
		myDisplay(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;

}

