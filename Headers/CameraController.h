#pragma once
#include "Config.h"
#include "MathController.h"

class CameraController {
    public:
        static void Left(int speedFactor) {
            double speed = 3.1415 / speedFactor;

            MathController::rotatePoint(up, speed, eye);
        };

        static void Right(int speedFactor) {
            double speed = 3.1415 / speedFactor;

            MathController::rotatePoint(up, -speed, eye);
        };

        static void Up(int speedFactor) {
            double speed = 3.1415 / speedFactor;
            double rot_axis[3];
            double look[3];

            look[0] = -eye[0];
            look[1] = -eye[1];
            look[2] = -eye[2];

            // Accounting for change in direction of 'up' vector
            MathController::crossProduct(look, up, rot_axis);
            MathController::normalize(rot_axis);

            MathController::rotatePoint(rot_axis, speed, eye);
            MathController::rotatePoint(rot_axis, speed, up);
        };

        static void Down(int speedFactor) {
            double speed = 3.1415 / speedFactor;
            double rot_axis[3];
            double look[3];

            look[0] = -eye[0];
            look[1] = -eye[1];
            look[2] = -eye[2];

            // Accounting for change in direction of 'up' vector
            MathController::crossProduct(look, up, rot_axis);
            MathController::normalize(rot_axis);

            MathController::rotatePoint(rot_axis, -speed, eye);
            MathController::rotatePoint(rot_axis, -speed, up);
        };
};