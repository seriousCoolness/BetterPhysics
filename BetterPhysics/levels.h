#pragma once
#include "stdafx.h"

void Delete_Splines(bool LevelTweaks[], int LoopType);
void Delete_Panels(bool LevelTweaks[]);
void Init_Levels(bool LevelTweaks[], const HelperFunctions& helperFunctions);
void Init_Cameras(bool LevelTweaks[], const HelperFunctions& helperFunctions);
void Handle_LandTables(std::string fileName, int levelId, int act, const HelperFunctions& helperFunctions);
