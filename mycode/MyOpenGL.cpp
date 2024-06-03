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
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С
		1,                                // �汾��
		PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ
		PFD_SUPPORT_OPENGL |              // ֧��OpenGL
		PFD_DOUBLEBUFFER,                 // ˫����ģʽ
		PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ
		24,                               // 24 λ��ɫ���
		0, 0, 0, 0, 0, 0,                 // ������ɫλ
		0,                                // û�з�͸���Ȼ���
		0,                                // ������λλ
		0,                                // ���ۼӻ���
		0, 0, 0, 0,                       // �����ۼ�λ
		32,                               // 32 λ��Ȼ���   
		0,                                // ��ģ�建��
		0,                                // �޸�������
		PFD_MAIN_PLANE,  // ����
		0,                                // ����
		0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ
	};

	int nPixelFormat;    // ���ص��ʽ
	if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		MessageBox(NULL, L"can not find proper mode", L"Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	SetPixelFormat(hDC, nPixelFormat, &pfd);
	hRC = wglCreateContext(hDC);    //����GDI��ͼ��ʹ�õ�HDC������Ӧ��HGLRC
	wglMakeCurrent(hDC, hRC);        //ʹOpenGL��ͼ��ʹ�õ�HGLRCΪ��ǰ��ͼ����

	return TRUE;
}

void InitOpenGL()
{
	glEnable(GL_DEPTH_TEST); // ������Ȳ���
	glEnable(GL_LIGHTING);   // ���ù���
	glEnable(GL_LIGHT0);     // ���ù�Դ0
}

void SetupLighting()
{
	GLfloat light_position[] = { -1.0f, -1.0f, 1.0f, 1.0f }; // ���Դλ��
	//GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };  // ������
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };  // �������
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // ���淴���

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void SetupMaterial()
{
	GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };  // ���ϻ����ⷴ������
	GLfloat mat_diffuse[] = { 0.8f, 0.0f, 0.0f, 1.0f };  // ����������ⷴ������
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // ���Ͼ��淴��ⷴ������
	GLfloat mat_shininess[] = { 50.0f };                 // ���Ͼ��淴����ɢ��/�ۼ��̶�

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
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // ���û���ģʽΪ�߿�

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
