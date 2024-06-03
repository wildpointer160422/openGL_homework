#pragma once

#include <GL/gl.h>
#include <GL/glut.h>

#define imageWidth 64
#define imageHeight 64

class MyOpenGL
{
private:
	HDC hDC;			//GDI��ͼ��ʹ�õĵ��豸�������
	HGLRC hRC;		//OpenGL��Ⱦʱʹ�õ���Ⱦ�������
	GLubyte m_image[imageWidth][imageHeight][3];
	double	m_WidthHeightRatio;
	double  m_LightX;

public:
	MyOpenGL();
	virtual ~MyOpenGL();

	bool SetupPixelFormat(HDC hdc);	//�������ظ�ʽΪ�ʺ�OpenGL�ĸ�ʽ
	void Init(void);									//��ʼ����Ⱦ���������Ե�����
	void Render(float m_rotationAngleX, float m_rotationAngleY);							//���ƴ���

	void Reshape(int width, int height);		//�ı䴰�ڴ�Сʱ���Ӵ����еĲ���

	void MakeImage(void);	//��������ͼ��

	MyOpenGL& operator++();
	MyOpenGL operator++(int);
};