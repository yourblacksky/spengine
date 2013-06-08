// SPShower.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SPShower.h"
#include <SPEngine.h>
#include "SPGameShow.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	SPGameFactory<SPGameShow>::GetSingleton().Produce(hInstance);
	SPGameManager::GetSingleton().Start();

	return 0;
}

