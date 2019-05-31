#include "IndexBuffer.h"
#include "CheckGLErrors.h"



#include <iostream>

IndexBuffer::IndexBuffer(GLuint size, const GLushort* data, GLuint count) : m_Count(count) {
	GLCall(glGenBuffers(1, &m_RendereID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendereID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendereID));
}

void IndexBuffer::UnBind() const{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::CleanupData(){
	GLCall(glDeleteBuffers(1, &m_RendereID));
}