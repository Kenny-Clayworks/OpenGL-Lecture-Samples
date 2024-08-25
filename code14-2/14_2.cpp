#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

//#pragma comment(linker, "/SUBSYSTEM:WINDOWS")   //도스창 안 뜨게 하기
//#pragma comment(linker, "/ENTRY:mainCRTStartup")

static GLfloat w[4][4] = {              //제어점 각각의 가중치 배열
    { 1.0, 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 },
    { 1.0, 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 },
};
static GLfloat ctlpointsCoordi[4][4][4];        //제어점의 화면상 위치
static GLfloat ctlpoints[4][4][4];              //제어점 배열
GLfloat knots[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };  //나트벡터
static GLUnurbsObj* theNurbs;                   //너브스 객체
GLint width = 300, height = 300;                //화면 너비와 높이
GLfloat point_mat_diffuse[]     = { 1.0, 0.5, 1.0, 1.0 };       //제어점 색
GLfloat point_mat_specular[]    = { 0.8, 0.0, 0.8, 0.0 };
GLfloat point_mat_emission[]    = { 0.0, 0.0, 0.0, 1.0 };
GLfloat point_mat_shininess[]   = { 30.0 };
GLfloat surface_mat_diffuse[]   = { 0.8, 0.8, 0.2, 1.0 };       //곡면의 색
GLfloat surface_mat_specular[]  = { 0.8, 0.0, 0.8, 0.0 };
GLfloat surface_mat_emission[]  = { 0.0, 0.0, 0.0, 1.0 };
GLfloat surface_mat_shininess[] = { 30.0 };


void InitSurface() {                    //제어점 위치 초기화
    int s, t;
    for (s = 0; s < 4; s++) {           //x, y, z 방향으로 -3에서 +3까지
        for (t = 0; t < 4; t++) {
            ctlpointsCoordi[s][t][0] = 2.0 * ((GLfloat)s - 1.5);
            ctlpointsCoordi[s][t][2] = 2.0 * ((GLfloat)t - 1.5);
            if ((s == 1 || s == 2) && (t == 1 || t == 2))
                ctlpointsCoordi[s][t][1] = 3.0;
            else
                ctlpointsCoordi[s][t][1] = -3.0;
            for (int k = 0; k < 3; k++)
                ctlpoints[s][t][k] = w[s][t] * ctlpointsCoordi[s][t][k];    //제어점 정보 초기화
            ctlpoints[s][t][3] = w[s][t];
        }
    }
}

void Init() {
    GLfloat light0_position[] = { 3.0, 1.0, 1.0, 1.0 };
    GLfloat light1_position[] = { -3.0, 1.0, 1.0, 1.0 };
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_AUTO_NORMAL);
    InitSurface();
    theNurbs = gluNewNurbsRenderer();
}

void MyReshape(GLint w, GLint h) {
    width = w;
    height = h;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(33.0, (GLfloat) w / (GLfloat) h, 3.0, 20.0);
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -15.0);
    glPushMatrix();
        glRotatef(45.0, 1.0, 0.0, 0.0);
        for (int i = 0; i < 4; i++) {               //제어점 위치 표시하기
            for (int j = 0; j < 4; j++) {
                glPushMatrix();
                    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, point_mat_diffuse);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, point_mat_specular);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, point_mat_emission);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, point_mat_shininess);
                    glPointSize(5.0);
                    glBegin(GL_POINTS);
                        glVertex3f(ctlpointsCoordi[i][j][0],
                            ctlpointsCoordi[i][j][1],
                            ctlpointsCoordi[i][j][2]);
                    glEnd();
                glPopMatrix();
            }
        }
        glPushMatrix();
            for (int i = 0; i < 4; i++) {           //제어 그래프 표시하기
                for (int j = 0; j < 3; j++) {
                    glBegin(GL_LINES);
                        glVertex3f(ctlpointsCoordi[i][j][0],
                            ctlpointsCoordi[i][j][1],
                            ctlpointsCoordi[i][j][2]);
                        glVertex3f(ctlpointsCoordi[i][j+1][0],
                            ctlpointsCoordi[i][j+1][1],
                            ctlpointsCoordi[i][j+1][2]);
                    glEnd();
                }
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 4; j++) {
                    glBegin(GL_LINES);
                    glVertex3f(ctlpointsCoordi[i][j][0],
                        ctlpointsCoordi[i][j][1],
                        ctlpointsCoordi[i][j][2]);
                    glVertex3f(ctlpointsCoordi[i+1][j][0],
                        ctlpointsCoordi[i+1][j][1],
                        ctlpointsCoordi[i+1][j][2]);
                    glEnd();
                }
            }
        glPopMatrix();
        glPushMatrix();
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, surface_mat_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, surface_mat_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, surface_mat_emission);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, surface_mat_shininess);
            gluBeginSurface(theNurbs);
                gluNurbsSurface(theNurbs, 8, knots, 8, knots, 4 * 4, 4,
                    &ctlpoints[0][0][0], 4, 4, GL_MAP2_VERTEX_4);
            gluEndSurface(theNurbs);
        glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}

void main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("NURBS Surface");
    Init();
    glutReshapeFunc(MyReshape);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
}
