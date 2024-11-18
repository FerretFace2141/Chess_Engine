#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "texture.h"
#include "shaders.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"

GLfloat size = 0.8f;

// Vertices coordinates
GLfloat vertices[] =
{ //  COORDINATES  /  TexCoord   //
	-size, -size,     0.0f, 0.0f, // Lower left corner
	-size,  size,     0.0f, 1.0f, // Upper left corner
	 size,  size,     1.0f, 1.0f, // Upper right corner
	 size, -size,     1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2, // Lower triangle
};

int main()
{
	// Initialize and configure GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1000, 1000, "Chess", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Initialize GLEW **THIS MUST OCCUR AFTER glfwMakeContextCurrent**
	glewInit();

	glViewport(0, 0, 1000, 1000);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Shaders\\default.vert", 
						 "C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Shaders\\default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes to VAO
	VAO1.linkAttrib(VBO1, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0); // Vertex Coords
	VAO1.linkAttrib(VBO1, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float))); // Texture Coords
	// Unbind all to prevent accidentally modifying them
	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();

	// Texture
	Texture image("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\board.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	image.texUnit(shaderProgram, "tex0", 0);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.activate();
		// Binds texture so that is appears in rendering
		image.bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.destroy();
	VBO1.destroy();
	EBO1.destroy();
	image.destroy();
	shaderProgram.destroy();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}