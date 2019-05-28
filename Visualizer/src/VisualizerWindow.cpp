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

GLuint cubeNumIndices;
GLuint starNumIndices;
GLuint cubeNormalNumIndices;

GLuint starIndexBufferByteOffset;
GLuint cubeNormalIndexBufferByteOffset;

//Camera camera;
//sf::Music music;
#define N 10000

void VisualizerWindow::SendDataToOpenGL() {

	std::vector<ShapeData> shapes;
	shapes.push_back(ShapeGenerator::MakePlane());

	vb.push_back(VertexBuffer(shapes[0].GetVertexBufferSize(), shapes[0].vertices));
	ib.push_back(IndexBuffer(shapes[0].GetIndexBufferSize(), shapes[0].indices, shapes[0].numIndices));

	layout.push_back(VertexBufferLayout());
	layout[0].Push<float>(3);
	layout[0].Push<float>(3);
	layout[0].Push<float>(3);
	
	va.push_back(VertexArray(vb[0], layout[0]));

	shapes[0].CleanupData();

	Shader shaderTmp("res/shaders/VertexShaderCode.glsl", "res/shaders/FragmentShaderCode.glsl");
	shader.push_back(shaderTmp);
	shader[0].Bind();

	va[0].UnBind();
	vb[0].UnBind();
	ib[0].UnBind();
	shader[0].UnBind();

	//ShapeData shape1 = ShapeGenerator::makeTeapot();
	//ShapeData shape2 = ShapeGenerator::MakePlane(100);
	//
	//NormalShapeData shape1Normal = ShapeGenerator::generateNormals(shape1);

	//glGenBuffers(1, &theVertexBufferID);
	//glBindBuffer(GL_ARRAY_BUFFER, theVertexBufferID);
	//glBufferData(GL_ARRAY_BUFFER, shape1.GetVertexBufferSize() + shape2.GetVertexBufferSize() + shape1Normal.GetVertexBufferSize(), 0, GL_STATIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, shape1.GetVertexBufferSize(), (void*)shape1.vertices);
	//glBufferSubData(GL_ARRAY_BUFFER, shape1.GetVertexBufferSize(), shape2.GetVertexBufferSize(), (void*)shape2.vertices);
	//glBufferSubData(GL_ARRAY_BUFFER, shape1.GetVertexBufferSize() + shape2.GetVertexBufferSize(), shape1Normal.GetVertexBufferSize(), (void*)shape1Normal.norVertices);
	//
	//glGenBuffers(1, &theIndexBufferID);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBufferID);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape1.GetIndexBufferSize() + shape2.GetIndexBufferSize() + shape1Normal.GetIndexBufferSize() , 0, GL_STATIC_DRAW);
	//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, shape1.GetIndexBufferSize(), (void*)shape1.indices);
	//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, shape1.GetIndexBufferSize(), shape2.GetIndexBufferSize(), (void*)shape2.indices);
	//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, shape1.GetIndexBufferSize() + shape2.GetIndexBufferSize(), shape1Normal.GetIndexBufferSize(), (void*)shape1Normal.norIndices);
	
	//cubeNumIndices = shape1.numIndices;
	//starNumIndices = shape2.numIndices;
	//cubeNormalNumIndices = shape1Normal.norNumIndices;
	
	//Setup vertex arrays
	//glGenVertexArrays(1, &cubeVertexArrayObjectID);
	//glGenVertexArrays(1, &starVertexArrayObjectID);
	//glGenVertexArrays(1, &cubeNormalVertexArrayObjectID);
	//
	//glBindVertexArray(cubeVertexArrayObjectID);
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);
	//glBindBuffer(GL_ARRAY_BUFFER, theVertexBufferID);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBufferID);
	//
	//glBindVertexArray(starVertexArrayObjectID);
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);
	//glBindBuffer(GL_ARRAY_BUFFER, theVertexBufferID);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(shape1.GetVertexBufferSize() + 0 * sizeof(GLfloat)));
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(shape1.GetVertexBufferSize() + 3 * sizeof(GLfloat)));
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(shape1.GetVertexBufferSize() + 6 * sizeof(GLfloat)));
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBufferID);
	//
	//glBindVertexArray(cubeNormalVertexArrayObjectID);
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, theVertexBufferID);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(shape1.GetVertexBufferSize() + shape2.GetVertexBufferSize() + 0 * sizeof(GLfloat)));
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBufferID);
	//
	//starIndexBufferByteOffset = shape1.GetIndexBufferSize();
	//cubeNormalIndexBufferByteOffset = shape1.GetIndexBufferSize() + shape2.GetIndexBufferSize();
	//
	//shape1.CleanupData();
	//shape2.CleanupData();
	//shape1Normal.CleanupData();
}

