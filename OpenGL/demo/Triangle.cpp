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
	//���ô��ڱ�����ɫ
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//Ϊ��������ϵ�Ĳü��������ò���
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);

	//�������α任����
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	//��ʼ�������ε�����
	pt2D verts[3] = { {-50.0, -25.0}, {50.0, -25.0}, {0.0, 50.0} };
	//�����ʾ����
	glClear(GL_COLOR_BUFFER_BIT);
	//������ɫ�����ɫ
	glColor3f(0.0, 0.0, 1.0);
	//�����ӿ��ڴ������
	glViewport(0, 0, 300, 300);
	triangle(verts);

	/*����������ת��ͨ�������ӿ���ʾ�����Ҳ�*/
	//�����������ɫΪ��ɫ
	glColor3f(1.0, 0.0, 0.0);
	//�����ӿ�Ϊ�����Ҳ�
	glViewport(300, 0, 300, 300);
	//��z����ת90��
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
