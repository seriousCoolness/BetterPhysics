#include "stdafx.h"
#include "levels.h"

HelperFunctions HelperFunctionsGlobal;

void Delete_Splines(bool LevelTweaks[11]) 
{

	if (LevelTweaks[0] && GetLevelAndAct() >= (256*1) && GetLevelAndAct() <= (256*1)+2)
	{
		WriteData<1>((char*)0x4BB1F0, 0xC3);

			
	}
	
	if (LevelTweaks[1] && GetLevelAndAct() >= (256*2) && GetLevelAndAct() <= (256 * 2) + 2)
	{
		WriteData<1>((char*)0x4BB1F0, 0xC3);
		
	}

	if (LevelTweaks[2] && GetLevelAndAct() >= (256 * 3) && GetLevelAndAct() <= (256 * 3) + 2)
	{
		WriteData<1>((char*)0x4BB1F0, 0xC3);
		
	}
	
	if (LevelTweaks[3] && GetLevelAndAct() >= (256 * 4) && GetLevelAndAct() <= (256 * 4) + 2)
	{
		
		WriteData<1>((char*)0x4BB1F0, 0xC3);
		
	}

	if (LevelTweaks[4] && GetLevelAndAct() >= (256 * 5) && GetLevelAndAct() <= (256 * 5) + 2)
	{
		WriteData<1>((char*)0x4BB1F0, 0xC3);
		
	}
	
	if (LevelTweaks[5] && GetLevelAndAct() >= (256 * 6) && GetLevelAndAct() <= (256 * 6) + 2)
	{
		WriteData<1>((char*)0x4BB1F0, 0xC3);
		
	}

	if (LevelTweaks[6] && GetLevelAndAct() >= (256 * 7) && GetLevelAndAct() <= (256 * 7) + 2)
	{
		WriteData<1>((char*)0x4BB1F0, 0xC3);
		
	}
	
	if (LevelTweaks[7] && GetLevelAndAct() >= (256 * 8) && GetLevelAndAct() <= (256 * 8) + 2)
	{
		WriteData<1>((char*)0x4BB1F0, 0xC3);
		
	}
	
	if (LevelTweaks[8] && GetLevelAndAct() >= (256 * 9) && GetLevelAndAct() <= (256 * 9) + 2)
	{
		WriteData<1>((char*)0x4BB1F0, 0xC3);
		
	}
	
	if (LevelTweaks[9] && GetLevelAndAct() >= (256 * 10) && GetLevelAndAct() <= (256 * 10) + 2)
	{
		WriteData<1>((char*)0x4BB1F0, 0xC3);
		
	}
	if (LevelTweaks[10] && GetLevelAndAct() >= (256 * 11) && GetLevelAndAct() <= (256 * 11) + 2)
	{
		WriteData<1>((char*)0x4BB1F0, 0xC3);

	}
}

