#pragma once

#include <gl\glew.h>
#include <QtOpenGL/QGLWidget>

#include "Camera.h"

class VisualizerWindow : public QGLWidget
{
private:
	//Camera camera;
protected:
	void initializeGL() override;
	void paintGL() override;

	void SendDataToOpenGL();
	void SendUpdatedDataToOpengl();
	void InstallShaders();
	std::string ReadShaderCode(const char* fileName);
	bool CheckStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERSOURCEPROC getInfoLogFunc,
		GLenum statusType);
	bool CheckShaderStatus(GLuint shaderID);
	bool CheckProgramStatus(GLuint programID);

	void mouseMoveEvent(QMouseEvent*);
	void keyPressEvent(QKeyEvent*);
public:
	~VisualizerWindow();
};