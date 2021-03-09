#include "stdafx.h"
#include "ReplaceFuncs.h"

void ReplaceCAM(std::string src, const HelperFunctions& helperFunctions)
{
	std::string fulldest;
	std::string fullsrc;
	fulldest = "system\\" + src + "_MOD.BIN";
	fullsrc = "system\\" + src + ".BIN";
	helperFunctions.ReplaceFile(fullsrc.c_str(), fulldest.c_str());
	//PrintDebug("Replace CAM file %s with file %s\n", fullsrc.c_str(), fulldest.c_str());
}