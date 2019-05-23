#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 vertexColor;
in layout(location = 2) vec3 normal;
uniform vec3 ambientLight;

uniform mat4 fullTransformMatrix;
uniform mat4 modelToWorldMatrix;

out vec3 thePosition;
out vec3 theNormal;

void main()
{
	vec4 v = vec4(position, 1.0);
	gl_Position = fullTransformMatrix * v;
	thePosition = vec3(modelToWorldMatrix * v);
	//theNormal = vec3(modelToWorldMatrix * vec4(normal,0));
	theNormal = normal;
}