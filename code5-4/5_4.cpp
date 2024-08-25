#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void MyDisplay() {                      //���÷��� �ݹ��Լ�
    glClear(GL_COLOR_BUFFER_BIT);       //GL ���º��� ����
    glViewport(0, 0, 300, 300);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);                //�Է� �⺻��� ����
        glVertex3f(-0.5, -0.5, 0.0);
        glVertex3f(0.5, -0.5, 0.0);
        glVertex3f(0.5, 0.5, 0.0);
        glVertex3f(-0.5, 0.5, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);               //GLUT ������ �Լ�
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Sample Drawing");

    glClearColor(0.0, 0.0, 0.0, 1.0);   //GL ���º��� ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(MyDisplay);         //GLUT �ݹ��Լ� ���
    glutMainLoop();                     //�̺�Ʈ ���� ����
    return 0;
}
