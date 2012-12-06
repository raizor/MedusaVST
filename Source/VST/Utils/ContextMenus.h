#pragma once
#include "types.h"
#include "Synth.h"

class ItemParamWrapper
{
public:
	void* item;
	int commandId;
	ItemParamWrapper(int cmdId);
};

class GContextMenu
{
public:
	GContextMenu();
	~GContextMenu();

	int SelectAt(const GPoint& pos);
	void AddItem(const char* item);

private:
	std::vector<char*> items;
};

class GContextMenuEx
{
public:
	GContextMenuEx();
	~GContextMenuEx();
	HMENU hPopupMenu;
	int SelectAt(const GPoint& pos);
	ItemParamWrapper* AddItem(int commandID, const char* item, void* obj = 0);
	void AddMenu(GContextMenuEx* menu, const char* name);

	std::vector<ItemParamWrapper*> items;


	int itemCount;
};