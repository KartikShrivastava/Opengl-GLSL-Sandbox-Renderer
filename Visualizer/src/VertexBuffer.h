#pragma once

#include <GL/glew.h>

struct Vertex;

class VertexBuffer {
private:
	GLuint m_RendererID;
public:
	VertexBuffer(GLuint size, const Vertex* data);
	//~VertexBuffer();

	void Bind() const;
	void UnBind() const;
};