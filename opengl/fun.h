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
extern const int timer;
//extern float a, b , c;
//extern double regx, regy ;

void creat_cube_list(const GLuint &index, float x, float y, float z, float l, float h, float w
	,float dx, float dz, vector<string> files);
void ground(const GLuint &index, float x, float y, float z, float l, float w, float h);

void myDisplay(GLFWwindow* window);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void scroll_callback(GLFWwindow* window, double x, double y);

void framebuffer_size_callback(GLFWwindow* window, int w, int h);

int np2(int v);
