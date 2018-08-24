#pragma once
#include <stdio.h>
#include <iostream>
#include <gl/glut.h>
#include <soil/SOIL.h>
#include <../../../../8.1/Include/shared/wtypes.h>
using namespace std;
#ifndef _CBMPLOADER_H_
#define _CBMPLOADER_H_
#define BITMAP_ID 0x4D42  //λͼ�ļ���־
/*
struct BITMAPINFOHEADER {
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
		DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
};*/
class CbmpLoader
{
public:
	CbmpLoader();
	~CbmpLoader();
	bool LoadBitmapa(const char* file); //����һ��bmp�ļ�            
	void FreeImage();               //�ͷ�ͼ������
	bool Load(const char* fileName);//����λͼ����������
	unsigned int ID;                //��������ID��
	int imageWidth;                 //ͼ����
	int imageHeight;                //ͼ��߶�
	unsigned char* image;           //ָ��ͼ������ָ��
};
#endif