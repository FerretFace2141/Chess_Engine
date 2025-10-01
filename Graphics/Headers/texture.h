#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaders.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum format, GLenum pixelType, GLuint texID);

	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void bind(GLenum slot);
	// Unbinds a texture
	void unbind();
	// Deletes a texture
	void destroy();
};
#endif