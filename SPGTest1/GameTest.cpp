#pragma once
#include "stdafx.h"
#include "GameTest.h"
#include "SPParticleSystemManager.h"
#include "SPParticleSystem3D.h"
#include <SPEngine.h>

using namespace SPEngine;
using namespace SPEngine::SPVertex;

GameTest::GameTest(HINSTANCE hInstance) : SPEngine::SPGame(hInstance){}

bool GameTest::Initialize()
{
	SPGame::Initialize();

	//d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//GetDevice()->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_CULLMODE,1);

	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, true); 
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_SPECULARENABLE, true); 

	
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);   
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCCOLOR);   
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCCOLOR); 

	return true;
}

bool GameTest::LoadContent()
{
	SPGame::LoadContent();

	anime = SPTextureManager::GetSingleton().GetAnime(L"a.png", 2, 4, 20);
	font = SPFontManager::GetSingleton().CreateFont(L"yh_100_2", 100, 0, 1, 5, false, L"微软雅黑");

	SPMaterialManager::GetSingleton().SetMaterial(SPMaterialManager::WHITE_MTRL);

	tex3D = SPTextureManager::GetSingleton().GetTexture(L"loading.png");

	SPCamera::GetSingleton().SetPosition(D3DXVECTOR3(0.0f, -1.0f, 0.0f));
	SPCamera::GetSingleton().SetProjection(D3DX_PI  * 0.5f, (float)SPWindow::GetSingleton().GetWidth() /
		(float)SPWindow::GetSingleton().GetHeight(), 0.2f, 10.0f);


	x = 400;
	y = 300;

	sound = new SPSound();
	sound2 = new SPSound();

	sound->Load(L"login.wav", 5, 0, 0, 0);
	//test mutipleSounds
	sound2->Load( L"menu.wav", XAUDIO2_LOOP_INFINITE,0, 5, 5);

	sound->Play();

	sound2->Play();


	//D3DXVECTOR3 minPoint = D3DXVECTOR3(200, 300, 0);
	//D3DXVECTOR3 maxPoint = D3DXVECTOR3(300, 400, 0);
	//BoundingBox particleBox;
	//particleBox.minPoint = minPoint;
	//particleBox.maxPoint = maxPoint;
	//minPoint = D3DXVECTOR3(-MAXIMUM_ALLOWED, -MAXIMUM_ALLOWED, -MAXIMUM_ALLOWED);
	//maxPoint = D3DXVECTOR3(MAXIMUM_ALLOWED, MAXIMUM_ALLOWED, MAXIMUM_ALLOWED);
	//BoundingBox boundBox;
	//boundBox.minPoint = minPoint;
	//boundBox.maxPoint = maxPoint;
	//particleSys.Load(spriteManager->GetDevice(), particleBox, boundBox, 20, 20, 0, 
	//	2 * D3DX_PI, 2.5f, Color::White, 50, 100, "snowball.png", 
	//	200, D3DXVECTOR3(0, 0, 0), 5, true, INFINITY);


	//particleBox.minPoint = D3DXVECTOR3(-4, -0.5f, -4);
	//particleBox.maxPoint = D3DXVECTOR3(4, 4, -4);
	snowSystem = new SPParticleSystem3D;
	D3DXVECTOR2 minPoint = D3DXVECTOR2(-4, -1);
	D3DXVECTOR2 maxPoint = D3DXVECTOR2(200, 200);
	BoundingBox2D particleBox2D;
	particleBox2D.minPoint = minPoint;
	particleBox2D.maxPoint = maxPoint;
	minPoint = D3DXVECTOR2(-2, -2);
	maxPoint = D3DXVECTOR2(800, 600);
	BoundingBox2D boundBox2D;
	boundBox2D.minPoint = minPoint;
	boundBox2D.maxPoint = maxPoint;

	//snowSystem->Load(SPDevice::GetSingleton().GetD3DDevice(), particleBox, boundBox, 1, 2, D3DX_PI / 6, D3DX_PI / 6 * 5,
	//	4.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 20, 100, "snowSmall.png", 600, D3DXVECTOR3(0, 0, 0), 5, true, INFINITY,
	//	0, 0, 4, D3DXVECTOR3(0.707f, 0, 0.707f), true, 1);
	
	SPTexturePtr tex = SPTextureManager::GetSingleton().GetTexture(L"snowSmall.png");

	snowSystem->LoadWith2D(particleBox2D, boundBox2D, 100, 200, D3DX_PI / 6, D3DX_PI / 6 * 5,

	4.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 20, 100, tex, 600, D3DXVECTOR2(0, 0),
	true,
		0, 0, -1, 1, D3DXVECTOR3(0, 1, 0), true, 1, 1, 1, -0.2, 0);

//=======
//	4.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 20, 100, "snowSmall.png", 600, D3DXVECTOR2(0, 0), 10, true, INFINITY,
//		0, 0, 1, D3DXVECTOR3(0, 1, 0), false, 1, 0.5f, 1);
//>>>>>>> .r7818

	
	//renderTarget
	//snowSystem->SetRenderTarget(renderTarget);

	SPParticleSystemManager::GetSingleton().AddParticleSystem(L"testParticle", snowSystem);

	//==================test CreateParticleSystem=============
	//SPParticleSystemManager::GetSingleton().CreateParticleSystem(L"testParticle", particleBox2D, boundBox2D, 100, 200, D3DX_PI / 6, D3DX_PI / 6 * 5,

	//	4.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 20, 100, tex, 600, D3DXVECTOR2(0, 0),
	//	true,
	//		0, 0, 1, D3DXVECTOR3(0, 1, 0), false, 1, 1, 1, -0.2, 0);

	renderTarget = SPTextureManager::GetSingleton().CreateParticleSystemTexture(L"testParticle", 800, 600);

	//SPParticleSystemManager::GetSingleton().Register(L"testParticle");
	return true;
}

