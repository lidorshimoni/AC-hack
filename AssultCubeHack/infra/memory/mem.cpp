#pragma once
#include "mem.h"

BYTE* mem::FindPattern(BYTE pattern[], int length, BYTE* begin, BYTE* end)
{
	int i = 0;
	for (BYTE* current = begin; current < end; current++)
	{
		//if pattern matches 100%
		if (i == length) return (current - length);

		//if wildcard or matching pattern
		if (pattern[i] == 0xff || *current == pattern[i]) i++;
		else i = 0; //if no match reset pattern
	}
	return nullptr;
}

std::vector<BYTE*> mem::FindPatterns(BYTE pattern[], int length, BYTE* begin, BYTE* end)
{
	BYTE* current = begin;
	std::vector<BYTE*> matches;

	while (current < end - length)
	{
		BYTE* temp = FindPattern(pattern, length, current, end);
		if (temp == nullptr) return matches;
		else
		{
			matches.push_back(temp);
			current = temp;
			current++;
		}
	}
	return matches;
}

//Credits to Solaire!
bool mem::Hook(void* src, void* dst, int len)
{
	if (len < 5)
	{
		return false;
	}

	DWORD  curProtection;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

	memset(src, 0x90, len);

	uintptr_t  relativeAddress = ((uintptr_t)dst - (uintptr_t)src) - 5;

	*(BYTE*)src = 0xE9;
	*(uintptr_t*)((uintptr_t)src + 1) = relativeAddress;

	DWORD  temp;
	VirtualProtect(src, len, curProtection, &temp);

	return true;
}

//Credits to Solaire!
void* mem::TrampolineHook(void* src, void* dst, int len)
{
	// Make sure the length is greater than 5
	if (len < 5) {
		return NULL;
	}

	// Create the gateway (len + 5 for the overwritten bytes + the jmp)
	void* gateway = VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	// Put the bytes that will be overwritten in the gateway
	memcpy(gateway, src, len);

	// Get the gateway to destination addy
	uintptr_t  gateJmpAddy = ((uintptr_t)src - (uintptr_t)gateway) - 5;

	// Add the jmp opcode to the end of the gateway
	*(BYTE*)((uintptr_t)gateway + len) = 0xE9;

	// Add the address to the jmp
	*(uintptr_t*)((uintptr_t)gateway + len + 1) = gateJmpAddy;

	// Place the hook at the destination
	Hook(src, dst, len);

	return gateway;
}

/*
class hook
{
public:
void * o;
void * h;
int len;

hook(char* functName, void* h, int len);
};

hook::hook(char* functName, void* h, int len)
{
}
*/

void mem::Patch(uintptr_t* dst, uintptr_t* src, int size)
{
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void mem::Nop(BYTE* dst, unsigned int size)
{
	DWORD oldProtect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldProtect, &oldProtect);
}

uintptr_t mem::FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); i++)
	{
		addr = *(uintptr_t*)addr;
		addr += offsets[i];
	}

	return addr;
}


//external patch
void PatchEx(HANDLE hProcess, void* dst, void* src, int size)
{
	DWORD oldprotect;
	VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	WriteProcessMemory(hProcess, dst, src, size, NULL);
	VirtualProtectEx(hProcess, dst, size, oldprotect, &oldprotect);
}

Hack::Hack(uintptr_t address, const char* newBytes)
{
	this->name = NULL;
	this->address = address;
	this->size = strlen(newBytes);
	memcpy(this->newBytes, newBytes, this->size);
	memcpy(this->oldBytes, (void*)address, this->size);
	bStatus = false;
}

Hack::Hack(uintptr_t address, uint8_t size)
{
	this->name = NULL;
	this->address = address;
	this->size = size;
	memset(this->newBytes, 0x90, size);
	memcpy(this->oldBytes, (void*)address, this->size);
	bStatus = false;
}

Hack::~Hack()
{
	this->Disable();
}

void Hack::Enable()
{
	mem::Patch((uintptr_t*)address, (uintptr_t*)newBytes, size);
	bStatus = true;
}

void Hack::Disable()
{
	mem::Patch((uintptr_t*)address, (uintptr_t*)oldBytes, size);
	bStatus = false;
}

void Hack::Toggle()
{
	bStatus = !bStatus;
	if (bStatus)
	{
		Enable();
	}
	else Disable();
}