void VisualizerWindow::paintGL() {
	renderer.Clear();
	glViewport(0, 0, width(), height());

	glm::mat4 modelToProjMat;
	glm::mat4 worldToViewMatrix = camera.GetWorldToViewMatrix();
	glm::mat4 viewToProjectionMatrix = glm::perspective(glm::radians(60.0f), ((float)width()) / height(), 0.1f, 300.0f);
	glm::mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

	{
		shader[0].Bind();
		shader[0].SetUniform3f("diffuseLightPosWorld", 0.0f, 2.0f, 0.0f);
		shader[0].SetUniform3fv("eyePosWorld", camera.GetPosition());
		shader[0].SetUniform4f("ambientLight", 0.1f, 0.1f, 0.1f, 1.0f);
		
		glm::mat4 modelToWorlMatrix =
			glm::translate(glm::vec3(5.0f, 3.0f, -5.0f)) *
			glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelToProjMat = worldToProjectionMatrix * modelToWorlMatrix;

		shader[0].SetUniformMat4f("modelToWorldMat", modelToWorlMatrix);
		shader[0].SetUniformMat4f("modelToProjMat", modelToProjMat);

		renderer.Draw(va[0], ib[0], shader[0]);
	}

	//glUniform3f(diffuseLightPosWorldUniformLoc, 0.0f, 2.0f, 0.0f);
	//glUniform3fv(eyePosWorldUniformLocation, 1, &camera.GetPosition()[0]);
	//glUniform4f(ambientLightUniformLoc, 0.1f, 0.1f, 0.1f, 1.0f); //ambient light

	////translated cube
	//glUseProgram(programID);
	//glBindVertexArray(cubeVertexArrayObjectID);
	//glm::mat4 cube1ModelToWorldMatrix =
	//	glm::translate(glm::vec3(5.0f, 3.0f, -5.0f)) * 
	//	glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//modelToProjMat = worldToProjectionMatrix * cube1ModelToWorldMatrix;
	//glUniformMatrix4fv(modelToWorldMatUniformLoc, 1, GL_FALSE, &cube1ModelToWorldMatrix[0][0]);
	//glUniformMatrix4fv(modelToProjMatUniformLoc, 1, GL_FALSE, &modelToProjMat[0][0]);
	//glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, 0);

	//normal
	//glUseProgram(normalProgramID);
	//glBindVertexArray(cubeNormalVertexArrayObjectID);
	//glUniformMatrix4fv(normalShaderModelToProjMatUniformLoc, 1, GL_FALSE, &modelToProjMat[0][0]);
	//glDrawElements(GL_LINES, cubeNormalNumIndices, GL_UNSIGNED_SHORT, (void*)cubeNormalIndexBufferByteOffset);

	//centered cube
	//glUseProgram(programID);
	//glBindVertexArray(cubeVertexArrayObjectID);
	//cube1ModelToWorldMatrix = glm::mat4(1);
	//modelToProjMat = worldToProjectionMatrix * cube1ModelToWorldMatrix;
	//glUniformMatrix4fv(modelToWorldMatUniformLoc, 1, GL_FALSE, &cube1ModelToWorldMatrix[0][0]);
	//glUniformMatrix4fv(modelToProjMatUniformLoc, 1, GL_FALSE, &modelToProjMat[0][0]);
	//glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, 0);

	//normal
	//glUseProgram(normalProgramID);
	//glBindVertexArray(cubeNormalVertexArrayObjectID);
	//glUniformMatrix4fv(normalShaderModelToProjMatUniformLoc, 1, GL_FALSE, &modelToProjMat[0][0]);
	//glDrawElements(GL_LINES, cubeNormalNumIndices, GL_UNSIGNED_SHORT, (void*)cubeNormalIndexBufferByteOffset);

	//star
	//glUseProgram(programID);
	//glBindVertexArray(starVertexArrayObjectID);
	//glm::mat4 starModelToWorldMatrix =
	//	glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)) *
	//	glm::rotate(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//modelToProjMat = worldToProjectionMatrix * starModelToWorldMatrix;
	//glUniformMatrix4fv(modelToWorldMatUniformLoc, 1, GL_FALSE, &starModelToWorldMatrix[0][0]);
	//glUniformMatrix4fv(modelToProjMatUniformLoc, 1, GL_FALSE, &modelToProjMat[0][0]);
	//glDrawElements(GL_TRIANGLES, starNumIndices, GL_UNSIGNED_SHORT, (void*)starIndexBufferByteOffset);

	//glUseProgram(normalProgramID);
	//glBindVertexArray(cubeNormalVertexArrayObjectID);
	//glUniformMatrix4fv(normalShaderModelToProjMatUniformLoc, 1, GL_FALSE, &modelToProjMat[0][0]);
	//glDrawElements(GL_LINES, cubeNormalNumIndices, GL_UNSIGNED_SHORT, (void*)cubeNormalIndexBufferByteOffset);
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

std::string VisualizerWindow::ReadShaderCode(const char* fileName) {
	std::ifstream inputFile(fileName);
	if (!inputFile.good()) {
		std::cout << "File failed to load... " << fileName << std::endl;
		exit(1);
	}
	return std::string(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>());
}

bool VisualizerWindow::CheckStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERSOURCEPROC getInfoLogFunc,
								   GLenum statusType) 
{
	GLint compileStatus;
	objectPropertyGetterFunc(objectID, statusType, &compileStatus);
	if (compileStatus != GL_TRUE) {
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLsizei bufferSize;
		std::unique_ptr<GLchar> buffer = std::make_unique<GLchar>(infoLogLength + 1);
		//std::unique_ptr<GLchar[]> buffer(new GLchar(infoLogLength+1));
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer.get());
		std::cout << buffer << std::endl;

		return false;
	}
	return true;
}

