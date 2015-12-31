// CirclePlugin.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "NXPlugin.h"
#include "CircleImplementation.h"

__declspec(dllexport) bool NXPluginImplementsInterface(const NXInterfaceID& interfaceToCheck)
{
	// This plugin only supports the one interface
	if( interfaceToCheck == ShapePluginInterfaceID )
		return true;

	return false;
}

__declspec(dllexport) NXInterface* NXPluginInstantiateInterface(const NXInterfaceID& interfaceToInstantiate)
{
	if( interfaceToInstantiate == ShapePluginInterfaceID )
		return new CircleImplementation();

	return 0;
}

__declspec(dllexport) void NXPluginReleaseInterface(NXInterface* interfaceToRelease)
{
	if (interfaceToRelease != 0)
	{
		delete interfaceToRelease;
	}
}