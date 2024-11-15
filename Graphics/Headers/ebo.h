#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);

	// Binds the EBO
	void bind();
	// Unbinds the EBO
	void unbind();
	// Deletes the EBO
	void destroy();
};

#endif