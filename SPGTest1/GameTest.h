#pragma once
#include <SPGame.h>
#include <SPVertex.h>
#include <SPParticleSystem3D.h>
#include <SPEngine.h>
#include <SPParticleSystemTexture.h>

//#pragma comment(lib, "SPEngine.lib")

using namespace SPEngine;
using namespace SPEngine::SPVertex;

class GameTest : public SPEngine::SPGame
{
public:
	SPParticleSystemTexturePtr texture;
	SPAnimatedTexturePtr anime;
	SPFontPtr font;
	SPSoundPtr sound, sound2;
	SPTexturePtr renderTarget;

	GameTest(HINSTANCE hInstance);
	bool LoadContent(void);
	bool Update(float timeDelta);
	bool Draw(float timeDelta);
	bool Initialize(void);

private:
	D3DXVECTOR2 position;
	float x, y;
	float volumeValue;
	double musicPoint;
	//ParticleSystem particleSys;
	SPParticleSystem3DPtr snowSystem;
	SPTexturePtr tex3D;
};