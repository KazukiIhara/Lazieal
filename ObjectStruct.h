#pragma once
// Include

// MyHedder
#include "MathFunction.h"

///
/// Common
/// 

// UVTransform
struct sUVTransform {
	Vector3 scale;
	float rotateZ;
	Vector3 translate;
};


///
/// 3D
/// 

// 3DTrasform
struct sTransform3D {
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

// 3D頂点データ用構造体
struct sVertexData3D {
	Vector4 position;
	Vector2 texcoord;
	Vector3 normal;
};

// 3D用マテリアル構造体
struct sMaterial3D {
	Vector4 color;
	int32_t enbleLighting;
	float padding[3];
	Matrix4x4 uvTransformMatrix;
	float shininess;
};

// トランスフォーメーション構造体
struct sTransformationMatrix {
	Matrix4x4 WVP;
	Matrix4x4 World;
	Matrix4x4 WorldInverseTransepose;
};


///
/// 2D
/// 

// 頂点データ用構造体
struct sVertexData2D {
	Vector4 position;
	Vector2 texcoord;
};

// 2D用のマテリアル構造体
struct sMaterial2D {
	Vector4 color;
	Matrix4x4 uvTransformMatrix;
};