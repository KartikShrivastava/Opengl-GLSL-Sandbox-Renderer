#version 430

in layout(location = 0)	vec3 position;

uniform mat4 normalShaderModelToProjMat;

out vec3 theColor;

void main(){
	vec4 v = vec4(position, 1.0);
	gl_Position = normalShaderModelToProjMat * v;
	theColor = vec3(1.0, 1.0, 0.5);
}