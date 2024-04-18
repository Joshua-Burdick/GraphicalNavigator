extern "C" {
    #include "glm.h"
}
#include <string>
#include "Headers/Config.h"
#include "Headers/Materials.h"
#include "Headers/InputController.h"

GLMmodel* pmodel2 = NULL;
GLuint importRotate;
int modelSpin = 0;

struct Light {
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat position[4];
};

//Setting White Light Source RGBA
GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 },
light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 },
light_specular[] = { 0.6, 0.6, 0.6, 1.0 },
light_position[] = { 0.0, 1.0, 0.0, 1.0 },
light_position2[] = { 0.0, 1.0, -6.0, 1.0 };

void set_material_props(Material material) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}

void set_light_props() {
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
    glEnable(GL_LIGHT2);

    glEnable(GL_LIGHTING);
}

void drawmodel(std::string modelName) {
    if (!pmodel2) {
        std::string filename = "data/" + modelName + ".obj";
        pmodel2 = glmReadOBJ((char*)filename.c_str());
        if (!pmodel2) exit(0);
        glmUnitize(pmodel2);
        glmFacetNormals(pmodel2);
        glmVertexNormals(pmodel2, 90.0);
    }

    glmDraw(pmodel2, GLM_SMOOTH);
    pmodel2 = NULL;
}

void drawImportRotate(std::string modelName) {
    glPushMatrix();
    glScalef(0.1, 0.1, 0.1);
    drawmodel(modelName);
    glPopMatrix();
}

void TimerRotate(int value) {
    modelSpin += 1;

    if (modelSpin > 360.0)
        modelSpin -= 360.0;

    glutPostRedisplay();
    glutTimerFunc(30, TimerRotate, 0);
}

void drawRoom() {
    glBegin(GL_QUADS);

    // Ceiling (y = 1.25f)
    glVertex3f(X_MAX, Y_MAX, -Z_MAX);
    glVertex3f(-X_MAX, Y_MAX, -Z_MAX);
    glVertex3f(-X_MAX, Y_MAX, Z_MAX);
    glVertex3f(X_MAX, Y_MAX, Z_MAX);

    // Floor (y = -0.5f)
    glVertex3f(X_MAX, Y_MIN, Z_MAX);
    glVertex3f(-X_MAX, Y_MIN, Z_MAX);
    glVertex3f(-X_MAX, Y_MIN, -Z_MAX);
    glVertex3f(X_MAX, Y_MIN, -Z_MAX);

    // Front face  (z = 3.0f)
    glVertex3f(X_MAX, Y_MAX, Z_MAX);
    glVertex3f(-X_MAX, Y_MAX, Z_MAX);
    glVertex3f(-X_MAX, Y_MIN, Z_MAX);
    glVertex3f(X_MAX, Y_MIN, Z_MAX);

    // Left face (x = -1.5f)
    glVertex3f(-X_MAX, Y_MAX, Z_MAX);
    glVertex3f(-X_MAX, Y_MAX, -Z_MAX);
    glVertex3f(-X_MAX, Y_MIN, -Z_MAX);
    glVertex3f(-X_MAX, Y_MIN, Z_MAX);

    // Right face (x = 1.5f)
    glVertex3f(X_MAX, Y_MAX, -Z_MAX);
    glVertex3f(X_MAX, Y_MAX, Z_MAX);
    glVertex3f(X_MAX, Y_MIN, Z_MAX);
    glVertex3f(X_MAX, Y_MIN, -Z_MAX);

    glEnd();  // End of drawing a cube
}

void drawDoorway() {
    glBegin(GL_QUADS);
        // Back face: Door frame (z = -3.0f)
        glVertex3f(X_MAX, Y_MIN, -Z_MAX);
        glVertex3f(X_MAX / 2, Y_MIN, -Z_MAX);
        glVertex3f(X_MAX / 2, Y_MAX / 2, -Z_MAX);
        glVertex3f(X_MAX, Y_MAX / 2, -Z_MAX);

        glVertex3f(-X_MAX, Y_MIN, -Z_MAX);
        glVertex3f(-X_MAX / 2, Y_MIN, -Z_MAX);
        glVertex3f(-X_MAX / 2, Y_MAX / 2, -Z_MAX);
        glVertex3f(-X_MAX, Y_MAX / 2, -Z_MAX);

        glVertex3f(X_MAX, Y_MAX / 2, -Z_MAX);
        glVertex3f(-X_MAX, Y_MAX / 2, -Z_MAX);
        glVertex3f(-X_MAX, Y_MAX, -Z_MAX);
        glVertex3f(X_MAX, Y_MAX, -Z_MAX);
    glEnd();
}

