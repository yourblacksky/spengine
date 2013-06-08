#pragma once
#include <SPEngine.h>
#include <KScript.h>

using namespace SPEngine;

class Test3D : public SPEngine::SPBaseScreen {

	float countDown;
	SPTexturePtr logo;
	SPTexturePtr blank;
	SPTexturePtr tex; 
	SPTexturePtr tex2;
	SPFontPtr font;
	SPEffectPtr pixelShader;
	float logoPosition;

public:
	Test3D(void);
	~Test3D(void);

	bool HandleInput( float timeDelta );
	bool Draw(float timeDelta);
	bool Load();
	bool Unload();
	bool Initialize();
};