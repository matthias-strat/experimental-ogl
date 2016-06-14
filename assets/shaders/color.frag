#version 330 core

in vec3 voColor;

out vec4 color;

void main()
{
	color = vec4(voColor, 1.0);
}