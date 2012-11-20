#pragma once

class GuiImage;
class objectStack
{
public:
	int max;
	int count;	
	void** items;
	void objectStack::pop();
	void objectStack::push(void* index);
	
	objectStack(int size);
	~objectStack(void);

	void* GetItem(int index);
};

class imageStack : public objectStack
{
public:
	imageStack(int size);
	GuiImage* GetItem(int index);
};
