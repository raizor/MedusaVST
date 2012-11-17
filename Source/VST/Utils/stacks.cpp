#include "stacks.h"
#include "GLImage.h"

// object stack

objectStack::objectStack(int size)
{
	max = size;
	items = new void*[max];	
	count = 0;
}

void objectStack::push(void* i)
{
	items[count++] = i;
}

void objectStack::pop()
{
	count--;
}

objectStack::~objectStack(void)
{
	delete(items);
}

// image stack

imageStack::imageStack(int size) : objectStack(size)
{

}

GLImage* imageStack::GetItem(int index)
{
	void* obj = items[index];
	return (GLImage*)obj;
}




