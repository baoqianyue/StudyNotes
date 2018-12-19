#include <iostream>
#include <glut.h>
#include <math.h>

using namespace std;

/*ͼ�ζ�ά���ϼ��α任demo*/
/*��һ���������ȶ�������λ����С50%,Ȼ������������ת90��,������y����ƽ��100��λ*/
/*�����任����ͳһ����������ϵ����ɵ�,�����õ��ǹ̶�����ϵ�任ģʽ*/
/*�ȵ��õı任��ִ��,����Խ��ִ�еı任�Ӿ���λ�ڱ任��������ʽ���ұ�*/  

GLsizei winWidth = 600, winHeight = 600;
/*��������ϵ����ʾ��Χ*/
//wc �� world coordinate����д
GLfloat xwcMin = 0.0, xwcMax = 225.0;
GLfloat ywcMin = 0.0, ywcMax = 225.0;

class wcPt2D {
public:
	GLfloat x, y;
};

typedef GLfloat Matrix3x3[3][3];
Matrix3x3 matComposite;//���帴�Ͼ���

const GLdouble pi = 3.1415926;

void init()
{
	//���ô��ڵı���ɫ�ǰ�ɫ
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

/*����3x3�ĵ�λ����*/
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

/*������m1ǰ�˾���m2,�����������m2��*/
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

/*ƽ�Ʊ任����*/
void translate2D(GLfloat tx, GLfloat ty)
{
	Matrix3x3 matTrans;
	//�Ƚ�ƽ�Ʊ任�����ʼΪ��λ��
	matrix3x3SetIdentity(matTrans);
	
	matTrans[0][2] = tx;
	matTrans[1][2] = ty;

	//��ƽ�Ʊ任����˸����ڸ��ϱ任������
	matrix3x3PreMultiply(matTrans, matComposite);

}

/*��ת�任����,����Ϊ�������ĵ����ת�Ƕ�*/
void rotate2D(wcPt2D pivotPt, GLfloat theta)
{
	Matrix3x3 matRotate;
	
	//������ת�任����
	matrix3x3SetIdentity(matRotate);

	matRotate[0][0] = cos(theta);
	matRotate[0][1] = -sin(theta);
	matRotate[0][2] = pivotPt.x * (1 - cos(theta)) + pivotPt.y * sin(theta);
	matRotate[1][0] = sin(theta);
	matRotate[1][1] = cos(theta);
	matRotate[1][2] = pivotPt.y * (1 - cos(theta)) - pivotPt.x * sin(theta);

	//����ת�任������˸��ϵ����ϱ任������
	matrix3x3PreMultiply(matRotate, matComposite);
}

/*���ű任����,����Ϊ��׼��fixedPt�ͱ����任ϵ��Sx, Sy*/
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

/*ʹ�ø��Ͼ������ͼ�α任��ĵ�����,����Ϊͼ�α߽��ĸ���,�ͱ߽��ϸ�������������*/
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
	//�����θ�������
	wcPt2D verts[3] = { {50.0, 25.0}, {150.0, 25.0}, {100.0, 100.0} };
	//���ĵ�����
	wcPt2D centroidPt;
	GLint k, xSum = 0, ySum = 0;
	for (GLint i = 0; i < nVerts; i++)
	{
		xSum += verts[i].x;
		ySum += verts[i].y;
	}

	//�������ĵ�����
	centroidPt.x = xSum / nVerts;
	centroidPt.y = ySum / nVerts;
	
	wcPt2D pivotPt, fixedPt;
	pivotPt = centroidPt;
	fixedPt = centroidPt;

	GLfloat tx = 0.0, ty = 100.0;
	GLfloat sx = 0.5, sy = 0.5;
	GLdouble theta = pi / 2.0;
	
	glClear(GL_COLOR_BUFFER_BIT); //�����ʾ���ڵ���ɫ����(�����ɫ)
	glColor3f(0.0, 0.0, 1.0); //��ǰ��ɫ����Ϊ��ɫ
	triangle(verts);

	//��ʼ�����Ͼ���Ϊ��λ��
	matrix3x3SetIdentity(matComposite);
	
	//���ݱ任���й������ϱ任����
	scale2D(sx, sy, fixedPt);
	rotate2D(pivotPt, theta);
	translate2D(tx, ty);

	//�����Ͼ���Ӧ�õ�ͼ�θ���������
	transformVerts2D(nVerts, verts);

	glColor3f(1.0, 0.0, 0.0);//���õ�ǰ��ɫΪ��ɫ
	triangle(verts); //���Ʊ任���ͼ��
	
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
	glutCreateWindow("��ά���ϼ��α任");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}

