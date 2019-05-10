#pragma once

#include "Vertex.h"

struct ShapeData {
	Vertex* vertices;
	unsigned int numVertices;
	unsigned short* indices;
	unsigned int numIndices;

	ShapeData() : vertices(0), numVertices(0), indices(0), numIndices(0){}

	int GetVertexBufferSize() const { return numVertices * sizeof(Vertex); }

	int GetIndexBufferSize() const{ return numIndices * sizeof(unsigned int); }

	void CleanupData() {
		delete[] vertices;
		delete[] indices;
		vertices = NULL;
		indices = NULL;
	}
};