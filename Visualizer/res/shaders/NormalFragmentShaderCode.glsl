#version 430

in vec3 theColor;

out vec4 dacolor;

void main()
{
	dacolor = vec4(theColor, 1.0);
};