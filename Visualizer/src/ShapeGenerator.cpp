#include "ShapeGenerator.h"
#include "Vertex.h"

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)

ShapeData ShapeGenerator::MakeTriangle()
{
	ShapeData shapeData;

	Vertex vertices[] = {
		glm::vec3(-1.0f, -1.0f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),

		glm::vec3(+0.0f, +1.0f, +0.0f),
		glm::vec3(+0.0f, +1.0f, +0.0f),

		glm::vec3(+1.0f, -1.0f, +0.0f),
		glm::vec3(+0.0f, +0.0f, +1.0f),
	};

	shapeData.numVertices = NUM_ARRAY_ELEMENTS(vertices);
	shapeData.vertices = new Vertex[shapeData.numVertices];		//memory leak
	memcpy(shapeData.vertices, vertices, sizeof(vertices));

	unsigned short indices[] = {
		0,1,2,
	};

	shapeData.numIndices = NUM_ARRAY_ELEMENTS(indices);
	shapeData.indices = new unsigned short[shapeData.numVertices];		//memory leak
	memcpy(shapeData.indices, indices, sizeof(indices));

	return shapeData;
}

ShapeData ShapeGenerator::MakeCube() {
	ShapeData ret;
	Vertex stackVerts[] =
	{
		glm::vec3(-1.0f, +1.0f, +1.0f),  // 0
		glm::vec3(+0.8f, +0.0f, +0.0f),	// Color
		//glm::vec3(+0.0f, +1.0f, +0.0f),  // Normal
		glm::vec3(+1.0f, +1.0f, +1.0f),  // 1
		glm::vec3(+0.8f, +0.0f, +0.0f),	// Color
		//glm::vec3(+0.0f, +1.0f, +0.0f),  // Normal
		glm::vec3(+1.0f, +1.0f, -1.0f),  // 2
		glm::vec3(+0.8f, +0.0f, +0.0f),	// Color
		//glm::vec3(+0.0f, +1.0f, +0.0f),  // Normal
		glm::vec3(-1.0f, +1.0f, -1.0f),  // 3
		glm::vec3(+0.8f, +0.0f, +0.0f),	// Color
		//glm::vec3(+0.0f, +1.0f, +0.0f),  // Normal
		
		glm::vec3(-1.0f, +1.0f, -1.0f),  // 4
		glm::vec3(+1.0f, +0.0f, +0.0f),  // Color
		//glm::vec3(+0.0f, +0.0f, -1.0f),  // Normal
		glm::vec3(+1.0f, +1.0f, -1.0f),  // 5
		glm::vec3(+1.0f, +0.0f, +0.0f),  // Color
		//glm::vec3(+0.0f, +0.0f, -1.0f),  // Normal
		glm::vec3(+1.0f, -1.0f, -1.0f),  // 6
		glm::vec3(+1.0f, +0.0f, +0.0f),  // Color
		//glm::vec3(+0.0f, +0.0f, -1.0f),  // Normal
		glm::vec3(-1.0f, -1.0f, -1.0f),  // 7
		glm::vec3(+1.0f, +0.0f, +0.0f),  // Color
		//glm::vec3(+0.0f, +0.0f, -1.0f),  // Normal
		
		glm::vec3(+1.0f, +1.0f, -1.0f),  // 8
		glm::vec3(+0.5f, +0.0f, +0.0f),  // Color
		//glm::vec3(+1.0f, +0.0f, +0.0f),  // Normal
		glm::vec3(+1.0f, +1.0f, +1.0f),  // 9
		glm::vec3(+0.5f, +0.0f, +0.0f),  // Color
		//glm::vec3(+1.0f, +0.0f, +0.0f),  // Normal
		glm::vec3(+1.0f, -1.0f, +1.0f),  // 10
		glm::vec3(+0.5f, +0.0f, +0.0f),  // Color
		//glm::vec3(+1.0f, +0.0f, +0.0f),  // Normal
		glm::vec3(+1.0f, -1.0f, -1.0f),  // 11
		glm::vec3(+0.5f, +0.0f, +0.0f),  // Color
		//glm::vec3(+1.0f, +0.0f, +0.0f),  // Normal
		
		glm::vec3(-1.0f, +1.0f, +1.0f),  // 12
		glm::vec3(+0.7f, +0.0f, +0.0f),  // Color
		//glm::vec3(-1.0f, +0.0f, +0.0f),  // Normal
		glm::vec3(-1.0f, +1.0f, -1.0f),  // 13
		glm::vec3(+0.7f, +0.0f, +0.0f),  // Color
		//glm::vec3(-1.0f, +0.0f, +0.0f),  // Normal
		glm::vec3(-1.0f, -1.0f, -1.0f),  // 14
		glm::vec3(+0.7f, +0.0f, +0.0f),  // Color
		//glm::vec3(-1.0f, +0.0f, +0.0f),  // Normal
		glm::vec3(-1.0f, -1.0f, +1.0f),  // 15
		glm::vec3(+0.7f, +0.0f, +0.0f),  // Color
		//glm::vec3(-1.0f, +0.0f, +0.0f),  // Normal
		
		glm::vec3(+1.0f, +1.0f, +1.0f),  // 16
		glm::vec3(+0.4f, +0.0f, +0.0f),  // Color
		//glm::vec3(+0.0f, +0.0f, +1.0f),  // Normal
		glm::vec3(-1.0f, +1.0f, +1.0f),  // 17
		glm::vec3(+0.4f, +0.0f, +0.0f),  // Color
		//glm::vec3(+0.0f, +0.0f, +1.0f),  // Normal
		glm::vec3(-1.0f, -1.0f, +1.0f),  // 18
		glm::vec3(+0.4f, +0.0f, +0.0f),  // Color
		//glm::vec3(+0.0f, +0.0f, +1.0f),  // Normal
		glm::vec3(+1.0f, -1.0f, +1.0f),  // 19
		glm::vec3(+0.4f, +0.0f, +0.0f),  // Color
		//glm::vec3(+0.0f, +0.0f, +1.0f),  // Normal
		
		glm::vec3(+1.0f, -1.0f, -1.0f),  // 20
		glm::vec3(+0.6f, +0.0f, +0.0f),  // Color
		//glm::vec3(+0.0f, -1.0f, +0.0f),  // Normal
		glm::vec3(-1.0f, -1.0f, -1.0f),  // 21
		glm::vec3(+0.6f, +0.0f, +0.0f),  // Color
		//glm::vec3(+0.0f, -1.0f, +0.0f),  // Normal
		glm::vec3(-1.0f, -1.0f, +1.0f),  // 22
		glm::vec3(+0.6f, +0.0f, +0.0f),  // Color
		//glm::vec3(+0.0f, -1.0f, +0.0f),  // Normal
		glm::vec3(+1.0f, -1.0f, +1.0f),  // 23
		glm::vec3(+0.6f, +0.0f, +0.0f),  // Color
		//glm::vec3(+0.0f, -1.0f, +0.0f),  // Normal
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(stackVerts);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, stackVerts, sizeof(stackVerts));

	unsigned short stackIndices[] = {
		0,   1,  2,  0,  2,  3, // Top
		4,   5,  6,  4,  6,  7, // Front
		8,   9, 10,  8, 10, 11, // Right
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Back
		20, 22, 21, 20, 23, 22, // Bottom
	};
	ret.numIndices = NUM_ARRAY_ELEMENTS(stackIndices);
	ret.indices = new unsigned short[ret.numIndices];
	memcpy(ret.indices, stackIndices, sizeof(stackIndices));

	return ret;
}

