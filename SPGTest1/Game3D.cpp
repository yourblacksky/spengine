#pragma once
#include "stdafx.h"
#include "Game3D.h"
#include <SPEngine.h>
#include <SPScreenManager.h>

using namespace SPEngine;

Game3D::Game3D(HINSTANCE hInstance) : SPEngine::SPGame(hInstance){}

bool Game3D::Initialize(void)
{
	SPGame::Initialize();

	// Render states (fill mode: wire frame)
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_FORCE_DWORD);
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, true); 
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_SPECULARENABLE, true); 
	
	SPScreenManager::GetSingleton().CreateScreen(L"test3D", new Test3D());
	SPScreenManager::GetSingleton().Register(L"test3D");

	return true; 
}

bool Game3D::LoadContent()
{
	SPGame::LoadContent();	

	// Set material
	//SPMaterialManager::GetSingleton().SetMaterial(SPMaterialManager::WHITE_MTRL);

	//// Camera & Projection
	//SPCamera::GetSingleton().SetPosition(D3DXVECTOR3(0.0f, -1.0f, 0.0f));
	//SPCamera::GetSingleton().SetProjection(D3DX_PI  * 0.5f,
	//	(float)SPConfigManager::GetSingleton().GetCurrentConfig().backBufferWidth /
	//	(float)SPConfigManager::GetSingleton().GetCurrentConfig().backBufferHeight
	//	, 0.2f, 10.0f);
	////camera.SetViewport(100, 100, 600, 300);

	// Lighting
	//SPLightManager::GetSingleton().EnableLighting();

	//SPLightManager::GetSingleton().AddLight(0, SPLightManager::InitPointLight(
	//	D3DXVECTOR3(0,0,5), SPColor::Red));
	//SPLightManager::GetSingleton().AddLight(1, SPLightManager::InitDirectionalLight( 
	//	D3DXVECTOR3(0,0,-10), SPColor::White));
	//SPLightManager::GetSingleton().AddLight(2, SPLightManager::InitSpotLight(
	//	D3DXVECTOR3(-10, 0, 0),D3DXVECTOR3(10, 0, 0), SPColor::Blue));
	//SPLightManager::GetSingleton().AddLight(3, SPLightManager::InitSpotLight(
	//	D3DXVECTOR3(10, 0, 0),D3DXVECTOR3(-10, 0, 0), SPColor::Green));

	SPLightManager::GetSingleton().DisableLighting();

	return true;
}

bool Game3D::Update(float timeDelta)
{	
	// Base update function
	SPGame::Update(timeDelta);

	return true;
}

bool Game3D::Draw(float timeDelta)
{
	// Base Draw function
	SPGame::Draw(timeDelta);

	return true;
}

bool Game3D::UnloadContent()
{
	SPGame::UnloadContent();
	return true;
}

Game3D::~Game3D()
{

}