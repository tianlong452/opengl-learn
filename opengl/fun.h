#pragma once
#include<GL/glut.h>  
#include <glfw/glfw3.h>
#include <glad/glad.h>
#include <math.h>
#include <iostream>
#include <soil/SOIL.h>
#include "skybox.h"
#include <gdiplus.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
extern float a, b , c;
extern double regx, regy ;
extern CSkyBox m_SkyBox;

void cube_tank_bottom(const GLuint &index, float x, float y, float z, float l, float w, float h);
void cube_tank_top(const GLuint &index, float x, float y, float z, float l, float w, float h);
void ground(const GLuint &index, float x, float y, float z, float l, float w, float h);

void myDisplay(GLFWwindow* window);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void scroll_callback(GLFWwindow* window, double x, double y);

void framebuffer_size_callback(GLFWwindow* window, int w, int h);

int np2(int v);
