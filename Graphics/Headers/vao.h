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

	// Links a VBO to the VAO using a certain layout
	void linkVBO(VBO& VBO, GLuint layout);
	void bind();
	void unbind();
	void destroy();
};

#endif