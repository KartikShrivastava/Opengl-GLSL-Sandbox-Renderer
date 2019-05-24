#include <iostream>
#include <fstream>
#include <memory>

//#include "SFML/Audio.hpp"
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
GLuint cubeNormalNumIndices;

GLuint starIndexBufferByteOffset;
GLuint cubeNormalIndexBufferByteOffset;

//Camera camera;
//sf::Music music;
#define N 10000

void VisualizerWindow::SendDataToOpenGL() {

	ShapeData cube = ShapeGenerator::MakeCube();
	ShapeData star = ShapeGenerator::MakePlane(300);

	NormalShapeData cubeNormal = ShapeGenerator::generateNormals(cube);

	glGenBuffers(1, &theVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, theVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, cube.GetVertexBufferSize() + star.GetVertexBufferSize() + cubeNormal.GetVertexBufferSize(), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, cube.GetVertexBufferSize(), (void*)cube.vertices);
	glBufferSubData(GL_ARRAY_BUFFER, cube.GetVertexBufferSize(), star.GetVertexBufferSize(), (void*)star.vertices);
	glBufferSubData(GL_ARRAY_BUFFER, cube.GetVertexBufferSize() + star.GetVertexBufferSize(), cubeNormal.GetVertexBufferSize(), (void*)cubeNormal.norVertices);
	
	glGenBuffers(1, &theIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.GetIndexBufferSize() + star.GetIndexBufferSize() + cubeNormal.GetIndexBufferSize() , 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, cube.GetIndexBufferSize(), (void*)cube.indices);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, cube.GetIndexBufferSize(), star.GetIndexBufferSize(), (void*)star.indices);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, cube.GetIndexBufferSize() + star.GetIndexBufferSize(), cubeNormal.GetIndexBufferSize(), (void*)cubeNormal.norIndices);
	
	cubeNumIndices = cube.numIndices;
	starNumIndices = star.numIndices;
	cubeNormalNumIndices = cubeNormal.norNumIndices;
	
	//Setup vertex arrays
	glGenVertexArrays(1, &cubeVertexArrayObjectID);
	glGenVertexArrays(1, &starVertexArrayObjectID);
	glGenVertexArrays(1, &cubeNormalVertexArrayObjectID);

	glBindVertexArray(cubeVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBufferID);

	glBindVertexArray(starVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(cube.GetVertexBufferSize() + 0 * sizeof(GLfloat)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(cube.GetVertexBufferSize() + 3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(cube.GetVertexBufferSize() + 6 * sizeof(GLfloat)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBufferID);

	glBindVertexArray(cubeNormalVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, theVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(cube.GetVertexBufferSize() + star.GetVertexBufferSize() + 0 * sizeof(GLfloat)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBufferID);

	starIndexBufferByteOffset = cube.GetIndexBufferSize();
	cubeNormalIndexBufferByteOffset = cube.GetIndexBufferSize() + star.GetIndexBufferSize();

	cube.CleanupData();
	star.CleanupData();

	/*	INSTANCING CODE
	GLuint fullTransformMatrixBufferID;
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

void VisualizerWindow::paintGL() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());

	glm::mat4 fullTransformMatrix;
	glm::mat4 viewToProjectionMatrix = glm::perspective(glm::radians(60.0f), ((float)width()) / height(), 0.1f, 300.0f);
	glm::mat4 worldToViewMatrix = camera.GetWorldToViewMatrix();
	glm::mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

	//glUniform3f(ambientLightUniformLocation, 1.0f, 1.0f, 1.0f); //ambient light
	glUniform3f(diffuseLightPosUniformLocation, 0.0f, 2.0f, 0.0f);

	//translated cube
	glUseProgram(programID);
	glBindVertexArray(cubeVertexArrayObjectID);
	glm::mat4 cube1ModelToWorldMatrix =
		glm::translate(glm::vec3(5.0f, 3.0f, -5.0f)) * 
		glm::rotate(glm::radians(0.0f), glm::vec3(0.3f, 0.4f, 0.5f));
	fullTransformMatrix = worldToProjectionMatrix * cube1ModelToWorldMatrix;
	glUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE, &cube1ModelToWorldMatrix[0][0]);
	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, 0);

	//normal
	glUseProgram(normalProgramID);
	glBindVertexArray(cubeNormalVertexArrayObjectID);
	glUniformMatrix4fv(normalFullTransformUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_LINES, cubeNormalNumIndices, GL_UNSIGNED_SHORT, (void*)cubeNormalIndexBufferByteOffset);

	//centered cube
	glUseProgram(programID);
	glBindVertexArray(cubeVertexArrayObjectID);
	cube1ModelToWorldMatrix = glm::mat4(1);
	fullTransformMatrix = worldToProjectionMatrix * cube1ModelToWorldMatrix;
	glUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE, &cube1ModelToWorldMatrix[0][0]);
	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, 0);

	//normal
	glUseProgram(normalProgramID);
	glBindVertexArray(cubeNormalVertexArrayObjectID);
	glUniformMatrix4fv(normalFullTransformUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_LINES, cubeNormalNumIndices, GL_UNSIGNED_SHORT, (void*)cubeNormalIndexBufferByteOffset);

	//star
	glUseProgram(programID);
	glBindVertexArray(starVertexArrayObjectID);
	glm::mat4 starModelToWorldMatrix =
		glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	fullTransformMatrix = worldToProjectionMatrix * starModelToWorldMatrix;
	glUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE, &starModelToWorldMatrix[0][0]);
	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, starNumIndices, GL_UNSIGNED_SHORT, (void*)starIndexBufferByteOffset);
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

void GetAudioData() {
	
}

void TurnUpTheVolume() {
	//if (!music.openFromFile("sound2.wav"))
		//std::cout << "SFML error: Failed to load audio file" << std::endl;
	//music.play();

	//GetFFT();
	//GetAudioData();
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
	InstallShaders();

	fullTransformUniformLocation = glGetUniformLocation(programID, "fullTransformMatrix");
	ambientLightUniformLocation = glGetUniformLocation(programID, "ambientLight");
	diffuseLightPosUniformLocation = glGetUniformLocation(programID, "diffuseLightPos");
	modelToWorldMatrixUniformLocation = glGetUniformLocation(programID, "modelToWorldMatrix");
	
	normalFullTransformUniformLocation = glGetUniformLocation(normalProgramID, "normalFullTransformMatrix");
	
	//TurnUpTheVolume();
}

VisualizerWindow::~VisualizerWindow() {
	glDeleteBuffers(1, &theVertexBufferID);
	glDeleteBuffers(1, &theIndexBufferID);
	glDeleteVertexArrays(1, &cubeVertexArrayObjectID);
	glDeleteBuffers(1, &starVertexArrayObjectID);
	glUseProgram(0);		//we can not delete the shader if its being used
	glDeleteProgram(programID);
}