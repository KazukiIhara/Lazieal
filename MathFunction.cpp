// Include

// MyHedder
#include "MathFunction.h"

float Length(Vector3 a) {
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

Vector3 Normalize(Vector3 a) {
	float length = Length(a);
	Vector3 normalizedVector;

	if (length != 0) {
		normalizedVector.x = a.x / length;
		normalizedVector.y = a.y / length;
		normalizedVector.z = a.z / length;
	} else {
		normalizedVector.x = 0;
		normalizedVector.y = 0;
		normalizedVector.z = 0;
	}

	return normalizedVector;
}

Vector3 ExtractionWorldPos(const Matrix4x4& m) {
	Vector3 worldPos{};
	/*ワールド座標の平行移動成分を取得*/
	worldPos.x = m.m[3][0];
	worldPos.y = m.m[3][1];
	worldPos.z = m.m[3][2];
	return worldPos;
}

Matrix4x4 MakeIdentityMatrix4x4() {
	Matrix4x4 result{};
	result.m[0][0] = 1.0f; result.m[0][1] = 0.0f; result.m[0][2] = 0.0f; result.m[0][3] = 0.0f;
	result.m[1][0] = 0.0f; result.m[1][1] = 1.0f; result.m[1][2] = 0.0f; result.m[1][3] = 0.0f;
	result.m[2][0] = 0.0f; result.m[2][1] = 0.0f; result.m[2][2] = 1.0f; result.m[2][3] = 0.0f;
	result.m[3][0] = 0.0f; result.m[3][1] = 0.0f; result.m[3][2] = 0.0f; result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 Inverse(const Matrix4x4& a) {
	Matrix4x4 A = a;
	Matrix4x4 B = MakeIdentityMatrix4x4();

	int i, j, k;
	for (i = 0; i < 4; ++i) {
		float scale = 1.0f / A.m[i][i];
		for (j = 0; j < 4; ++j) {
			A.m[i][j] *= scale;
			B.m[i][j] *= scale;
		}
		for (k = 0; k < 4; ++k) {
			if (k != i) {
				float factor = A.m[k][i];
				for (j = 0; j < 4; ++j) {
					A.m[k][j] -= factor * A.m[i][j];
					B.m[k][j] -= factor * B.m[i][j];
				}
			}
		}
	}

	return B;
}

Matrix4x4 Transpose(const Matrix4x4& a) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = a.m[j][i];
		}
	}
	return result;
}

Matrix4x4 MakeInverseTransposeMatrix(const Matrix4x4& a) {
	Matrix4x4 result = Inverse(a);
	result = Transpose(result);
	return result;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result = {
		 scale.x, 0.0f, 0.0f, 0.0f,
		 0.0f,scale.y,0.0f, 0.0f,
		 0.0f, 0.0f, scale.z, 0.0f,
		 0.0f, 0.0f, 0.0f, 1.0f,
	};
	return result;
}

Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 rotateX{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, std::cos(radian), std::sin(radian), 0.0f,
		0.0f, -std::sin(radian), std::cos(radian), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};
	return rotateX;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 rotateY{
		std::cos(radian), 0.0f, -std::sin(radian), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		std::sin(radian), 0.0f, std::cos(radian), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};
	return rotateY;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 rotateZ{
		std::cos(radian), std::sin(radian), 0.0f, 0.0f,
		-std::sin(radian), std::cos(radian), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};
	return rotateZ;
}

Matrix4x4 MakeRotateXYZMatrixRad(const Vector3& rotate) {
	Matrix4x4 rotateX = MakeRotateXMatrix(rotate.x * std::numbers::pi_v<float>);
	Matrix4x4 rotateY = MakeRotateYMatrix(rotate.y * std::numbers::pi_v<float>);
	Matrix4x4 rotateZ = MakeRotateZMatrix(rotate.z * std::numbers::pi_v<float>);

	Matrix4x4 result = rotateX * rotateY * rotateZ;
	return result;
}

Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate) {
	Matrix4x4 rotateX = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateY = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZ = MakeRotateZMatrix(rotate.z);

	Matrix4x4 result = rotateX * rotateY * rotateZ;
	return result;
}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		translate.x, translate.y, translate.z, 1.0f
	};
	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result = MakeScaleMatrix(scale) * MakeRotateXYZMatrixRad(rotate) * MakeTranslateMatrix(translate);
	return result;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRaito, float nearClip, float farClip) {
	Matrix4x4 result =
	{
		(1.0f / aspectRaito) * (1.0f / std::tan(fovY / 2.0f)),0.0f,0.0f,0.0f,
		0.0f, 1.0f / std::tan(fovY / 2.0f), 0.0f, 0.0f,
		0.0f, 0.0f, farClip / (farClip - nearClip),1.0f,
		0.0f, 0.0f, (-nearClip * farClip) / (farClip - nearClip),0.0f,
	};
	return result;
}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result =
	{
		2.0f / (right - left), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f / (farClip - nearClip), 0.0f,
		(left + right) / (left - right),(top + bottom) / (bottom - top), nearClip / (nearClip - farClip),1.0f,
	};
	return result;
}

Matrix4x4 MakeUVMatrix(const Vector2& scale, const float& rotateZ, const Vector2& translate) {
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotateZ);
	Matrix4x4 scaleMatrix = MakeScaleMatrix(Vector3(scale.x, scale.y, 1.0f));
	Matrix4x4 translateMatrix = MakeTranslateMatrix(Vector3(translate.x, translate.y, 0.0f));
	return scaleMatrix * rotateZMatrix * translateMatrix;
}

void DecomposeUVMatrix(const Matrix4x4& matrix, Vector3& scale, float& rotateZ, Vector2& translate) {
	// Extract translation
	translate.x = matrix.m[3][0];
	translate.y = matrix.m[3][1];

	// Extract rotation
	rotateZ = std::atan2(matrix.m[1][0], matrix.m[0][0]);

	// Extract scale
	scale.x = matrix.m[0][0] / std::cos(rotateZ);
	scale.y = matrix.m[1][1] / std::cos(rotateZ);
	scale.z = 1.0f; // UV matrix is 2D, so z-scale is assumed to be 1.0
}

Matrix4x4 ComposeUVMatrix(const Vector3& scale, float rotateZ, const Vector2& translate) {
	Matrix4x4 matrix;

	float cosZ = std::cos(rotateZ);
	float sinZ = std::sin(rotateZ);

	// Apply scale and rotation
	matrix.m[0][0] = scale.x * cosZ;
	matrix.m[0][1] = scale.x * -sinZ;
	matrix.m[1][0] = scale.y * sinZ;
	matrix.m[1][1] = scale.y * cosZ;

	// Apply translation
	matrix.m[3][0] = translate.x;
	matrix.m[3][1] = translate.y;

	// Set other elements to identity matrix values
	matrix.m[0][2] = matrix.m[0][3] = 0.0f;
	matrix.m[1][2] = matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = matrix.m[2][1] = matrix.m[2][2] = matrix.m[2][3] = 0.0f;
	matrix.m[3][2] = 0.0f;
	matrix.m[3][3] = 1.0f;

	return matrix;
}
