#include "GL/glew.h"
#include <iostream>

//Remove all previous error before calling the function 'x'
void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

//check is any error has occured in the 'x' function call
bool GLLogError(const char* funtion, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error occured] : " << error << "\n" << funtion << "\n" << file << " : " << line << std::endl;
		return false;
	}
	return true;
}