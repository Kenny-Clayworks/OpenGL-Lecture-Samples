#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <io.h>
#include <stdlib.h>

//#pragma comment(linker, "/SUBSYSTEM:WINDOWS")   //도스창 안뜨게 하기
//#pragma comment(linker, "/ENTRY:mainCRTStartup")

GLhandleARB h_vertex, h_frag, h_program;        //전역변수
GLint width = 300, height = 300;                //화면 폭과 높이

char* SourceRead(char* fileName) {      //셰이더 소스파일을 읽어서 문자열로 바꾸는 함수
    FILE* p_Sourcefile = NULL;
    char* contents = NULL;
    int length = 0;
    if (fileName != NULL) {
        int tempfile = _open(fileName, _A_RDONLY);
        length = _lseek(tempfile, 0, SEEK_END); //메모리 할당을 위해 소스파일의 길이 알아보기
        _close(tempfile);

        p_Sourcefile = fopen(fileName, "rt");
        if (p_Sourcefile != NULL) {
            if (0 < length) {
                contents = (char*) malloc(sizeof(char) * (length + 1));         //소스파일 길이만큼 메모리 할당
                length = fread(contents, sizeof(char), length, p_Sourcefile);   //소스파일을 메모리로
                contents[length] = '\0';                                        //문자열에 종료문자 넣기
            }
            fclose(p_Sourcefile);
        }
    }
    return contents;
}

void MyReshape(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, (GLfloat) width / (GLfloat) height, 1.0, 10.0);
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    glutSolidTeapot(1);
    glutSwapBuffers();
}

void InitShaders() {
    char *vertex_source, *frag_source;      //셰이더 생성하기
    h_vertex = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
    h_frag   = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
    vertex_source = SourceRead((char *)"glsl_example.vert");
    frag_source   = SourceRead((char *)"glsl_example.frag");
    const char* p_vertex_source = vertex_source;
    const char* p_frag_source   = frag_source;
    glShaderSourceARB(h_vertex, 1, &p_vertex_source, NULL);
    glShaderSourceARB(h_frag, 1, &p_frag_source, NULL);
    free(vertex_source);
    free(frag_source);

    glCompileShaderARB(h_vertex);
    glCompileShaderARB(h_frag);
    h_program = glCreateProgramObjectARB();     //프로그램 생성하기
    glAttachObjectARB(h_program, h_vertex);
    glAttachObjectARB(h_program, h_frag);
    glLinkProgramARB(h_program);
    glUseProgramObjectARB(h_program);
}

void Init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_AUTO_NORMAL);
    GLfloat light0_diffuse[]  = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat light0_ambient[]  = { 0.8, 0.0, 0.0, 1.0 };
    GLfloat light0_position[] = { 0.8, -0.5, 2.3, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    InitShaders();
}

void main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("GLSL Example Program");
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glewInit();
    if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader) {   //GLSL 지원여부 확인
        Init();
        glutMainLoop();
    }
}
