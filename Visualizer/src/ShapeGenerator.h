#pragma once

#include "ShapeData.h"

class ShapeGenerator {
	static ShapeData makePlaneVerts(int dimensions);
	static ShapeData makePlaneIndices(int dimensions);

	// Teapot helpers
	static void generatePatches(float * v, float * n, float * tc, unsigned short* el, int grid);
	static void moveLid(int grid, float *v, glm::mat4 lidTransform);
	static void buildPatchReflect(int patchNum,
		float *B, float *dB,
		float *v, float *n,
		float *tc, unsigned short *el,
		int &index, int &elIndex, int &tcIndex, int grid,
		bool reflectX, bool reflectY);
	static void buildPatch(glm::vec3 patch[][4],
		float *B, float *dB,
		float *v, float *n, float *tc,
		unsigned short *el,
		int &index, int &elIndex, int &tcIndex,
		int grid, glm::mat3 reflect,
		bool invertNormal);
	static void getPatch(int patchNum, glm::vec3 patch[][4], bool reverseV);
	static void computeBasisFunctions(float * B, float * dB, int grid);
	static glm::vec3 evaluate(int gridU, int gridV, float *B, glm::vec3 patch[][4]);
	static glm::vec3 evaluateNormal(int gridU, int gridV,
		float *B, float *dB, glm::vec3 patch[][4]);
public:
	static glm::vec3 RandomColor();
	static ShapeData MakeTriangle();
	static ShapeData MakeCube();
	static ShapeData MakeStar();
	static ShapeData MakePlane(int dimensions = 10);
	static ShapeData makeTeapot(unsigned int tesselation = 10, const glm::mat4& lidTransform = glm::mat4());
};
