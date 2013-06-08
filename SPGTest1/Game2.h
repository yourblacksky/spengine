#pragma once
#include <SPGame.h>
#include <KScriptRunner.h>
#include <SPScriptManager.h>
#include "LogoScreen.h"
#include "TestScreen.h"

//#pragma comment(lib, "SPEngine.lib")
//#pragma comment(lib, "KScript.lib")

using namespace SPEngine;

class Game2 : public SPEngine::SPGame
{
	LogoScreen logoScreen;
	TestScreen testScreen;

public:
	Game2(){}
	Game2(HINSTANCE hInstance);
	~Game2();

	bool Initialize();
	bool Draw(float timeDelta);
	bool Update(float timeDelta);
	bool LoadContent();	
	bool UnloadContent();
};

