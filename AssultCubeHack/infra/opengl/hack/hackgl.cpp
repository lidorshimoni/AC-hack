#pragma once
#include "hackgl.h"

void GL::Hook(const char* function, uintptr_t& oFunction, void* hFunction)
{
	HMODULE hMod = GetModuleHandle("opengl32.dll");

	if (hMod)
	{
		oFunction = (uintptr_t)mem::TrampolineHook((void*)GetProcAddress(hMod, function), hFunction, 5);
	}
}

void GL::unHook(const char* function, void* oFunction) {
	LPVOID orgAddr = GetProcAddress(GetModuleHandle("opengl32.dll"), function);

	std::cout << orgAddr;

	DWORD curProtection;
	VirtualProtect(orgAddr, 5, PAGE_EXECUTE_READWRITE, &curProtection);
	memcpy_s(orgAddr, 5, oFunction, 5);
	VirtualProtect(orgAddr, 5, curProtection, &curProtection);

	//Nop-ing the gateway, not sure if needed :P
	DWORD curProtect;
	VirtualProtect(oFunction, 5, PAGE_EXECUTE_READWRITE, &curProtect);
	memset(oFunction, 0x90, 5);
	VirtualProtect(oFunction, 5, curProtect, &curProtect);

}

void GL::SetupOrtho()
{
	//OA
	/*
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, this->viewport[3], this->viewport[4], 0, -1.0f, 1.0f);
	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	*/

	//AC
	//glPushMatrix();
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_BLEND); //Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.
		

}

void GL::RestoreGL()
{
	glDisable(GL_BLEND); //Disable blending.
	glEnable(GL_DEPTH_TEST);
	/*
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	*/
}

void GL::DrawFilledRect(float x, float y, float width, float height, const GLubyte color[3])
{
	//glColor3ub(color[0], color[1], color[2]);
	glColor4ub(color[0], color[1], color[2], 180);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

void GL::DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3])
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
	glColor4ub(color[0], color[1], color[2], 180);
	glVertex2f(x - 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5f, y - 0.5f);
	glEnd();
}