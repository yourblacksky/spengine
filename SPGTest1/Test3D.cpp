#include "StdAfx.h"
#include "Test3D.h"
#include <SPEngine.h>
#include <SPScreenManager.h>

using namespace SPEngine;

Test3D::Test3D(void)
{
	transitionOnTime = 0.2f;
	transitionOffTime = 0.2f;
	logoPosition = 0;
	countDown = 4.0f;
}

Test3D::~Test3D(void)
{
	Unload();
}

bool Test3D::HandleInput( float timeDelta )
{
	if (SPInputManager::GetSingleton().GetMouse()->ButtonDown(0))
	{
		SPCamera::GetSingleton().Walk(timeDelta);
	}

	if (SPInputManager::GetSingleton().GetMouse()->ButtonDown(1))
	{
		SPCamera::GetSingleton().Walk(-timeDelta);
	}

	return true;
}

bool Test3D::Draw( float timeDelta )
{
	if (!isDisplay)
	{
		return false;
	}

	static float angle = 0;
	angle += timeDelta;
	float pos = abs(cos(angle));

	tex2->Fill(D3DCOLOR_COLORVALUE(pos,pos,pos,pos));

	pixelShader->SetTexture(1, tex2);

	//scalingCenter, scalingRotation, scaling, rotationCenter, rotation, translation
	SPSpriteManager3D::GetSingleton().Render(tex, pixelShader, D3DXVECTOR3(0, 0, 0), 
			D3DXQUATERNION(0, 0, 0, 0),	D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 0, 0),
			D3DXQUATERNION(sin(angle / 2), 0, 0, cos(angle / 2)), D3DXVECTOR3(0, 0, 0));

	SPSpriteManager3D::GetSingleton().Render(logo, NULL, D3DXVECTOR3(0, 0, 0), 
			D3DXQUATERNION(0, 0, 0, 0),	D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 0, 0),
			D3DXQUATERNION(cos((6.28 - angle) / 2), 0, 0, sin((6.28 - angle) / 2)), D3DXVECTOR3(0, 0, 0));

    return true; 
}

bool Test3D::Load()
{
	logo = SPTextureManager::GetSingleton().GetTexture(L"sos.jpg");
	tex = SPTextureManager::GetSingleton().GetTexture(L"ab.jpg");
	blank = SPTextureManager::GetSingleton().GetTexture(L"blank.jpg");
	font = SPFontManager::GetSingleton().CreateFont(L"yh_101", 100, 0, 1, 5, false, L"Î¢ÈíÑÅºÚ");
	tex2 = SPTextureManager::GetSingleton().CreateBlankTexture(L"blank", 2, 2, SPColor::White);
	pixelShader = new SPEffect(L"testPS.txt");

	return true;
}

bool Test3D::Unload()
{
	return true;
}

bool Test3D::Initialize()
{
	return true;
}