void Delete_Panels(bool LevelTweaks[11])
{

	if (LevelTweaks[0] && GetLevelAndAct() >= (256 * 1) && GetLevelAndAct() <= (256 * 1) + 2)
	{
		

		// Disable all dash panels
		WriteData((char*)0x007A4450, 0xC3i8);

	}

	if (LevelTweaks[1] && GetLevelAndAct() >= (256 * 2) && GetLevelAndAct() <= (256 * 2) + 2)
	{
		

		// Disable all dash panels
		WriteData((char*)0x007A4450, 0xC3i8);
	}

	if (LevelTweaks[2] && GetLevelAndAct() >= (256 * 3) && GetLevelAndAct() <= (256 * 3) + 2)
	{
		

		// Disable all dash panels
		WriteData((char*)0x007A4450, 0xC3i8);
	}

	if (LevelTweaks[3] && GetLevelAndAct() >= (256 * 4) && GetLevelAndAct() <= (256 * 4) + 2)
	{

		

		// Disable all dash panels
		WriteData((char*)0x007A4450, 0xC3i8);
	}

	if (LevelTweaks[4] && GetLevelAndAct() >= (256 * 5) && GetLevelAndAct() <= (256 * 5) + 2)
	{
		

		// Disable all dash panels
		WriteData((char*)0x007A4450, 0xC3i8);
	}

	if (LevelTweaks[5] && GetLevelAndAct() >= (256 * 6) && GetLevelAndAct() <= (256 * 6) + 2)
	{
		

		// Disable all dash panels
		WriteData((char*)0x007A4450, 0xC3i8);
	}

	if (LevelTweaks[6] && GetLevelAndAct() >= (256 * 7) && GetLevelAndAct() <= (256 * 7) + 2)
	{
		

		// Disable all dash panels
		WriteData((char*)0x007A4450, 0xC3i8);
	}

	if (LevelTweaks[7] && GetLevelAndAct() >= (256 * 8) && GetLevelAndAct() <= (256 * 8) + 2)
	{
		

		// Disable all dash panels
		WriteData((char*)0x007A4450, 0xC3i8);
	}

	if (LevelTweaks[8] && GetLevelAndAct() >= (256 * 9) && GetLevelAndAct() <= (256 * 9) + 2)
	{
		

		// Disable all dash panels
		WriteData((char*)0x007A4450, 0xC3i8);
	}

	if (LevelTweaks[9] && GetLevelAndAct() >= (256 * 10) && GetLevelAndAct() <= (256 * 10) + 2)
	{
		

		// Disable all dash panels
		WriteData((char*)0x007A4450, 0xC3i8);
	}
	if (LevelTweaks[10] && GetLevelAndAct() >= (256 * 11) && GetLevelAndAct() <= (256 * 11) + 2)
	{
		

		// Disable all dash panels
		WriteData((char*)0x007A4450, 0xC3i8);
	}
}

void Init_Levels(bool LevelTweaks[11], const HelperFunctions& helperFunctions)
{
	if (LevelTweaks[0])
	{
		//Handle_LandTables("EC1", LevelIDs_EmeraldCoast, 1, helperFunctions);
		ReplaceSET("SET0100S", helperFunctions);
		ReplaceSET("SET0100A", helperFunctions);
		ReplaceSET("SET0100B", helperFunctions);
		ReplaceSET("SET0100E", helperFunctions);
		ReplaceSET("SET0100K", helperFunctions);
		ReplaceSET("SET0100M", helperFunctions);
		//Handle_LandTables("EC2", LevelIDs_EmeraldCoast, 2, helperFunctions);

		

	}

	if (LevelTweaks[1])
	{
		
		
	}

	if (LevelTweaks[2])
	{
		
		
	}

	if (LevelTweaks[3])
	{

		//Handle_LandTables("SH1", LevelIDs_SpeedHighway, 0, helperFunctions);

		
	}

	if (LevelTweaks[4])
	{
		
		
	}

	if (LevelTweaks[5])
	{
		
		
	}

	if (LevelTweaks[6])
	{
		
		
	}

	if (LevelTweaks[7])
	{
		
		
	}

	if (LevelTweaks[8])
	{
		
		
	}

	if (LevelTweaks[9])
	{
		
		
	}
	if (LevelTweaks[10])
	{
		
		
	}
}

void Init_Cameras(bool LevelTweaks[11], const HelperFunctions& helperFunctions)
{

	if (LevelTweaks[0])
	{
		ReplaceCAM("CAM0100E", helperFunctions);
		ReplaceCAM("CAM0100S", helperFunctions);
		ReplaceCAM("CAM0101S", helperFunctions);
	}

	if (LevelTweaks[1])
	{


	}

	if (LevelTweaks[2])
	{


	}

	if (LevelTweaks[3])
	{

		ReplaceCAM("CAM0400M", helperFunctions);
		ReplaceCAM("CAM0400S", helperFunctions);

	}

	if (LevelTweaks[4])
	{


	}

	if (LevelTweaks[5])
	{


	}

	if (LevelTweaks[6])
	{


	}

	if (LevelTweaks[7])
	{


	}

	if (LevelTweaks[8])
	{


	}

	if (LevelTweaks[9])
	{


	}
	if (LevelTweaks[10])
	{


	}

}

void Handle_LandTables(std::string fileName, int levelId, int act, const HelperFunctions& helperFunctions)
{
	std::string fullFile = "system\\" + fileName + ".sa1lvl";

	LandTableInfo* info = new LandTableInfo(helperFunctions.GetReplaceablePath(fullFile.c_str()));
	LandTable* land = info->getlandtable();

	if (land) {
		GeoLists[levelId * 8 + act] = land;
	}
}