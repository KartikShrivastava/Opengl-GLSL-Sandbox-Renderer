#include <iostream>
#include <fstream>
#include <memory>

#include "VisualizerWindow.h"

const float X_DELTA = 0.1f;
uint TRIANGLE_BYTE_SIZE = 3 * 6 * sizeof(float);
uint numTriangles;

void VisualizerWindow::SendDataToOpenGL() {
	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, 10000, NULL, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
}

void VisualizerWindow::SendUpdatedDataToOpengl() {
	const float THIS_TRIANGLE_X = -1.0f + numTriangles * X_DELTA;
	float vertices[] = {
		THIS_TRIANGLE_X			 , 1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		THIS_TRIANGLE_X			 , 0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		THIS_TRIANGLE_X + X_DELTA, 1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	};
	glBufferSubData(GL_ARRAY_BUFFER, numTriangles * TRIANGLE_BYTE_SIZE, TRIANGLE_BYTE_SIZE, vertices);
	numTriangles++;
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

	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!CheckProgramStatus(programID))
		return;

	glUseProgram(programID);
}

void VisualizerWindow::initializeGL() {
	setMinimumSize(600, 600);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	SendDataToOpenGL();
	InstallShaders();
}
 
void VisualizerWindow::paintGL() {
	//glClearColor(0.5f, 0.2f, 0.8f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());
	SendUpdatedDataToOpengl();
	glDrawArrays(GL_TRIANGLES, (numTriangles - 1) * 3, numTriangles * 3);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}