bool VisualizerWindow::CheckShaderStatus(GLuint shaderID) {
	return CheckStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool VisualizerWindow::CheckProgramStatus(GLuint programID) {
	return CheckStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

void VisualizerWindow::InstallShaders() {

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint normalVertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint normalFragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	std::string temp = ReadShaderCode("res/shaders/VertexShaderCode.glsl");	//include this file at the location of executable
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);

	temp = ReadShaderCode("res/shaders/FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	temp = ReadShaderCode("res/shaders/NormalVertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(normalVertexShaderID, 1, adapter, 0);

	temp = ReadShaderCode("res/shaders/NormalFragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(normalFragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);
	glCompileShader(normalVertexShaderID);
	glCompileShader(normalFragmentShaderID);

	if (!CheckShaderStatus(vertexShaderID) || !CheckShaderStatus(fragmentShaderID) || 
		!CheckShaderStatus(normalVertexShaderID) || !CheckShaderStatus(normalFragmentShaderID)) {
		return;
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	normalProgramID = glCreateProgram();
	glAttachShader(normalProgramID, normalVertexShaderID);
	glAttachShader(normalProgramID, normalFragmentShaderID);
	glLinkProgram(normalProgramID);

	if (!CheckProgramStatus(programID) || !CheckProgramStatus(normalProgramID))
		return;

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteShader(normalVertexShaderID);
	glDeleteShader(normalFragmentShaderID);

	//glUseProgram(programID);
	//glUseProgram(normalProgramID);
}

void VisualizerWindow::initializeGL() {
	setMinimumSize(800, 500);
	setMouseTracking(true);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CW);
	SendDataToOpenGL();
	//InstallShaders();

	//modelToProjMatUniformLoc = glGetUniformLocation(programID, "modelToProjMat");//
	//ambientLightUniformLoc = glGetUniformLocation(programID, "ambientLight");//
	//diffuseLightPosWorldUniformLoc = glGetUniformLocation(programID, "diffuseLightPosWorld");//
	//modelToWorldMatUniformLoc = glGetUniformLocation(programID, "modelToWorldMat");//
	//eyePosWorldUniformLocation = glGetUniformLocation(programID, "eyePosWorld");//
	//
	//normalShaderModelToProjMatUniformLoc = glGetUniformLocation(normalProgramID, "normalShaderModelToProjMat");
}

//VisualizerWindow::~VisualizerWindow() {
	//glDeleteBuffers(1, &theVertexBufferID);
	//glDeleteBuffers(1, &theIndexBufferID);
	//glDeleteVertexArrays(1, &cubeVertexArrayObjectID);
	//glDeleteBuffers(1, &starVertexArrayObjectID);
	//glUseProgram(0);		//we can not delete the shader if its being used
	//glDeleteProgram(programID);
//}