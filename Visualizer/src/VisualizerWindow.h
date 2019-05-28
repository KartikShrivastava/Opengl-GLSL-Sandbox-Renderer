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
	GLuint programID;
	GLuint normalProgramID;	//programID for normalVertexShader
	GLint modelToProjMatUniformLoc;
	GLint modelToWorldMatUniformLoc;
	GLint ambientLightUniformLoc;
	GLint diffuseLightPosWorldUniformLoc;
	GLint normalShaderModelToProjMatUniformLoc;
	GLint eyePosWorldUniformLocation;
	GLuint theVertexBufferID;
	GLuint theIndexBufferID;
	GLuint cubeVertexArrayObjectID;
	GLuint starVertexArrayObjectID;
	GLuint cubeNormalVertexArrayObjectID;
	std::vector<VertexBuffer> vb;
	std::vector<IndexBuffer> ib;
	std::vector<VertexBufferLayout> layout;
	std::vector<VertexArray> va;
	std::vector<Shader> shader;
	Renderer renderer;

	//void SendUpdatedDataToOpengl();
	void SendDataToOpenGL();
	bool CheckStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERSOURCEPROC getInfoLogFunc, GLenum statusType);
	bool CheckShaderStatus(GLuint shaderID);
	bool CheckProgramStatus(GLuint programID);
	std::string ReadShaderCode(const char* fileName);
	void InstallShaders();

protected:
	void initializeGL() override;
	void paintGL() override;
	void mouseMoveEvent(QMouseEvent*);
	void keyPressEvent(QKeyEvent*);

public:
	//~VisualizerWindow();
};