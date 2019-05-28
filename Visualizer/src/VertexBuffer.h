#pragma once

#include <GL/glew.h>
#include "Vertex.h"

class VertexBuffer {
private:
	GLuint m_RendererID;
public:
	VertexBuffer(GLuint size, const Vertex* data);
	//~VertexBuffer();

	void Bind() const;
	void UnBind() const;
};