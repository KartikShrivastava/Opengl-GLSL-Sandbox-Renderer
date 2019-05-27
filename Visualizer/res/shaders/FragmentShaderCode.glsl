#version 430

in vec3 vertexPosWorld;
in vec3 normalWorld;

uniform vec3 diffuseLightPosWorld;
uniform vec3 eyePosWorld;
uniform vec4 ambientLight;

out vec4 daColor;

void main()
{	
	//Diffuse lighting calculation
	vec3 lightVectorWorld = normalize(diffuseLightPosWorld - vertexPosWorld);
	float brightness = dot(lightVectorWorld, normalize(normalWorld));
	vec4 diffuseLight = vec4(brightness, brightness, brightness, 1.0);

	//Specular lighting calculation
	vec3 eyeVectorWorld = normalize(eyePosWorld - vertexPosWorld);
	vec3 reflectVectorWorld = reflect(-lightVectorWorld, normalWorld);
	float specularity = dot(reflectVectorWorld, eyeVectorWorld);
	specularity = pow(specularity, 50);
	vec4 specularLight = vec4(specularity, specularity, specularity, 1.0);

	daColor = ambientLight + clamp(diffuseLight,0,1) + clamp(specularLight,0,1);
};