//////////////////////////////////////////////////////////////////////////
/// @file		SPGame.cpp the implement file of base SPGame class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-15
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPGame.h"
#include "SPColorHelper.h"
#include "SPMaterialManager.h"
#include "SPLightManager.h"
#include "SPLogHelper.h"
#include "SPMessageHelper.h"
#include "SPDevice.h"
#include "SPComponentFactory.h"
#include "SPTextureManager.h"
#include "SPComponentManager.h"
#include "SPSpriteManager.h"
#include "SPFontWriter.h"
#include "SPCamera.h"
#include "SPInputManager.h"
#include "SPFontManager.h"
#include "SPScreenManager.h"
#include "SPSpriteManager3D.h"
#include "FPSDisplayer.h"
#include "SPSoundManager.h"
#include "SPShaderManager.h"
#include "SPConfigManager.h"
#include "SPWindow.h"
#include "SPVideoManager.h"
#include "SPParticleSystemManager.h"
#include "SPFilePacker.h"

namespace SPEngine
{
	#pragma region Constructor
	SPGame::SPGame(		
		HINSTANCE	setHInstance, 
		int			setWidth,
		int			setHeight,
		bool		isFullScreen,
		D3DDEVTYPE	deviceType)
	{
		SPConfig config;
		config.workingWidth = setWidth;
		config.workingHeight = setHeight;
		config.windowWidth = setWidth;
		config.windowHeight = setHeight;
		config.windowed = !isFullScreen;
		config.deviceType = deviceType;
		SPConfigManager::GetSingleton().SetConfig(config);
		isLockFPS = true;
		lockedFPS = 60;
		isExiting = false;
		isGameThreadRunning = false;
		isRendering = false;
		isNeedToRender = true;
		hInstance = setHInstance;
		hGameThreadExited = CreateEvent( NULL, FALSE, FALSE, NULL );
	}

	SPGame::SPGame(	HINSTANCE setHInstance)
	{
		SPConfigManager::GetSingleton().LoadConfig("config.cfg");
		isLockFPS = true;
		lockedFPS = 60;
		isExiting = false;
		isGameThreadRunning = false;
		isRendering = false;
		isNeedToRender = true;
		hInstance = setHInstance;
		hGameThreadExited = CreateEvent( NULL, FALSE, FALSE, NULL );
	}	
	#pragma endregion

	#pragma region Destructor
	SPGame::~SPGame(void)
	{		
		//UnloadContent();
		//CleanUp();
	}
	#pragma endregion

	#pragma region Initialize
	bool SPGame::BuildEngine()
	{
		//HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

		SPLogHelper::WriteLog("============= Game Starting =============");

		SPConfig config = SPConfigManager::GetSingleton().GetCurrentConfig();

		// Initialize D3D with default config.
		if (!SPDevice::GetSingleton().InitializeD3D(config))
		{
			SPMessageHelper::Msg("Failed to initialize D3D!");
			SPLogHelper::WriteLog("[Game] ERROR: Failed to initialize D3D!");
			return false;
		}

		return true;
	}
	#pragma endregion

	#pragma region Game
	bool SPGame::Start()
	{
		SPConfig config = SPConfigManager::GetSingleton().GetCurrentConfig();

		//
		// Initialize window with default config.
		// 

		if (!SPWindow::GetSingleton().Initialize(
			hInstance, config.windowWidth, config.windowHeight, 
			!config.windowed))
		{
			SPMessageHelper::Msg("Failed to initialize game window!");
			SPLogHelper::WriteLog("[Game] ERROR: Failed to initialize game window!");
			return false;
		}		

		//
		// Start game thread
		// 

		isGameThreadRunning = CloseHandle(
			CreateThread(NULL, 0, GameThreadProc, (void*)this, 0, NULL)) == TRUE;

		SPWindow::GetSingleton().EnterMsgLoop();

		return true;
	}

