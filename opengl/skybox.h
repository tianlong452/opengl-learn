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

/** 天空盒类 */
class CSkyBox
{
public:
	/** 构造函数 */
	CSkyBox();
	~CSkyBox();

	/** 初始化 */
	bool Init();

	/** 渲染天空 */
	void  CreateSkyBox(float x, float y, float z,float width, float height,float length);

private:

	CbmpLoader m_texture[6];   /**< 天空盒纹理 */

};


#endif ///__SKYBOX_H__