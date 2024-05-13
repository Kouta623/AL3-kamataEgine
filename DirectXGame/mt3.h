#include<math.h>
#include<assert.h>
//#include <Novice.h>
#include <stdio.h>
#include <Vector3.h>
#include <Vector4.h>



static const int kRowHeight = 20;
static const int kColumnWidth = 60;



//
//struct Vector3 {
//	float x, y, z;
//};
//
//struct Matrix3x3
//{
//	float m[3][3];
//};
//
//struct Matrix4x4
//{
//	float m[4][4];
//};

//void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
//	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
//	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
//	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
//	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
//
//}
//
//void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
//	for (int row = 0; row < 4; ++row) {
//		for (int column = 0; column < 4; ++column) {
//			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column], label);
//		}
//	}
//}



//加算
Vector3 Add(const Vector3& v1, Vector3& v2) {
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);

}

//減算
Vector3 Subtract(const Vector3& v1, Vector3& v2) {
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

//スカラー倍
Vector3 Multiply(float scalar, Vector3& v) {

	Vector3 result;
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;

}

//内積
float Dot(const Vector3& v1, const Vector3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

//長さ
float Length(const Vector3& v) {
	return sqrtf(Dot(v, v));
}


//正規化
Vector3 Normalize(const Vector3& v) {

	Vector3 result;
	result.x = v.x / Length(v);
	result.y = v.y / Length(v);
	result.z = v.z / Length(v);
	return result;


}


//行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return result;
}

//行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return result;
}

//行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0.0f;
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return result;
}

