#pragma once
#include "NXInterface.h"

// 83c9ba88-aff6-11e5-bf7f-feff819cdc9f
#define ShapePluginInterfaceID (NXInterfaceID(0x83c9ba88, 0xaff611e5, 0xbf7ffeff, 0x819cdc9f))



class ShapePluginInterface : public NXInterface
{
public:
	ShapePluginInterface() : NXInterface()
	{
		_interfaceID = ShapePluginInterfaceID;
	}

	virtual const char* GetShapeName() const = 0;
	virtual void DrawShape() const = 0;


private:
};

