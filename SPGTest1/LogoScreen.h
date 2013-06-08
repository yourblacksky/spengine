#pragma once
#include <SPBaseScreen.h>
#include <SPTexture.h>
#include <SPFont.h>
#include <SPPointer.h>

using namespace SPEngine;

class LogoScreen :
	public SPEngine::SPBaseScreen
{
	float countDown;
	SPTexturePtr logo;
	SPTexturePtr blank;
	SPFontPtr font;
	float logoPosition;

public:
	LogoScreen(void);
	~LogoScreen(void);

	bool HandleInput( float timeDelta );
	bool Update(float timeDelta);
	bool Draw(float timeDelta);
	bool Load();
	bool Unload();
	bool Initialize();
};

