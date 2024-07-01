#include "AABB.h"

bool IsCollision(const aabb& a, const aabb& b) { 
	
	if ((a.min.x <= b.max.x && a.max.x >= b.min.x) && 
		(a.min.y <= b.max.y && a.max.y >= b.min.y )&& 
		(a.min.z <= b.max.z && a.max.z >= b.min.z)) {
		return true;
	}
	return false; 
}
