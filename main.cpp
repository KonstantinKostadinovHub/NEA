#include "World.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"



World world;

int main()
{
	world.init();
	while (world.isOpen())
	{
		world.run();
	}

	ImGui::SFML::Shutdown();

	return 0;
}