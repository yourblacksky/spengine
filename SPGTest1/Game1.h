#pragma once
#include <SPEngine.h>

using namespace SPEngine;

class Game1 : public SPEngine::SPGame
{
public:
	SPTexturePtr tex;
	SPTexturePtr tex2;
	SPEffectPtr pixelShader;

	Game1(HINSTANCE hInstance);

	bool Initialize(void);
	bool LoadContent();
	bool UnloadContent();
	bool Draw(float timeDelta);
};

