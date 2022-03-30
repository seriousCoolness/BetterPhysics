#include "stdafx.h"
#include "HelperFuncs.h"

void ReplaceCAM(std::string src, const HelperFunctions& helperFunctions)
{
	std::string fulldest;
	std::string fullsrc;
	fulldest = "system\\" + src + "_MOD.BIN";
	fullsrc = "system\\" + src + ".BIN";
	helperFunctions.ReplaceFile(fullsrc.c_str(), fulldest.c_str());
	//PrintDebug("Replace CAM file %s with file %s\n", fullsrc.c_str(), fulldest.c_str());
}
void ReplaceSET(std::string src, const HelperFunctions& helperFunctions)
{
	std::string fulldest;
	std::string fullsrc;
	fulldest = "system\\" + src + "_MOD.BIN";
	fullsrc = "system\\" + src + ".BIN";
	helperFunctions.ReplaceFile(fullsrc.c_str(), fulldest.c_str());
	//PrintDebug("Replace CAM file %s with file %s\n", fullsrc.c_str(), fulldest.c_str());
}
int sgn(float val) {
	return (0 < val) - (val < 0);
}

void LookAt(NJS_VECTOR* from, NJS_VECTOR* to, Angle* outx, Angle* outy) {
	NJS_VECTOR unit = *to;

	njSubVector(&unit, from);

	if (outy) {
		*outy = static_cast<Angle>(atan2f(unit.x, unit.z) * 65536.0f * 0.1591549762031479f);
	}

	if (outx) {
		if (from->y == to->y) {
			*outx = 0;
		}
		else {
			Float len = 1.0f / squareroot(unit.z * unit.z + unit.x * unit.x + unit.y * unit.y);

			*outx = static_cast<Angle>((acos(len * 3.3499999f) * 65536.0f * 0.1591549762031479f)
				- (acos(-(len * unit.y)) * 65536.0f * 0.1591549762031479f));
		}
	}
}

void PlayerLookAt(NJS_VECTOR* from, NJS_VECTOR* to, Angle* outx, Angle* outy) {
	LookAt(from, to, outx, outy);

	if (outy) {
		*outy = -(*outy) + 0x4000;
	}
}

void DotProduct(NJS_VECTOR* v1, NJS_VECTOR* v2, NJS_VECTOR* vOut) {
	vOut->x = v1->x * v2->x;
	if (fabsf(v1->x) == 0 || fabsf(v2->x) == 0)
		vOut->x = 0;
	vOut->y = v1->y * v2->y;
	if (fabsf(v1->y) == 0 || fabsf(v2->y) == 0)
		vOut->y = 0;
	vOut->z = v1->z * v2->z;
	if (fabsf(v1->z) == 0 || fabsf(v2->z) == 0)
		vOut->z = 0;
}

void RotateVectorY(NJS_VECTOR* vector, Angle angle) 
{
	float length = sqrtf((vector->x * vector->x) + (vector->z * vector->z));
	float angle_radians = angle * ((2.0f * 3.141592f) / 65536.0f);

	vector->x = length * (cos(angle_radians) * (65536.0f / (2.0f * 3.141592f)));
	vector->z = length * (sin(angle_radians) * (65536.0f / (2.0f * 3.141592f)));

}

std::string toBinary(int n)
{
	std::string r;
	while (n != 0) { r = (n % 2 == 0 ? "0" : "1") + r; n /= 2; }
	return r;
}