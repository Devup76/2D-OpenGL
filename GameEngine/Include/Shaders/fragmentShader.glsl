#version 330 core
	out vec4 FragColor;

	in vec2 TexCoord;

	uniform sampler2D texture1;

	void main() 
	{
		// --Debug--
		// Displays a gradient showing the texture coordinates on the object.
		// FragColor = vec4(TexCoord, 0.0, 1.0);

		FragColor = texture(texture1, TexCoord);
	}