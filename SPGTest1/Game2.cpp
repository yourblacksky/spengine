#pragma once
#include "stdafx.h"
#include "Game2.h"
#include <SPEngine.h>
#include <SPScreenManager.h>


using namespace SPEngine;

Game2::Game2(HINSTANCE hInstance) : SPEngine::SPGame(hInstance){}

bool Game2::Initialize(void)
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
	
	SPScreenManager::GetSingleton().CreateScreen(L"logo", new LogoScreen());
	SPScreenManager::GetSingleton().Register(L"logo");

	return true; 
}

bool Game2::LoadContent()
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

bool Game2::Update(float timeDelta)
{	
	// Base update function
	SPGame::Update(timeDelta);

	return true;
}

bool Game2::Draw(float timeDelta)
{
	// Base Draw function
	SPGame::Draw(timeDelta);

	return true;
}

bool Game2::UnloadContent()
{
	SPGame::UnloadContent();

	return true;
}

Game2::~Game2()
{

}

