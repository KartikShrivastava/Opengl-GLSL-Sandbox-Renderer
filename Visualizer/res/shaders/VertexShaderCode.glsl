#version 430

in layout(location = 0) vec4 vertexPositionModel;
in layout(location = 1) vec3 vertexColor;
in layout(location = 2) vec3 normalModel;

uniform mat4 modelToProjMat;
uniform mat4 modelToWorldMat;

out vec3 vertexPosWorld;
out vec3 normalWorld;

void main()
{
	gl_Position = modelToProjMat * vertexPositionModel;
	vertexPosWorld = vec3(modelToWorldMat * vertexPositionModel);			//apply the vector addition for diffuse light on world coordinates not just model coordinates
	normalWorld = vec3(modelToWorldMat * vec4(normalModel,0));					//apply rotation to normals (rotation issue with diffuse)
}