#include "ShapeGenerator.h"
#include "Vertex.h"

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)

ShapeData ShapeGenerator::MakeTriangle()
{
	ShapeData shapeData;

	Vertex vertices[] = {
		glm::vec3(-1.0f, -1.0f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +1.0f),

		glm::vec3(+0.0f, +1.0f, +0.0f),
		glm::vec3(+0.0f, +1.0f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +1.0f),

		glm::vec3(+1.0f, -1.0f, +0.0f),
		glm::vec3(+0.0f, +0.0f, +1.0f),
		glm::vec3(+1.0f, +0.0f, +1.0f),
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
		glm::vec3(+0.8f, +0.0f, +0.0f),	 // Color
		glm::vec3(+0.0f, +1.0f, +0.0f),  // Normal
		glm::vec3(+1.0f, +1.0f, +1.0f),  // 1
		glm::vec3(+0.8f, +0.0f, +0.0f),	 // Color
		glm::vec3(+0.0f, +1.0f, +0.0f),  // Normal
		glm::vec3(+1.0f, +1.0f, -1.0f),  // 2
		glm::vec3(+0.8f, +0.0f, +0.0f),	 // Color
		glm::vec3(+0.0f, +1.0f, +0.0f),  // Normal
		glm::vec3(-1.0f, +1.0f, -1.0f),  // 3
		glm::vec3(+0.8f, +0.0f, +0.0f),	 // Color
		glm::vec3(+0.0f, +1.0f, +0.0f),  // Normal
		
		glm::vec3(-1.0f, +1.0f, -1.0f),  // 4
		glm::vec3(+1.0f, +0.0f, +0.0f),  // Color
		glm::vec3(+0.0f, +0.0f, -1.0f),  // Normal
		glm::vec3(+1.0f, +1.0f, -1.0f),  // 5
		glm::vec3(+1.0f, +0.0f, +0.0f),  // Color
		glm::vec3(+0.0f, +0.0f, -1.0f),  // Normal
		glm::vec3(+1.0f, -1.0f, -1.0f),  // 6
		glm::vec3(+1.0f, +0.0f, +0.0f),  // Color
		glm::vec3(+0.0f, +0.0f, -1.0f),  // Normal
		glm::vec3(-1.0f, -1.0f, -1.0f),  // 7
		glm::vec3(+1.0f, +0.0f, +0.0f),  // Color
		glm::vec3(+0.0f, +0.0f, -1.0f),  // Normal
		
		glm::vec3(+1.0f, +1.0f, -1.0f),  // 8
		glm::vec3(+0.5f, +0.0f, +0.0f),  // Color
		glm::vec3(+1.0f, +0.0f, +0.0f),  // Normal
		glm::vec3(+1.0f, +1.0f, +1.0f),  // 9
		glm::vec3(+0.5f, +0.0f, +0.0f),  // Color
		glm::vec3(+1.0f, +0.0f, +0.0f),  // Normal
		glm::vec3(+1.0f, -1.0f, +1.0f),  // 10
		glm::vec3(+0.5f, +0.0f, +0.0f),  // Color
		glm::vec3(+1.0f, +0.0f, +0.0f),  // Normal
		glm::vec3(+1.0f, -1.0f, -1.0f),  // 11
		glm::vec3(+0.5f, +0.0f, +0.0f),  // Color
		glm::vec3(+1.0f, +0.0f, +0.0f),  // Normal
		
		glm::vec3(-1.0f, +1.0f, +1.0f),  // 12
		glm::vec3(+0.7f, +0.0f, +0.0f),  // Color
		glm::vec3(-1.0f, +0.0f, +0.0f),  // Normal
		glm::vec3(-1.0f, +1.0f, -1.0f),  // 13
		glm::vec3(+0.7f, +0.0f, +0.0f),  // Color
		glm::vec3(-1.0f, +0.0f, +0.0f),  // Normal
		glm::vec3(-1.0f, -1.0f, -1.0f),  // 14
		glm::vec3(+0.7f, +0.0f, +0.0f),  // Color
		glm::vec3(-1.0f, +0.0f, +0.0f),  // Normal
		glm::vec3(-1.0f, -1.0f, +1.0f),  // 15
		glm::vec3(+0.7f, +0.0f, +0.0f),  // Color
		glm::vec3(-1.0f, +0.0f, +0.0f),  // Normal
		
		glm::vec3(+1.0f, +1.0f, +1.0f),  // 16
		glm::vec3(+0.4f, +0.0f, +0.0f),  // Color
		glm::vec3(+0.0f, +0.0f, +1.0f),  // Normal
		glm::vec3(-1.0f, +1.0f, +1.0f),  // 17
		glm::vec3(+0.4f, +0.0f, +0.0f),  // Color
		glm::vec3(+0.0f, +0.0f, +1.0f),  // Normal
		glm::vec3(-1.0f, -1.0f, +1.0f),  // 18
		glm::vec3(+0.4f, +0.0f, +0.0f),  // Color
		glm::vec3(+0.0f, +0.0f, +1.0f),  // Normal
		glm::vec3(+1.0f, -1.0f, +1.0f),  // 19
		glm::vec3(+0.4f, +0.0f, +0.0f),  // Color
		glm::vec3(+0.0f, +0.0f, +1.0f),  // Normal
		
		glm::vec3(+1.0f, -1.0f, -1.0f),  // 20
		glm::vec3(+0.6f, +0.0f, +0.0f),  // Color
		glm::vec3(+0.0f, -1.0f, +0.0f),  // Normal
		glm::vec3(-1.0f, -1.0f, -1.0f),  // 21
		glm::vec3(+0.6f, +0.0f, +0.0f),  // Color
		glm::vec3(+0.0f, -1.0f, +0.0f),  // Normal
		glm::vec3(-1.0f, -1.0f, +1.0f),  // 22
		glm::vec3(+0.6f, +0.0f, +0.0f),  // Color
		glm::vec3(+0.0f, -1.0f, +0.0f),  // Normal
		glm::vec3(+1.0f, -1.0f, +1.0f),  // 23
		glm::vec3(+0.6f, +0.0f, +0.0f),  // Color
		glm::vec3(+0.0f, -1.0f, +0.0f),  // Normal
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

//TODO: add normals for star
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

glm::vec3 ShapeGenerator::RandomColor() {
	glm::vec3 ret;
	ret.y = rand() / (float)RAND_MAX;
	//ret.y = rand() / (float)RAND_MAX; 
	float temp = rand() / (float)RAND_MAX;
	ret.z = temp > 0.5f ? 0.5 : temp;
	ret.x = 0.0f;
	return ret;
}

ShapeData ShapeGenerator::makePlaneVerts(int dimensions)
{
	ShapeData ret;
	ret.numVertices = dimensions * dimensions;
	int mid = dimensions / 2;
	ret.vertices = new Vertex[ret.numVertices];
	for (int i = 0; i < dimensions; i++) {
		for (int j = 0; j < dimensions; j++) {
			ret.vertices[i*dimensions + j].position.x = (float)(j - mid);
			ret.vertices[i*dimensions + j].position.y = 0;
			ret.vertices[i*dimensions + j].position.z = (float)(i - mid);
			ret.vertices[i*dimensions + j].normal = glm::vec3(0, 1, 0);
			ret.vertices[i*dimensions + j].color = glm::vec3(0.8f, 0.8f, 0.9f);// RandomColor();
		}
	}

	return ret;
}

ShapeData ShapeGenerator::makePlaneIndices(int dimensions)
{
	ShapeData ret;
	ret.numIndices = (dimensions - 1) * (dimensions - 1) * 2 * 3;	//faces * numofTri in a face * numofIndi in a tri
	ret.indices = new unsigned short[ret.numIndices];
	int index = 0;
	for (int row = 0; row < dimensions - 1; row++) {
		for (int column = 0; column < dimensions - 1; column++) {
			ret.indices[index++] = dimensions * row + column;
			ret.indices[index++] = dimensions * row + column + dimensions;
			ret.indices[index++] = dimensions * row + column + dimensions + 1;

			ret.indices[index++] = dimensions * row + column;
			ret.indices[index++] = dimensions * row + column + dimensions + 1;
			ret.indices[index++] = dimensions * row + column + 1;
		}
	}
	assert(index = ret.numIndices);
	return ret;
}

ShapeData ShapeGenerator::MakePlane(int dimensions)
{
	ShapeData ret = makePlaneVerts(dimensions);
	ShapeData ret2 = makePlaneIndices(dimensions);
	ret.numIndices = ret2.numIndices;
	ret.indices = ret2.indices;

	return ret;
}

ShapeData ShapeGenerator::makeTeapot(glm::uint tesselation, const glm::mat4& lidTransform)
{
	ShapeData ret;

	ret.numVertices = 32 * (tesselation + 1) * (tesselation + 1);
	glm::uint faces = tesselation * tesselation * 32;
	float* vertices = new float[ret.numVertices * 3];
	float* normals = new float[ret.numVertices * 3];
	float* textureCoordinates = new float[ret.numVertices * 2];
	ret.numIndices = faces * 6;
	ret.indices = new unsigned short[ret.numIndices];

	generatePatches(vertices, normals, textureCoordinates, ret.indices, tesselation);
	//moveLid(tesselation, vertices, lidTransform);

	// Adapt/convert their data format to mine
	ret.vertices = new Vertex[ret.numVertices];
	for (glm::uint i = 0; i < ret.numVertices; i++)
	{
		Vertex& v = ret.vertices[i];
		v.position.x = vertices[i * 3 + 0];
		v.position.y = vertices[i * 3 + 1];
		v.position.z = vertices[i * 3 + 2];
		v.normal.x = normals[i * 3 + 0];
		v.normal.y = normals[i * 3 + 1];
		v.normal.z = normals[i * 3 + 2];
		v.color = RandomColor();
	}
	return ret;
}

void ShapeGenerator::generatePatches(float * v, float * n, float * tc, unsigned short* el, int grid) {
	float * B = new float[4 * (grid + 1)];  // Pre-computed Bernstein basis functions
	float * dB = new float[4 * (grid + 1)]; // Pre-computed derivitives of basis functions

	int idx = 0, elIndex = 0, tcIndex = 0;

	// Pre-compute the basis functions  (Bernstein polynomials)
	// and their derivatives
	computeBasisFunctions(B, dB, grid);

	// Build each patch
	// The rim
	buildPatchReflect(0, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
	// The body
	buildPatchReflect(1, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
	buildPatchReflect(2, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
	// The lid
	buildPatchReflect(3, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
	buildPatchReflect(4, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
	// The bottom
	buildPatchReflect(5, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
	// The handle
	buildPatchReflect(6, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);
	buildPatchReflect(7, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);
	// The spout
	buildPatchReflect(8, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);
	buildPatchReflect(9, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);

	delete[] B;
	delete[] dB;
}

void ShapeGenerator::moveLid(int grid, float *v, glm::mat4 lidTransform) {

	int start = 3 * 12 * (grid + 1) * (grid + 1);
	int end = 3 * 20 * (grid + 1) * (grid + 1);

	for (int i = start; i < end; i += 3)
	{
		glm::vec4 vert = glm::vec4(v[i], v[i + 1], v[i + 2], 1.0f);
		vert = lidTransform * vert;
		v[i] = vert.x;
		v[i + 1] = vert.y;
		v[i + 2] = vert.z;
	}
}

void ShapeGenerator::buildPatchReflect(int patchNum,
	float *B, float *dB,
	float *v, float *n,
	float *tc, unsigned short *el,
	int &index, int &elIndex, int &tcIndex, int grid,
	bool reflectX, bool reflectY)
{
	glm::vec3 patch[4][4];
	glm::vec3 patchRevV[4][4];
	getPatch(patchNum, patch, false);
	getPatch(patchNum, patchRevV, true);

	// Patch without modification
	buildPatch(patch, B, dB, v, n, tc, el,
		index, elIndex, tcIndex, grid, glm::mat3(1.0f), true);

	// Patch reflected in x
	if (reflectX) {
		buildPatch(patchRevV, B, dB, v, n, tc, el,
			index, elIndex, tcIndex, grid, glm::mat3(glm::vec3(-1.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 1.0f)), false);
	}

	// Patch reflected in y
	if (reflectY) {
		buildPatch(patchRevV, B, dB, v, n, tc, el,
			index, elIndex, tcIndex, grid, glm::mat3(glm::vec3(1.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, -1.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 1.0f)), false);
	}

	// Patch reflected in x and y
	if (reflectX && reflectY) {
		buildPatch(patch, B, dB, v, n, tc, el,
			index, elIndex, tcIndex, grid, glm::mat3(glm::vec3(-1.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, -1.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 1.0f)), true);
	}
}

void ShapeGenerator::buildPatch(glm::vec3 patch[][4],
	float *B, float *dB,
	float *v, float *n, float *tc,
	unsigned short *el,
	int &index, int &elIndex, int &tcIndex, int grid, glm::mat3 reflect,
	bool invertNormal)
{
	int startIndex = index / 3;
	float tcFactor = 1.0f / grid;

	for (int i = 0; i <= grid; i++)
	{
		for (int j = 0; j <= grid; j++)
		{
			glm::vec3 pt = reflect * evaluate(i, j, B, patch);
			glm::vec3 norm = reflect * evaluateNormal(i, j, B, dB, patch);
			if (invertNormal)
				norm = -norm;

			v[index] = pt.x;
			v[index + 1] = pt.y;
			v[index + 2] = pt.z;

			n[index] = norm.x;
			n[index + 1] = norm.y;
			n[index + 2] = norm.z;

			tc[tcIndex] = i * tcFactor;
			tc[tcIndex + 1] = j * tcFactor;

			index += 3;
			tcIndex += 2;
		}
	}

	for (int i = 0; i < grid; i++)
	{
		int iStart = i * (grid + 1) + startIndex;
		int nextiStart = (i + 1) * (grid + 1) + startIndex;
		for (int j = 0; j < grid; j++)
		{
			el[elIndex] = iStart + j;
			el[elIndex + 1] = nextiStart + j + 1;
			el[elIndex + 2] = nextiStart + j;

			el[elIndex + 3] = iStart + j;
			el[elIndex + 4] = iStart + j + 1;
			el[elIndex + 5] = nextiStart + j + 1;

			elIndex += 6;
		}
	}
}

#include "TeapotData.h"

void ShapeGenerator::getPatch(int patchNum, glm::vec3 patch[][4], bool reverseV)
{
	for (int u = 0; u < 4; u++) {          // Loop in u direction
		for (int v = 0; v < 4; v++) {     // Loop in v direction
			if (reverseV) {
				patch[u][v] = glm::vec3(
					Teapot::cpdata[Teapot::patchdata[patchNum][u * 4 + (3 - v)]][0],
					Teapot::cpdata[Teapot::patchdata[patchNum][u * 4 + (3 - v)]][1],
					Teapot::cpdata[Teapot::patchdata[patchNum][u * 4 + (3 - v)]][2]
				);
			}
			else {
				patch[u][v] = glm::vec3(
					Teapot::cpdata[Teapot::patchdata[patchNum][u * 4 + v]][0],
					Teapot::cpdata[Teapot::patchdata[patchNum][u * 4 + v]][1],
					Teapot::cpdata[Teapot::patchdata[patchNum][u * 4 + v]][2]
				);
			}
		}
	}
}

void ShapeGenerator::computeBasisFunctions(float * B, float * dB, int grid) {
	float inc = 1.0f / grid;
	for (int i = 0; i <= grid; i++)
	{
		float t = i * inc;
		float tSqr = t * t;
		float oneMinusT = (1.0f - t);
		float oneMinusT2 = oneMinusT * oneMinusT;

		B[i * 4 + 0] = oneMinusT * oneMinusT2;
		B[i * 4 + 1] = 3.0f * oneMinusT2 * t;
		B[i * 4 + 2] = 3.0f * oneMinusT * tSqr;
		B[i * 4 + 3] = t * tSqr;

		dB[i * 4 + 0] = -3.0f * oneMinusT2;
		dB[i * 4 + 1] = -6.0f * t * oneMinusT + 3.0f * oneMinusT2;
		dB[i * 4 + 2] = -3.0f * tSqr + 6.0f * t * oneMinusT;
		dB[i * 4 + 3] = 3.0f * tSqr;
	}
}

glm::vec3 ShapeGenerator::evaluate(int gridU, int gridV, float *B, glm::vec3 patch[][4])
{
	glm::vec3 p(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			p += patch[i][j] * B[gridU * 4 + i] * B[gridV * 4 + j];
		}
	}
	return p;
}

glm::vec3 ShapeGenerator::evaluateNormal(int gridU, int gridV, float *B, float *dB, glm::vec3 patch[][4])
{
	glm::vec3 du(0.0f, 0.0f, 0.0f);
	glm::vec3 dv(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			du += patch[i][j] * dB[gridU * 4 + i] * B[gridV * 4 + j];
			dv += patch[i][j] * B[gridU * 4 + i] * dB[gridV * 4 + j];
		}
	}
	return glm::normalize(glm::cross(du, dv));
}

NormalShapeData ShapeGenerator::generateNormals(const ShapeData & data)
{
	NormalShapeData ret;
	ret.norNumVertices = data.numVertices * 2;
	ret.norVertices = new NormalVertex[ret.norNumVertices];
	data.vertices;
	//assign normals (each normal is made up of two vertex position : base vertex vector position + normal unit vector position
	for (int i = 0; i < data.numVertices; i++) {
		glm::uint index = i * 2;
		ret.norVertices[index].position = data.vertices[i].position;
		ret.norVertices[index+1].position = data.vertices[i].position + data.vertices[i].normal;
	}

	//assing indices
	ret.norNumIndices = ret.norNumVertices;
	ret.norIndices = new GLushort[ret.norNumIndices];
	for (int i = 0; i < ret.norNumVertices; i++) {
		ret.norIndices[i] = i;
	}
	return ret;
}