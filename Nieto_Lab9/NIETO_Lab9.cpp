#include <GL/glut.h>
#include <cmath>

float camX = 0, camY = 0, camZ = 12;
float yaw = 0, pitch = 0;

float rotX = 0, rotY = 0;

float diamondSize = 2.0f;

float sphereDist = 5.0f;
float sphereRadius = 0.5f;

float vertices[6][3] = {
    {0, diamondSize, 0},
    {0, -diamondSize, 0},
    {-diamondSize, 0, 0},
    {diamondSize, 0, 0},
    {0, 0, diamondSize},
    {0, 0, -diamondSize}
};

int faces[8][3] = {
    {0, 4, 3}, {0, 3, 5}, {0, 5, 2}, {0, 2, 4},
    {1, 3, 4}, {1, 5, 3}, {1, 2, 5}, {1, 4, 2}
};

float sphereColors[3][4] = {
    {1, 0, 0, 1},
    {0, 0, 1, 1},
    {1, 1, 0, 1}
};

float spherePos[3][3] = {
    { sphereDist, 0, 0},
    {-sphereDist / 2, 0,  sphereDist * 0.866f},
    {-sphereDist / 2, 0, -sphereDist * 0.866f}
};

void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    GLfloat ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    for (int i = 0; i < 3; i++) {
        GLenum light = GL_LIGHT0 + i;
        glEnable(light);

        GLfloat pos[] = { spherePos[i][0], spherePos[i][1], spherePos[i][2], 1.0f };
        GLfloat color[] = { sphereColors[i][0], sphereColors[i][1], sphereColors[i][2], 1.0f };
        glLightfv(light, GL_POSITION, pos);
        glLightfv(light, GL_DIFFUSE, color);
        glLightfv(light, GL_SPECULAR, color);

        GLfloat dir[] = { -spherePos[i][0], -spherePos[i][1], -spherePos[i][2] };
        glLightfv(light, GL_SPOT_DIRECTION, dir);
        glLightf(light, GL_SPOT_CUTOFF, 40.0f);
        glLightf(light, GL_SPOT_EXPONENT, 15.0f);
    }
}

void drawDiamond() {
    GLfloat matDiff[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matDiff);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 8; i++) {
        int* f = faces[i];
        glVertex3fv(vertices[f[0]]);
        glVertex3fv(vertices[f[1]]);
        glVertex3fv(vertices[f[2]]);
    }
    glEnd();
}

void drawSpheres() {
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(spherePos[i][0], spherePos[i][1], spherePos[i][2]);

        GLfloat matEmission[] = { sphereColors[i][0], sphereColors[i][1], sphereColors[i][2], 1.0f };
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmission);

        GLfloat zero[] = { 0, 0, 0, 1 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, zero);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, zero);

        glutSolidSphere(sphereRadius, 20, 20);

        GLfloat noEmission[] = { 0, 0, 0, 1 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, noEmission);

        glPopMatrix();
    }
}

void updateCamera() {
    glLoadIdentity();
    float lx = sin(yaw) * cos(pitch);
    float ly = sin(pitch);
    float lz = -cos(yaw) * cos(pitch);
    gluLookAt(camX, camY, camZ, camX + lx, camY + ly, camZ + lz, 0, 1, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    updateCamera();
    setupLighting();

    glPushMatrix();
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);

    drawSpheres();
    drawDiamond();
    glPopMatrix();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int) {
    float moveSpeed = 0.2f, rotSpeed = 5.0f;
    if (key == 'w') camZ -= moveSpeed;
    if (key == 's') camZ += moveSpeed;
    if (key == 'a') camX -= moveSpeed;
    if (key == 'd') camX += moveSpeed;
    if (key == 'q') camY -= moveSpeed;
    if (key == 'e') camY += moveSpeed;
    if (key == 'i') rotX -= rotSpeed;
    if (key == 'k') rotX += rotSpeed;
    if (key == 'j') rotY -= rotSpeed;
    if (key == 'l') rotY += rotSpeed;

    glutPostRedisplay();
}

void arrows(int key, int, int) {
    float s = 0.05f;
    if (key == GLUT_KEY_LEFT) yaw -= s;
    if (key == GLUT_KEY_RIGHT) yaw += s;
    if (key == GLUT_KEY_UP) pitch += s;
    if (key == GLUT_KEY_DOWN) pitch -= s;
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)w / h, 0.1f, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(900, 700);
    glutCreateWindow("NIETO_Lab9");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrows);

    glutMainLoop();
    return 0;
}
