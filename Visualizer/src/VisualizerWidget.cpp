#include "VisualizerWidget.h"
#include "VisualizerWindow.h"
#include <Qt\qdebug.h>
#include <Qtgui\qvboxlayout>
#include <Qtgui\qhboxlayout>
#include "DebugSlider.h"

VisualizerWidget::VisualizerWidget()
{
	QVBoxLayout* mainLayout;
	setLayout(mainLayout = new QVBoxLayout);
	QVBoxLayout* controlsLayout;
	mainLayout->addLayout(controlsLayout = new QVBoxLayout);
	mainLayout->addWidget(visualizerWindow = new VisualizerWindow(&visualizerModel));

	QHBoxLayout* lightPosLayout;
	controlsLayout->addLayout(lightPosLayout = new QHBoxLayout);

	lightPosLayout->addWidget(lightXSlider = new DebugSlider);
	lightPosLayout->addWidget(lightYSlider = new DebugSlider(3,0));
	lightPosLayout->addWidget(lightZSlider = new DebugSlider);
	
	connect(lightXSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
	connect(lightYSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
	connect(lightZSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));

	sliderValueChanged();
}

void VisualizerWidget::sliderValueChanged() {
	visualizerModel.lightPos.x = lightXSlider->value();
	visualizerModel.lightPos.y = lightYSlider->value();
	visualizerModel.lightPos.z = lightZSlider->value();
	visualizerWindow->repaint();
}