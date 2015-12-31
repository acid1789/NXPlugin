// SquarePlugin.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "NXInterface.h"
#include "SquareImplementation.h"

__declspec(dllexport) bool NXPluginImplementsInterface(const NXInterfaceID& interfaceToCheck)
{
	if( interfaceToCheck == ShapePluginInterfaceID )
		return true;

	return false;
}

__declspec(dllexport) NXInterface* NXPluginInstantiateInterface(const NXInterfaceID& interfaceToInstantiate)
{
	if (interfaceToInstantiate == ShapePluginInterfaceID)
		return new SquareImplementation();

	return 0;
}

__declspec(dllexport) void NXPluginReleaseInterface(NXInterface* interfaceToRelease)
{
	if (interfaceToRelease != 0)
	{
		delete interfaceToRelease;
	}
}