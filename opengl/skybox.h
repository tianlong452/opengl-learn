#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#define GL_CLAMP_TO_EDGE    0x812F

#include<GL/glut.h>  
#include <glfw/glfw3.h>
#include <glad/glad.h>
#include <math.h>
#include <iostream>
#include <string>
#include "CbmpLoader.h"
using namespace std;

/** ��պ��� */
class CSkyBox
{
public:
	/** ���캯�� */
	CSkyBox();
	~CSkyBox();

	/** ��ʼ�� */
	bool Init();

	/** ��Ⱦ��� */
	void  CreateSkyBox(float x, float y, float z,float width, float height,float length);

private:

	CbmpLoader m_texture[6];   /**< ��պ����� */

};


#endif ///__SKYBOX_H__