#ifndef VBO_H
#define VBO_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VBO
{
    public:
        GLuint ID;
        VBO(GLfloat* vertices, GLsizeiptr size);

        void bind();
        void unbind();
        void destroy();
};

#endif