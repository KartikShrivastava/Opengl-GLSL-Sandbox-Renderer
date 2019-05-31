#pragma once
#include <QtGui/qwidget.h>
#include "VisualizerModel.h"

class DebugSlider;
class VisualizerWindow;

class VisualizerWidget : public QWidget {
private:
	Q_OBJECT

	DebugSlider* lightXSlider;
	DebugSlider* lightYSlider;
	DebugSlider* lightZSlider;

	VisualizerWindow* visualizerWindow;
	VisualizerModel visualizerModel;

private slots:
	void sliderValueChanged();

public:
	VisualizerWidget();
};