#pragma once
#include"Vector3.h"
struct  aabb {
	Vector3 min;
	Vector3 max;
};

bool IsCollision(const aabb& a, const aabb& b);