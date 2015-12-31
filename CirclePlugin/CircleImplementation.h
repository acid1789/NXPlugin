#pragma once


#include "ShapePluginInterface.h"
class CircleImplementation : public ShapePluginInterface
{
public:
	CircleImplementation();
	virtual ~CircleImplementation();

	const char* GetShapeName() const;
	void DrawShape() const;
};

