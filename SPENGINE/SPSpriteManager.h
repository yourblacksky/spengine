//////////////////////////////////////////////////////////////////////////
/// @file		SPSpriteManager.h the header file of SPSpriteManager class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-23
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3dx9core.h>
#include <list>
#include "SPSprite.h"
#include "SPAnimatedTexture.h"
#include "SPComponent.h"
#include "SPSingleton.h"

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPSpriteManager to create and draw sprite.
	///
	//////////////////////////////////////////////////////////////////////
	class SPSpriteManager :
		public SPComponent, 
		public SPSingleton<SPSpriteManager>
	{
		typedef list<SPSprite> SPSpriteList;
		typedef SPSpriteList::iterator SPSpriteIterator;

		SPSpriteList sprites;
		SPTexturePtr currentTarget;
		bool isTopological;
		//SPEffectPtr blendEffect;

	public:
		LPD3DXSPRITE Renderer;
		LPD3DXSPRITE innerRenderer;

	public:
		SPSpriteManager(void);
		~SPSpriteManager(void);

		bool Initialize();
		bool Load();
		bool Unload();
		bool Update(float timeDelta);
		bool PreDraw();
		bool Draw(float timeDelta);
		bool PostDraw();
		bool DrawSimple(float timeDelta);
		bool DrawTopological(float timeDelta);
		//bool DrawTopologicalWithBlend(float timeDelta);
		bool TopologicalSort();

		bool AddSprite(
			SPTexturePtr	tex,
			SPEffectPtr pixelShader,
			D3DXVECTOR3 center,
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			SPTexturePtr	target);
		//bool AddSprite( 
		//	SPTexturePtr	tex ,
		//	SPEffectPtr pixelShader,
		//	D3DXMATRIX	transformMatrix, 
		//	RECT		secRect,
		//	D3DXVECTOR3 center,
		//	D3DXVECTOR3 position,
		//	D3DCOLOR	color,
		//	SPTexturePtr target);
		bool AddSprite( 
			SPTexturePtr	tex ,
			SPEffectPtr pixelShader,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DXVECTOR2 translation,
			RECT		srcRect,
			D3DXVECTOR3 center, 
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			SPTexturePtr target);

		bool DrawSprite(SPSprite sprite);

		/// @name Render functions
		/// @{
		/// @brief Render on screen
		bool Render(
			SPTexturePtr tex,
			SPEffectPtr ps,
			SPTexturePtr target);
		bool Render(
			SPTexturePtr tex, 
			SPEffectPtr ps,
			float		x,
			float		y,
			SPTexturePtr target);
		bool Render(
			SPTexturePtr tex,
			SPEffectPtr ps,
			float		x,
			float		y,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool Render(
			SPTexturePtr tex,
			SPEffectPtr ps,
			float		x,
			float		y,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool Render(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			SPTexturePtr target);
		bool Render(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool Render(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 center,
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool Render(
			SPTexturePtr tex,
			SPEffectPtr ps,
			float		x,
			float		y,
			float		scale,
			float		rotation,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool Render(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool Render(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);

		/// @brief Render on screen with rectangle
		bool RenderOnScreen(
			SPTexturePtr tex,
			SPEffectPtr ps,
			SPRectangle destRect,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool RenderOnScreen(
			SPTexturePtr tex,
			SPEffectPtr ps,
			SPRectangle srcRect,
			SPRectangle destRect,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);

		/// @brief Render with transform matrix
		//bool RenderWithMatrix(
		//	SPTexturePtr tex,
		//	SPEffectPtr ps,
		//	D3DXMATRIX	transformMatrix,
		//	D3DXVECTOR3 center,
		//	D3DXVECTOR3 position,
		//	D3DCOLOR	color,
		//	SPTexturePtr target);
		//bool RenderWithMatrix(
		//	SPTexturePtr tex,
		//	SPEffectPtr ps,
		//	D3DXMATRIX	transformMatrix,
		//	RECT		srcRect,
		//	D3DXVECTOR3 center,
		//	D3DXVECTOR3 position,
		//	D3DCOLOR	color,
		//	SPTexturePtr target);

		/// @brief Render with scaling 
		bool RenderWithScaling(
			SPTexturePtr tex,
			SPEffectPtr ps,
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderWithScaling(
			SPTexturePtr tex,
			SPEffectPtr ps,
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool RenderWithScaling(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			float		scale,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderWithScaling(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderWithScaling(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color,
			SPTexturePtr target);

		/// @brief Render with rotation
		bool RenderWithRotation(
			SPTexturePtr tex,
			SPEffectPtr ps,
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderWithRotation(
			SPTexturePtr tex,
			SPEffectPtr ps,
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool RenderWithRotation(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderWithRotation(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);

		/// @brief Render basic
		bool RenderBasic(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 center, 
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DXVECTOR2 translation,
			SPTexturePtr target);
		bool RenderBasic(
			SPTexturePtr tex,
			SPEffectPtr ps,
			RECT		srcRect,
			D3DXVECTOR3 center, 
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DXVECTOR2 translation,
			SPTexturePtr target);

		/// @brief Render centered
		bool RenderCentered(
			SPTexturePtr tex, 
			SPEffectPtr ps,
			SPTexturePtr target);
		bool RenderCentered(
			SPTexturePtr tex,
			SPEffectPtr ps,
			float		x,
			float		y,
			SPTexturePtr target);
		bool RenderCentered(
			SPTexturePtr tex,
			SPEffectPtr ps,
			float		x,
			float		y,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderCentered(
			SPTexturePtr tex,
			SPEffectPtr ps,
			float		x,
			float		y,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool RenderCentered(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			SPTexturePtr target);
		bool RenderCentered(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderCentered(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 center,
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderCentered(
			SPTexturePtr tex,
			SPEffectPtr ps,
			float		x,
			float		y,
			float		scale,
			float		rotation,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool RenderCentered(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderCentered(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderCentered(
			SPTexturePtr tex,
			SPEffectPtr ps,
			SPRectangle srcRect,
			D3DXVECTOR3 position,
			float		scale,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderCentered(
			SPTexturePtr tex,
			SPEffectPtr ps,
			SPRectangle srcRect,
			D3DXVECTOR3 position,
			float		scale,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);

		/// @brief Render centered with scaling
		bool RenderCenteredWithScaling(
			SPTexturePtr tex,
			SPEffectPtr ps,
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderCenteredWithScaling(
			SPTexturePtr tex,
			SPEffectPtr ps,
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool RenderCenteredWithScaling(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			float		scale,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderCenteredWithScaling(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderCenteredWithScaling(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color,
			SPTexturePtr target);

		/// @brief Render centered with rotation
		bool RenderCenteredWithRotation(
			SPTexturePtr tex,
			SPEffectPtr ps,
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderCenteredWithRotation(
			SPTexturePtr tex,
			SPEffectPtr ps,
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool RenderCenteredWithRotation(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool RenderCenteredWithRotation(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);

		/// @brief Render centered basic
		bool RenderCenteredBasic(
			SPTexturePtr tex,
			SPEffectPtr ps,
			D3DXVECTOR3 center, 
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DXVECTOR2 translation,
			SPTexturePtr target);
		bool RenderCenteredBasic(
			SPTexturePtr tex,
			SPEffectPtr ps,
			RECT		srcRect,
			D3DXVECTOR3 center, 
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DXVECTOR2 translation,
			SPTexturePtr target);
		/// @}

		/// @name Animated render function.
		/// @{
		bool ARender(
			SPAnimatedTexturePtr anime, 
			SPEffectPtr ps,
			SPTexturePtr target);
		bool ARender(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			float		x,
			float		y,
			SPTexturePtr target);
		bool ARender(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			float		x,
			float		y,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARender(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			float		x,
			float		y,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool ARender(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			SPTexturePtr target);
		bool ARender(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARender(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			D3DXVECTOR3 center,
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARender(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			float		x,
			float		y,
			float		scale,
			float		rotation,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool ARender(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARender(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);

		/// @brief Render animation on screen with rectangle
		bool ARenderOnScreen(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			SPRectangle destRect,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);	

		/// @brief Render animation with scaling 
		bool ARenderWithScaling(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderWithScaling(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool ARenderWithScaling(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			float		scale,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderWithScaling(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderWithScaling(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color,
			SPTexturePtr target);

		/// @brief Render animation with rotation
		bool ARenderWithRotation(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderWithRotation(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool ARenderWithRotation(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderWithRotation(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);


		bool ARenderBasic(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			D3DXVECTOR3 center, 
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DXVECTOR2 translation,
			SPTexturePtr target);

		/// @brief Render animation centered
		bool ARenderCentered(
			SPAnimatedTexturePtr anime, 
			SPEffectPtr ps,
			SPTexturePtr target);
		bool ARenderCentered(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			float		x,
			float		y,
			SPTexturePtr target);
		bool ARenderCentered(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			float		x,
			float		y,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderCentered(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			float		x,
			float		y,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool ARenderCentered(
			SPAnimatedTexturePtr anime,
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			SPTexturePtr target);
		bool ARenderCentered(
			SPAnimatedTexturePtr anime, 
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderCentered(
			SPAnimatedTexturePtr anime, 
			SPEffectPtr ps,
			D3DXVECTOR3 center,
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderCentered(
			SPAnimatedTexturePtr anime, 
			SPEffectPtr ps,
			float		x,
			float		y,
			float		scale,
			float		rotation,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool ARenderCentered(
			SPAnimatedTexturePtr anime, 
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderCentered(
			SPAnimatedTexturePtr anime, 
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderCentered(
			SPAnimatedTexturePtr anime, 
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			float		scale,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderCentered(
			SPAnimatedTexturePtr anime, 
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			float		scale,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);

		/// @brief Render centered with scaling
		bool ARenderCenteredWithScaling(
			SPAnimatedTexturePtr anime, 
			SPEffectPtr ps,
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderCenteredWithScaling(
			SPAnimatedTexturePtr anime, 
			SPEffectPtr ps,
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool ARenderCenteredWithScaling(
			SPAnimatedTexturePtr anime, SPEffectPtr ps,
			D3DXVECTOR3 position,
			float		scale,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderCenteredWithScaling(
			SPAnimatedTexturePtr anime, SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderCenteredWithScaling(
			SPAnimatedTexturePtr anime, 
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color,
			SPTexturePtr target);

		/// @brief Render centered with rotation
		bool ARenderCenteredWithRotation(
			SPAnimatedTexturePtr anime, 
			SPEffectPtr ps,
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderCenteredWithRotation(
			SPAnimatedTexturePtr anime, 
			SPEffectPtr ps,
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color,
			float		depth,
			SPTexturePtr target);
		bool ARenderCenteredWithRotation(
			SPAnimatedTexturePtr anime, 
			SPEffectPtr ps,
			D3DXVECTOR3 position,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);
		bool ARenderCenteredWithRotation(
			SPAnimatedTexturePtr anime, SPEffectPtr ps,
			D3DXVECTOR3 position,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color,
			SPTexturePtr target);

		/// @brief Render centered basic
		bool ARenderCenteredBasic(
			SPAnimatedTexturePtr anime, SPEffectPtr ps,
			D3DXVECTOR3 center, 
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DXVECTOR2 translation,
			SPTexturePtr target);
		/// @}
	};
}


