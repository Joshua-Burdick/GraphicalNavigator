#pragma once
#include "CameraController.h"

class InputController {
    public:
        static void Keyboard(unsigned char key, int x, int y) {
            switch (key) {
                // ESC key to exit
                case 27: exit(0); break;
                case 'W':
                case 'w':
                    ZMOVE += eye[2] * 0.2;
                    XMOVE += eye[0] * 0.2;
                    break;
                case 'S':
                case 's':
                    ZMOVE -= eye[2] * 0.2;
                    XMOVE -= eye[0] * 0.2;
                    break;
                case 'A':
                case 'a':
                    XMOVE += eye[2] * 0.2;
                    ZMOVE -= eye[0] * 0.2;
                    break;
                case 'D':
                case 'd':
                    XMOVE -= eye[2] * 0.2;
                    ZMOVE += eye[0] * 0.2;
                    break;
                case 'r':
                    eye[0] = 0; eye[1] = 0; eye[2] = 1;
                    up[0] = 0; up[1] = 1; up[2] = 0;
                    break;
                // Space bar to open door
                case 32:
                    if (isDoorAnimating || abs(-Z_MAX + ZMOVE) > 1.0f) break;
                    isDoorAnimating = true;
                    if (doorAngle == 0.0) glutTimerFunc(30, DoorRotate, 0);
                    else glutTimerFunc(30, DoorRotate, 1);
                    break;
            }

            // Wall boundaries
            if (XMOVE >= X_MAX - 0.3) XMOVE = X_MAX - 0.3;
            else if (XMOVE <= -X_MAX + 0.3) XMOVE = -X_MAX + 0.3;

            if (ZMOVE > Z_MAX - 0.3 && ZMOVE < Z_MAX && (XMOVE > X_MAX / 2 || XMOVE < -X_MAX / 2 || doorAngle == 0.0f)) ZMOVE = Z_MAX - 0.3;
            else if (ZMOVE < Z_MAX + 0.3 && ZMOVE > Z_MAX && (XMOVE > X_MAX / 2 || XMOVE < -X_MAX / 2 || doorAngle == 0.0f)) ZMOVE = Z_MAX + 0.3;
            else if (ZMOVE > 3*Z_MAX - 0.3) ZMOVE = Z_MAX - 0.3;
            else if (ZMOVE < -Z_MAX + 0.3) ZMOVE = -Z_MAX + 0.3;

            glutPostRedisplay();
        }

        // Special keys callback
        static void SpecialKeys(int key, int x, int y) {
            switch (key) {
                case GLUT_KEY_LEFT: CameraController::Left(32); break;
                case GLUT_KEY_RIGHT: CameraController::Right(32); break;
                case GLUT_KEY_UP:    CameraController::Up(32); break;
                case GLUT_KEY_DOWN:  CameraController::Down(32); break;
            }

            glutPostRedisplay();
        }

        static void PassiveMouseMove(int x, int y) {
            if (x - currentX > 0) CameraController::Right(128);
            else if (x - currentX < 0) CameraController::Left(128);

            if (y - currentY > 0) CameraController::Down(128);
            else if (y - currentY < 0) CameraController::Up(128);

            currentX = x;
            currentY = y;

            if (x < 100 || x > windowWidth - 100) {
                currentX = windowWidth/2;
                currentY = windowHeight/2;   
                glutWarpPointer(windowWidth/2, windowHeight/2);
            } else if (y < 100 || y > windowHeight - 100) {
                currentX = windowWidth/2;
                currentY = windowHeight/2;
                glutWarpPointer(windowWidth/2, windowHeight/2);
            }

            glutPostRedisplay();
        }
};