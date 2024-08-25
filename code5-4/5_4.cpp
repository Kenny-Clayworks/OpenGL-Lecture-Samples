#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void MyDisplay() {                      //디스플레이 콜백함수
    glClear(GL_COLOR_BUFFER_BIT);       //GL 상태변수 설정
    glViewport(0, 0, 300, 300);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);                //입력 기본요소 정의
        glVertex3f(-0.5, -0.5, 0.0);
        glVertex3f(0.5, -0.5, 0.0);
        glVertex3f(0.5, 0.5, 0.0);
        glVertex3f(-0.5, 0.5, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);               //GLUT 윈도우 함수
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Sample Drawing");

    glClearColor(0.0, 0.0, 0.0, 1.0);   //GL 상태변수 설정
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(MyDisplay);         //GLUT 콜백함수 등록
    glutMainLoop();                     //이벤트 루프 진입
    return 0;
}
