#include "VisualizerWidget.h"
#include "VisualizerWindow.h"
#include <Qtgui\qvboxlayout>
#include <Qtgui\qhboxlayout>
#include "DebugSlider.h"

VisualizerWidget::VisualizerWidget()
{
	QVBoxLayout* mainLayout;
	setLayout(mainLayout = new QVBoxLayout);
	QVBoxLayout* controlsLayout;
	mainLayout->addLayout(controlsLayout = new QVBoxLayout);
	mainLayout->addWidget(new VisualizerWindow);

	QHBoxLayout* scaleLayout;
	controlsLayout->addLayout(scaleLayout = new QHBoxLayout);
	scaleLayout->addWidget(new DebugSlider(0, -5, 5, false, 400));
	scaleLayout->addWidget(new DebugSlider(0, -5, 5, false, 400));
	scaleLayout->addWidget(new DebugSlider(0, -5, 5, false, 400));
}
