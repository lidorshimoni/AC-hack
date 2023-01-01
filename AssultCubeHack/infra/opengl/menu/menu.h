#pragma once
#include "../../../stdafx.h"
#include "../hack/hackgl.h"
#include "../text/gltext.h"

enum rowtype_t { M_FUNCTION, M_HEADER, M_TAB, M_FOOTER, M_LABEL};
#define MENU_FONT_HEIGHT 15
#define MENU_FONT_WIDTH 9
#define MENU_ROW_YBUFFER 3
#define MENU_ROW_XBUFFER (MENU_FONT_WIDTH * 2)
#define MENU_LINE_WIDTH 2
#define MENU_FONT_LABEL_COLOR rgb::white
#define MENU_FONT_OFF_COLOR rgb::red
#define MENU_FONT_ON_COLOR rgb::green
#define MENU_OUTLINE_COLOR rgb::black

class row;

class Menu_t
{
public:
	GL::Font font;
	bool bMenuBuilt = false;
	float width;
	float height;
	float x, y;
	//int numTabs;
	float nextRowY;
	int longRowStrLen;
	std::vector<row> rows;

	void BuildMenu(std::vector<row> newRows, float x2, float y2);
	void GetMenuWidth();
	void GetLongestFunction();
	void Draw();
};

class row
{
public:
	enum rowtype_t type;
	char* text;
	char* text2;
	bool* status;
	float height;
	Menu_t* pmenu;

	row(rowtype_t type, char* text, bool* status);
	void Draw();
};

class tab
{
	//
};