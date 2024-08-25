#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

//#pragma comment(linker, "/SUBSYSTEM:WINDOWS")       //����â�� �� �߰� �ϱ� ���ؼ�
//#pragma comment(linker, "/ENTRY:mainCRTStartup")    //�������� ��Ʈ�� ����Ʈ�� ����

GLfloat light_position[] = { 5.0, 10.0, 50.0, 0.0 };    //���� ��ġ
int width = 800, height = 400;                          //������ ũ��
GLint startX = 100, startY = 120;                       //�����ڽ� ����
GLint endX = 250, endY = 270;

void Init() {
    glShadeModel(GL_SMOOTH);
    glClearColor(0.1f, 0.1f, 0.2f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void MyReshape(GLint w, GLint h) {
    width = w;
    height = h;
    glutPostRedisplay();
}

void MySpecialkeys(GLint key, GLint x, GLint y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            if (endX <= 400) {
                startX += 1; endX += 1;
            }
            break;
        case GLUT_KEY_LEFT:
            if (startX >= 0) {
                startX -= 1; endX -= 1;
            }
            break;
        case GLUT_KEY_UP:   //GLUT �� GL �� y ���� ���� �ݴ� �������� ������
            if (endY <= 800) {
                startY -= 1; endY -= 1;
            }
            break;
        case GLUT_KEY_DOWN:
            if (startY >= 0) {
                startY += 1; endY += 1;
            }
            break;
    }
    glutPostRedisplay();
}

void MyMouseClick(GLint button, GLint state, GLint x, GLint y) {
    if (GLUT_LEFT_BUTTON == button && GLUT_DOWN == state) {
        startX = x; startY = y;
    }
}

void MyMouseMove(GLint x, GLint y) {
    endX = x; endY = y;
    glutPostRedisplay();
}

void DrawScissorBox() {         //�����ڽ� ��ü�� ȭ�鿡 ���̱� ���� �Լ�
    glBegin(GL_POLYGON);
        glVertex3f((GLfloat) startX / (GLfloat) (width / 2),
            (GLfloat) (height-startY) / (GLfloat) height, 1.0);
        glVertex3f((GLfloat) startX / (GLfloat) (width / 2),
            (GLfloat) (height-endY) / (GLfloat) height, 1.0);
        glVertex3f((GLfloat) endX / (GLfloat) (width / 2),
            (GLfloat) (height-endY) / (GLfloat) height, 1.0);
        glVertex3f((GLfloat) endX / (GLfloat) (width / 2),
            (GLfloat) (height-startY) / (GLfloat) height, 1.0);
    glEnd();
}

void DrawScene() {              //����, ����ü, �� �����ڸ� �׸��� �Լ�
    glPushMatrix();
        glColor3f(0.5, 0.5, 1.0);
        glutSolidSphere(0.7, 100.0, 100.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.5);
        glTranslatef(2.0, 2.0, 0.0);
        glutSolidCube(1.8);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(0.0, 2.0, 0.0);
        glutSolidTeapot(0.5);
    glPopMatrix();
}

void MyDisplay() {              //��Ŭ���� �ݹ�
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, width/2, height);          //ù ��° ����Ʈ
    glPushMatrix();
        glPushMatrix();
            glScalef(0.15, 0.15, 0.15);    glTranslatef(2.0, 2.0, 0.0);
            DrawScene();                        //���� �׽�Ʈ ���� ���
        glPopMatrix();
        glEnable(GL_BLEND);
        glColor4f(0.8, 0.8, 0.8, 0.5);
        DrawScissorBox();                       //���� �ڽ� ��� �׸���
        glDisable(GL_BLEND);
    glPopMatrix();
    glLoadIdentity();
    glViewport(width/2, 0, width/2, height);    //�� ��° ����Ʈ
    glPushMatrix();
        glEnable(GL_SCISSOR_TEST);              //���� �׽�Ʈ Ȱ��ȭ
        if (endY > startY) {                    //���� �����ڽ��� ���ϴ� �Լ�
            glScissor(startX+400, abs(height-endY),
                abs(endX-startX), abs(endY-startY));
        }
        else {
            glScissor(startX+400, abs(height-startY),
                abs(endX-startX), abs(endY-startY));
        }
        glPushMatrix();
            glScalef(0.15, 0.15, 0.15);
            glTranslatef(2.0, 2.0, 0.0);
            DrawScene();                        //���� �׽�Ʈ ���� ���
        glPopMatrix();
        glDisable(GL_SCISSOR_TEST);
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Scissoring Example");
    Init();
    glutReshapeFunc(MyReshape);
    glutSpecialFunc(MySpecialkeys);
    glutMouseFunc(MyMouseClick);
    glutMotionFunc(MyMouseMove);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}