// 逆行列
Matrix4x4 Invers(const Matrix4x4& m)
{
	Matrix4x4 result{};
	float determinant = m.m[0][0] * (m.m[1][1] * m.m[2][2] * m.m[3][3] +
		m.m[2][1] * m.m[3][2] * m.m[1][3] +
		m.m[3][1] * m.m[1][2] * m.m[2][3] -
		m.m[3][1] * m.m[2][2] * m.m[1][3] -
		m.m[2][1] * m.m[1][2] * m.m[3][3] -
		m.m[1][1] * m.m[3][2] * m.m[2][3]) -
		m.m[0][1] * (m.m[1][0] * m.m[2][2] * m.m[3][3] +
			m.m[2][0] * m.m[3][2] * m.m[1][3] +
			m.m[3][0] * m.m[1][2] * m.m[2][3] -
			m.m[3][0] * m.m[2][2] * m.m[1][3] -
			m.m[2][0] * m.m[1][2] * m.m[3][3] -
			m.m[1][0] * m.m[3][2] * m.m[2][3]) +
		m.m[0][2] * (m.m[1][0] * m.m[2][1] * m.m[3][3] +
			m.m[2][0] * m.m[3][1] * m.m[1][3] +
			m.m[3][0] * m.m[1][1] * m.m[2][3] -
			m.m[3][0] * m.m[2][1] * m.m[1][3] -
			m.m[2][0] * m.m[1][1] * m.m[3][3] -
			m.m[1][0] * m.m[3][1] * m.m[2][3]) -
		m.m[0][3] * (m.m[1][0] * m.m[2][1] * m.m[3][2] +
			m.m[2][0] * m.m[3][1] * m.m[1][2] +
			m.m[3][0] * m.m[1][1] * m.m[2][2] -
			m.m[3][0] * m.m[2][1] * m.m[1][2] -
			m.m[2][0] * m.m[1][1] * m.m[3][2] -
			m.m[1][0] * m.m[3][1] * m.m[2][2]);



	if (determinant != 0) {
		result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] +
			m.m[2][1] * m.m[3][2] * m.m[1][3] +
			m.m[3][1] * m.m[1][2] * m.m[2][3] -
			m.m[3][1] * m.m[2][2] * m.m[1][3] -
			m.m[2][1] * m.m[1][2] * m.m[3][3] -
			m.m[1][1] * m.m[3][2] * m.m[2][3]) /
			determinant;

		result.m[0][1] = -(m.m[0][1] * m.m[2][2] * m.m[3][3] +
			m.m[2][1] * m.m[3][2] * m.m[0][3] +
			m.m[3][1] * m.m[0][2] * m.m[2][3] -
			m.m[3][1] * m.m[2][2] * m.m[0][3] -
			m.m[2][1] * m.m[0][2] * m.m[3][3] -
			m.m[0][1] * m.m[3][2] * m.m[2][3]) /
			determinant;

		result.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] +
			m.m[1][1] * m.m[3][2] * m.m[0][3] +
			m.m[3][1] * m.m[0][2] * m.m[1][3] -
			m.m[3][1] * m.m[1][2] * m.m[0][3] -
			m.m[1][1] * m.m[0][2] * m.m[3][3] -
			m.m[0][1] * m.m[3][2] * m.m[1][3]) /
			determinant;

		result.m[0][3] = -(m.m[0][1] * m.m[1][2] * m.m[2][3] +
			m.m[1][1] * m.m[2][2] * m.m[0][3] +
			m.m[2][1] * m.m[0][2] * m.m[1][3] -
			m.m[2][1] * m.m[1][2] * m.m[0][3] -
			m.m[1][1] * m.m[0][2] * m.m[2][3] -
			m.m[0][1] * m.m[2][2] * m.m[1][3]) /
			determinant;


		result.m[1][0] = -(m.m[1][0] * m.m[2][2] * m.m[3][3] +
			m.m[2][0] * m.m[3][2] * m.m[1][3] +
			m.m[3][0] * m.m[1][2] * m.m[2][3] -
			m.m[3][0] * m.m[2][2] * m.m[1][3] -
			m.m[2][0] * m.m[1][2] * m.m[3][3] -
			m.m[1][0] * m.m[3][2] * m.m[2][3]) /
			determinant;

		result.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] +
			m.m[2][0] * m.m[3][2] * m.m[0][3] +
			m.m[3][0] * m.m[0][2] * m.m[2][3] -
			m.m[3][0] * m.m[2][2] * m.m[0][3] -
			m.m[2][0] * m.m[0][2] * m.m[3][3] -
			m.m[0][0] * m.m[3][2] * m.m[2][3]) /
			determinant;

		result.m[1][2] = -(m.m[0][0] * m.m[1][2] * m.m[3][3] +
			m.m[1][0] * m.m[3][2] * m.m[0][3] +
			m.m[3][0] * m.m[0][2] * m.m[1][3] -
			m.m[3][0] * m.m[1][2] * m.m[0][3] -
			m.m[1][0] * m.m[0][2] * m.m[3][3] -
			m.m[0][0] * m.m[3][2] * m.m[1][3]) /
			determinant;

		result.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] +
			m.m[1][0] * m.m[2][2] * m.m[0][3] +
			m.m[2][0] * m.m[0][2] * m.m[1][3] -
			m.m[2][0] * m.m[1][2] * m.m[0][3] -
			m.m[1][0] * m.m[0][2] * m.m[2][3] -
			m.m[0][0] * m.m[2][2] * m.m[1][3]) /
			determinant;


		result.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] +
			m.m[2][0] * m.m[3][1] * m.m[1][3] +
			m.m[3][0] * m.m[1][1] * m.m[2][3] -
			m.m[3][0] * m.m[2][1] * m.m[1][3] -
			m.m[2][0] * m.m[1][1] * m.m[3][3] -
			m.m[1][0] * m.m[3][1] * m.m[2][3]) /
			determinant;

		result.m[2][1] = -(m.m[0][0] * m.m[2][1] * m.m[3][3] +
			m.m[2][0] * m.m[3][1] * m.m[0][3] +
			m.m[3][0] * m.m[0][1] * m.m[2][3] -
			m.m[3][0] * m.m[2][1] * m.m[0][3] -
			m.m[2][0] * m.m[0][1] * m.m[3][3] -
			m.m[0][0] * m.m[3][1] * m.m[2][3]) /
			determinant;

		result.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] +
			m.m[1][0] * m.m[3][1] * m.m[0][3] +
			m.m[3][0] * m.m[0][1] * m.m[1][3] -
			m.m[3][0] * m.m[1][1] * m.m[0][3] -
			m.m[1][0] * m.m[0][1] * m.m[3][3] -
			m.m[0][0] * m.m[3][1] * m.m[1][3]) /
			determinant;

		result.m[2][3] = -(m.m[0][0] * m.m[1][1] * m.m[2][3] +
			m.m[1][0] * m.m[2][1] * m.m[0][3] +
			m.m[2][0] * m.m[0][1] * m.m[1][3] -
			m.m[2][0] * m.m[1][1] * m.m[0][3] -
			m.m[1][0] * m.m[0][1] * m.m[2][3] -
			m.m[0][0] * m.m[2][1] * m.m[1][3]) /
			determinant;

		result.m[3][0] = -(m.m[1][0] * m.m[2][1] * m.m[3][2] +
			m.m[2][0] * m.m[3][1] * m.m[1][2] +
			m.m[3][0] * m.m[1][1] * m.m[2][2] -
			m.m[3][0] * m.m[2][1] * m.m[1][2] -
			m.m[2][0] * m.m[1][1] * m.m[3][2] -
			m.m[1][0] * m.m[3][1] * m.m[2][2]) /
			determinant;

		result.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2] +
			m.m[2][0] * m.m[3][1] * m.m[0][2] +
			m.m[3][0] * m.m[0][1] * m.m[2][2] -
			m.m[3][0] * m.m[2][1] * m.m[0][2] -
			m.m[2][0] * m.m[0][1] * m.m[3][2] -
			m.m[0][0] * m.m[3][1] * m.m[2][2]) /
			determinant;

		result.m[3][2] = -(m.m[0][0] * m.m[1][1] * m.m[3][2] +
			m.m[1][0] * m.m[3][1] * m.m[0][2] +
			m.m[3][0] * m.m[0][1] * m.m[1][2] -
			m.m[3][0] * m.m[1][1] * m.m[0][2] -
			m.m[1][0] * m.m[0][1] * m.m[3][2] -
			m.m[0][0] * m.m[3][1] * m.m[1][2]) /
			determinant;

		result.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] +
			m.m[1][0] * m.m[2][1] * m.m[0][2] +
			m.m[2][0] * m.m[0][1] * m.m[1][2] -
			m.m[2][0] * m.m[1][1] * m.m[0][2] -
			m.m[1][0] * m.m[0][1] * m.m[2][2] -
			m.m[0][0] * m.m[2][1] * m.m[1][2]) /
			determinant;
	}

	return result;
}


