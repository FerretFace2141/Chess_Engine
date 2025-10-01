#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Inputs texture for this pixel from the Vertex Shader
in float texID;

// ID for each texture (13 total)
uniform sampler2D tex0, tex1, tex2, tex3, tex4, tex5, tex6, tex7, tex8, tex9, tex10, tex11, tex12;

void main()
{
	if(texID == 0.0)
		FragColor = texture(tex0, texCoord);
	else if (texID == 1.0)
		FragColor = texture(tex1, texCoord);
	else if (texID == 2.0)
		FragColor = texture(tex2, texCoord);
	else if (texID == 3.0)
		FragColor = texture(tex3, texCoord);
}