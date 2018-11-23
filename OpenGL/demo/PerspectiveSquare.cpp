#include <iostream>
#include <glut.h>

using namespace std;

GLint winWidth = 600, winHeight = 600;
GLfloat x0 = 100.0, y_0 = 50.0, z0 = 50.0;//观察坐标系原点
GLfloat xref = 50.0, yref = 50.0, zref = 0.0; //观察点坐标  
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; //观察平面向上向量

/*设置裁剪窗口的坐标范围*/
GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;

/*设置远近裁剪平面的距离*/
GLfloat dnear = 25.0, dfar = 125.0;


void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(x0, y_0, z0, xref, yref, zref, Vx, Vy, Vz);
	glMatrixMode(GL_PROJECTION);
	glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}


void displayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT);
	/*设置正方形填充*/
	glColor3f(0.0, 1.0, 0.0);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);  //背面设置为线框 
	glBegin(GL_QUADS);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);
	glVertex3f(100.0, 100.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);
	glEnd();

	glFlush();//强制刷新
}

void reshapeFunc(GLint newWidth, GLint newHeight)
{
	glViewport(0.0, 0.0, newWidth, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Perspective view of a square");
	
	init();
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(reshapeFunc);

	glutMainLoop();

	return 0;
}