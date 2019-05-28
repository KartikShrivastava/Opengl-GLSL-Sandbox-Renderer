#include <iostream>
#include <fstream>
#include <memory>

#include "gtc/matrix_transform.hpp"
#include "gtx/transform.hpp"
#include "QtGui/qmouseevent"
#include "QtGui/qkeyevent"

#include "Renderer.h"
#include "ShapeGenerator.h"
#include "VisualizerWindow.h"
#include "Shader.h"

#define N 10000

void VisualizerWindow::initializeGL() {
	setMinimumSize(800, 500);
	setMouseTracking(true);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	SendDataToOpenGL();
}

void VisualizerWindow::SendDataToOpenGL() {
	
	std::vector<ShapeData> shapes;
	
	shapes.push_back(ShapeGenerator::makeTeapot());
	shapes.push_back(ShapeGenerator::MakeCube());
	shapes.push_back(ShapeGenerator::MakePlane(50));

	for (int i = 0; i < shapes.size(); i++) {
		vb.push_back(VertexBuffer(shapes[i].GetVertexBufferSize(), shapes[i].vertices));
		ib.push_back(IndexBuffer(shapes[i].GetIndexBufferSize(), shapes[i].indices, shapes[i].numIndices));
		layout.push_back(VertexBufferLayout());
		layout[i].Push<float>(3);	//vertex position
		layout[i].Push<float>(3);	//vertex color
		layout[i].Push<float>(3);	//normals
		va.push_back(VertexArray(vb[i], layout[i]));
	}

	for(auto shape : shapes)
		shape.CleanupData();
	shapes.clear();

	shader.push_back(Shader());
	shader[0].CreateShader("res/shaders/VertexShaderCode.glsl", "res/shaders/FragmentShaderCode.glsl");
}

void VisualizerWindow::paintGL() {
	renderer.Clear();
	glViewport(0, 0, width(), height());

	glm::mat4 modelToProjMat;
	glm::mat4 worldToViewMatrix = camera.GetWorldToViewMatrix();
	glm::mat4 viewToProjectionMatrix = glm::perspective(glm::radians(50.0f), ((float)width()) / height(), 0.1f, 300.0f);
	glm::mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

	shader[0].Bind();
	shader[0].SetUniform3f("diffuseLightPosWorld", 0.0f, 2.0f, 0.0f);
	shader[0].SetUniform3fv("eyePosWorld", camera.GetPosition());
	shader[0].SetUniform4f("ambientLight", 0.1f, 0.1f, 0.1f, 1.0f);
	
	{	//teapot
		glm::mat4 modelToWorlMatrix = glm::translate(glm::vec3(2.0f, 2.0f, -8.0f)) * glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelToProjMat = worldToProjectionMatrix * modelToWorlMatrix;
		shader[0].SetUniformMat4f("modelToWorldMat", modelToWorlMatrix);
		shader[0].SetUniformMat4f("modelToProjMat", modelToProjMat);
		renderer.Draw(va[0], ib[0], shader[0]);
	}

	{	//cube
		for (int i = 0; i <= 360; i+=30) {
			glm::mat4 modelToWorlMatrix = glm::rotate(glm::radians((float)i), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::vec3(0.0f, 1.0f, -8.0f));
			modelToProjMat = worldToProjectionMatrix * modelToWorlMatrix;
			shader[0].SetUniformMat4f("modelToWorldMat", modelToWorlMatrix);
			shader[0].SetUniformMat4f("modelToProjMat", modelToProjMat);
			renderer.Draw(va[1], ib[1], shader[0]);
		}
	}

	{	//plane
		glm::mat4 modelToWorlMatrix = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)) * glm::rotate(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelToProjMat = worldToProjectionMatrix * modelToWorlMatrix;
		shader[0].SetUniformMat4f("modelToWorldMat", modelToWorlMatrix);
		shader[0].SetUniformMat4f("modelToProjMat", modelToProjMat);
		renderer.Draw(va[2], ib[2], shader[0]);
	}

}

void VisualizerWindow::mouseMoveEvent(QMouseEvent* e) {
	camera.MouseUpdate(glm::vec2(e->x(), e->y()));
	repaint();
}

void VisualizerWindow::keyPressEvent(QKeyEvent* e) {
	switch (e->key()) {
		case Qt::Key::Key_W:
			camera.MoveForward();
			break;
		case Qt::Key::Key_A:
			camera.StrafeLeft();
			break;
		case Qt::Key::Key_S:
			camera.MoveBackward();
			break;
		case Qt::Key::Key_D:
			camera.StrafeRight();
			break;
		case Qt::Key::Key_Z:
			camera.MoveUp();
			break;
		case Qt::Key::Key_X:
			camera.MoveDown();
			break;
	}
	repaint();
}

VisualizerWindow::~VisualizerWindow() {
	vb.clear();
	ib.clear();
	layout.clear();
	va.clear();
	shader.clear();
}