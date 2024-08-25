#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

GLUquadricObj* qobj;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (0., 1., 1.);
    gluSphere(qobj, 1., 20, 20);        //������ 1, �����̽� 20��, ���� 20��
    glutSwapBuffers();
}

void gfxinit() {
    qobj = gluNewQuadric();                 //���ο� ��� ��ü ����
    gluQuadricDrawStyle(qobj, GLU_LINE);    //���̾� ������ ������
}

void myReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40., (GLfloat) w / (GLfloat) h, 1., 10.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.);
    glTranslatef(0., 0., -1.);
}

void main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("simple");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    gfxinit();
    glutMainLoop();
}
