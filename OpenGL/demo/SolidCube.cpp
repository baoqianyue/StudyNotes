#include <iostream>
#include <glut.h>

using namespace std;

GLint winWidth = 600, winHeight = 600;

GLfloat x0 = 0.0, y_0 = 0.0, z0 = 10.0; //观察坐标系原点
GLfloat xref = 0.0, yref = 0.0, zref = 0.0; //参考点坐标(视点) 立方体的中心为视点

GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; //观察平面向上向量(观察坐标系Y轴)

/*裁剪窗口参数设置*/
GLfloat xwMin = -1.0, ywMin = -1.0, xwMax = 1.0, ywMax = 1.0;
/*远近裁剪平面的距离*/
GLfloat dnear = 1.5, dfar = 20.0;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0); //设置背景色为白色
	/*观察变换*/
	gluLookAt(x0, y_0, z0, xref, yref, zref, Vx, Vy, Vz);//三维观察参数
	/*模型变换*/
	glMatrixMode(GL_MODELVIEW);
	glScalef(5.0, 5.0, 5.0);//比例缩放
	glRotatef(45.0, 0.0, 1.0, 1.0);//旋转
	
	/*投影变换*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);//透视投影,设置透视裁剪体

}

void displayFcn()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0); //设置前景色为绿色
	glutSolidCube(1.0); //绘制单位立方体
	glColor3f(0.0, 0.0, 0.0); //设置前景色为黑色
	glLineWidth(2.0); //设置线宽
	glutWireCube(1.0); //绘制单位立方体线框
	
	glFlush(); //强制刷新
}

void reshapeFunc(GLint newWidth, GLint newHeight)
{
	/*视口变换*/
	glViewport(0, 0, newWidth, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Solid Cube");
	
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(reshapeFunc);
	glutMainLoop();
	return 0;
}