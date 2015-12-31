#include "NXPluginSystem.h"
#include <windows.h>

#pragma comment(lib, "User32.lib")

static const char* s_PluginDir = 0;
static std::vector<NXPlugin*> s_LoadedPlugins;

NXInterfaceID NXPluginManager::NullInterface( 0, 0, 0, 0 );

static bool IsZipFile(char* fileName)
{
	return false;
}

static void LoadPlugins()
{
	char path[MAX_PATH];
	strcpy(path, s_PluginDir);
	strcat(path, "\\*");

	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA(path, &findData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// Load the plugin from the directory
				NXPlugin* plugin = NXPlugin::Load(findData.cFileName);
				if( plugin )
					s_LoadedPlugins.push_back(plugin);
			}
			else
			{
				// Its a file, if its a zip file, import it now
				if (IsZipFile(findData.cFileName))
				{
					// Do the import to extract this into a folder
					NXPluginManager::ImportPlugin(findData.cFileName);

					// Delete the zip from here
					DeleteFileA(findData.cFileName);
				}
			}

		} while( FindNextFileA(hFind, &findData) );
	}
}

static void UnloadPlugins()
{
	for (size_t i = 0; i < s_LoadedPlugins.size(); i++)
	{
		NXPlugin* plugin = s_LoadedPlugins[i];
		delete plugin;
	}
	s_LoadedPlugins.clear();
}

void NXPluginManager::Init(const char* pluginDir)
{
	if(s_PluginDir != 0)
		return;	// Already initialized, nothing to do here
	s_PluginDir = pluginDir;
	
	// Look in the supplied folder for all plugins
	LoadPlugins();

	// Setup folder watcher to load any plugins that get dropped in
}

void NXPluginManager::Shutdown()
{
	// Shutdown folder watcher

	// Unload all plugins
	UnloadPlugins();

	// Clear the pluign dir
	s_PluginDir = 0;
}

std::vector<const NXPlugin*> NXPluginManager::GetPlugins(const NXInterfaceID& implementsInterface)
{
	std::vector<const NXPlugin*> matchingPlugins;

	bool includeAll = implementsInterface.IsZero();

	for (size_t i = 0; i < s_LoadedPlugins.size(); i++)
	{
		NXPlugin* plugin = s_LoadedPlugins[i];
		if( includeAll || plugin->ImplementsInterface(implementsInterface)  )
			matchingPlugins.push_back(plugin);
	}

	return matchingPlugins;
}