#pragma once

#include <vector>

#include <gl\glew.h>
#include <QtOpenGL/QGLWidget>

#include "Camera.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"

class VisualizerWindow : public QGLWidget
{
private:
	Camera camera;
	Renderer renderer;
	std::vector<VertexBuffer> vb;
	std::vector<IndexBuffer> ib;
	std::vector<VertexBufferLayout> layout;
	std::vector<VertexArray> va;
	std::vector<Shader> shader;

	void SendDataToOpenGL();

protected:
	void initializeGL() override;
	void paintGL() override;
	void mouseMoveEvent(QMouseEvent*);
	void keyPressEvent(QKeyEvent*);

public:
	~VisualizerWindow();
};