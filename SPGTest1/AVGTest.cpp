#include "StdAfx.h"
#include "AVGTest.h"
#include <SPGame.h>
#include <SPConfig.h>
#include <VideoScreen.h>
#include <SPScreenManager.h>
#include <SPConfigManager.h>
#include <SPGameManager.h>

using namespace SPEngine;
using namespace SPAVG;

AVGTest::AVGTest(HINSTANCE hInstance) :
	SPEngine::SPAdventureGame(hInstance){}

	AVGTest::~AVGTest()
	{

	}

	bool AVGTest::Update( float timeDelta )
	{
		SPAdventureGame::Update(timeDelta);

		SPConfig config1;
		SPConfig config2;

		config1.windowWidth = 800;
		config1.windowHeight = 600;
		
		config1.backBufferWidth = 800;
		config1.backBufferHeight = 600;

		config2.windowed = false;
		config2.windowWidth = 1920;
		config2.windowHeight = 1080;
		
		config2.backBufferWidth = 1920;
		config2.backBufferHeight = 1080;

		if (SPInputManager::GetSingleton().GetKeyboard()->ButtonJustDown(DIK_1))
		{
			SPGameManager::GetSingleton().ApplyConfig(config1);
		}

		if (SPInputManager::GetSingleton().GetKeyboard()->ButtonJustDown(DIK_2))
		{
			SPGameManager::GetSingleton().ApplyConfig(config2);
		}	

		return true;
	}

	//
//AVGTest::AVGTest(){}

// AVGTest::AVGTest( HINSTANCE hInstance ){}

//bool AVGTest::LoadContent()
//{
//
//}
//
//bool AVGTest::Update( float timeDelta )
//{
//	throw std::exception("The method or operation is not implemented.");
//}
//
//void AVGTest::CleanUp()
//{
//	throw std::exception("The method or operation is not implemented.");
//}
//
//bool AVGTest::UnloadContent()
//{
//	throw std::exception("The method or operation is not implemented.");
//}
//
	bool AVGTest::Initialize()
	{
		if(!SPAdventureGame::Initialize())
		{
			return false;
		}

		SPScreenManager::GetSingleton().CreateScreen("video", new VideoScreen("logo01.avi"));
		SPScreenManager::GetSingleton().Register("video");

		return true;
	}
//
//bool AVGTest::Start()
//{
//	throw std::exception("The method or operation is not implemented.");
//}
//
//bool AVGTest::Draw( float timeDelta )
//{
//	throw std::exception("The method or operation is not implemented.");
//}