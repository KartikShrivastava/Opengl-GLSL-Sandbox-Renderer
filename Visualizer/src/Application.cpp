#include <iostream>

#include <QtGui/qapplication.h>
#include "VisualizerWindow.h"
#include "VisualizerWidget.h"

/*void PlayAudioWithSoundBuffer() {
	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile("bulletTrain.ogg")) {
		std::cout << "Error loading the sound file" << std::endl;
	}

	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
}*/

int main(int argc, char* argv[]) {

	QApplication app(argc, argv);
	VisualizerWindow window;
	window.show();

	//VisualizerWidget widget;
	//widget.show();

	return app.exec();
}