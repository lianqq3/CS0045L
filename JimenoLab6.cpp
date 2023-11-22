#include <GL/freeglut.h>

GLfloat zoom = 1.0f;
GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;

void specialKeys(int key, int x, int y);
void display();
void reshape(int width, int height);
void mouseWheel(int wheel, int direction, int x, int y);
void drawOctahedron();
void initOpenGL();
void setMaterialAndLight();
void setCamera();
void applyRotation();
void setViewport(int width, int height);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lab6 Jimeno Pink Octahedron");

    initOpenGL();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutMouseWheelFunc(mouseWheel);

    glutMainLoop();
    return 0;
}

void initOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void setMaterialAndLight() {
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightPos[] = {1.0f, 1.0f, 1.0f, 0.0f};
    for (int i = 0; i < 3; ++i) {
        glEnable(GL_LIGHT0 + i);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, lightColor);
        glLightfv(GL_LIGHT0 + i, GL_POSITION, lightPos);
    }

    GLfloat pinkColor[] = {1.0f, 0.75f, 0.8f, 1.0f};  
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pinkColor);
}

void setCamera() {
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0 * zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void applyRotation() {
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
}

void setViewport(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void drawOctahedron() {
    glutSolidOctahedron();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setCamera();
    applyRotation();
    setMaterialAndLight();
    drawOctahedron();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    setViewport(width, height);
}

void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT) angleY += 5.0f;
    else if (key == GLUT_KEY_LEFT) angleY -= 5.0f;
    else if (key == GLUT_KEY_UP) angleX += 5.0f;
    else if (key == GLUT_KEY_DOWN) angleX -= 5.0f;

    glutPostRedisplay();
}

void mouseWheel(int wheel, int direction, int x, int y) {
    if (direction == 1) {
        zoom *= 1.1f;
    } else {
        zoom /= 1.1f;
    }

    glutPostRedisplay();
}

