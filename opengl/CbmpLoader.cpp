#include"CbmpLoader.h"
#pragma warning( disable : 4996)
CbmpLoader::CbmpLoader()
{
	image = 0;
	imageWidth = 0;
	imageHeight = 0;
}
CbmpLoader::~CbmpLoader()
{
	FreeImage();
}
bool CbmpLoader::Loadimg(const char* file)
{
	Mat img = imread(file);
	cvtColor(img, img, CV_BGR2BGRA);
	imageWidth = img.cols;                    //����ͼ���͸߶�
	imageHeight = img.rows;
	image = new unsigned char[imageWidth*imageHeight*4];//�����ڴ�
	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			image[i*j * 4 + 4 * j + 0] = img.at<Vec4b>(i, j)[0] = 0;
			image[i*j * 4 + 4 * j + 1] = img.at<Vec4b>(i, j)[1] = 0;
			image[i*j * 4 + 4 * j + 2] = img.at<Vec4b>(i, j)[2] = 0;
			image[i*j*4 +4* j + 3] = img.at<Vec4b>(i, j)[3];
		}
	}
	return true;
}
bool CbmpLoader::LoadBitmapa(const char* file)
{
	FILE *pFile = 0;                          //�����ļ�ָ��
	BITMAPINFOHEADER bitmapInfoHeader;      //����λͼ�ļ�λͼ��Ϣ���ļ�ͷ�ṹ
	BITMAPFILEHEADER header;
	unsigned char textureColors = 0;      //���ڽ�ͼ����ɫ��BGR�任��RGB 
	pFile = fopen(file, "rb+");               //���ļ���������
	if (pFile == 0)
		return false;
	fread(&header, sizeof(BITMAPFILEHEADER), 1, pFile);//����λͼ�ļ�ͷ��Ϣ
	if (header.bfType != BITMAP_ID)                   //����Ƿ�Ϊλͼ�ļ�
	{
		fclose(pFile);
		return false;
	}
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);//����λͼ�ļ���Ϣ
	imageWidth = bitmapInfoHeader.biWidth;                    //����ͼ���͸߶�
	imageHeight = bitmapInfoHeader.biHeight;
	if (bitmapInfoHeader.biSizeImage == 0)                   //ȷ����ȡ���ݵĴ�С
		bitmapInfoHeader.biSizeImage = bitmapInfoHeader.biWidth *
		bitmapInfoHeader.biHeight * 3;
	fseek(pFile, header.bfOffBits, SEEK_SET);           //ָ��ָ�����ݿ�ʼλ��
	image = new unsigned char[bitmapInfoHeader.biSizeImage];//�����ڴ�
	if (!image)                                          //����Ƿ����ɹ�
	{
		delete[] image;
		fclose(pFile);
		return false;
	}
	fread(image, bitmapInfoHeader.biSizeImage, 1, pFile);   //��ȡͼ����Ϣ
															/** ��ͼ����ɫ���ݸ�ʽ���н���,��BGRת��ΪRGB */
	for (int index = 0; index < (int)bitmapInfoHeader.biSizeImage; index += 3)
	{
		textureColors = image[index];
		image[index] = image[index + 2];
		image[index + 2] = textureColors;
	}
	fclose(pFile);
	return true;
}
void CbmpLoader::FreeImage()
{
	if (image)
	{
		delete[]image;
		image = 0;
	}
}
bool CbmpLoader::Load(const char* fileName)
{
	if (!LoadBitmapa(fileName))
	{
		cout << "����λͼ�ļ�ʧ��!" << endl;
		exit(0);
	}
	/** ��������������� */
	glGenTextures(1, &ID);

	/** ����������� */
	glBindTexture(GL_TEXTURE_2D, ID);

	/** �����˲� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/** �������� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, imageWidth,
		imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
		image);
	return true;
}