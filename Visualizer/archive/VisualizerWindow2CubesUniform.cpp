#include <iostream>
#include <fstream>
#include <memory>

#include "SFML/Audio.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtx/transform.hpp"
//#include "kiss_fft.h"

#include "Vertex.h"
#include "ShapeGenerator.h"
#include "VisualizerWindow.h"

GLuint programID;
GLuint numIndices;

sf::Music music;
#define N 10000

void VisualizerWindow::SendDataToOpenGL() {
	ShapeData shape = ShapeGenerator::MakeCube();
	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.GetVertexBufferSize(), shape.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	
	GLuint indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.GetIndexBufferSize(), shape.indices, GL_STATIC_DRAW);
	numIndices = shape.numIndices;

	shape.CleanupData();
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
	glewInit();
	glEnable(GL_DEPTH_TEST);
	SendDataToOpenGL();
	InstallShaders();

	//TurnUpTheVolume();
}
 
void VisualizerWindow::paintGL() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());

	GLint fullTransformMatrixUniformLocation = glGetUniformLocation(programID, "fullTransformMatrix");
	glm::mat4 fullTransformMatrix;
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), ((float)width()) / height(), 0.1f, 10.0f);

	//cube 1
	glm::mat4 translationMatrix = glm::translate(glm::vec3(-1.0f, 0.0f, -6.0f));
	//glm::mat4 rotationMatrix = glm::rotate(glm::radians(36.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	fullTransformMatrix = projectionMatrix * translationMatrix;// *rotationMatrix;

	glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);

	//cube 2
	translationMatrix = glm::translate(glm::vec3(1.0f, 0.0f, -6.75f));
	//rotationMatrix = glm::rotate(glm::radians(126.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	fullTransformMatrix = projectionMatrix * translationMatrix;// *rotationMatrix;

	glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
}

VisualizerWindow::~VisualizerWindow() {
	glUseProgram(0);		//we can not delete the shader if its being used
	glDeleteProgram(programID);
}