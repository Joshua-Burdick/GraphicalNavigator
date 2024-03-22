extern "C" {
    #include "glm.h"
}
#include "Headers/Config.h"
#include "Headers/InputController.h"

GLMmodel* pmodel2 = NULL;
GLuint importRotate;
int modelSpin = 0;

void drawmodel_rosevase(void) {
    if (!pmodel2) {
        pmodel2 = glmReadOBJ((char*)"data/f-16.obj");
        if (!pmodel2) exit(0);
        glmUnitize(pmodel2);
        glmFacetNormals(pmodel2);
        glmVertexNormals(pmodel2, 90.0);
    }

    glmDraw(pmodel2, GLM_SMOOTH | GLM_MATERIAL);
}

void drawImportRotate() {
    //Rose vase - imported
    glPushMatrix();
    glScalef(0.1, 0.1, 0.1);
    drawmodel_rosevase();
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
    glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
    glVertex3f(X_MAX, Y_MAX, -Z_MAX);
    glVertex3f(-X_MAX, Y_MAX, -Z_MAX);
    glVertex3f(-X_MAX, Y_MAX, Z_MAX);
    glVertex3f(X_MAX, Y_MAX, Z_MAX);

    // Floor (y = -0.5f)
    glColor3f(1.0f, 0.5f, 0.0f);     // Orange
    glVertex3f(X_MAX, Y_MIN, Z_MAX);
    glVertex3f(-X_MAX, Y_MIN, Z_MAX);
    glVertex3f(-X_MAX, Y_MIN, -Z_MAX);
    glVertex3f(X_MAX, Y_MIN, -Z_MAX);

    // Front face  (z = 3.0f)
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(X_MAX, Y_MAX, Z_MAX);
    glVertex3f(-X_MAX, Y_MAX, Z_MAX);
    glVertex3f(-X_MAX, Y_MIN, Z_MAX);
    glVertex3f(X_MAX, Y_MIN, Z_MAX);

    // Left face (x = -1.5f)
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(-X_MAX, Y_MAX, Z_MAX);
    glVertex3f(-X_MAX, Y_MAX, -Z_MAX);
    glVertex3f(-X_MAX, Y_MIN, -Z_MAX);
    glVertex3f(-X_MAX, Y_MIN, Z_MAX);

    // Right face (x = 1.5f)
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(X_MAX, Y_MAX, -Z_MAX);
    glVertex3f(X_MAX, Y_MAX, Z_MAX);
    glVertex3f(X_MAX, Y_MIN, Z_MAX);
    glVertex3f(X_MAX, Y_MIN, -Z_MAX);

    glEnd();  // End of drawing a cube
}

void drawDoorway() {
    glBegin(GL_QUADS);
        // Back face: Door frame (z = -3.0f)
        glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
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
            glColor3f(0.5f, 0.5f, 0.5f);
            glTranslatef(0, -0.1f, 0);
            glRotatef(90, 1, 0, 0);
            gluCylinder(gluNewQuadric(), 0.2, 0.2, 0.7, 32, 32);
        glPopMatrix();

        glColor3f(0.5, 0.5, 1.0);
        glScalef(4.0,4.0,4.0);
        glRotatef(modelSpin, 0, 1, 0);
        glCallList(importRotate);
    glPopMatrix();
}

void display(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    // Where the camera is looking
    gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

    glTranslatef(XMOVE, 0, ZMOVE);

    glPushMatrix();
        drawRoom();
        glRotatef(180, 0, 1, 0);
        glTranslatef(0, 0, 6.0);
        drawRoom();
    glPopMatrix();

    // Draw doorway over door if in first room
    if (ZMOVE > Z_MAX) {
        drawDoorway();
    }

    // Draw pedestal model behind door if in first room
    if (ZMOVE < Z_MAX && doorAngle != 0.0f) {
        drawPedestalModel();
    }

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

    // Draw doorway behind door if in second room
    if (ZMOVE < Z_MAX) {
        drawDoorway();
    }

    // Draw pedestal model in front of door if in second room
    if (ZMOVE > Z_MAX) {
        drawPedestalModel();
    }

    glFlush();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    // Define window properties
    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition((screenWidth / 2) - (windowWidth / 2), (screenHeight / 2) - (windowHeight / 2));

    glEnable(GL_DEPTH_TEST);

    // Make window
    glutCreateWindow(WINDOW_NAME);

    // Display
    glMatrixMode(GL_PROJECTION);

    gluPerspective(60, aspect, 0, 10);

    importRotate = glGenLists(2);
    glNewList(importRotate, GL_COMPILE);
    drawImportRotate();
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