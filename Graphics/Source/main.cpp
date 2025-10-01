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
int square_x1 = 1, square_y1 = 1;
int square_x2 = 3, square_y2 = 5;

// Vertices coordinates
GLfloat vertices[] =
{ //  COORDINATES  //   TEXCOORD   //  TEXTURE
    // Board	 
	 size,  size,     1.0f, 1.0f,     0.0f, // Upper right corner
	 size, -size,     1.0f, 0.0f,     0.0f, // Lower right corner
	-size, -size,     0.0f, 0.0f,     0.0f, // Lower left corner
	-size,  size,     0.0f, 1.0f,     0.0f, // Upper left corner

	// Lower left square
	(size + -square_x * 0.175f),     (size + -square_y * 0.175f),         1.0f, 1.0f,     10.0f,   // Upper right corner
	(size + -square_x * 0.175f),     (size + -(square_y+1) * 0.175f),     1.0f, 0.0f,     10.0f,   // Lower right corner
	(size + -(square_x+1) * 0.175f), (size + -(square_y+1) * 0.175f),     0.0f, 0.0f,     10.0f,   // Lower left corner
	(size + -(square_x+1) * 0.175f), (size + -square_y * 0.175f),     	  0.0f, 1.0f,     10.0f,   // Upper left corner

	// Lower left square
	(size + -square_x1 * 0.175f),     (size + -square_y1 * 0.175f),       1.0f, 1.0f,     11.0f,  // Upper right corner
	(size + -square_x1 * 0.175f),     (size + -(square_y1+1) * 0.175f),   1.0f, 0.0f,     11.0f,  // Lower right corner
	(size + -(square_x1+1) * 0.175f), (size + -(square_y1+1) * 0.175f),   0.0f, 0.0f,     11.0f,  // Lower left corner
	(size + -(square_x1+1) * 0.175f), (size + -square_y1 * 0.175f),       0.0f, 1.0f,     11.0f,  // Upper left corner

	(size + -square_x2 * 0.175f),     (size + -square_y2 * 0.175f),       1.0f, 1.0f,     12.0f,  // Upper right corner
	(size + -square_x2 * 0.175f),     (size + -(square_y2+1) * 0.175f),   1.0f, 0.0f,     12.0f,  // Lower right corner
	(size + -(square_x2+1) * 0.175f), (size + -(square_y2+1) * 0.175f),   0.0f, 0.0f,     12.0f,  // Lower left corner
	(size + -(square_x2+1) * 0.175f), (size + -square_y2 * 0.175f),       0.0f, 1.0f,     12.0f,  // Upper left corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 2, // Upper triangle
	0, 2, 1, // Lower triangle
	
	4, 7, 6, // Upper triangle
	4, 6, 5, // Lower triangle
	
	8, 11, 10, // Upper triangle
	8, 10, 9,  // Lower triangle

	12, 15, 14,
	12, 14, 13,
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
	VAO.linkAttrib(VBO, 0, 2, GL_FLOAT, 5 * sizeof(float), (void*)0); // Vertex Coords
	VAO.linkAttrib(VBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(2 * sizeof(GLfloat))); // Texture Coords
	VAO.linkAttrib(VBO, 2, 1, GL_FLOAT, 5 * sizeof(float), (void*)(4 * sizeof(GLfloat))); // Texture
	
	// Unbind VAO
	VAO.unbind();

	// Textures
	Texture board("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\board.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	board.texUnit(shaderProgram, "tex0", 0);
	// White Pieces
	Texture white_king("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\white_king.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE, 1);
	white_king.texUnit(shaderProgram, "tex1", 1);
	Texture white_queen("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\white_queen.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE, 2);
	white_queen.texUnit(shaderProgram, "tex2", 2);
	Texture white_rook("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\white_rook.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE, 3);
	white_rook.texUnit(shaderProgram, "tex3", 3);
	Texture white_bishop("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\white_bishop.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE, 3);
	white_bishop.texUnit(shaderProgram, "tex4", 4);
	Texture white_knight("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\white_knight.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE, 3);
	white_knight.texUnit(shaderProgram, "tex5", 5);
	Texture white_pawn("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\white_pawn.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE, 3);
	white_pawn.texUnit(shaderProgram, "tex6", 6);
	// Black Pieces
	Texture black_king("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\black_king.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE, 1);
	black_king.texUnit(shaderProgram, "tex7", 7);
	Texture black_queen("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\black_queen.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE, 2);
	black_queen.texUnit(shaderProgram, "tex8", 8);
	Texture black_rook("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\black_rook.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE, 3);
	black_rook.texUnit(shaderProgram, "tex9", 9);
	Texture black_bishop("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\black_bishop.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE, 3);
	black_bishop.texUnit(shaderProgram, "tex10", 10);
	Texture black_knight("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\black_knight.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE, 3);
	black_knight.texUnit(shaderProgram, "tex11", 11);
	Texture black_pawn("C:\\Users\\Zach\\Documents\\Code\\Chess_Engine\\Graphics\\Resources\\Textures\\black_pawn.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE, 3);
	black_pawn.texUnit(shaderProgram, "tex12", 12);

	// Enable blending and configure the blend function for transparency blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Main while loop
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

		// Bind Textures
		board.bind(GL_TEXTURE0);
		white_king.bind(GL_TEXTURE1);
		white_queen.bind(GL_TEXTURE2);
		white_rook.bind(GL_TEXTURE3);
		white_bishop.bind(GL_TEXTURE4);
		white_knight.bind(GL_TEXTURE5);
		white_pawn.bind(GL_TEXTURE6);
		black_king.bind(GL_TEXTURE7);
		black_queen.bind(GL_TEXTURE8);
		black_rook.bind(GL_TEXTURE9);
		black_bishop.bind(GL_TEXTURE10);
		black_knight.bind(GL_TEXTURE11);
		black_pawn.bind(GL_TEXTURE12);
		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

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
	//white_king.destroy();
	shaderProgram.destroy();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}