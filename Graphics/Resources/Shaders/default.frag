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
	else if (texID == 4.0)
		FragColor = texture(tex4, texCoord);
	else if (texID == 5.0)
		FragColor = texture(tex5, texCoord);
	else if (texID == 6.0)
		FragColor = texture(tex6, texCoord);
	else if (texID == 7.0)
		FragColor = texture(tex7, texCoord);
	else if (texID == 8.0)
		FragColor = texture(tex8, texCoord);
	else if (texID == 9.0)
		FragColor = texture(tex9, texCoord);
	else if (texID == 10.0)
		FragColor = texture(tex10, texCoord);
	else if (texID == 11.0)
		FragColor = texture(tex11, texCoord);
	else if (texID == 12.0)
		FragColor = texture(tex12, texCoord);
}