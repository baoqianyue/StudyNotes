#include <iostream>
#include <glut.h>

using namespace std;

GLint winWidth = 600, winHeight = 600;

GLfloat x0 = 0.0, y_0 = 0.0, z0 = 10.0; //�۲�����ϵԭ��
GLfloat xref = 0.0, yref = 0.0, zref = 0.0; //�ο�������(�ӵ�) �����������Ϊ�ӵ�

GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; //�۲�ƽ����������(�۲�����ϵY��)

/*�ü����ڲ�������*/
GLfloat xwMin = -1.0, ywMin = -1.0, xwMax = 1.0, ywMax = 1.0;
/*Զ���ü�ƽ��ľ���*/
GLfloat dnear = 1.5, dfar = 20.0;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0); //���ñ���ɫΪ��ɫ
	/*�۲�任*/
	gluLookAt(x0, y_0, z0, xref, yref, zref, Vx, Vy, Vz);//��ά�۲����
	/*ģ�ͱ任*/
	glMatrixMode(GL_MODELVIEW);
	glScalef(5.0, 5.0, 5.0);//��������
	glRotatef(45.0, 0.0, 1.0, 1.0);//��ת
	
	/*ͶӰ�任*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);//͸��ͶӰ,����͸�Ӳü���

}

void displayFcn()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0); //����ǰ��ɫΪ��ɫ
	glutSolidCube(1.0); //���Ƶ�λ������
	glColor3f(0.0, 0.0, 0.0); //����ǰ��ɫΪ��ɫ
	glLineWidth(2.0); //�����߿�
	glutWireCube(1.0); //���Ƶ�λ�������߿�
	
	glFlush(); //ǿ��ˢ��
}

void reshapeFunc(GLint newWidth, GLint newHeight)
{
	/*�ӿڱ任*/
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