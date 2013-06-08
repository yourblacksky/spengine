#pragma once
#include <SPGame.h>
#include <KScriptRunner.h>
#include <SPScriptManager.h>
#include "Test.h"

//#pragma comment(lib, "SPEngine.lib")
//#pragma comment(lib, "KScript.lib")

using namespace SPEngine;

class Huiii : public SPEngine::SPGame
{
	Test testScreen;

public:
	Huiii(){}
	Huiii(HINSTANCE hInstance);
	~Huiii();

	bool Initialize();
	bool Draw(float timeDelta);
	bool Update(float timeDelta);
	bool LoadContent();	
	bool UnloadContent();
};