bool GameTest::Update(float timeDelta)
{
	//particleSys.Update(timeDelta);
	//snowSystem.Update(timeDelta);
	//SPParticleSystemManager::GetSingleton().Update(timeDelta);

	if(SPInputManager::GetSingleton().GetMouse()->IsScrolledUp())
	{
		SPCamera::GetSingleton().Walk(1);
	}

	if(SPInputManager::GetSingleton().GetMouse()->IsScrolledDown())
	{
		SPCamera::GetSingleton().Walk(-1);
	}

	if(::GetAsyncKeyState('A') & 0x8000f) x -= 100 * timeDelta;
	if(::GetAsyncKeyState('S') & 0x8000f) y += 100 * timeDelta;
	if(::GetAsyncKeyState('D') & 0x8000f) x += 100 * timeDelta;
	if(::GetAsyncKeyState('W') & 0x8000f) y -= 100 * timeDelta;
	if(x < 0) x = 0;
	if(y < 0) y = 0;
	if(x > 800) x = 800;
	if(y > 600) y = 600;

	if(SPInputManager::GetSingleton().GetMouse()->ButtonJustDown(0))
		sound2->Pause(2);
	if(SPInputManager::GetSingleton().GetMouse()->ButtonJustDown(1))
		sound2->Play(2);

	//sound.GetVolume(volumeValue);
	//if(inputManager.keyboard->ButtonJustDown(DIK_V))

	//	//volumeValue -= 0.1f;
	//else if(inputManager.keyboard->ButtonJustDown(DIK_B))
	//	//volumeValue += 0.1f; 
	//sound.SetVolume(volumeValue);
	volumeValue = SPSoundManager::GetSingleton().GetVolume();
	if(SPInputManager::GetSingleton().GetKeyboard()->ButtonJustDown(DIK_V))
		volumeValue -= 0.1f;
	else if(SPInputManager::GetSingleton().GetKeyboard()->ButtonJustDown(DIK_B))
		volumeValue += 0.1f; 
	SPSoundManager::GetSingleton().SetVolume(volumeValue);

	//musicPoint = sound->TestUse();

	//sound.Update(timeDelta);
	//sound2.Update(timeDelta);

	if(SPInputManager::GetSingleton().GetKeyboard()->ButtonJustDown(DIK_H))
		SPParticleSystemManager::GetSingleton().GetParticleSystem(L"testParticle")->Stop();
	if(SPInputManager::GetSingleton().GetKeyboard()->ButtonJustDown(DIK_G))
		SPParticleSystemManager::GetSingleton().GetParticleSystem(L"testParticle")->Play();
	SPGame::Update(timeDelta);

	return true;
}

bool GameTest::Draw(float timeDelta)
{
	//particleSys.Draw(timeDelta);
	Refresh(SPColor::Gray);

	//snowSystem.Draw(timeDelta);
	//SPParticleSystemManager::GetSingleton().Draw(timeDelta);

	SPSpriteManager::GetSingleton().Render(renderTarget, NULL, NULL);

	SPSpriteManager::GetSingleton().ARenderCentered(anime, NULL, D3DXVECTOR3(x, y, 0), 
		1, D3DXVECTOR2(32, 32), 0, SPColor::White, NULL);

	SPFontWriter::GetSingleton().WriteCentered(font, NULL, L"这么难看", D3DXVECTOR2(300, 300),SPColor::White , 0, 1, NULL);

	SPFontWriter::GetSingleton().WriteCentered(font, NULL, SPStringHelper::ToWString(volumeValue),
		D3DXVECTOR2(300, 500),D3DXCOLOR(0, 1, 1, 0.5f), 0, 1, NULL);

	SPFontWriter::GetSingleton().WriteCentered(font, NULL, SPStringHelper::ToWString(musicPoint, 5), 
		D3DXVECTOR2(400, 500), SPColor::White, 0, 1, NULL);

	SPFontWriter::GetSingleton().WriteCentered(font, NULL, SPStringHelper::ToWString(sound->GetLength()),
		D3DXVECTOR2(100,50), SPColor::White, 0, 1, NULL);

	SPSpriteManager3D::GetSingleton().RenderByPosition(tex3D, NULL, D3DXVECTOR3(0, 0, 0));

	SPGame::Draw(timeDelta);

	return true;
}

