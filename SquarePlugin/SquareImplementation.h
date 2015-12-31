#pragma once

#include "ShapePluginInterface.h"
class SquareImplementation : public ShapePluginInterface
{
public:
	SquareImplementation();
	virtual ~SquareImplementation();

	const char* GetShapeName() const;
	void DrawShape() const;
};

