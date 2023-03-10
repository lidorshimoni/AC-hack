#include "esp.h"

#define GAME_UNIT_MAGIC 400
#define VIRTUAL_SCREEN_WIDTH 800
#define PLAYER_HEIGHT 5.25f
#define PLAYER_WIDTH 2.0f
#define EYE_HEIGHT 4.5f
#define PLAYER_ASPECT_RATIO PLAYER_HEIGHT / PLAYER_WIDTH

#define ESP_FONT_HEIGHT 15
#define ESP_FONT_WIDTH 9

// should just take game as argument eh?

void FW::ESP::DrawBox(FW::Player_t p, vec3 screen, GL::Font & font, int windowWidth)
{
	const GLubyte* color = nullptr;
	float line_thickness = 1.0f;
	if (p.state != ALIVE) // if enemy is dead
		return;
	if (p.bEnemy)
	{
		color = rgb::red;
		line_thickness = 2.0f;
	}
	else color = rgb::green;

	float scale = (GAME_UNIT_MAGIC / p.dist) * (windowWidth / VIRTUAL_SCREEN_WIDTH);
	float x = screen.x - scale;
	float y = screen.y - scale * PLAYER_ASPECT_RATIO;
	float width = scale * 2;
	float height = scale * PLAYER_ASPECT_RATIO * 2;

	GL::DrawOutline(x, y, width, height, line_thickness, color);

	float textX = font.centerText(x, width, strlen(p.name) * ESP_FONT_WIDTH);
	float textY = y - ESP_FONT_HEIGHT / 2;
	font.Print(textX, textY, color, "%s", p.name);
}

//loop through players
void FW::ESP::ESP(std::vector<FW::Player_t> players, float matrix[16], int windowWidth, int windowHeight, GL::Font& font)
{
	for (auto p : players)
	{
		vec3 center = *p.head;
		center.z = center.z - EYE_HEIGHT + PLAYER_HEIGHT / 2;

		if (WorldToScreen(center, p.screen, matrix, windowWidth, windowHeight))
		{
			DrawBox(p, p.screen, font, windowWidth);
		}
	}
}