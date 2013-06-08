#pragma once
#include <SPGame.h>
#include <KScriptRunner.h>
#include <SPScriptManager.h>
#include "Test3D.h"

//#pragma comment(lib, "SPEngine.lib")
//#pragma comment(lib, "KScript.lib")

using namespace SPEngine;

class Game3D : public SPEngine::SPGame
{
	Test3D testScreen; 

public:
	Game3D(){}
	Game3D(HINSTANCE hInstance);
	~Game3D();

	bool Initialize();
	bool Draw(float timeDelta);
	bool Update(float timeDelta);
	bool LoadContent();	
	bool UnloadContent();
};