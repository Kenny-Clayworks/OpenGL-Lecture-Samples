#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glColor3f(0.62, 0.45, 0.35);
    glBegin(GL_POLYGON);
        glVertex3f(-.9, -.9, .1);
        glVertex3f(.9, -.9, .1);
        glVertex3f(.9, .9, .1);
        glVertex3f(-.9, .9, .1);
    glEnd();
    glColor3f(.92, .63, .45);
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.0, 0.5, 0.5);
    glEnd();
    glDepthMask(GL_TRUE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-.9, -.9, .1);
        glVertex3f(.9, -.9, .1);
        glVertex3f(.9, .9, .1);
        glVertex3f(-.9, .9, .1);
    glEnd();
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Drawing Example");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}
