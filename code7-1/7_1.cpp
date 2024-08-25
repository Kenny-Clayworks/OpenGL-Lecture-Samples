#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

int Width, Height;

void Init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );

    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );
}

void DrawScene() {
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
        glTranslatef(0.0, -1.0, 0.0);
        glBegin(GL_QUADS);
            glVertex3f(2.0, 0.0, 2.0);
            glVertex3f(2.0, 0.0, -2.0);
            glVertex3f(-2.0, 0.0, -2.0);
            glVertex3f(-2.0, 0.0, 2.0);
        glEnd();
    glPopMatrix();

    glColor3f(0.3, 0.3, 0.7);
    glPushMatrix();
        glTranslatef(0.0, 0.0, -0.5);
        glutWireTeapot(1.0);
    glPopMatrix();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glViewport(0, 0, Width/2, Height/2);
    glPushMatrix();
        gluLookAt(0.0, 0.0, 1.0,   0.0, 0.0, 0.0,   0.0, 1.0, 0.0);
        DrawScene();
    glPopMatrix();
    glViewport(Width/2, 0, Width/2, Height/2);
    glPushMatrix();
        gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
        DrawScene();
    glPopMatrix();
    glViewport(0, Height/2, Width/2, Height/2);
    glPushMatrix();
        gluLookAt(0.0, 1.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, -1.0);
        DrawScene();
    glPopMatrix();
    glViewport(Width/2, Height/2, Width/2, Height/2);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        gluPerspective(30, 1.0, 3.0, 50.0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            gluLookAt(5.0, 5.0, 5.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
            DrawScene();
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glFlush();
}

void MyReshape(int w, int h) {
    Width = w;
    Height = h;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    Width = 500;
    Height = 500;
    glutInitDisplayMode(GLUT_SINGLE |GLUT_RGBA);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Sample Drawing");
    Init();
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutMainLoop();
    return 0;
}
