#pragma once

#include "GL/glew.h"
#include "NormalVertex.h"

struct NormalShapeData {
	NormalVertex* norVertices;
	GLuint norNumVertices;
	GLushort* norIndices;
	GLuint norNumIndices;

	NormalShapeData():norVertices(0),norNumVertices(0),norIndices(0),norNumIndices(0){}

	int GetVertexBufferSize() const { return norNumVertices * sizeof(NormalVertex); }

	int GetIndexBufferSize() const { return norNumIndices * sizeof(GLushort); }

	void CleanupData() {
		delete[] norVertices;
		delete[] norIndices;
		norVertices = NULL;
		norIndices = NULL;
		norNumVertices = norNumIndices = 0;
	}
};