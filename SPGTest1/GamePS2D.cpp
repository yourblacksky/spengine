#pragma once
#include "stdafx.h"
#include "SPParticleSystemManager.h"
#include "SPSpriteManager.h"
#include "GamePS2D.h"
#include <SPEngine.h>

using namespace SPEngine;
using namespace SPEngine::SPVertex;

GamePS2D::GamePS2D(HINSTANCE hInstance) : SPEngine::SPGame(hInstance){}

bool GamePS2D::Initialize()
{
	SPGame::Initialize();

	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_CULLMODE,1);

	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, true); 
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_SPECULARENABLE, true); 


	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);   
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCCOLOR);   
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCCOLOR); 

	return true;
}

bool GamePS2D::LoadContent()
{
	SPGame::LoadContent();
	//======================================================¡£◊”œµÕ≥≤‚ ‘
	D3DXVECTOR3 minPoint = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 maxPoint = D3DXVECTOR3(800, 600, 0);
	SPBoundingBox particleBox;
	particleBox.minPoint = minPoint;
	particleBox.maxPoint = maxPoint;
	minPoint = D3DXVECTOR3(-MAXIMUM_ALLOWED, -MAXIMUM_ALLOWED, -MAXIMUM_ALLOWED);
	maxPoint = D3DXVECTOR3(MAXIMUM_ALLOWED, MAXIMUM_ALLOWED, MAXIMUM_ALLOWED);
	SPBoundingBox boundBox;
	boundBox.minPoint = minPoint;
	boundBox.maxPoint = maxPoint;
	particleSys.Load(SPDevice::GetSingleton().GetD3DDevice(), particleBox, boundBox, 5, 20, 0, D3DX_PI * 2, 5,
		SPColor::White, 50, 1000, L"snowball.png", 50, D3DXVECTOR3(0, 0, 0), 5, false, INFINITE);
	//SPParticleSystemManager::GetSingleton().CreateParticleSystem(L"testParticleSystem", &particleSys);
//	SPParticleSystemManager::GetSingleton().Register(L"testParticleSystem");
	//========================================================
	textureTest = SPTextureManager::GetSingleton().GetTexture(L"snowball.png");
	return true;
}

bool GamePS2D::Update(float timeDelta)
{
	SPParticleSystemManager::GetSingleton().Update(timeDelta);
	SPGame::Update(timeDelta);
	return true;
}

bool GamePS2D::Draw(float timeDelta)
{
	SPParticleSystemManager::GetSingleton().Draw(timeDelta);
	SPSpriteManager::GetSingleton().RenderCentered(textureTest, NULL, 0, 0, NULL);
	SPGame::Draw(timeDelta);
	return true;
}