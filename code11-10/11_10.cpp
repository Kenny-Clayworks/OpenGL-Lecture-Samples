#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <glaux.h>    // �ʹ� ������ glaux�� ������� �ʴ´�. 
#include <stdio.h>

// glaux�� ������� �ʰ� �ؽ��� ��Ʈ���� �ε��ϱ� ���� AUX_RGBImageRec ����ü�� �����ϰ� LoadBMP�� ���ۼ���
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>

typedef struct _AUX_RGBImageRec {
    GLint sizeX, sizeY;
    unsigned char* data;
} AUX_RGBImageRec;

GLfloat xrot = 0.9f, yrot = 0.8f, zrot = 1.0f;
unsigned int MyTextureObject[1];
AUX_RGBImageRec* pTextureImage[1];  //�ؽ��� ���� ������ ����Ű�� ������

void MyReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat) w / (GLfloat) h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  //�ո�
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  //�޸�
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  //����
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  //�Ʒ���
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  //������
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  //������
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();
    glutSwapBuffers();
}

void MyTimer(int Value) {
    glRotatef(xrot,1.0f,0.0f,0.0f);
    glRotatef(yrot,0.0f,1.0f,0.0f);
    glRotatef(zrot,0.0f,0.0f,1.0f);
    glutPostRedisplay();
    glutTimerFunc(50, MyTimer, 1);
}
/*
// auxDIBImageLoad�� �����Ǿ� �� �̻� �������� �ʴ´�.
AUX_RGBImageRec* LoadBMP(char* szFilename) { 
    FILE* pFile = NULL;
    if (!szFilename) {
        return NULL;
    }
    pFile = fopen(szFilename, "r");
    if (pFile) {
        fclose(pFile);
        return auxDIBImageLoad((WCHAR *)szFilename);     //���Ϸκ��� �޸𸮷�
    }
    return NULL;
}
*/
// BMP������ �о� AUX_RGBImageRec ����ü�� �����ϴ� LoadBMP �Լ��� ���� �ۼ���
AUX_RGBImageRec* LoadBMP(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return nullptr;
    }

    BITMAPFILEHEADER bfh;
    file.read(reinterpret_cast<char*>(&bfh), sizeof(BITMAPFILEHEADER));

    if (bfh.bfType != 0x4D42) { // "BM"
        std::cerr << "Not a BMP file: " << filename << std::endl;
        return nullptr;
    }

    BITMAPINFOHEADER bih;
    file.read(reinterpret_cast<char*>(&bih), sizeof(BITMAPINFOHEADER));

    if (bih.biBitCount != 24) {
        std::cerr << "Only 24-bit BMPs are supported." << std::endl;
        return nullptr;
    }

    AUX_RGBImageRec* texture = new AUX_RGBImageRec;
    texture->sizeX = bih.biWidth;
    texture->sizeY = bih.biHeight;

    int imageSize = texture->sizeX * texture->sizeY * 3;
    texture->data = new unsigned char[imageSize];

    // Move file pointer to the beginning of bitmap data
    file.seekg(bfh.bfOffBits, std::ios::beg);

    // Calculate padding
    int padding = (4 - (texture->sizeX * 3) % 4) % 4;

    // Read the bitmap data
    std::vector<unsigned char> row(texture->sizeX * 3 + padding);
    for (int y = texture->sizeY - 1; y >= 0; y--) { // BMP is stored bottom-to-top
        file.read(reinterpret_cast<char*>(row.data()), row.size());
        for (int x = 0; x < texture->sizeX; x++) {
            int i = (y * texture->sizeX + x) * 3;
            texture->data[i] = row[x * 3 + 2];     // Red
            texture->data[i + 1] = row[x * 3 + 1]; // Green
            texture->data[i + 2] = row[x * 3];     // Blue
        }
    }

    file.close();
    return texture;
}

int LoadGLTextures(char* szFilePath){       //������ �ε��ϰ� �ؽ��ķ� ��ȯ
    int Status = FALSE;
    glClearColor(0.0, 0.0, 0.0, 0.5);
    memset(pTextureImage, 0, sizeof(void*) * 1);    //�����͸� �η�

    if (pTextureImage[0] = LoadBMP((char *)szFilePath)) {   //��Ʈ���� �ε��ϰ� ����Ȯ��
        Status = TRUE;                              //���� �÷��� True��
        glGenTextures(1, &MyTextureObject[0]);      //�ؽ��� ����
        glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3,
            pTextureImage[0]->sizeX, pTextureImage[0]->sizeY,
            0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[0]->data);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glEnable(GL_TEXTURE_2D);
    }
    if (pTextureImage[0]) {                 //�ؽ��İ� �����ϸ�
        if (pTextureImage[0]->data) {       //�ؽ��� ������ �����ϸ�
            free(pTextureImage[0]->data);   //�ؽ��� ������� �ݳ�
        }
        free(pTextureImage[0]);             //�ؽ��� �ݳ�
    }
    return Status;
}

void main(int argc, char** argv) {
    if (argc <= 1) {
        printf("\n%s\n\n","Usage : TextureDLG3_Consol.exe [BMPFileName.bmp]");
        exit(1);
    }
    else if (argc > 2) {
        printf("\nToo Many Arguments!\nArgument is Only one\n");
        exit(1);
    }
    else { 
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutCreateWindow("OpenGL Sample Program");
        glutDisplayFunc(MyDisplay);
        glutReshapeFunc(MyReshape);
        glutTimerFunc(500, MyTimer, 1);

        if (LoadGLTextures(argv[1])) {
            glEnable(GL_TEXTURE_2D);
            glShadeModel(GL_SMOOTH);
            glClearDepth(1.0);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
            glutMainLoop();
        }
    }
}
