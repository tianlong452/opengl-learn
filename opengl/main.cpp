#include "fun.h"
#include   <time.h>   
int main(int argc, char* argv[])
{
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
	glClearColor(0.0f, 0.8f, 1.0f, 0.8f);
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


	GLuint index = glGenLists(4);
	cube(index, -0.5, -0.5, -1, 1, 0.5, 2);
	ground(index+1, -0.5, -0.5, -0.5, 1, 1, 1);
	cube(index + 2, -0.25, 0, -0.5, 0.5, 0.25, 1);
	cube(index + 3, 0, 0.1, 0, 0.05, 0.05, 1.5);
	while (!glfwWindowShouldClose(window))
	{
		myDisplay(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;

}

