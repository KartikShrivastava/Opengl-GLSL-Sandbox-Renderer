#include "Renderer.h"

#include <iostream>
#include "GL/glew.h"

#include "CheckGLErrors.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

void Renderer::Clear() const {
	GLCall(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));
}

void Renderer::DrawTri(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
	//shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_SHORT, 0));
}

void Renderer::DrawLine(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
	//shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_LINES, ib.GetCount(), GL_UNSIGNED_SHORT, 0));
}