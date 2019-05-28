#pragma once

#include "GL/glew.h"
#include "Vertex.h"



#include <iostream>

struct ShapeData {
	Vertex* vertices;
	GLuint numVertices;
	GLushort* indices;
	GLuint numIndices;

	ShapeData() : vertices(0), numVertices(0), indices(0), numIndices(0){}

	//~ShapeData() {
	//	std::cout << "Shape Data destructor called" << std::endl;
	//}

	GLuint GetVertexBufferSize() const { return numVertices * sizeof(Vertex); }

	GLuint GetIndexBufferSize() const{ return numIndices * sizeof(GLushort); }

	void CleanupData() {
		delete[] vertices;
		delete[] indices;
		vertices = NULL;
		indices = NULL;
		numVertices = numIndices = 0;	
	}
};