void drawPedestalModel() {
    glPushMatrix();
        glTranslatef(0, 0, -7.0);

        glPushMatrix();
            glTranslatef(0, -0.1f, 0);
            glRotatef(90, 1, 0, 0);
            gluCylinder(gluNewQuadric(), 0.2, 0.2, 0.7, 32, 32);
        glPopMatrix();

        glScalef(4.0,4.0,4.0);
        glRotatef(modelSpin, 0, 1, 0);
        glCallList(importRotate);
    glPopMatrix();
}

void drawTeapotCube() {
    // Teapot Cube
    glPushMatrix();
        set_material_props(ShadedCube);
        glTranslatef(0, -0.5, 1.5);
        glutSolidCube(0.75);

        set_material_props(DiffuseTeapot);
        glTranslatef(0, 0.45, 0.25);
        glutSolidTeapot(0.1);

        set_material_props(MetallicTeapot);
        glTranslatef(-0.25, 0, -0.5);
        glutSolidTeapot(0.1);

        set_material_props(GlossyTeapot);
        glTranslatef(0.5, 0, 0);
        glutSolidTeapot(0.1);
    glPopMatrix();
}

void display(void) {
    set_material_props(WallMaterial);
    set_light_props();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    // Where the camera is looking
    gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

    glTranslatef(XMOVE, 0, ZMOVE);

    // Room
    glPushMatrix();
        drawRoom();
        glRotatef(180, 0, 1, 0);
        glTranslatef(0, 0, 6.0);
        drawRoom();
    glPopMatrix();

    // Teapot Cube
    drawTeapotCube();

    // Porsche
    glPushMatrix();
        set_material_props(DiffuseTeapot);
        glTranslatef(0.85, -0.5, 1.25);
        glRotatef(225, 0, 1, 0);
        glScalef(3.0, 3.0, 3.0);
        glCallList(importRotate + 1);
    glPopMatrix();

    glPushMatrix();
        set_material_props(MetallicTeapot);
        glTranslatef(-0.9, -0.2, -1.0);
        glRotatef(60, 0, 1, 0);
        glScalef(6.0, 6.0, 6.0);
        glCallList(importRotate + 3);
    glPopMatrix();

    set_material_props(WallMaterial);

    // Doorway
    drawDoorway();

    // Door
    glPushMatrix();
        glTranslatef(-X_MAX / 2, 0, -Z_MAX);
        glRotatef(doorAngle, 0, 1, 0);
        glTranslatef(X_MAX / 2, 0, Z_MAX);

        glBegin(GL_QUADS);
            glColor3f(0.5f, 0.5f, 0.5f); // Gray
            glVertex3f(X_MAX / 2, Y_MIN, -Z_MAX);
            glVertex3f(-X_MAX / 2, Y_MIN, -Z_MAX);
            glVertex3f(-X_MAX / 2, Y_MAX / 2, -Z_MAX);
            glVertex3f(X_MAX / 2, Y_MAX / 2, -Z_MAX);
        glEnd();
    glPopMatrix();

    drawPedestalModel(); // F-16

    // Soccerball
    glPushMatrix();
        glTranslatef(1.0, -0.5, -8.0);
        glScalef(2.0, 2.0, 2.0);
        glCallList(importRotate + 2);
    glPopMatrix();

    glFlush();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    // Define window properties
    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition((screenWidth / 2) - (windowWidth / 2), (screenHeight / 2) - (windowHeight / 2));

    // Make window
    glutCreateWindow(WINDOW_NAME);
    glEnable(GL_DEPTH_TEST);

    // Display
    glMatrixMode(GL_PROJECTION);

    gluPerspective(60, aspect, 0.0001, 20);

    importRotate = glGenLists(3);
    glNewList(importRotate, GL_COMPILE);
    drawImportRotate("f-16");
    glEndList();

    glNewList(importRotate + 1, GL_COMPILE);
    drawImportRotate("porsche");
    glEndList();

    glNewList(importRotate + 2, GL_COMPILE);
    drawImportRotate("soccerball");
    glEndList();

    glNewList(importRotate + 3, GL_COMPILE);
    drawImportRotate("al");
    glEndList();

    glutDisplayFunc(display);
    glutKeyboardFunc(InputController::Keyboard);
    glutSpecialFunc(InputController::SpecialKeys);
    glutPassiveMotionFunc(InputController::PassiveMouseMove);

    glutTimerFunc(30, TimerRotate, 0);

    glutSetCursor(GLUT_CURSOR_NONE);

    glutMainLoop();

    return 0;
}