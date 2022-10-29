#include "pch.h"
#include "Geom.h"

float GetDistanceVec3(vec src, vec dst) {
	return
		(sqrtf(
			((src.x - dst.x) * (src.x - dst.x)) +
			((src.y - dst.y) * (src.y - dst.y)) +
			((src.z - dst.z) * (src.z - dst.z))
		));
}

vec CalcAngle(vec src, vec dst) {
	vec angle;
	angle.x = -atan2f(dst.x - src.x, dst.y - src.y) / PI * 180.0f + 180.0f;
	angle.y = asinf((dst.z - src.z) / GetDistanceVec3(src, dst)) * (180.0f / PI);
	angle.z = 0.0f;

	return angle;
}