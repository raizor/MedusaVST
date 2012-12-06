#include "contextmenus.h"
#include "../GUI/Components/GuiMainWindow.h"

GContextMenu::GContextMenu()
{
}

GContextMenu::~GContextMenu()
{
}

int GContextMenu::SelectAt(const GPoint& pos)
{
	HMENU hPopupMenu = CreatePopupMenu();

	POINT screenPos = {(LONG)pos.x, (LONG)pos.y};
	ClientToScreen((HWND)GuiMainWindow::hWindow, &screenPos);

	for (unsigned int i=0; i<items.size(); i++)
	{
		InsertMenuA(hPopupMenu, i+1, MF_BYCOMMAND | MF_STRING, i+1, items[i]);
	}

	int result = TrackPopupMenu(hPopupMenu, TPM_RETURNCMD, screenPos.x, screenPos.y, 0, (HWND)GuiMainWindow::hWindow, NULL);

	DestroyMenu(hPopupMenu);

	return result - 1;
}

void GContextMenu::AddItem(const char* item)
{
	char *itemCopy=new char[strlen(item)+1];
	strcpy(itemCopy, item);

	items.push_back(itemCopy);
}

ItemParamWrapper::ItemParamWrapper(int cmdId)
{
	commandId = cmdId;
}

// ------------------------------------------

GContextMenuEx::GContextMenuEx()
{
	hPopupMenu = CreatePopupMenu();

	itemCount = 0;
}

GContextMenuEx::~GContextMenuEx()
{
	DestroyMenu(hPopupMenu);
}

int GContextMenuEx::SelectAt(const GPoint& pos)
{
	POINT screenPos = {(LONG)pos.x, (LONG)pos.y};
	ClientToScreen((HWND)GuiMainWindow::hWindow, &screenPos);

	int result = TrackPopupMenu(hPopupMenu, TPM_RETURNCMD, screenPos.x, screenPos.y, 0, (HWND)GuiMainWindow::hWindow, NULL);

	return result;
}

ItemParamWrapper* GContextMenuEx::AddItem(int commandID, const char* name, void* obj)
{
	int cmdId = commandID;
	if (obj)
		cmdId = (int)obj;
	
	// We don't create copies of strings here, since the Lua GC will (hopefully) not collect them because it blocks on menu tracking
	InsertMenuA(hPopupMenu, itemCount+1, MF_BYCOMMAND | MF_STRING, cmdId, name);
	ItemParamWrapper* w = new ItemParamWrapper(cmdId);
	w->item = obj;
	itemCount++;
	return w;
}

void GContextMenuEx::AddMenu(GContextMenuEx* menu, const char* name)
{
	// We don't create copies of strings here, since the Lua GC will (hopefully) not collect them because it blocks on menu tracking
	InsertMenuA(hPopupMenu, itemCount+1, MF_BYCOMMAND | MF_POPUP, (UINT_PTR)menu->hPopupMenu, name);

	itemCount++;
}