	bool SPGame::Exit()
	{
		isExiting = true;

		BOOL resutl = PostMessage(SPWindow::GetSingleton().GetHWnd(), WM_GAMETHREADEXIT, NULL, NULL);		

		return false;
	}

	bool SPGame::ExitGameThread()
	{
		SPLogHelper::WriteLog("============= Game Exiting =============");

		isExiting = true;
		WaitForSingleObject(hGameThreadExited, INFINITE);
		//while(IsGameThreadRunning())
		//{
		//	Sleep(500);
		//}

		CleanUp();

		SPLogHelper::WriteLog("============= Game Exited! =============\n\n");

		PostQuitMessage(0);

		return true;
	}

	DWORD WINAPI SPGame::GameThreadProc(PVOID pParam)
	{
		CoInitializeEx(NULL, COINIT_MULTITHREADED);

		SPLogHelper::WriteLog("[Game] Game Thread Starts.");

		SPGame* currentGame = (SPGame*)pParam;

		//
		// Check if the engine is successfully built.
		// 

		if (!currentGame->BuildEngine())
		{
			SPLogHelper::WriteLog("[Game] ERROR: Failed To Build Engine!");
			return false;
		}

		//
		// Initialize components and load contents.
		// 

		if(!currentGame->InitializeComponents())
		{
			SPLogHelper::WriteLog("[Game] ERROR: Failed To Initialize Game!");
			return false;
		}

		if(!currentGame->Load())
		{
			SPLogHelper::WriteLog("[Game] ERROR: Failed To Load Game Content!");
			return false;
		}

		SPLogHelper::WriteLog("============= Game Starts! =============");

		SPWindow::GetSingleton().Update();
		SPWindow::GetSingleton().Show();
		SPWindow::GetSingleton().Focus();

		while (true)
		{
			//
			// Get time in millisecond.
			// 

			static float lastTimeMS = (float)timeGetTime();
			
			float currentTimeMS = (float)timeGetTime();
			float timeDeltaS = (currentTimeMS - lastTimeMS) * 0.001f;
			lastTimeMS = currentTimeMS;		

			if(currentGame->isExiting)
			{
				currentGame->isGameThreadRunning = false;
				break;
			}

			//
			// Render and calculate render time
			// 

			float renderTimeBeginMS = (float)timeGetTime();

			if (!currentGame->Render(timeDeltaS))
			{
				currentGame->isGameThreadRunning = false;
				currentGame->Exit();
				break;
			}

			float renderTimeEndMS = (float)timeGetTime();

			float renderTimeDeltaMS = renderTimeEndMS - renderTimeBeginMS;

			//
			// Lock FPS
			// 

			if (currentGame->IsLockFPS())
			{
				float timePerFrameMS = 1000.0f / currentGame->GetLockedFPS();

				if (renderTimeDeltaMS < timePerFrameMS)
				{
					Sleep(timePerFrameMS - renderTimeDeltaMS);
				}
			}
			
			
		}

		//
		// Don't know why program just crashed when exited in XP without sleeping.
		// 
		// 

		//Sleep(1000);

		if(!currentGame->UnloadContent())
		{
			SPLogHelper::WriteLog("[Game] ERROR: Failed To Unload Game Content!");
			return false;
		}

		currentGame->isGameThreadRunning = false;

		CoUninitialize();

		SetEvent(currentGame->hGameThreadExited);

		return 0;
	}

