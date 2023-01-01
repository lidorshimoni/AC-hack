#pragma once
#include "../opengl/hack/hackgl.h"
#include "../opengl/text/gltext.h"
#include "../player/player.h"

namespace FW
{
	namespace ESP
	{
		void DrawBox(FW::Player_t p, vec3 screen, GL::Font& font, int windowWidth);
		void ESP(std::vector<FW::Player_t> players, float matrix[16], int windowWidth, int windowHeight, GL::Font& font);
	}
}