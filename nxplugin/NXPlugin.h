#pragma once

#include "NXInterface.h"

typedef bool (*ImplementsInterfaceProc)(const NXInterfaceID& interfaceToCheck);
typedef NXInterface* (*InstantiateInterfacePoc)(const NXInterfaceID& interfaceToInstantiate);
typedef void (*ReleaseInterfaceProc)(NXInterface* interfaceToRelease);

class NXPlugin
{
	NXPlugin(void* dynamicLibrary, const char* pluginFileName);
public:
	~NXPlugin();

	bool ImplementsInterface(const NXInterfaceID& interfaceToCheck) const;

	NXInterface* InstantiateInterface(const NXInterfaceID& interfaceToInstantiate) const;
	void ReleaseInterface(NXInterface* interfaceToRelease) const;


	static NXPlugin* Load(const char* pluginPath);

private:
	void* _dynamicLib;
	ImplementsInterfaceProc _ImplementsInterface;
	InstantiateInterfacePoc _InstantiateInterface;
	ReleaseInterfaceProc _ReleaseInterface;
};