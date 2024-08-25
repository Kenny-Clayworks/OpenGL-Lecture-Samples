#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);       //컬러버퍼에 초기화 색을 가함
    glColor3f(0.5, 0.5, 0.5);           //회색
    glBegin(GL_POLYGON);                //사각형
        glVertex3f(-0.5, -0.5, 0.0);    //좌하단 좌표
        glVertex3f(0.5, -0.5, 0.0);     //좌하단 좌표
        glVertex3f(0.5, 0.5, 0.0);      //우상단 좌표
        glVertex3f(-0.5, 0.5, 0.0);     //좌상단 좌표
    glEnd();
    glFlush();
}

void MyReshape(int NewWidth, int NewHeight) {
    glViewport(0, 0, NewWidth, NewHeight);
    GLfloat WidthFactor = (GLfloat) NewWidth / (GLfloat) 300;
    GLfloat HeightFactor = (GLfloat) NewHeight / (GLfloat) 300;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor,
        -1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Example Drawing");
    glClearColor(1.0, 1.0, 1.0, 1.0);   //초기화 색은 백색
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutMainLoop();
    return 0;
}
