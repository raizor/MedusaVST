#pragma once

#include "types.h"

class GContextMenu
{
public:
	GContextMenu();
	~GContextMenu();

	int SelectAt(const GPoint& pos);
	void AddItem(const char* item);

private:
	std::vector<char *> items;
};

class GContextMenuEx
{
public:
	GContextMenuEx();
	~GContextMenuEx();

	int SelectAt(const GPoint& pos);
	void AddItem(int commandID, const char* item);
	void AddMenu(GContextMenuEx* menu, const char* name);

	HMENU hPopupMenu;

	int itemCount;
};