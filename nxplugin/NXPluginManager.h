#pragma once
#include "NXInterface.h"
#include <vector>


class NXPlugin;

class NXPluginManager
{
public:
	static void Init(const char* pluginDir);
	static void Shutdown();

	static std::vector<const NXPlugin*> GetPlugins(const NXInterfaceID& implementsInterface);

	static const NXPlugin* ImportPlugin(const char* pluginZipFile);
	static void RemovePlugin(const NXPlugin* pluginToRemove);

	static NXInterfaceID NullInterface;
};
