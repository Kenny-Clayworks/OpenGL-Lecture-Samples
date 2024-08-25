#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

//#pragma comment(linker, "/SUBSYSTEM:WINDOWS")       //도스창을 안 뜨게 하기 위해서
//#pragma comment(linker, "/ENTRY:mainCRTStartup")    //윈도우즈 엔트리 포인트를 변경

GLfloat light_position[] = { 5.0, 10.0, 50.0, 0.0 };    //광원 위치
int width = 800, height = 400;                          //윈도우 크기
GLint startX = 100, startY = 120;                       //시저박스 영역
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
        case GLUT_KEY_UP:   //GLUT 와 GL 의 y 축은 서로 반대 방향으로 움직임
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

void DrawScissorBox() {         //시저박스 자체를 화면에 보이기 위한 함수
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

void DrawScene() {              //원구, 육면체, 차 주전자를 그리는 함수
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

void MyDisplay() {              //디스클레이 콜백
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, width/2, height);          //첫 번째 뷰포트
    glPushMatrix();
        glPushMatrix();
            glScalef(0.15, 0.15, 0.15);    glTranslatef(2.0, 2.0, 0.0);
            DrawScene();                        //시저 테스트 이전 장면
        glPopMatrix();
        glEnable(GL_BLEND);
        glColor4f(0.8, 0.8, 0.8, 0.5);
        DrawScissorBox();                       //시저 박스 모습 그리기
        glDisable(GL_BLEND);
    glPopMatrix();
    glLoadIdentity();
    glViewport(width/2, 0, width/2, height);    //두 번째 뷰포트
    glPushMatrix();
        glEnable(GL_SCISSOR_TEST);              //시저 테스트 활성화
        if (endY > startY) {                    //실제 시저박스를 가하는 함수
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
            DrawScene();                        //시저 테스트 이후 장면
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
