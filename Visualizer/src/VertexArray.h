#pragma once
#include "GL/glew.h"

class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout);
	//~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
};