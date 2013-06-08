// SPGTest1.cpp : A Test Game Using SPEngine
//

#include "stdafx.h"
#include "SPGTest1.h"
#include "Game1.h"
#include "Game2.h"
#include "GameTest.h"
#include "Huiii.h"
#include "Game3D.h"
#include "GamePS2D.h"
#include <SPEngine.h>

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
/*	Game1 game1(hInstance);
	game1.Start();*/	

	//SPGamePtr game1 = SPGameFactory<Game1>::GetSingleton().Produce(hInstance);
	//SPGameManager::GetSingleton().Start();

	//SPGamePtr game2 = SPGameFactory<Game2>::GetSingleton().Produce(hInstance);
	//SPGameManager::GetSingleton().Start();

	//SPGamePtr game3 = SPGameFactory<Huiii>::GetSingleton().Produce(hInstance);
	//SPGameManager::GetSingleton().Start();

	//GameTest gameTest(hInstance);
	//gameTest.Start();

	//AVGTest avgTest(hInstance);
	//avgTest.Start();

	//SPGamePtr gamePS2D = SPGameFactory<GamePS2D>::GetSingleton().Produce(hInstance);
	//SPGameManager::GetSingleton().Start();
	
	SPGamePtr gameTest = SPGameFactory<GameTest>::GetSingleton().Produce(hInstance);
	SPGameManager::GetSingleton().Start();

	return 0;
}
