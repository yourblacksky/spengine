#pragma once
#include <SPEngine.h>
#include <KScript.h>


using namespace SPEngine;

class Print;

class PrintScriptManager : public SPScriptManager
{
public:
	PrintScriptManager(){}
	~PrintScriptManager(){}	
};

class TestScreen:
	public SPEngine::SPBaseScreen
{
	friend class Print;
	SPTexturePtr blank;
	SPTexturePtr texture;
	SPAnimatedTexturePtr anime;
	SPFontPtr font;
	SPSoundPtr sound;
	PrintScriptManager print;
	ArgsFunctionPtr p;
	SPTexturePtr tex3D;
	SPVideoPtr video;
	SPVideoTexturePtr videoTexture;
	SPEffectPtr pixelShader;

public:
	TestScreen(void);
	~TestScreen(void);

	bool HandleInput(float timeDelta);
	bool Update(float timeDelta);
	bool Draw(float timeDelta);
	bool Load();
	bool Unload();
	bool Initialize();
};

class Print : public ExtendedArgsFunction
{	
public:
	TestScreen* test;

	Print(){}
	~Print(){}
	Print(TestScreen* setTest)
	{
		test = setTest;
	}
	virtual Value Function(KScript::Script* currentScript, vector<Value> args );

};