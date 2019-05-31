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
#include "VisualizerModel.h"

#define N 10000

void VisualizerWindow::initializeGL() {
	setMinimumSize(800, 500);
	setMouseTracking(false);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	SendDataToOpenGL();
}

void VisualizerWindow::SendDataToOpenGL() {
	
	GenerateShapes();
	//GenerateNormals();

	shader.push_back(Shader());
	shader[0].CreateShader("res/shaders/VertexShaderCode.glsl", "res/shaders/FragmentShaderCode.glsl");
	shader.push_back(Shader());
	shader[1].CreateShader("res/shaders/NormalVertexShaderCode.glsl", "res/shaders/NormalFragmentShaderCode.glsl");
}

void VisualizerWindow::GenerateShapes() {
	std::vector<ShapeData> shapes;

	shapes.push_back(ShapeGenerator::makeTeapot());
	shapes.push_back(ShapeGenerator::MakeCube());
	shapes.push_back(ShapeGenerator::MakePlane(50));
	shapes.push_back(ShapeGenerator::MakeStar());

	for (size_t i = 0; i < shapes.size(); i++) {
		vb.push_back(VertexBuffer(shapes[i].GetVertexBufferSize(), shapes[i].vertices));
		ib.push_back(IndexBuffer(shapes[i].GetIndexBufferSize(), shapes[i].indices, shapes[i].numIndices));
		layout.push_back(VertexBufferLayout());
		layout[i].Push<float>(3);		//vertex position
		layout[i].Push<float>(3);		//vertex color
		if(i != shapes.size() - 1)		//dont add normals for star, as I havent added it yet :P
			layout[i].Push<float>(3);	//normals
		va.push_back(VertexArray(vb[i], layout[i]));
	}

	for (auto shape : shapes)
		shape.CleanupData();
	shapes.clear();
}

void VisualizerWindow::GenerateNormals() {
	std::vector<NormalShapeData> normals;
	normals.push_back(ShapeGenerator::generateNormals(ShapeGenerator::MakeCube()));
	size_t normalIndex = vb.size();

	vb.push_back(VertexBuffer(normals[0].GetVertexBufferSize(), normals[0].norVertices));
	ib.push_back(IndexBuffer(normals[0].GetIndexBufferSize(), normals[0].norIndices, normals[0].norNumIndices));
	layout.push_back(VertexBufferLayout());
	layout[normalIndex].Push<float>(3);	//normals
	va.push_back(VertexArray(vb[normalIndex], layout[normalIndex]));

	for (auto normal : normals)
		normal.CleanupData();
	normals.clear();
}

void VisualizerWindow::paintGL() {
	renderer.Clear();
	glViewport(0, 0, width(), height());

	glm::mat4 modelToProjMat;
	glm::mat4 worldToViewMatrix = camera.GetWorldToViewMatrix();
	glm::mat4 viewToProjectionMatrix = glm::perspective(glm::radians(50.0f), ((float)width()) / height(), 0.1f, 300.0f);
	glm::mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

	shader[0].Bind();
	shader[0].SetUniform3fv("diffuseLightPosWorld", visualizerModel->lightPos);
	shader[0].SetUniform3fv("eyePosWorld", camera.GetPosition());
	shader[0].SetUniform4f("ambientLight", 0.15f, 0.15f, 0.1f, 1.0f);
	
	{	//teapot
		glm::mat4 modelToWorlMatrix = glm::translate(glm::vec3(2.0f, 2.0f, -8.0f)) * glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelToProjMat = worldToProjectionMatrix * modelToWorlMatrix;
		shader[0].SetUniformMat4f("modelToWorldMat", modelToWorlMatrix);
		shader[0].SetUniformMat4f("modelToProjMat", modelToProjMat);
		renderer.DrawTri(va[0], ib[0], shader[0]);
	}

	{	//cube
		for (int i = 0; i <= 360; i+=30) {
			glm::mat4 modelToWorlMatrix = glm::rotate(glm::radians((float)i), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::vec3(0.0f, 1.0f, -8.0f));
			modelToProjMat = worldToProjectionMatrix * modelToWorlMatrix;
			shader[0].SetUniformMat4f("modelToWorldMat", modelToWorlMatrix);
			shader[0].SetUniformMat4f("modelToProjMat", modelToProjMat);
			renderer.DrawTri(va[1], ib[1], shader[0]);
		}
	}

	{	//plane
		glm::mat4 modelToWorlMatrix = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)) * glm::rotate(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelToProjMat = worldToProjectionMatrix * modelToWorlMatrix;
		shader[0].SetUniformMat4f("modelToWorldMat", modelToWorlMatrix);
		shader[0].SetUniformMat4f("modelToProjMat", modelToProjMat);
		renderer.DrawTri(va[2], ib[2], shader[0]);
	}

	{	//lamp : uses normal shader
		shader[1].Bind();
		glm::mat4 modelToWorlMatrix = glm::translate(visualizerModel->lightPos) * glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
		modelToProjMat = worldToProjectionMatrix * modelToWorlMatrix;
		shader[1].SetUniformMat4f("normalShaderModelToProjMat", modelToProjMat);
		renderer.DrawTri(va[3], ib[3], shader[1]);
	}
}

void VisualizerWindow::mouseMoveEvent(QMouseEvent* e) {
	setFocus();
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

VisualizerWindow::VisualizerWindow(VisualizerModel* model) : visualizerModel(model) {
	
}

VisualizerWindow::~VisualizerWindow() {
	for (size_t i = 0; i < vb.size(); i++) {
		vb[i].CleanupData();
		ib[i].CleanupData();
		va[i].CleanupData();
	}
	for (size_t i = 0; i < shader.size(); i++)
		shader[i].CleanupData();
	vb.clear();
	ib.clear();
	layout.clear();
	va.clear();
	shader.clear();
}