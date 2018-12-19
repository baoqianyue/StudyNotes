#include <iostream>
#include <glut.h>
#include <math.h>

using namespace std;

/*图形二维复合几何变换demo*/
/*将一个三角形先对其中心位置缩小50%,然后绕其中心旋转90度,最后进行y方向平移100单位*/
/*整个变换是在统一的世界坐标系下完成的,即采用的是固定坐标系变换模式*/
/*先调用的变换先执行,而且越早执行的变换子矩阵位于变换矩阵连乘式的右边*/  

GLsizei winWidth = 600, winHeight = 600;
/*世界坐标系的显示范围*/
//wc 是 world coordinate的缩写
GLfloat xwcMin = 0.0, xwcMax = 225.0;
GLfloat ywcMin = 0.0, ywcMax = 225.0;

class wcPt2D {
public:
	GLfloat x, y;
};

typedef GLfloat Matrix3x3[3][3];
Matrix3x3 matComposite;//定义复合矩阵

const GLdouble pi = 3.1415926;

void init()
{
	//设置窗口的背景色是白色
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

/*构建3x3的单位矩阵*/
void matrix3x3SetIdentity(Matrix3x3 matIndent3x3)
{
	GLint row, col;
	for (row = 0; row < 3; row++)
	{
		for (col = 0; col < 3; col++)
		{
			matIndent3x3[row][col] = (row == col);
		}
	}
}

/*将矩阵m1前乘矩阵m2,将结果保存在m2中*/
void matrix3x3PreMultiply(Matrix3x3 m1, Matrix3x3 m2)
{
	GLint row, col;
	Matrix3x3 matTemp;

	for (row = 0; row < 3; row++)
		for (col = 0; col < 3; col++)
			matTemp[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col];

	for (row = 0; row < 3; row++)
		for (col = 0; col < 3; col++)
			m2[row][col] = matTemp[row][col];
}

/*平移变换函数*/
void translate2D(GLfloat tx, GLfloat ty)
{
	Matrix3x3 matTrans;
	//先将平移变换矩阵初始为单位阵
	matrix3x3SetIdentity(matTrans);
	
	matTrans[0][2] = tx;
	matTrans[1][2] = ty;

	//将平移变换阵左乘复合在复合变换矩阵中
	matrix3x3PreMultiply(matTrans, matComposite);

}

/*旋转变换函数,参数为物体中心点和旋转角度*/
void rotate2D(wcPt2D pivotPt, GLfloat theta)
{
	Matrix3x3 matRotate;
	
	//构造旋转变换矩阵
	matrix3x3SetIdentity(matRotate);

	matRotate[0][0] = cos(theta);
	matRotate[0][1] = -sin(theta);
	matRotate[0][2] = pivotPt.x * (1 - cos(theta)) + pivotPt.y * sin(theta);
	matRotate[1][0] = sin(theta);
	matRotate[1][1] = cos(theta);
	matRotate[1][2] = pivotPt.y * (1 - cos(theta)) - pivotPt.x * sin(theta);

	//将旋转变换矩阵左乘复合到复合变换矩阵中
	matrix3x3PreMultiply(matRotate, matComposite);
}

/*缩放变换函数,参数为基准点fixedPt和比例变换系数Sx, Sy*/
void scale2D(GLfloat sx, GLfloat sy, wcPt2D fixedPt)
{
	Matrix3x3 matScale;
	
	matrix3x3SetIdentity(matScale);
	matScale[0][0] = sx;
	matScale[0][2] = (1 - sx) * fixedPt.x;
	matScale[1][1] = sy;
	matScale[1][2] = (1 - sy) * fixedPt.y;

	matrix3x3PreMultiply(matScale, matComposite);
}

/*使用复合矩阵计算图形变换后的点坐标,参数为图形边界点的个数,和边界上各个点的齐次坐标*/
void transformVerts2D(GLint nVerts, wcPt2D *verts)
{
	GLfloat temp;
	for (GLint k = 0; k < nVerts; k++)
	{
		temp = matComposite[0][0] * verts[k].x + matComposite[0][1] * verts[k].y + matComposite[0][2];
		verts[k].y = matComposite[1][0] * verts[k].x + matComposite[1][1] * verts[k].y + matComposite[1][2];
		verts[k].x = temp;
	}
}

void triangle(wcPt2D *verts)
{
	GLint k;
	glBegin(GL_TRIANGLES);
	for (k = 0; k < 3; k++)
		glVertex2f(verts[k].x, verts[k].y);
	glEnd();
}

void displayFcn()
{
	GLint nVerts = 3;
	//三角形各点坐标
	wcPt2D verts[3] = { {50.0, 25.0}, {150.0, 25.0}, {100.0, 100.0} };
	//中心点坐标
	wcPt2D centroidPt;
	GLint k, xSum = 0, ySum = 0;
	for (GLint i = 0; i < nVerts; i++)
	{
		xSum += verts[i].x;
		ySum += verts[i].y;
	}

	//计算中心点坐标
	centroidPt.x = xSum / nVerts;
	centroidPt.y = ySum / nVerts;
	
	wcPt2D pivotPt, fixedPt;
	pivotPt = centroidPt;
	fixedPt = centroidPt;

	GLfloat tx = 0.0, ty = 100.0;
	GLfloat sx = 0.5, sy = 0.5;
	GLdouble theta = pi / 2.0;
	
	glClear(GL_COLOR_BUFFER_BIT); //清空显示窗口的颜色缓存(清除白色)
	glColor3f(0.0, 0.0, 1.0); //当前颜色设置为蓝色
	triangle(verts);

	//初始化复合矩阵为单位阵
	matrix3x3SetIdentity(matComposite);
	
	//根据变换序列构建复合变换矩阵
	scale2D(sx, sy, fixedPt);
	rotate2D(pivotPt, theta);
	translate2D(tx, ty);

	//将复合矩阵应用到图形各点坐标上
	transformVerts2D(nVerts, verts);

	glColor3f(1.0, 0.0, 0.0);//设置当前颜色为红色
	triangle(verts); //绘制变换后的图形
	
	glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);

	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("二维复合几何变换");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}

