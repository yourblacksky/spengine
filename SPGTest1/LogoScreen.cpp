#include "StdAfx.h"
#include "LogoScreen.h"
#include "TestScreen.h"
#include <SPEngine.h>

using namespace SPEngine;

LogoScreen::LogoScreen(void)
{
	transitionOnTime = 0.2f;
	transitionOffTime = 0.2f;
	logoPosition = 0;
	countDown = 4.0f;
}

LogoScreen::~LogoScreen(void)
{
	Unload();
}

bool LogoScreen::HandleInput( float timeDelta )
{
	if (SPInputManager::GetSingleton().GetMouse()->ButtonDown(0))
	{
		if(countDown > 2)
		{
			countDown = 2;
		}
	}
	return true;
}

bool LogoScreen::Update( float timeDelta )
{
	if (state == Active && countDown > 0)
	{
		countDown -= timeDelta;
		if(countDown >= 3)
		{
			logoPosition = 4 - countDown;
		}
		else if(countDown <= 2 && countDown >=1)
		{
			logoPosition = countDown - 1;
		}		
	}	

	if (state == Active && countDown <= 0)
	{
		ExitScreen();
		SPScreenManager::GetSingleton().CreateScreen(L"test", new TestScreen());
		SPScreenManager::GetSingleton().Register(L"test");
	}

	return true;
}

bool LogoScreen::Draw( float timeDelta )
{
	if (!isDisplay)
	{
		return false;
	}

	SPSpriteManager::GetSingleton().RenderOnScreen(blank, NULL, SPRectangle(0,0,
		SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth, 
		SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight),
		SPColor::Black, 0, NULL);

	SPTexturePtr tex = logo;
	SPSpriteManager::GetSingleton().RenderCentered(tex, NULL, 400, 250, D3DXCOLOR(255, 255, 0, logoPosition), 0);

	SPFontWriter::GetSingleton().Write(font, NULL, SPStringHelper::ToWString(countDown), D3DXVECTOR2(0,0), SPColor::White, 0, 1, NULL);

	return true;
}

bool LogoScreen::Load()
{
	logo = SPTextureManager::GetSingleton().GetTexture(L"logo_long_m_a.png");
	blank = SPTextureManager::GetSingleton().GetTexture(L"blank.jpg");
	font = SPFontManager::GetSingleton().CreateFont(L"yh_101", 100, 0, 1, 5, false, L"Î¢ÈíÑÅºÚ");

	return true;
}

bool LogoScreen::Unload()
{
	//if (screenManager)
	//{
	//	screenManager->RemoveScreen(this);
	//	screenManager = NULL;
	//}

	return true;
}

bool LogoScreen::Initialize()
{
	return true;
}
