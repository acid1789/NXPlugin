// HostApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "NXPluginSystem.h"
#include "ShapePluginInterface.h"


int main()
{
	// Initialize plugin manager
	NXPluginManager::Init("./Plugins");

	// Get all plugins that implement the ShapePluginInterface
	std::vector<const NXPlugin*> plugins = NXPluginManager::GetPlugins(ShapePluginInterfaceID);

	// Ask the user to pick one
	printf("Choose a shape:\n");
	printf("  0: None\n");
	for (size_t i = 0; i < plugins.size(); i++)
	{
		ShapePluginInterface* shape = (ShapePluginInterface*)plugins[i]->InstantiateInterface(ShapePluginInterfaceID);
		printf("  %d: %s\n", (int)i + 1, shape->GetShapeName());
		plugins[i]->ReleaseInterface(shape);
	}
	int selection = getchar() - '0';

	// Draw the selected shape
	if (selection < 0 || selection > plugins.size())
	{
		printf("Invalid selection\n");
	}
	else if (selection == 0)
	{
		printf("You dont want a shape? :( Ok Bye\n");
	}
	else if (selection <= plugins.size())
	{
		ShapePluginInterface* shape = (ShapePluginInterface*)plugins[selection - 1]->InstantiateInterface(ShapePluginInterfaceID);
		shape->DrawShape();
		plugins[selection - 1]->ReleaseInterface(shape);
	}

	NXPluginManager::Shutdown();
    return 0;
}

