#pragma once
#include <SPGame.h>
#include <SPVertex.h>
#include "SPParticleSystemManager.h"
#include <SPEngine.h>

using namespace SPEngine;

class GamePS2D : public SPEngine::SPGame
{
public:
	GamePS2D(HINSTANCE hInstance);
	bool LoadContent(void);
	bool Update(float timeDelta);
	bool Draw(float timeDelta);
	bool Initialize(void);
private:
	SPParticleSystem2D particleSys;
	SPTexturePtr textureTest;
};