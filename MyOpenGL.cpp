#include "stdafx.h"
#include "MyOpenGL.h"


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

void MyOpenGL::Init(void)
{
	GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_diffuse[] = { 1.0,0.0,1.0,1.0 };
	GLfloat mat_shiness[] = { 1000.0 };

	GLfloat light_pos[] = { 0.0,200.0,50.0,1.0 };

	GLfloat light_specular[] = { 0.0,0.0,1.0,1.0 };
	GLfloat light_diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_ambient[] = { 0.2,0.2,0.2,1.0 };

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* ��������մ������*/
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);	//��������Ļ��������
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse);	//����������ϣ������䣩

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);		//���ù�Դ������ǿ��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);	//����������ϣ������䣩

	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);	//���ù�Դ���淴��ǿ��
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);	//����������ϣ����淴�䣩	
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiness);	//����������ϣ����淴��Ĺ��ȣ�

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);		//���ù�Դλ��	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	/* ��������մ������*/

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//	glTranslatef(0.0, 0.0, -2.0);	//��-Z����ƫ��	
}

void MyOpenGL::Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	m_WidthHeightRatio = (double)width / height;
}

void MyOpenGL::Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//͸��ͶӰ  
	//1.5����ƽ�棬��-Z��������ӵ�1.5��Ҳ������Z=3.5��λ��
	//20.0:Զƽ�棬��-Z��������ӵ�20.0��Ҳ������Z=-15.0��λ��
	//glFrustum (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	glFrustum( -5.0*m_WidthHeightRatio, 5.0*m_WidthHeightRatio, -5.0, 5.0, 1.5, 20.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(m_LightX, 0.0, 0.0);
	GLfloat light_pos[] = { -100.0,200.0,50.0,1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);		//���ù�Դλ��
	glPopMatrix();

	glutSolidSphere(4.0,50,50);

	glDepthMask(GL_FALSE);
	glDisable(GL_LIGHTING);	

	//����͸������1
	glColor4f(0, 0, 1, 0.5);	
	glBegin(GL_QUADS);
		glVertex3f(-5.0, -5.0, 10.0);
		glVertex3f(-5.0, 5.0, 10.0);
		glVertex3f(5.0, 5.0, 10.0);
		glVertex3f(5.0, -5.0, 10.0);
	glEnd();

	//����͸������2
	glColor4f(0, 1, 0, 0.0);

	glBegin(GL_QUADS);
	glVertex3f(-5.0, -5.0, 12.0);
	glVertex3f(-5.0, 5.0, 12.0);
	glVertex3f(5.0, 5.0, 12.0);
	glVertex3f(5.0, -5.0, 12.0);
	glEnd();

	glDepthMask(GL_TRUE);
	glEnable(GL_LIGHTING);

	glFlush();
	SwapBuffers(hDC);
}

void MyOpenGL::MakeImage(void)
{
	int i, j, r, g, b;

	/*���ݵ��λ�����ò�ͬ����ɫ*/
	for (i = 0; i < imageWidth; i++)
	{
		for (j = 0; j <imageHeight; j++)
		{
			r = (i*j) % 255;
			g = (i*i) % 255;
			b = (j*j) % 255;

			m_image[i][j][0] = (GLubyte)b;
			m_image[i][j][1] = (GLubyte)g;
			m_image[i][j][2] = (GLubyte)r;
		}
	}
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