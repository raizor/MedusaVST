#pragma once
#include "../../includes.h"

class GLImageManager
{
public:
	GLImageManager(void);
	~GLImageManager(void);
	GLImage* GetImageById(int id);
	static GLImageManager* instance;
	static void InitInstance();
private:
	imageStack* glImages;
};