	bool SPGame::Render(float timeDeltaS)
	{
		elapsedLastTimeS = timeDeltaS;

		if (isExiting)
		{
			return false;
		}

		SPWindow::GetSingleton().Update(timeDeltaS);

		bool backgroundLoading = IsBackgroundLoading();

		if (backgroundLoading)
		{
			UpdateWhileLoading(timeDeltaS);
		}
		else if (!Update(timeDeltaS))
		{
			SPLogHelper::WriteLog("[Game] WARNING: Failed To Update!");
			return false;
		}

		HRESULT hr = E_FAIL;

		if (true)
		{
			// Clear target buffer and z buffer
			Refresh(0xffffffff);

			isRendering = true;

			SPDevice::GetSingleton().GetD3DDevice()->BeginScene();
		
			if (backgroundLoading)
			{
				LockDrawingWhileLoading();
				DrawWhileLoading(timeDeltaS);
				UnlockDrawingWhileLoading();
			}
			else if(!Draw(timeDeltaS))
			{
				SPLogHelper::WriteLog("[Game] WARNING: Failed To Draw!");
				return false;
			}

			SPDevice::GetSingleton().GetD3DDevice()->EndScene();

			isRendering = false;

			hr = SPDevice::GetSingleton().GetD3DDevice()->Present(0, 0, 0, 0);
		}

		// Get current config.
		SPConfig currentConfig = SPConfigManager::GetSingleton().GetCurrentConfig();

		// Reset full screen if window is just active.
		if (!SPConfigManager::GetSingleton().GetCurrentConfig().windowed 
			&& SPWindow::GetSingleton().IsJustActive())
		{
			if (ResetDevice(currentConfig))
			{
				isNeedToRender = true;
			}

			return true;
		}

		if (FAILED(hr))
		{
			isNeedToRender = false;

			//SPLogHelper::WriteLog("[Game] WARNING: Render Frame Failed!");

			HRESULT dhr = SPDevice::GetSingleton().GetD3DDevice()->TestCooperativeLevel();

			if (dhr == D3DERR_DEVICELOST || dhr == D3DERR_DEVICENOTRESET)
			{
				

				if (currentConfig.windowed)
				{
					if(ResetDevice(currentConfig))
					{
						isNeedToRender = true;
						return true;
					}
				}
				else
				{
					if (SPWindow::GetSingleton().IsActive())
					{
						if(ResetDevice(currentConfig))
						{
							isNeedToRender = true;
							return true;
						}
					}
					else
					{
						currentConfig.windowed = true;

						if(ResetDevice(currentConfig))
						{
							isNeedToRender = true;
							return true;
						}
					}
				}

				return true;
			}
		}

		return true;
	}

	bool SPGame::InitializeComponents()
	{
		SPLogHelper::WriteLog("[Game] Initializing Game ...");

		// Create component manager.
		SPComponentManager::GetSingleton();
		SPPointer<SPComponentManager> componentManager = SPComponentManager::GetSingletonPtr();

		// Create component singletons.		
		SPTextureManager::GetSingleton();
		SPVideoManager::GetSingleton();
		SPSpriteManager::GetSingleton();
		SPSpriteManager3D::GetSingleton();
		SPCamera::GetSingleton();
		SPLightManager::GetSingleton();
		SPMaterialManager::GetSingleton();
		SPInputManager::GetSingleton();
		SPFontManager::GetSingleton();
		SPFontWriter::GetSingleton();
		SPScreenManager::GetSingleton();
		SPSoundManager::GetSingleton();
		SPShaderManager::GetSingleton();
		SPParticleSystemManager::GetSingleton();
		SPFilePacker::GetSingleton();

		// Register components.
		componentManager->RegisterComponent(L"texture", SPTextureManager::GetSingletonPtr());			
		componentManager->RegisterComponent(L"video", SPVideoManager::GetSingletonPtr());
		componentManager->RegisterComponent(L"particle", SPParticleSystemManager::GetSingletonPtr());
		componentManager->RegisterComponent(L"camera", SPCamera::GetSingletonPtr());
		componentManager->RegisterComponent(L"light", SPLightManager::GetSingletonPtr());
		componentManager->RegisterComponent(L"material", SPMaterialManager::GetSingletonPtr());
		componentManager->RegisterComponent(L"input", SPInputManager::GetSingletonPtr());
		componentManager->RegisterComponent(L"screen", SPScreenManager::GetSingletonPtr());
		componentManager->RegisterComponent(L"sound", SPSoundManager::GetSingletonPtr());		
		componentManager->RegisterComponent(L"shader", SPShaderManager::GetSingletonPtr());
		componentManager->RegisterComponent(L"font", SPFontManager::GetSingletonPtr());		

		Initialize();

		componentManager->RegisterComponent(L"sprite_3d", SPSpriteManager3D::GetSingletonPtr());
		componentManager->RegisterComponent(L"font_writer", SPFontWriter::GetSingletonPtr());		
		componentManager->RegisterComponent(L"sprite", SPSpriteManager::GetSingletonPtr());

		// Register custom components.
		SPComponentFactory<FPSDisplayer>::GetSingleton().Produce(
			L"fps", SPComponentManager::GetSingleton());

		// Enable components to be updated and drawn.
		SPCamera::GetSingleton().Enable();
		SPVideoManager::GetSingleton().Enable();
		SPTextureManager::GetSingleton().Enable();
		SPSpriteManager::GetSingleton().Enable();
		SPSpriteManager3D::GetSingleton().Enable();
		SPInputManager::GetSingleton().Enable();
		SPFontManager::GetSingleton().Enable();
		SPFontWriter::GetSingleton().Enable();
		SPSoundManager::GetSingleton().Enable();
		SPScreenManager::GetSingleton().Enable();
		SPParticleSystemManager::GetSingleton().Enable();

		// Enable custom component.
		SPComponentManager::GetSingleton().GetComponent(L"fps")->Enable();

		if (!SPComponentManager::GetSingleton().Initialize())
		{
			return false;
		}		

		return true;
	}

