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

void VisualizerWindow::SendDataToOpenGL() {
	
	std::vector<ShapeData> shapes;
	shapes.push_back(ShapeGenerator::makeTeapot());
	
	vbuf = new VertexBuffer(shapes[0].GetVertexBufferSize(), shapes[0].vertices);
	ibuf = new IndexBuffer(shapes[0].GetIndexBufferSize(), shapes[0].indices, shapes[0].numIndices);

	layout1 = new VertexBufferLayout();
	layout1->Push<float>(3);
	layout1->Push<float>(3);
	layout1->Push<float>(3);

	va1 = new VertexArray(*vbuf, *layout1);

	shapes[0].CleanupData();
	shapes.clear();

	sh1 = new Shader();
	sh1->CreateShader("res/shaders/VertexShaderCode.glsl", "res/shaders/FragmentShaderCode.glsl");
	sh1->Bind();

	vbuf->UnBind();
	ibuf->UnBind();
	va1->UnBind();
	sh1->UnBind();
}

void VisualizerWindow::paintGL() {
	renderer.Clear();
	glViewport(0, 0, width(), height());

	glm::mat4 modelToProjMat;
	glm::mat4 worldToViewMatrix = camera.GetWorldToViewMatrix();
	glm::mat4 viewToProjectionMatrix = glm::perspective(glm::radians(60.0f), ((float)width()) / height(), 0.1f, 300.0f);
	glm::mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

	{
		sh1->Bind();
		sh1->SetUniform3f("diffuseLightPosWorld", 0.0f, 2.0f, 0.0f);
		sh1->SetUniform3fv("eyePosWorld", camera.GetPosition());
		sh1->SetUniform4f("ambientLight", 0.1f, 0.1f, 0.1f, 1.0f);
		
		glm::mat4 modelToWorlMatrix =
			glm::translate(glm::vec3(0.0f, 0.0f, -5.0f)) *
			glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelToProjMat = worldToProjectionMatrix * modelToWorlMatrix;

		sh1->SetUniformMat4f("modelToWorldMat", modelToWorlMatrix);
		sh1->SetUniformMat4f("modelToProjMat", modelToProjMat);

		renderer.Draw(*va1, *ibuf, *sh1);
	}

}

void VisualizerWindow::mouseMoveEvent(QMouseEvent* e) {			//this is an overloaded version of a Qt method
	camera.MouseUpdate(glm::vec2(e->x(), e->y()));
	repaint();
}

void VisualizerWindow::keyPressEvent(QKeyEvent* e) {			//this is an overloaded version of a Qt method
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

void VisualizerWindow::initializeGL() {
	setMinimumSize(800, 500);
	setMouseTracking(true);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	SendDataToOpenGL();
}

//VisualizerWindow::~VisualizerWindow() {
	//glDeleteBuffers(1, &theVertexBufferID);
	//glDeleteBuffers(1, &theIndexBufferID);
	//glDeleteVertexArrays(1, &cubeVertexArrayObjectID);
	//glDeleteBuffers(1, &starVertexArrayObjectID);
	//glUseProgram(0);		//we can not delete the shader if its being used
	//glDeleteProgram(programID);
//}