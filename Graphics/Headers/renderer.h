#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "texture.h"
#include "shaders.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"

using std::vector;

// Function for generating vertices array
void genVertices(vector<GLfloat> &vertices, char postion[81]);

// Function for generating indices array
void genIndices(vector<GLuint> &indices, char postion[81]);

// Rendering loop function
void drawGame();

#endif