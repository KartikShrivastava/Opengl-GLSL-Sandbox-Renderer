#include "VertexArray.h"
#include "CheckGLErrors.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout){
	GLCall(glGenVertexArrays(1, &m_RendererID));
	AddBuffer(vb, layout);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout){
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() const{
	GLCall(glBindVertexArray(0));
}

void VertexArray::CleanupData(){
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}
