#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;

	Vector3& operator+=(Vector3 num) {

		x += num.x;
		y += num.y;
		z += num.z;

		return *this;
	}

};
