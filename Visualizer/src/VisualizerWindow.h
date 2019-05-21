#pragma once

#include <gl\glew.h>
#include <QtOpenGL/QGLWidget>

#include "Camera.h"

class VisualizerWindow : public QGLWidget
{
private:
	Camera camera;
	GLuint programID;
	GLint fullTransformUniformLocation;
	GLuint cubeVertexArrayObjectID;
	GLuint starVertexArrayObjectID;

	//void SendUpdatedDataToOpengl();
	void SendDataToOpenGL();
	bool CheckStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERSOURCEPROC getInfoLogFunc, GLenum statusType);
	bool CheckShaderStatus(GLuint shaderID);
	bool CheckProgramStatus(GLuint programID);
	std::string ReadShaderCode(const char* fileName);
	void InstallShaders();
	void SetupVertexArrrays();

protected:
	void initializeGL() override;
	void paintGL() override;
	void mouseMoveEvent(QMouseEvent*);
	void keyPressEvent(QKeyEvent*);

public:
	~VisualizerWindow();
};