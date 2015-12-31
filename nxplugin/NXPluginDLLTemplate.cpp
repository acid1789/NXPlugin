#include "NXInterface.h"

__declspec(dllexport) bool NXPluginImplementsInterface(const NXInterfaceID& interfaceToCheck)
{
	return false;
}

__declspec(dllexport) NXInterface* NXPluginInstantiateInterface(const NXInterfaceID& interfaceToInstantiate)
{
	return 0;
}

__declspec(dllexport) void NXPluginReleaseInterface(NXInterface* interfaceToRelease)
{
	if (interfaceToRelease != 0)
	{
		delete interfaceToRelease;
	}
}