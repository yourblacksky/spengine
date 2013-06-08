//////////////////////////////////////////////////////////////////////////
/// @file		SPSprite.cpp the implement file of SPSprite class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPSprite.h"
#include "SPColorHelper.h"
#include "SPConfigManager.h"

using namespace SPEngine;

SPSprite::SPSprite(void)
{
	texture = NULL;
	effect = NULL;
	//transformMatrix = D3DXMATRIX();
	sourceRect = RECT();
	center = D3DXVECTOR3();
	position = D3DXVECTOR3();
	scalingCenter = D3DXVECTOR2(0, 0),
	scalingRotation = 0,
	scaling = D3DXVECTOR2(1, 1),
	rotationCenter = D3DXVECTOR2(0, 0),
	rotation = 0,
	translation = D3DXVECTOR2(0, 0),
	color = SPColor::White;
	renderTarget = NULL;
}

SPSprite::~SPSprite(void)
{
}

SPSprite::SPSprite( 
	SPTexturePtr setTex,
	SPEffectPtr setPS, 
	RECT setSourceRect,
	D3DXVECTOR3 setCenter,
	D3DXVECTOR3 setPos,
	D3DXVECTOR2 setScalingCenter,
	float		setScalingRotation,
	D3DXVECTOR2 setScaling,
	D3DXVECTOR2 setRotationCenter,
	float		setRotation,
	D3DXVECTOR2 setTranslation,
	D3DCOLOR setColor, 
	SPTexturePtr setTarget )
{
	texture = setTex;
	effect = setPS;
	//transformMatrix = setTrans;
	sourceRect = setSourceRect;
	center = setCenter;
	position = setPos;
	scalingCenter = setScalingCenter,
	scalingRotation = setScalingRotation,
	scaling = setScaling,
	rotationCenter = setRotationCenter,
	rotation = setRotation,
	translation = setTranslation,
	color = setColor;
	renderTarget = setTarget;
}

SPSprite::SPSprite( 
	SPTexturePtr setTex,
	SPEffectPtr setPS, 
	RECT setSourceRect,
	D3DXVECTOR3 setCenter,
	D3DXVECTOR3 setPos,
	D3DCOLOR setColor, 
	SPTexturePtr setTarget )
{
	texture = setTex;
	effect = setPS;
	//transformMatrix = setTrans;
	sourceRect = setSourceRect;
	center = setCenter;
	position = setPos;
	scalingCenter = D3DXVECTOR2(0, 0),
	scalingRotation = 0,
	scaling = D3DXVECTOR2(1, 1),
	rotationCenter = D3DXVECTOR2(0, 0),
	rotation = 0,
	translation = D3DXVECTOR2(0, 0),
	color = setColor;
	renderTarget = setTarget;
}

D3DXMATRIX SPSprite::TransformMatrix()
{
	D3DXMATRIX transformMatrix;
	D3DXMatrixTransformation2D(&transformMatrix, &scalingCenter,
		scalingRotation, &scaling, &rotationCenter,
		rotation, &translation);

	return transformMatrix;
}


