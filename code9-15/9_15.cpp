#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define GAP     16

void redisplay_all();

GLuint    window, world, screen, command;
GLfloat   fDelta = 0.0f;
GLboolean bBlend = true;
GLboolean bSmooth = true;
GLfloat   Red = 0.0;
GLfloat   Green = 0.0;
GLfloat   Blue = 0.0;
GLint     Index = 0;

unsigned char PALETTE[16][3] = {
    { 255, 255, 255 },      // WHITE
    {   0, 255, 255 },      // CYAN
    { 255,   0, 255 },      // PURPLE
    {   0,   0, 255 },      // BLUE
    { 192, 192, 192 },      // LIGHT GRAY
    { 128, 128, 128 },      // DARK GRAY
    {   0, 128, 128 },      // DARK TEAL
    { 128,   0, 128 },      // DARK PURPLE
    {   0,   0, 128 },      // DARK BLUE
    { 255, 255,   0 },      // YELLOW
    {   0, 255,   0 },      // GREEN
    { 128, 128,   0 },      // DARK YELLOW
    {   0, 128,   0 },      // DARK GREEN
    { 255,   0,   0 },      // RED
    { 128,   0,   0 },      // DARK RED
    {   0,   0,   0 },      // BLACK
};

void world_display() {
    Red   = PALETTE[Index][0] / 255.0f;
    Green = PALETTE[Index][1] / 255.0f;
    Blue  = PALETTE[Index][2] / 255.0f;
    glColor3f(Red, Green, Blue);
    if (bBlend) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    if (bSmooth) {
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    }
    glBegin(GL_LINES);
        glVertex3f(-1.0 + fDelta,  1.0, 0.0);
        glVertex3f( 1.0 - fDelta, -1.0, 0.0);
        glVertex3f(-1.0, -1.0 + fDelta, 0.0);
        glVertex3f( 1.0,  1.0 - fDelta, 0.0);
    glEnd();
    if (bSmooth)
        glDisable(GL_LINE_SMOOTH);
    if (bBlend)
        glDisable(GL_BLEND);
    glutSwapBuffers();
}

void world_timer(int Value) {
    if (fDelta< 2.0f) {
        fDelta = fDelta + 0.1;
    }
    else {
        fDelta = 0.0;
        if (++Index >= 15) {
            Index = 0;
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }
    redisplay_all();
    glutTimerFunc(100, world_timer, 1);
}

void screen_display() {
    static unsigned char buffer[128 * 128 * 4 * 2];
    glutSetWindow(world);
    glReadPixels(0, 0, 128, 128, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glutSetWindow(screen);
    glPixelZoom(4, 4);
    glDrawPixels(128, 128, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glPixelZoom(0, 0);
    glutSwapBuffers();
}

void main_display() {
    glClearColor(0.8, 0.8, 0.8, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

void main_keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'b':   bBlend = !bBlend;   break;      //혼합 함수 사용
    case 's':   bSmooth = !bSmooth; break;      //스무딩 함수 사용
    case 't':   if (!bBlend)
                    bBlend = bSmooth = true;    //두가지 함수 모두 사용
                else
                    bBlend = bSmooth = false;   //두가지 함수 모두 사용안함
                break;
    case 27:    exit(0);
    }
}

void redisplay_all() {
//    glutSetWindow(command);
//    glutPostRedisplay();
    glutSetWindow(world);
    glutPostRedisplay();
    glutSetWindow(screen);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(128 + 512 + GAP * 3, 512 + GAP * 2);
    glutInitWindowPosition(0, 0);
    glutInit(&argc, argv);

    window = glutCreateWindow("Line Antialiasing Demo");
    glutDisplayFunc(main_display);
    glutKeyboardFunc(main_keyboard);

    world = glutCreateSubWindow(window, GAP, GAP, 128, 128);
    glutDisplayFunc(world_display);
    glutKeyboardFunc(main_keyboard);

    screen = glutCreateSubWindow(window, GAP + 128 + GAP, GAP, 512, 512);
    glutDisplayFunc(screen_display);
    glutKeyboardFunc(main_keyboard);

    redisplay_all();
    glutTimerFunc(100, world_timer, 1);
    glutMainLoop();
    return 0;
}
