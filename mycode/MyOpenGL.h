#pragma once

#include <GL/gl.h>
#include <GL/glut.h>

#define imageWidth 64
#define imageHeight 64

class MyOpenGL
{
private:
	HDC hDC;			//GDI绘图中使用的的设备环境句柄
	HGLRC hRC;		//OpenGL渲染时使用的渲染环境句柄
	GLubyte m_image[imageWidth][imageHeight][3];
	double	m_WidthHeightRatio;
	double  m_LightX;

public:
	MyOpenGL();
	virtual ~MyOpenGL();

	bool SetupPixelFormat(HDC hdc);	//设置像素格式为适合OpenGL的格式
	void Init(void);									//初始化渲染过程中属性的设置
	void Render(float m_rotationAngleX, float m_rotationAngleY);							//绘制代码

	void Reshape(int width, int height);		//改变窗口大小时对视窗进行的操作

	void MakeImage(void);	//创建纹理图像

	MyOpenGL& operator++();
	MyOpenGL operator++(int);
};