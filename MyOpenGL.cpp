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

	/* 以下与光照处理相关*/
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);	//设置整体的环境光参数
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse);	//设置物体材料（漫反射）

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);		//设置光源漫反射强度
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);	//设置物体材料（漫反射）

	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);	//设置光源镜面反射强度
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);	//设置物体材料（镜面反射）	
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiness);	//设置物体材料（镜面反射的光洁度）

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);		//设置光源位置	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	/* 以上与光照处理相关*/

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//	glTranslatef(0.0, 0.0, -2.0);	//向-Z方向偏移	
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

	//透视投影  
	//1.5：近平面，沿-Z方向距离视点1.5，也就是在Z=3.5的位置
	//20.0:远平面，沿-Z方向距离视点20.0，也就是在Z=-15.0的位置
	//glFrustum (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	glFrustum( -5.0*m_WidthHeightRatio, 5.0*m_WidthHeightRatio, -5.0, 5.0, 1.5, 20.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(m_LightX, 0.0, 0.0);
	GLfloat light_pos[] = { -100.0,200.0,50.0,1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);		//设置光源位置
	glPopMatrix();

	glutSolidSphere(4.0,50,50);

	glDepthMask(GL_FALSE);
	glDisable(GL_LIGHTING);	

	//设置透明玻璃1
	glColor4f(0, 0, 1, 0.5);	
	glBegin(GL_QUADS);
		glVertex3f(-5.0, -5.0, 10.0);
		glVertex3f(-5.0, 5.0, 10.0);
		glVertex3f(5.0, 5.0, 10.0);
		glVertex3f(5.0, -5.0, 10.0);
	glEnd();

	//设置透明玻璃2
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

	/*根据点的位置设置不同的颜色*/
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