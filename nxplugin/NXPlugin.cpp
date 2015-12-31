#include "NXPluginSystem.h"
#include <Windows.h>

NXPlugin::NXPlugin(void* dynamicLib, const char* pluginFileName)
{
	_dynamicLib = dynamicLib;
	_ImplementsInterface = (ImplementsInterfaceProc)GetProcAddress((HMODULE)_dynamicLib, "NXPluginImplementsInterface");
	_InstantiateInterface = (InstantiateInterfacePoc)GetProcAddress((HMODULE)_dynamicLib, "NXPluginInstantiateInterface");
	_ReleaseInterface = (ReleaseInterfaceProc)GetProcAddress((HMODULE)_dynamicLib, "NXPluginReleaseInterface");
}

NXPlugin::~NXPlugin()
{
	FreeLibrary((HMODULE)_dynamicLib);
}

bool NXPlugin::ImplementsInterface(const NXInterfaceID& interfaceToCheck) const
{
	if( !_ImplementsInterface)
		return false;

	return _ImplementsInterface(interfaceToCheck);
}

NXInterface* NXPlugin::InstantiateInterface(const NXInterfaceID& interfaceToInstantiate) const
{
	if( !_InstantiateInterface)
		return 0;

	return _InstantiateInterface(interfaceToInstantiate);
}

void NXPlugin::ReleaseInterface(NXInterface* interfaceToRelease) const
{
	if( _ReleaseInterface )
		_ReleaseInterface(interfaceToRelease);
}

bool LoadManifestFile(const char* manifestFileName, char* pluginFileName, size_t sizeofPluginFileName)
{
	bool retVal = false;

	// Open the manifest file
	FILE* f = fopen(manifestFileName, "rb");
	if (f)
	{
		// Get the size of the file, its ok if we truncate to 32 bits here.  We really cant handle that much data anyway
		fseek(f, 0, SEEK_END);
		size_t len = (size_t)ftell(f);
		fseek(f, 0, SEEK_SET);

		// Read the file data into memory
		char* fileData = (char*)malloc(len + 1);
		fread(fileData, 1, len, f);
		fclose(f);
		fileData[len] = 0;

		// Make file data a null terminated string containing the first line of the file
		char* endLine = fileData;
		while (*endLine && *endLine != '\n' && *endLine != '\r')
			endLine++;
		*endLine = 0;
		len = strlen(fileData);

		// Make sure we have enough space
		size_t pathLen = strlen(pluginFileName);
		size_t space = sizeofPluginFileName - pathLen;
		if (space > len)
		{
			memcpy(pluginFileName + pathLen, fileData, len + 1);		// Copy file data into the output path
			retVal = true;
		}

		// Cleanup
		free(fileData);
	}

	return retVal;
}

NXPlugin* NXPlugin::Load(const char* pluginPath)
{
	// Load manifest file
	char manifestFile[1024];
	strcpy(manifestFile, pluginPath);
	strcat(manifestFile, "/manifest.txt");

	char pluginFile[1024];
	strcpy(pluginFile, pluginPath);
	strcat(pluginFile, "/");
	if( !LoadManifestFile(manifestFile, pluginFile, sizeof(pluginFile)) )
		return 0;

	// Load the main plugin dll
	HMODULE lib = LoadLibraryA(pluginFile);
	if( lib == 0 )
		return 0;

	// Make sure this is a valid nx plugin?
	FARPROC addr = GetProcAddress(lib, "NXPluginImplementsInterface");
	if( addr == 0 )
		return 0;

	return new NXPlugin(lib, pluginFile);
}