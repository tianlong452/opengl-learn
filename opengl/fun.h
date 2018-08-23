#pragma once
#include<GL/glut.h>  
#include <glfw/glfw3.h>
#include <glad/glad.h>
#include <math.h>
#include <iostream>
using namespace std;

extern float a, b , c;
extern int regx, regy ;

void cube(const GLuint &index, float x, float y, float z, float l, float w, float h);

void ground(const GLuint &index, float x, float y, float z, float l, float w, float h);

void myDisplay(GLFWwindow* window);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void scroll_callback(GLFWwindow* window, double x, double y);

void framebuffer_size_callback(GLFWwindow* window, int w, int h);