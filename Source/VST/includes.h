#pragma once

#define ENABLE_CONSOLE

#include <windows.h>
#include <cstdio>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Utils/glext.h"
#include "Utils/GLImage.h"
#include "Utils/GlHelpers.h"
#include "Utils/stacks.h"
#include "Utils/types.h"
#include "Utils/gevent.h"
#include "resources/resource.h"
#include "Synth.h"

#define DebugPrint(txt) printf("SYNTH: %s", txt);
#define DebugPrintLine(txt) printf("SYNTH: %s\n", txt);