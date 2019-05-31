#pragma once

#include <GL/glew.h>

struct Vertex;
struct NormalVertex;

class VertexBuffer {
private:
	GLuint m_RendererID;
public:
	VertexBuffer(GLuint size, const Vertex* data);
	VertexBuffer(GLuint size, const NormalVertex* data);

	void Bind() const;
	void UnBind() const;

	void CleanupData();
};