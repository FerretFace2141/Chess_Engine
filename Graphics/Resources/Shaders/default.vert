#version 330 core

// Positions/Coordinates
layout (location = 0) in vec2 aPos;
// Texture Coordinates
layout (location = 1) in vec2 aTex;
// Shift Values
layout (location = 2) in float bTex;

// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;
out float texID;

void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);

	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;

	// Outputs the texture for this pixel to the vertex shader
	texID = bTex;
}