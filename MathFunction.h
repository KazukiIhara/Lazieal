#pragma once
// Include
#include <cmath>
#include <numbers>

// MyHedder
#include "MathOperator.h"

///
/// Vector2
/// 



///
/// Vector3
/// 

float Length(Vector3 a);

Vector3 Normalize(Vector3 a);

Vector3 ExtractionWorldPos(const Matrix4x4& m);

///
/// Vector4
/// 


///
/// Matrix4x4
/// 

// 単位行列作成関数
Matrix4x4 MakeIdentityMatrix4x4();

// 逆行列作成関数
Matrix4x4 Inverse(const Matrix4x4& a);

// 転置行列
Matrix4x4 Transpose(const Matrix4x4& a);

// 逆転置行列
Matrix4x4 MakeInverseTransposeMatrix(const Matrix4x4& a);

// 拡縮行列作成関数
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

// 回転行列作成関数
Matrix4x4 MakeRotateXMatrix(float radian); // X回転
Matrix4x4 MakeRotateYMatrix(float radian); // Y回転
Matrix4x4 MakeRotateZMatrix(float radian); // Z回転
Matrix4x4 MakeRotateXYZMatrixRad(const Vector3& rotate); // XYZ回転*pi
Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate); // XYZ回転

// 平行移動行列作成関数
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

// アフィン変換関数
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRaito, float nearClip, float farClip);

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

void DecomposeUVMatrix(const Matrix4x4& matrix, Vector3& scale, float& rotateZ, Vector3& translate);

Matrix4x4 ComposeUVMatrix(const Vector3& scale, float rotateZ, const Vector3& translate);
