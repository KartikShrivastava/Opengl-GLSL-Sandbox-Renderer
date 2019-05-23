#version 430

out vec4 dacolor;
in vec3 thePosition;
in vec3 theNormal;

uniform vec3 diffuseLightPos;

void main()
{
	vec3 lightVector = normalize(diffuseLightPos - thePosition);
	float brightness = dot(lightVector, theNormal);
	dacolor = vec4(brightness, brightness, brightness, 1.0);
};