#include "stdafx.h"
#include "MyOpenGL.h"
#define M_PI 3.1415926
bool isRotating = false;

MyOpenGL::MyOpenGL()
{
	//winWidth = 600;
	//winHeight = 600;
	m_LightX = 0.0;
}


MyOpenGL::~MyOpenGL()
{
}

bool MyOpenGL::SetupPixelFormat(HDC hdc)
{
	hDC = hdc;

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小
		1,                                // 版本号
		PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图
		PFD_SUPPORT_OPENGL |              // 支持OpenGL
		PFD_DOUBLEBUFFER,                 // 双缓存模式
		PFD_TYPE_RGBA,                    // RGBA 颜色模式
		24,                               // 24 位颜色深度
		0, 0, 0, 0, 0, 0,                 // 忽略颜色位
		0,                                // 没有非透明度缓存
		0,                                // 忽略移位位
		0,                                // 无累加缓存
		0, 0, 0, 0,                       // 忽略累加位
		32,                               // 32 位深度缓存   
		0,                                // 无模板缓存
		0,                                // 无辅助缓存
		PFD_MAIN_PLANE,  // 主层
		0,                                // 保留
		0, 0, 0                           // 忽略层,可见性和损毁掩模
	};

	int nPixelFormat;    // 像素点格式
	if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		MessageBox(NULL, L"can not find proper mode", L"Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	SetPixelFormat(hDC, nPixelFormat, &pfd);
	hRC = wglCreateContext(hDC);    //利用GDI绘图所使用的HDC创建对应的HGLRC
	wglMakeCurrent(hDC, hRC);        //使OpenGL绘图所使用的HGLRC为当前绘图工具

	return TRUE;
}

void InitOpenGL()
{
	glEnable(GL_DEPTH_TEST); // 启用深度测试
	glEnable(GL_LIGHTING);   // 启用光照
	glEnable(GL_LIGHT0);     // 启用光源0
}

void SetupLighting()
{
	GLfloat light_position[] = { -1.0f, -1.0f, 1.0f, 1.0f }; // 点光源位置
	//GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };  // 环境光
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };  // 漫反射光
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 镜面反射光

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void SetupMaterial()
{
	GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };  // 材料环境光反射属性
	GLfloat mat_diffuse[] = { 0.8f, 0.0f, 0.0f, 1.0f };  // 材料漫反射光反射属性
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 材料镜面反射光反射属性
	GLfloat mat_shininess[] = { 50.0f };                 // 材料镜面反射光的散射/聚集程度

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}


void MyOpenGL::Init(void)
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	InitOpenGL();
	SetupLighting();
	SetupMaterial();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glTranslatef(1.0, 1.0, -2.0);
}

void MyOpenGL::Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	m_WidthHeightRatio = (double)width / height;
}

void DrawSphere() {
	const int X_SEGMENTS = 20;
	const int Y_SEGMENTS = 20;
	const int length = 7;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 设置绘制模式为线框

	for (int i = 0; i < X_SEGMENTS; ++i) {
		double theta1 = i * 2 * M_PI / X_SEGMENTS;
		double theta2 = (i + 1) * 2 * M_PI / X_SEGMENTS;

		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j <= Y_SEGMENTS; ++j) {
			double phi = j * M_PI / Y_SEGMENTS;
			double x1 = cos(theta1) * sin(phi)* length;
			double y1 = sin(theta1) * sin(phi)* length;
			double z1 = cos(phi)*length;

			double x2 = cos(theta2) * sin(phi)*length;
			double y2 = sin(theta2) * sin(phi)*length;
			double z2 = cos(phi)*length;

			glVertex3d(x1, y1, z1);
			glVertex3d(x2, y2, z2);
		}
		glEnd();
	}
}

void MyOpenGL::Render(float m_rotationAngleX,float m_rotationAngleY)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-5.0 * m_WidthHeightRatio, 5.0 * m_WidthHeightRatio, -5.0, 5.0, 1.5, 20.0);

	glMatrixMode(GL_MODELVIEW);

	//glutSolidSphere(4.0,50,50);
	DrawSphere();
	glRotatef(m_rotationAngleX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_rotationAngleY, 0.0f, 1.0f, 0.0f);
	glRotatef(1, 1.0f, 0.0f, 0.0f);
	glRotatef(1, 0.0f, 1.0f, 0.0f);
	glDepthMask(GL_TRUE);
	glEnable(GL_LIGHTING);

	glFlush();
	SwapBuffers(hDC);
}





MyOpenGL& MyOpenGL::operator++()
{
	m_LightX = m_LightX + 2.0;
	if (m_LightX >= 100.0)
		m_LightX = -100.0;
	return *this;
}

MyOpenGL MyOpenGL::operator++(int)
{
	MyOpenGL temp(*this);

	m_LightX = m_LightX + 2.0;
	if (m_LightX >= 200.0)
		m_LightX = 0.0;

	return temp;
}
