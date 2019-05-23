#pragma once

#include "GL/glew.h"
#include "Vertex.h"

struct ShapeData {
	Vertex* vertices;
	GLuint numVertices;
	GLushort* indices;
	GLuint numIndices;

	ShapeData() : vertices(0), numVertices(0), indices(0), numIndices(0){}

	int GetVertexBufferSize() const { return numVertices * sizeof(Vertex); }

	int GetIndexBufferSize() const{ return numIndices * sizeof(GLushort); }

	void CleanupData() {
		delete[] vertices;
		delete[] indices;
		vertices = NULL;
		indices = NULL;
		numVertices = numIndices = 0;	
	}
};