//転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {

	Matrix4x4 result = {};

	result.m[0][0] = m.m[0][0];
	result.m[0][1] = m.m[1][0];
	result.m[0][2] = m.m[2][0];
	result.m[0][3] = m.m[3][0];

	result.m[1][0] = m.m[0][1];
	result.m[1][1] = m.m[1][1];
	result.m[1][2] = m.m[2][1];
	result.m[1][3] = m.m[3][1];

	result.m[2][0] = m.m[0][2];
	result.m[2][1] = m.m[1][2];
	result.m[2][2] = m.m[2][2];
	result.m[2][3] = m.m[3][2];

	result.m[3][0] = m.m[0][3];
	result.m[3][1] = m.m[1][3];
	result.m[3][2] = m.m[2][3];
	result.m[3][3] = m.m[3][3];

	return result;
}

//単位行列
Matrix4x4 MakeIdentity4x4() {

	Matrix4x4 result = {};

	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;

}

//平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {

	Matrix4x4 result = {};
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][2] = translate.z;
	result.m[3][1] = translate.y;
	result.m[3][0] = translate.x;
	result.m[3][3] = 1.0f;

	return Matrix4x4(result);
}

//拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result={};
	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

		return Matrix4x4(result);
}


//回転行列
Matrix4x4 RotationX(float rotate) {
	float cosA = cosf(rotate);
	float sinA = sinf(rotate);

	Matrix4x4 result={};
	result.m[0][0] = 1;
	result.m[1][1] = cosA;
	result.m[1][2] = sinA;
	result.m[2][1] = -sinA;
	result.m[2][2] = cosA;
	result.m[3][3] = 1;


	return Matrix4x4(result);
}


Matrix4x4 RotationY(float rotate) {
	float cosA = cosf(rotate);
	float sinA = sinf(rotate);

	Matrix4x4 result={};
	result.m[0][0] = cosA;
	result.m[0][2] = -sinA;
	result.m[1][1] = 1;
	result.m[2][0] = sinA;
	result.m[2][2] = cosA;
	result.m[3][3] = 1;


	return Matrix4x4(result);
}

Matrix4x4 RotationZ(float rotate) {
	float cosA = cosf(rotate);
	float sinA = sinf(rotate);

	Matrix4x4 result={};
	result.m[0][0] = cosA;
	result.m[0][1] = sinA;
	result.m[1][0] = -sinA;
	result.m[1][1] = cosA;
	result.m[2][2] = 1;
	result.m[3][3] = 1;
	
	return Matrix4x4(result);
}

//座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result={};

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

//アフィン変換
Matrix4x4 MakeAffineMatrix(const Vector3& translate, const Vector3& rotate, const Vector3& scale) {
	
	Matrix4x4 makeRotateXMatrix = RotationX(rotate.x);
	Matrix4x4 makeRotateYMatrix = RotationY(rotate.y);
	Matrix4x4 makeRotateZMatrix = RotationZ(rotate.z);

	Matrix4x4 makeRotate = Multiply(makeRotateXMatrix, Multiply(makeRotateYMatrix, makeRotateZMatrix));

	Matrix4x4 matScale = MakeScaleMatrix(scale);
	Matrix4x4 matTranslate = MakeTranslateMatrix(translate);

	return Matrix4x4(Multiply((Multiply(matScale, makeRotate)),matTranslate));
}