//////////////////////////////////////////////////////////////////////////
/// @file		SPSprite.h the header file of SPSprite class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPTexture.h"
#include "SPEffect.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief class SPSprite to represent a 2D sprite.
	/// 
	//////////////////////////////////////////////////////////////////////
	class SPSprite
	{
	public:
		SPTexturePtr texture;
		SPEffectPtr effect;
		//D3DXMATRIX	transformMatrix;
		RECT		sourceRect;
		D3DXVECTOR3 center;
		D3DXVECTOR3 position;
		D3DCOLOR	color; 
		SPTexturePtr renderTarget;
		D3DXVECTOR2 scalingCenter;
		float		scalingRotation;
		D3DXVECTOR2 scaling;
		D3DXVECTOR2 rotationCenter;
		float		rotation;
		D3DXVECTOR2 translation;

	public:
		SPSprite(void);
		SPSprite(
			SPTexturePtr,
			SPEffectPtr,
			RECT,
			D3DXVECTOR3,
			D3DXVECTOR3,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DXVECTOR2 translation,
			D3DCOLOR,
			SPTexturePtr);
		SPSprite(
			SPTexturePtr,
			SPEffectPtr,
			RECT,
			D3DXVECTOR3,
			D3DXVECTOR3,
			D3DCOLOR,
			SPTexturePtr);
		~SPSprite(void);

		D3DXMATRIX TransformMatrix();
	};
}


