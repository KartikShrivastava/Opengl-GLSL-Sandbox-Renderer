#pragma once
#include "GL/glew.h"

class IndexBuffer
{
private:
	GLuint m_RendereID;
	GLuint m_Count;
public:
	IndexBuffer(GLuint size, const GLushort* data, GLuint count);
	//~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetCount() const { return m_Count; }
};