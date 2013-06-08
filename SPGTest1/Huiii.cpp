#pragma once
#include "stdafx.h"
#include "Huiii.h"
#include "Test.h"
#include <SPEngine.h>
#include <SPScreenManager.h>


using namespace SPEngine;

Huiii::Huiii(HINSTANCE hInstance) : SPEngine::SPGame(hInstance){}

bool Huiii::Initialize(void)
{
	SPGame::Initialize();

	// Render states (fill mode: wire frame)
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_FORCE_DWORD);
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, true); 
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_SPECULARENABLE, true); 

	//Device->SetRenderState(D3DRS_ALPHABLENDENABLE,   TRUE );
	//Device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	//Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); 
	//Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE );
	//Device->SetRenderState(D3DRS_ALPHAREF,        0x0f ); 
	//Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );

	//Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);   
	//Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCCOLOR);   
	//Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCCOLOR); 
	
	SPScreenManager::GetSingleton().CreateScreen(L"test", new Test());
	SPScreenManager::GetSingleton().Register(L"test");

	return true; 
}

bool Huiii::LoadContent()
{
	SPGame::LoadContent();	

	// Set material
	SPMaterialManager::GetSingleton().SetMaterial(SPMaterialManager::WHITE_MTRL); 

	// Camera & Projection
	SPCamera::GetSingleton().SetPosition(D3DXVECTOR3(0.0f, -1.0f, 0.0f));
	SPCamera::GetSingleton().SetProjection(D3DX_PI  * 0.5f,
		(float)SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth /
		(float)SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight
		, 0.2f, 10.0f);
	//camera.SetViewport(100, 100, 600, 400);

	// Lighting
	SPLightManager::GetSingleton().EnableLighting();

	SPLightManager::GetSingleton().AddLight(0, SPLightManager::InitPointLight(
		D3DXVECTOR3(0,0,5), SPColor::Red));
	SPLightManager::GetSingleton().AddLight(1, SPLightManager::InitDirectionalLight( 
		D3DXVECTOR3(0,0,-10), SPColor::White));
	SPLightManager::GetSingleton().AddLight(2, SPLightManager::InitSpotLight(
		D3DXVECTOR3(-10, 0, 0),D3DXVECTOR3(10, 0, 0), SPColor::Blue));
	SPLightManager::GetSingleton().AddLight(3, SPLightManager::InitSpotLight(
		D3DXVECTOR3(10, 0, 0),D3DXVECTOR3(-10, 0, 0), SPColor::Green));

	SPLightManager::GetSingleton().TurnOnAll();

	return true;
}

bool Huiii::Update(float timeDelta)
{	
	// Base update function
	SPGame::Update(timeDelta);

	return true;
}

bool Huiii::Draw(float timeDelta)
{
	// Base Draw function
	SPGame::Draw(timeDelta);

	return true;
}

bool Huiii::UnloadContent()
{
	SPGame::UnloadContent();

	return true;
}

Huiii::~Huiii()
{

}

