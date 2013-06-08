#pragma once
#include "stdafx.h"
#include "Game1.h"
#include <SPEngine.h>
#include <SPPixelShader.h>
#include <SPEffect.h>


using namespace SPEngine;

Game1::Game1(HINSTANCE hInstance) : SPEngine::SPGame(hInstance)	
{
	return;
}

bool Game1::Initialize(void)
{
	SPGame::Initialize();

	return true;
}

ID3DXSprite* Renderer;
SPEffectPtr effect;
SPEffectPtr effect2;

bool Game1::Draw(float timeDelta)
{
	//Refresh(SPColor::White);	

	//Renderer->Begin(D3DXSPRITE_ALPHABLEND);

	static float time = 0;
	time += timeDelta;
	float pos = abs(sin(time));

	//tex2->Fill(D3DCOLOR_COLORVALUE(pos,pos,pos,pos));
	//pixelShader->SetTexture(1, tex2);

	//SPSpriteManager::GetSingleton().Render(tex, pixelShader, NULL);

	//SPGame::Draw(timeDelta);

	//SPSpriteManager::GetSingleton().RenderCentered(tex,NULL,300,200,NULL);
	
	//Renderer->Begin(D3DXSPRITE_ALPHABLEND);
	//UINT numPass;	
	//effect->SetTexture(1, tex2);
	//D3DXMATRIX transfromation;
	//D3DXMatrixOrthoOffCenterLH(&transfromation, 0, GetWidth(), GetHeight(),0,0,1);
	//D3DXMATRIX translation;
	//D3DXMatrixTranslation(&translation, -0.5, -0.5, 0);
	//effect->SetMatrix("MatrixTransform", translation * transfromation);
	////effect2->SetTexture(1, tex2);
	//effect->ApplyEffect();
	//effect->GetCore()->GetEffect()->Begin(&numPass, 0);

	//for(int num = 0; num < numPass; num++)
	//{
	//	

	//	effect->GetCore()->GetEffect()->BeginPass(num);		
	//	
	//	Renderer->Draw(tex->GetD3DTexture(), 0, 0, 0, SPColor::White);
	//	Renderer->Flush();
	//	
	//	effect->GetCore()->GetEffect()->EndPass();

	//	
	//}

	//effect->GetCore()->GetEffect()->End();		
	//Renderer->End();
	
	//SPTexturePtr target = SPTextureManager::GetSingleton().CreateRenderTarget(768,768);
	//SPTexturePtr target2 = SPTextureManager::GetSingleton().CreateRenderTarget(768,768);
	//SPSpriteManager::GetSingleton().Render(tex2, effect, target);
	//SPSpriteManager::GetSingleton().Render(target, effect2, target2);
	//SPSpriteManager::GetSingleton().Render(target2, NULL, NULL);

	

	return SPGame::Draw(timeDelta);
}

bool Game1::LoadContent()
{
	SPGame::LoadContent();

	//D3DXCreateSprite(SPDevice::GetSingleton().GetD3DDevice(), &Renderer);

	//effect = new SPEffect(L"test_effect.txt");
	//effect2 = new SPEffect(L"mix_mask.mm");
	////pixelShader = new SPPixelShader(L"testPS.txt");
	//tex = SPTextureManager::GetSingleton().GetAnime(L"loading.png",2,4,14);
	//tex2 = SPTextureManager::GetSingleton().GetTexture(L"mask_st_02.jpg");

	return true;
}

bool Game1::UnloadContent()
{
	SPGame::UnloadContent();

	return true;
}

