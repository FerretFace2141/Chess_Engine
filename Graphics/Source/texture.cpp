#include "texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum format, GLenum pixelType, GLuint texID)
{
	// Assigns the type of the texture to the texture object
	type = texType;

	// Assigns the texture an ID
	ID = texID;

	// Stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// Flip the image so that it appears right side up
	stbi_set_flip_vertically_on_load(true);

	// Generates an OpenGL texture object
	glGenTextures(1, &ID);

	// Bind the texture so that we can configure it
	glBindTexture(texType, ID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Assigns the image to the OpenGL Texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Generates MipMaps
	glGenerateMipmap(texType);

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::bind(GLenum slot)
{
	glActiveTexture(slot);
	glBindTexture(type, ID);
}

void Texture::unbind()
{
	glBindTexture(type, 0);
}

void Texture::destroy()
{
	glDeleteTextures(1, &ID);
}