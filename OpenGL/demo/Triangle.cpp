#include <iostream>
#include <glut.h>

using namespace std;

class pt2D {
public:
	GLfloat x, y;
};

void triangle(pt2D *verts)
{
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 3; i++)
	{
		glVertex2f(verts[i].x, verts[i].y);
	}
	glEnd();
}

void init()
{
	//设置窗口背景颜色
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//为世界坐标系的裁剪窗口设置参数
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);

	//构建几何变换矩阵
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	//初始化三角形的坐标
	pt2D verts[3] = { {-50.0, -25.0}, {50.0, -25.0}, {0.0, 50.0} };
	//清空显示窗口
	glClear(GL_COLOR_BUFFER_BIT);
	//设置蓝色填充颜色
	glColor3f(0.0, 0.0, 1.0);
	//设置视口在窗口左侧
	glViewport(0, 0, 300, 300);
	triangle(verts);

	/*将三角形旋转并通过设置视口显示窗口右侧*/
	//先设置填充颜色为红色
	glColor3f(1.0, 0.0, 0.0);
	//设置视口为窗口右侧
	glViewport(300, 0, 300, 300);
	//绕z轴旋转90度
	glRotated(90.0, 0.0, 0.0, 1.0);
	triangle(verts);
	glFlush();
}


int main(int argc, char ** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 300);
	glutCreateWindow("viewport Train");
	init();
	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}
