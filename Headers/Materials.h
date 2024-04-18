#pragma once
#include "Config.h"

struct Material {
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
};

//Setting materials for Red object
Material WallMaterial = { {0.3, 0.1, 0.1, 1.0}, {0.5, 0.3, 0.3, 1.0}, {0.5, 0.3, 0.3, 1.0}, 2 };
Material ShadedCube = { {0.1, 0.1, 0.3, 1.0}, {0.3, 0.3, 0.4, 1.0}, {0.3, 0.3, 0.5, 1.0}, 3 };
Material DiffuseTeapot = { {0.1, 0.1, 0.1, 1.0}, {0.3, 0.3, 0.3, 1.0}, {0.3, 0.3, 0.3, 1.0}, 3 };
Material MetallicTeapot = { {0.5, 0.5, 0.1, 1.0}, {0.1, 0.1, 0.3, 1.0}, {0.6, 0.6, 0.8, 1.0}, 3 };
Material GlossyTeapot = { {0.1, 0.1, 0.1, 1.0}, {0.2, 0.3, 0.2, 1.0}, {0.4, 0.7, 0.4, 1.0}, 3 };