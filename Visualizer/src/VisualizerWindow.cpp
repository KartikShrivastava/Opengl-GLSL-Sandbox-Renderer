#include <iostream>
#include <fstream>
#include <memory>

#include "SFML/Audio.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtx/transform.hpp"
#include "QtGui/qmouseevent"
#include "QtGui/qkeyevent"
//#include "kiss_fft.h"

#include "Vertex.h"
#include "ShapeGenerator.h"
#include "VisualizerWindow.h"

GLuint cubeNumIndices;
GLuint starNumIndices;

GLuint cubeVertexBufferID;
GLuint cubeIndexBufferID;
GLuint starVertexBufferID;
GLuint starIndexBufferID;

//Camera camera;
sf::Music music;
#define N 10000

void VisualizerWindow::SendDataToOpenGL() {

	//cube
	ShapeData shape = ShapeGenerator::MakeCube();
	glGenBuffers(1, &cubeVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.GetVertexBufferSize(), shape.vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	
	glGenBuffers(1, &cubeIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.GetIndexBufferSize(), shape.indices, GL_STATIC_DRAW);
	cubeNumIndices = shape.numIndices;
	shape.CleanupData();

	//star
	shape = ShapeGenerator::MakeStar();
	glGenBuffers(1, &starVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, starVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.GetVertexBufferSize(), shape.vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	glGenBuffers(1, &starIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, starIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.GetIndexBufferSize(), shape.indices, GL_STATIC_DRAW);
	starNumIndices = shape.numIndices;
	shape.CleanupData();

	/*GLuint fullTransformMatrixBufferID;
	glGenBuffers(1, &fullTransformMatrixBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, fullTransformMatrixBufferID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * 2, 0, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(GL_FLOAT) * 0));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(GL_FLOAT) * 4));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(GL_FLOAT) * 8));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(GL_FLOAT) * 12));
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	shape.CleanupData();
	*/

}

void VisualizerWindow::SetupVertexArrrays() {
	glGenVertexArrays(1, &cubeVertexArrayObjectID);
	glGenVertexArrays(1, &starVertexArrayObjectID);
	
	glBindVertexArray(cubeVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndexBufferID);

	glBindVertexArray(starVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, starVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, starIndexBufferID);
}

void VisualizerWindow::paintGL() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());

	glm::mat4 fullTransformMatrix;
	glm::mat4 viewToProjectionMatrix = glm::perspective(glm::radians(60.0f), ((float)width()) / height(), 0.1f, 10.0f);
	glm::mat4 worldToViewMatrix = camera.GetWorldToViewMatrix();
	glm::mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

	//cube
	glBindVertexArray(cubeVertexArrayObjectID);
	glm::mat4 cube1ModelToWorldMatrix =
		glm::translate(glm::vec3(1.0f, 0.2f, -10.0f)) *
		glm::rotate(glm::radians(120.f), glm::vec3(0.0f, 0.0f, 1.0f));
	fullTransformMatrix = worldToProjectionMatrix * cube1ModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, 0);

	//star
	glBindVertexArray(starVertexArrayObjectID);
	glm::mat4 starModelToWorldMatrix =
		glm::translate(glm::vec3(2.0f, 0.0f, -6.0f)) *
		glm::rotate(glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	fullTransformMatrix = worldToProjectionMatrix * starModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, starNumIndices, GL_UNSIGNED_SHORT, 0);

	/*glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), ((float)width()) / height(), 0.1f, 10.0f);
	glm::mat4 fullTransforms[] = {
		projectionMatrix * camera.GetWorldToViewMatrix() * glm::translate(glm::vec3(-1.0f, 0.0f, -6.15f))* glm::rotate(glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		projectionMatrix * camera.GetWorldToViewMatrix() * glm::translate(glm::vec3(2.0f, 0.0f, -6.0f)) * glm::rotate(glm::radians(30.0f), glm::vec3(1.0f,0.0f,0.0f))
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(fullTransforms), fullTransforms, GL_DYNAMIC_DRAW);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());
	glDrawElementsInstanced(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0, 2);*/
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

bool VisualizerWindow::CheckShaderStatus(GLuint programID) {
	return CheckStatus(programID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool VisualizerWindow::CheckProgramStatus(GLuint programID) {
	return CheckStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

void VisualizerWindow::InstallShaders() {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	std::string temp = ReadShaderCode("res/shaders/VertexShaderCode.glsl");	//include this file at the location of executable
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);

	temp = ReadShaderCode("res/shaders/FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!CheckShaderStatus(vertexShaderID) || !CheckShaderStatus(fragmentShaderID)) {
		return;
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!CheckProgramStatus(programID))
		return;

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glUseProgram(programID);
}

void GetAudioData() {
	
}

void TurnUpTheVolume() {
	if (!music.openFromFile("sound2.wav"))
		std::cout << "SFML error: Failed to load audio file" << std::endl;
	music.play();

	//GetFFT();
	//GetAudioData();
}

void VisualizerWindow::initializeGL() {
	setMinimumSize(800, 500);
	setMouseTracking(true);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	SendDataToOpenGL();
	SetupVertexArrrays();
	InstallShaders();

	fullTransformUniformLocation = glGetUniformLocation(programID, "fullTransformMatrix");
	//TurnUpTheVolume();
}

VisualizerWindow::~VisualizerWindow() {
	glUseProgram(0);		//we can not delete the shader if its being used
	glDeleteProgram(programID);
}