ShapeData ShapeGenerator::MakeStar() {
	ShapeData ret;
	Vertex stackVerts[] = {
		//Face 1
		glm::vec3(+0.0f, +0.0f, +0.1f), //0
		glm::vec3(+0.6f, +0.6f, +0.6f), //color
		glm::vec3(+0.2f, +0.0f, +0.1f), //1
		glm::vec3(+0.6f, +0.6f, +0.6f), //color
		glm::vec3(+0.0f, +1.0f, +0.0f), //2
		glm::vec3(+0.6f, +0.6f, +0.6f), //color
		
		//Face 2
		//0
		glm::vec3(+0.866f, -0.5f, +0.0f), //3
		glm::vec3(+0.6f, +0.6f, +0.6f), //color
		//1
		
		//Face 3
		glm::vec3(+0.0f, +0.0f, +0.1f), //4
		glm::vec3(+0.4f, +0.4f, +0.4f), //color
		glm::vec3(+0.0f, -0.2f, +0.1f), //5
		glm::vec3(+0.4f, +0.4f, +0.4f), //color
		glm::vec3(+0.866f, -0.5f, +0.0f), //6
		glm::vec3(+0.4f, +0.4f, +0.4f), //color

		//Face 4
		//4
		glm::vec3(-0.866f, -0.5f, +0.0f), //7
		glm::vec3(+0.4f, +0.4f, +0.4f), //color
		//5

		//Face 5
		glm::vec3(+0.0f, +0.0f, +0.1f), //8
		glm::vec3(+1.0f, +1.0f, +1.0f), //color
		glm::vec3(-0.2f, +0.0f, +0.1f), //9
		glm::vec3(+1.0f, +1.0f, +1.0f), //color
		glm::vec3(-0.866f, -0.5f, +0.0f), //10
		glm::vec3(+1.0f, +1.0f, +1.0f), //color
		
		//Face 6
		//8
		glm::vec3(+0.0f, +1.0f, +0.0f), //11
		glm::vec3(+1.0f, +1.0f, +1.0f), //color

		//side faces
		glm::vec3(+0.0f, +1.0f, +0.0f), //12
		glm::vec3(+0.2f, +0.2f, +0.2f), //color
		glm::vec3(+0.2f, +0.0f, +0.1f), //13
		glm::vec3(+0.2f, +0.2f, +0.2f), //color
		glm::vec3(+0.2f, -0.0f, -0.1f), //14
		glm::vec3(+0.2f, +0.2f, +0.2f), //color

		//13
		glm::vec3(+0.866f, -0.5f, +0.0f), //15
		glm::vec3(+0.2f, +0.2f, +0.2f), //color
		//14

		//15
		glm::vec3(+0.0f, -0.2f, +0.1f), //16
		glm::vec3(+0.2f, +0.2f, +0.2f), //color
		glm::vec3(+0.0f, -0.2f, -0.1f), //17
		glm::vec3(+0.2f, +0.2f, +0.2f), //color

		//16
		glm::vec3(-0.866f, -0.5f, +0.0f), //18
		glm::vec3(+0.2f, +0.2f, +0.2f), //color
		//17

		//18
		glm::vec3(-0.2f, +0.0f, +0.1f), //19
		glm::vec3(+0.2f, +0.2f, +0.2f), //color
		glm::vec3(-0.2f, +0.0f, -0.1f), //20
		glm::vec3(+0.2f, +0.2f, +0.2f), //color

		//19
		glm::vec3(+0.0f, +1.0f, +0.0f), //21
		glm::vec3(+0.2f, +0.2f, +0.2f), //color
		//20

		//Back faces
		glm::vec3(+0.0f, +0.0f, -0.1f), //22
		glm::vec3(+0.6f, +0.6f, +0.6f), //color
		glm::vec3(+0.2f, +0.0f, -0.1f), //23
		glm::vec3(+0.6f, +0.6f, +0.6f), //color

		glm::vec3(+0.0f, +0.0f, -0.1f), //24
		glm::vec3(+0.4f, +0.4f, +0.4f), //color
		glm::vec3(+0.0f, -0.2f, -0.1f), //25
		glm::vec3(+0.4f, +0.4f, +0.4f), //color

		glm::vec3(+0.0f, +0.0f, -0.1f), //26
		glm::vec3(+1.0f, +1.0f, +1.0f), //color
		glm::vec3(-0.2f, +0.0f, -0.1f), //27
		glm::vec3(+1.0f, +1.0f, +1.0f), //color
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(stackVerts);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, stackVerts, sizeof(stackVerts));

	unsigned short stackIndices[] = {
		0, 1, 2, 0, 3, 1,
		4, 5, 6, 4, 7, 5,
		8, 9, 10, 8, 11, 9,
		12, 13, 14,
		13, 15, 14,
		15, 16, 17,
		16, 18, 17,
		18, 19, 20,
		19, 21, 20,
		22, 2, 23, 22, 23, 3,
		24, 6, 25, 24, 25, 7,
		26, 10, 27, 26, 27, 11,
	};
	ret.numIndices = NUM_ARRAY_ELEMENTS(stackIndices);
	ret.indices = new unsigned short[ret.numIndices];
	memcpy(ret.indices, stackIndices, sizeof(stackIndices));

	return ret;
}