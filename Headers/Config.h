#pragma once
#include <GL/glut.h>
#include <stdio.h>

#define WINDOW_NAME "Nice Room Ya Got There. Be A Shame If Somebody-"

// Window dimensions
static int windowWidth = 1024;
static int windowHeight = 768;

static int screenWidth = 0, screenHeight = 0;
static int currentX = windowWidth / 2, currentY = windowHeight / 2;

// Aspect ratio
static float aspect = float(windowWidth) / float(windowHeight);

// Is camera rotating
static float spin = 0.0;
static bool rotating = false;

// Camera rotation limits
static const float Y_ROT_MAX = 0.93f;
static const float Y_ROT_MIN = -0.71f;

// Camera movement limits
static const float X_MAX = 1.5f;
static const float Y_MAX = 1.25f, Y_MIN = -0.75f;
static const float Z_MAX = 3.0f;

// Camera position vectors
static double eye[] = { 0,0,1 };
static double center[] = { 0,0,0 };
static double up[] = { 0,1,0 };

// Camera movement amounts
static float XMOVE = 0.0f, ZMOVE = 0.0f;

// Door animation
static float doorAngle = 0.0f;
static bool isDoorAnimating = false;

static void DoorRotate(int value) {
    if (!isDoorAnimating) return;
    value == 0 ? doorAngle += 5.0 : doorAngle -= 5.0;
    if (doorAngle == 90.0 || doorAngle == 0.0)
        isDoorAnimating = false;

    glutPostRedisplay();
    glutTimerFunc(30, DoorRotate, value);
}