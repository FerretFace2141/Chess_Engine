#ifndef VAO_H
#define VAO_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vbo.h"

class VAO
{
public:
	GLuint ID;
	VAO();

	// Links a VBO Attribute such as a position or color to the VAO
	void linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void bind();
	void unbind();
	void destroy();
};

#endif