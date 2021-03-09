// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <cstdio>
#include <vector>
#include <algorithm>
#include <stdlib.h>

// TODO: reference additional headers your program requires here

#include "SADXModLoader.h"
#include "IniFile.hpp"
#include "LandTableInfo.h"
#include "ReplaceFuncs.h"
#include "Trampoline.h"
#include "levels.h"
#include <fstream>
#include <iostream>