#pragma once

#include "ShapeData.h"

class ShapeGenerator {
public:
	static ShapeData MakeTriangle();
	static ShapeData MakeCube();
	static ShapeData MakeStar();
};
