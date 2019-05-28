#include "VertexBuffer.h"
#include "CheckGLErrors.h"
#include "Vertex.h"

#include <iostream>

VertexBuffer::VertexBuffer(GLuint size, const Vertex* data){
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

//VertexBuffer::~VertexBuffer(){
//	std::cout << "VertexBuffer destructor called" << std::endl;
//	GLCall(glDeleteBuffers(1, &m_RendererID));
//}

void VertexBuffer::Bind() const{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::UnBind() const{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
