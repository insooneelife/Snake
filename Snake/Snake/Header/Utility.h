#pragma once

#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include "Data.h"
#include "SDL.h"

class Utility
{
public:
	static void gotoxy(int x, int y)
	{
		COORD posXY = { x,y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posXY);
	}

	static void printStringOnPos(std::string part, Pos pos)
	{
		gotoxy(pos.x * 2, pos.y);
		std::cout << part;
	}



	/* Call this instead of exit(), so we can clean up SDL: atexit() is evil. */
	static void quit(int rc)
	{
		SDL_Quit();
		exit(rc);
	}

	static void print_string(char **text, size_t *maxlen, const char *fmt, ...)
	{
		int len;
		va_list ap;

		va_start(ap, fmt);
		len = SDL_vsnprintf(*text, *maxlen, fmt, ap);
		if (len > 0) {
			*text += len;
			if (((size_t)len) < *maxlen) {
				*maxlen -= (size_t)len;
			}
			else {
				*maxlen = 0;
			}
		}
		va_end(ap);
	}

	static void
		print_modifiers(char **text, size_t *maxlen)
	{
		int mod;
		print_string(text, maxlen, " modifiers:");
		mod = SDL_GetModState();
		if (!mod) {
			print_string(text, maxlen, " (none)");
			return;
		}
		if (mod & KMOD_LSHIFT)
			print_string(text, maxlen, " LSHIFT");
		if (mod & KMOD_RSHIFT)
			print_string(text, maxlen, " RSHIFT");
		if (mod & KMOD_LCTRL)
			print_string(text, maxlen, " LCTRL");
		if (mod & KMOD_RCTRL)
			print_string(text, maxlen, " RCTRL");
		if (mod & KMOD_LALT)
			print_string(text, maxlen, " LALT");
		if (mod & KMOD_RALT)
			print_string(text, maxlen, " RALT");
		if (mod & KMOD_LGUI)
			print_string(text, maxlen, " LGUI");
		if (mod & KMOD_RGUI)
			print_string(text, maxlen, " RGUI");
		if (mod & KMOD_NUM)
			print_string(text, maxlen, " NUM");
		if (mod & KMOD_CAPS)
			print_string(text, maxlen, " CAPS");
		if (mod & KMOD_MODE)
			print_string(text, maxlen, " MODE");
	}

	static void
		PrintModifierState()
	{
		char message[512];
		char *spot;
		size_t left;

		spot = message;
		left = sizeof(message);

		print_modifiers(&spot, &left);
		SDL_Log("Initial state:%s\n", message);
	}

	static void PrintKey(SDL_Keysym * sym, SDL_bool pressed, SDL_bool repeat)
	{
		char message[512];
		char *spot;
		size_t left;

		spot = message;
		left = sizeof(message);

		/* Print the keycode, name and state */
		if (sym->sym)
		{
			print_string(&spot, &left,
				"Key %s:  scancode %d = %s, keycode 0x%08X = %s ",
				pressed ? "pressed " : "released",
				sym->scancode,
				SDL_GetScancodeName(sym->scancode),
				sym->sym, SDL_GetKeyName(sym->sym));
		}
		else
		{
			print_string(&spot, &left,
				"Unknown Key (scancode %d = %s) %s ",
				sym->scancode,
				SDL_GetScancodeName(sym->scancode),
				pressed ? "pressed " : "released");
		}
		print_modifiers(&spot, &left);
		if (repeat) 
		{
			print_string(&spot, &left, " (repeat)");
		}
		SDL_Log("%s\n", message);
	}

	static void PrintText(char *eventtype, char *text)
	{
		char *spot, expanded[1024];

		expanded[0] = '\0';
		for (spot = text; *spot; ++spot)
		{
			size_t length = SDL_strlen(expanded);
			SDL_snprintf(expanded + length, sizeof(expanded) - length, "\\x%.2x", (unsigned char)*spot);
		}
		SDL_Log("%s Text (%s): \"%s%s\"\n", eventtype, expanded, *text == '"' ? "\\" : "", text);
	}
};