	bool SPGame::Initialize()
	{
		return true;
	}

	bool SPGame::LoadContent()
	{
		SPLogHelper::WriteLog("[Game] Loading Game Content ...");

		if (!SPComponentManager::GetSingleton().Load())
		{
			return false;
		}

		return true;
	}

	bool SPGame::UnloadContent()
	{
		if(!SPComponentManager::GetSingleton().Unload())
		{
			return false;
		}		

		return true;
	}

	bool SPGame::Update(float timeDelta)
	{
		if (!SPComponentManager::GetSingleton().Update(timeDelta))
		{
			return false;
		}

		return true;
	}

	bool SPGame::Draw(float timeDelta)
	{	
		if (!SPComponentManager::GetSingleton().Draw(timeDelta))
		{
			return false;
		}

		return true;
	}

	void SPGame::CleanUp()
	{
		SPWindow::GetSingleton().UnregisterWindowClass();

		return;
	}	
	#pragma endregion

	bool SPGame::Refresh( D3DCOLOR color )
	{
		SPDevice::GetSingleton().GetD3DDevice()->
			Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, color, 1.0f, 0); 

		return true;
	}

	int SPGame::GetWidth()
	{
		return SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth;
	}

	int SPGame::GetHeight()
	{
		return SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight;;
	}

	bool SPGame::ResetDevice( SPConfig config )
	{
		SPLogHelper::WriteLog("[Game] Ready to Reset Device.");

		SPLogHelper::WriteLog("[Game] Unloading Game Content ...");

		if(!UnloadContent())
		{
			SPLogHelper::WriteLog("[Game] ERROR: Failed to unload game content!");
			return false;
		}

		SPLogHelper::WriteLog("[Game] Reseting Device ...");
		if (!SPDevice::GetSingleton().ResetDevice(config))
		{
			SPLogHelper::WriteLog("[Game] ERROR: Failed to reset d3d device!");
			return false;
		}

		SPLogHelper::WriteLog("[Game] Completed Reseting Device.");

		SPLogHelper::WriteLog("[Game] Reloading Game Content ...");
		if(!ReloadContent())
		{
			SPLogHelper::WriteLog("[Game] ERROR: Failed to reload content after reseting device!");

			return false;
		}

		return true;
	}

	bool SPGame::ReloadContent()
	{
		if(!SPComponentManager::GetSingleton().Reload())
		{
			return false;
		}

		return true;
	}

	bool SPGame::IsRendering()
	{
		return isRendering;
	}

	float SPGame::GetLastTimeS()
	{
		return elapsedLastTimeS;
	}

	bool SPGame::ApplyConfig( SPConfig config )
	{
		LockDrawingWhileLoading();

		SPConfig oldConfig = SPConfigManager::GetSingleton().GetCurrentConfig();

		SPConfigManager::GetSingleton().SetConfig(config);			

		if(!ResetDevice(config))
		{
			SPConfigManager::GetSingleton().SetConfig(oldConfig);
			UnlockDrawingWhileLoading();
			//exit(0);
			return false;
		}

		SPWindow::GetSingleton().AdjustMainWindow(
			!config.windowed,
			config.windowWidth, 
			config.windowHeight);

		UnlockDrawingWhileLoading();

		return true;
	}

	bool SPGame::IsGameThreadRunning()
	{
		return isGameThreadRunning;
	}

	bool SPGame::Load()
	{
		BeginBackgroundLoading();

		CloseHandle(
			CreateThread(NULL, 0, BackgroundLoadingThread, (void*)this, 0, NULL));

		return IsBackgroundLoading();
	}

	DWORD WINAPI SPGame::BackgroundLoadingThread( PVOID pParam )
	{
		((SPGame*)pParam)->LoadContent();

		((SPGame*)pParam)->EndBackgroundLoading();

		return 0;
	}

	bool SPGame::IsBackgroundLoading()
	{
		backgroundLoadingLock.Lock();
		bool result = isBackgroundLoading;
		backgroundLoadingLock.Unlock();

		return result;
	}

	void SPGame::EndBackgroundLoading()
	{
		backgroundLoadingLock.Lock();
		isBackgroundLoading = false;
		backgroundLoadingLock.Unlock();
	}

	void SPGame::BeginBackgroundLoading()
	{
		backgroundLoadingLock.Lock();
		isBackgroundLoading = true;
		backgroundLoadingLock.Unlock();
	}

	bool SPGame::UpdateWhileLoading( float timeDelta )
	{
		SPFontManager::GetSingleton().Update(timeDelta);
		SPFontWriter::GetSingleton().Update(timeDelta);			
		SPSoundManager::GetSingleton().Update(timeDelta);
		SPVideoManager::GetSingleton().Update(timeDelta);
		SPTextureManager::GetSingleton().Update(timeDelta);
		SPSpriteManager::GetSingleton().Update(timeDelta);			
		SPSpriteManager3D::GetSingleton().Update(timeDelta);

		return true;
	}

	bool SPGame::DrawWhileLoading( float timeDelta )
	{
		SPFontWriter::GetSingleton().Draw(timeDelta);			
		SPSpriteManager::GetSingleton().Draw(timeDelta);			
		SPSpriteManager3D::GetSingleton().Draw(timeDelta);

		return true;
	}

	bool SPGame::LockDrawingWhileLoading()
	{
		drawWhileLoadingLock.Lock();

		return true;
	}

	bool SPGame::UnlockDrawingWhileLoading()
	{
		drawWhileLoadingLock.Unlock();

		return true;
	}

	bool SPGame::IsLockFPS()
	{
		return isLockFPS;
	}

	int SPGame::GetLockedFPS()
	{
		return lockedFPS;
	}

	bool SPGame::LockFPSAt( int fps )
	{
		if (fps <= 0)
		{
			return false;
		}

		isLockFPS = true;
		
		lockedFPS = fps;

		return true;
	}

	bool SPGame::UnlockFPS()
	{
		isLockFPS = false;

		return true;
	}

	bool SPGame::LockFPS()
	{
		isLockFPS = true;

		return true;
	}



}