#include "../includes.h"
#include "gevent.h"

const char* EMPTY_KEY = "";

GEvent::GEvent()
{
	isHandled = false;

	key[0] = '\0';
	key[1] = '\0';

	wParam = 0;
}

bool GEvent::HasModifier(int modifier)
{
	return (modifiers & modifier)!=0;
}
