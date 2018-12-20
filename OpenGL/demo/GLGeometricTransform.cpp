#include <math.h>
#include <glut.h>

using namespace std;


/*1.调用自定义的三位旋转变换函数rotate3D,将一个矩形实现绕p1p2旋转轴逆时针90°的三维旋转*/
/*2/再以xy平面上以矩形左下角点为基准点进行xy方向都为50%的缩小变换,3.然后向y方向平移100单位*/
/*其中p1p2向量构成的向量轴垂直于xy平面并且通过原xy平面上矩形左下角的向量,效果上表现为绕xy平面上矩形左下角顶点的二维旋转*/

/*因为要使用GL库函数,OpenGL中的变化函数采用活动坐标系变换模式*/
/*如果要以固定坐标系模式来考虑整个变换过程,必须以应用相反的次序引入变换*/
/*先调用的变换后执行,后调用的变换先执行,每次新的变换矩阵都是通过右乘复合矩阵与之合并的*/

GLsizei winWidth = 600, winHeight = 600;

GLfloat xwcMin = -300.0, xwcMax = 300.0;
GLfloat ywcMin = -300.0, ywcMax = 300.0;

//定义三维空间点
class wcPt3D
{
public:
	GLfloat x, y, z;
};

void init()
{
	//设置窗口背景颜色为白色
	glClearColor(1.0, 1.0, 1.0, 0.0);
}


/*自定义三维旋转函数,参数为p1和p2点坐标和旋转角度*/
/*平移到原点-旋转-平移回原位置*/
void rotate3D(wcPt3D p1, wcPt3D p2, GLfloat theta)
{
	//计算旋转轴的向量表示
	GLfloat vx = p2.x - p1.x;
	GLfloat vy = p2.y - p1.y;
	GLfloat vz = p2.z - p1.z;

	//因为OpenGL活动坐标系模式,所以下列变换顺序与调用顺序相反
	//旋转完成后需要将p1和连带图形移动回原来的位置
	glTranslatef(p1.x, p1.y, p1.z);

	//绕坐标原点进行旋转
	glRotatef(theta, vx, vy, vz);

	//将p1移动到原点位置(就是将图形移动到与原点重合,这是绕任意轴旋转的第一步)
	glTranslatef(-p1.x, -p1.y, -p1.z);

}

/*自定义三维比例缩放函数,参数为比例系数和固定点*/
/*平移到原点-缩放-平移回原位置*/
void scale3D(GLfloat sx, GLfloat sy, GLfloat sz, wcPt3D fixedPt)
{
	//变换顺序和调用顺序相反
	glTranslatef(fixedPt.x, fixedPt.y, fixedPt.z);
	glScalef(sx, sy, sz);
	glTranslatef(-fixedPt.x, -fixedPt.y, -fixedPt.z);
}

void displayFcn()
{
	//给定几何变换参数
	wcPt3D p1, p2, fixedPt;
	//p1为矩形左下角的点
	p1.x = 50;
	p1.y = 100;
	p1.z = 0;
	p2.x = 50;
	p2.y = 100;
	p2.z = 1;
	//缩放和旋转的参照点和旋转轴就是p1或者通过p1
	fixedPt = p1;

	//缩放参数
	GLfloat sx = 0.5, sy = 0.5, sz = 1;
	//平移参数
	GLfloat tx = 0.0, ty = 100.0, tz = 0.0;
	//旋转参数
	GLdouble theta = 90.0;
	
	glClear(GL_COLOR_BUFFER_BIT);//清除窗口颜色缓存
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //清空变换矩阵为单位矩阵,恢复原始坐标系状态
	
	//绘制原图形
	glColor3f(0.0, 0.0, 1.0);
	glRecti(50, 100, 200, 150);

	//执行几何变换
	//调用顺序和实际变换顺序相反
	glTranslatef(tx, ty, tz);
	scale3D(sx, sy, sz, fixedPt);
	rotate3D(p1, p2, theta);

	//显示变换后的图形
	glColor3f(1.0, 0.0, 0.0);
	glRecti(50, 100, 200, 150);

	glFlush();
}

void reshapeFcn(int newWidth, int newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char ** argv)
{

	glutInit(&argc, argv);
	glutInitWindowPosition(50, 50);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("三维几何变换,使用GL库函数实现");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(reshapeFcn);
	glutMainLoop();
	return 0;
}