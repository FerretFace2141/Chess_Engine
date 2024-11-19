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

GLfloat size = 0.7f;
int square_x = 7, square_y = 7;

// Vertices coordinates
GLfloat vertices[] =
{ //  COORDINATES  /   TexCoord   //
    // Board
	-size, -size,     0.0f, 0.0f, // Lower left corner
	-size,  size,     0.0f, 1.0f, // Upper left corner
	 size,  size,     1.0f, 1.0f, // Upper right corner
	 size, -size,     1.0f, 0.0f,  // Lower right corner

	// Lower left square
	(size + -square_x * 0.175f),     (size + -square_y * 0.175f),         0.0f, 0.0f, // Lower left corner
	(size + -square_x * 0.175f),     (size + -(square_y+1) * 0.175f),     0.0f, 1.0f, // Upper left corner
	(size + -(square_x+1) * 0.175f), (size + -(square_y+1) * 0.175f),     1.0f, 1.0f, // Upper right corner
	(size + -(square_x+1) * 0.175f), (size + -square_y * 0.175f),     	  1.0f, 0.0f,  // Lower right corner*/
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2, // Lower triangle
	4, 6, 5, // Upper triangle
	4, 7, 6, // Lower triangle*/
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
	VAO VAO;
	VAO.bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO(indices, sizeof(indices));

	// Links VBO attributes to VAO
	VAO.linkAttrib(VBO, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0); // Vertex Coords
	VAO.linkAttrib(VBO, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(GLfloat))); // Texture Coords
	// Unbind all to prevent accidentally modifying them
	VAO.unbind();
	VBO.unbind();
	EBO.unbind();

	// Textures
	Texture board("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\board.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture white_king("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\black_king.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	// Main while loop
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.activate();
		// Bind the VAO so OpenGL knows to use it
		VAO.bind();

		board.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		white_king.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6*sizeof(GLuint)));

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}
	glDisable(GL_BLEND);

	// Delete all the objects we've created
	VAO.destroy();
	VBO.destroy();
	EBO.destroy();
	board.destroy();
	white_king.destroy();
	shaderProgram.destroy();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}