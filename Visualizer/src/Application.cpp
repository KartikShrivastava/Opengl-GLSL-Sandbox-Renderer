#include <iostream>

#include <QtGui/qapplication.h>
#include "VisualizerWindow.h"
#include "VisualizerWidget.h"

int main(int argc, char* argv[]) {
	 
	QApplication app(argc, argv);
	VisualizerWidget window;
	window.show();

	//VisualizerWindow window;		//Check out VisualizerWindow class for all OpenGL stuff
	//window.show();

	return app.exec();
}