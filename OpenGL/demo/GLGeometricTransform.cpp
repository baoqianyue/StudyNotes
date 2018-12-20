#include <math.h>
#include <glut.h>

using namespace std;


/*1.�����Զ������λ��ת�任����rotate3D,��һ������ʵ����p1p2��ת����ʱ��90�����ά��ת*/
/*2/����xyƽ�����Ծ������½ǵ�Ϊ��׼�����xy����Ϊ50%����С�任,3.Ȼ����y����ƽ��100��λ*/
/*����p1p2�������ɵ������ᴹֱ��xyƽ�沢��ͨ��ԭxyƽ���Ͼ������½ǵ�����,Ч���ϱ���Ϊ��xyƽ���Ͼ������½Ƕ���Ķ�ά��ת*/

/*��ΪҪʹ��GL�⺯��,OpenGL�еı仯�������û����ϵ�任ģʽ*/
/*���Ҫ�Թ̶�����ϵģʽ�����������任����,������Ӧ���෴�Ĵ�������任*/
/*�ȵ��õı任��ִ��,����õı任��ִ��,ÿ���µı任������ͨ���ҳ˸��Ͼ�����֮�ϲ���*/

GLsizei winWidth = 600, winHeight = 600;

GLfloat xwcMin = -300.0, xwcMax = 300.0;
GLfloat ywcMin = -300.0, ywcMax = 300.0;

//������ά�ռ��
class wcPt3D
{
public:
	GLfloat x, y, z;
};

void init()
{
	//���ô��ڱ�����ɫΪ��ɫ
	glClearColor(1.0, 1.0, 1.0, 0.0);
}


/*�Զ�����ά��ת����,����Ϊp1��p2���������ת�Ƕ�*/
/*ƽ�Ƶ�ԭ��-��ת-ƽ�ƻ�ԭλ��*/
void rotate3D(wcPt3D p1, wcPt3D p2, GLfloat theta)
{
	//������ת���������ʾ
	GLfloat vx = p2.x - p1.x;
	GLfloat vy = p2.y - p1.y;
	GLfloat vz = p2.z - p1.z;

	//��ΪOpenGL�����ϵģʽ,�������б任˳�������˳���෴
	//��ת��ɺ���Ҫ��p1������ͼ���ƶ���ԭ����λ��
	glTranslatef(p1.x, p1.y, p1.z);

	//������ԭ�������ת
	glRotatef(theta, vx, vy, vz);

	//��p1�ƶ���ԭ��λ��(���ǽ�ͼ���ƶ�����ԭ���غ�,��������������ת�ĵ�һ��)
	glTranslatef(-p1.x, -p1.y, -p1.z);

}

/*�Զ�����ά�������ź���,����Ϊ����ϵ���͹̶���*/
/*ƽ�Ƶ�ԭ��-����-ƽ�ƻ�ԭλ��*/
void scale3D(GLfloat sx, GLfloat sy, GLfloat sz, wcPt3D fixedPt)
{
	//�任˳��͵���˳���෴
	glTranslatef(fixedPt.x, fixedPt.y, fixedPt.z);
	glScalef(sx, sy, sz);
	glTranslatef(-fixedPt.x, -fixedPt.y, -fixedPt.z);
}

void displayFcn()
{
	//�������α任����
	wcPt3D p1, p2, fixedPt;
	//p1Ϊ�������½ǵĵ�
	p1.x = 50;
	p1.y = 100;
	p1.z = 0;
	p2.x = 50;
	p2.y = 100;
	p2.z = 1;
	//���ź���ת�Ĳ��յ����ת�����p1����ͨ��p1
	fixedPt = p1;

	//���Ų���
	GLfloat sx = 0.5, sy = 0.5, sz = 1;
	//ƽ�Ʋ���
	GLfloat tx = 0.0, ty = 100.0, tz = 0.0;
	//��ת����
	GLdouble theta = 90.0;
	
	glClear(GL_COLOR_BUFFER_BIT);//���������ɫ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //��ձ任����Ϊ��λ����,�ָ�ԭʼ����ϵ״̬
	
	//����ԭͼ��
	glColor3f(0.0, 0.0, 1.0);
	glRecti(50, 100, 200, 150);

	//ִ�м��α任
	//����˳���ʵ�ʱ任˳���෴
	glTranslatef(tx, ty, tz);
	scale3D(sx, sy, sz, fixedPt);
	rotate3D(p1, p2, theta);

	//��ʾ�任���ͼ��
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
	glutCreateWindow("��ά���α任,ʹ��GL�⺯��ʵ��");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(reshapeFcn);
	glutMainLoop();
	return 0;
}