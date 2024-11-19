#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

// ID for each texture (13 total)
uniform sampler2D tex0, tex1, tex2, tex3, tex4, tex5, tex6, tex7, tex8, tex9, tex10, tex11, tex12;

void main()
{
	FragColor = texture(tex0, texCoord);
	if(texture(tex0, texCoord).a < 0.1)
		discard;
}