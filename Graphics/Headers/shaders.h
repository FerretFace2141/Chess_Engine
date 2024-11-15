#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const std::string& filename);

class Shader
{
    public:
        GLuint ID;
        Shader(const char* vertexFile, const char* fragmentFile);

        void activate();
        void destroy();
};

#endif