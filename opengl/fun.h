#pragma once
#include<GL/glut.h>  
#include <glfw/glfw3.h>
#include <glad/glad.h>
#include <math.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
using namespace cv;
using namespace std;

#define frame 50

void creat_cube_list(const GLuint &index, float x, float y, float z, float l, float h, float w
	,float dx, float dz, vector<string> files);
void ground(const GLuint &index, float x, float y, float z, string filename);

void myDisplay(GLFWwindow* window);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void dokey(int key);

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);

void do_mouse(GLFWwindow* window, int mkey, int dx, int dy);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void scroll_callback(GLFWwindow* window, double x, double y);

void framebuffer_size_callback(GLFWwindow* window, int w, int h);

void mainloop(GLFWwindow *window);
int np2(int v);
