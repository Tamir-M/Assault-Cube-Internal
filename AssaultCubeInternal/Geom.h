#pragma once
#define PI 3.14159265358979323846


struct vec { float x, y, z; };

float GetDistanceVec3(vec src, vec dst);

vec CalcAngle(vec src, vec dst);