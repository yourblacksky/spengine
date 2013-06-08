#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIEventHandler.h"

using namespace KScript;

class SSFWait;

class SUIWaitHandler : public SUIEventHandler
{
public:
	SSFWait* ssf;

	SUIWaitHandler(SSFWait* wc);

	virtual bool Function( SUIEventPtr e );
};

class SSFWait : public SScriptFunction
{
public:
	float totalTimeS;
	SUIComponentPtr waitComponent;
	SUIEventHandlerPtr originHandler;
	SUIEventHandlerPtr waitHandler;
	bool isClicked;

public:
	SSFWait()
	{
		waitHandler = new SUIWaitHandler(this);
		originHandler = NULL;
		waitComponent = NULL;
		isClicked = false;
		totalTimeS = 0;
	}

	bool Function(VariableMap args, bool isRead)
	{
		float waitTimeS = 0;

		//
		// If skip mode on and not auto mode, just skip waiting.
		// 

		if (SScriptManager::GetSingleton().IsSkipModeOn()
			&& (SScriptManager::GetSingleton().GetSkipMode() == SScriptManager::SkipAll
			|| (SScriptManager::GetSingleton().GetSkipMode() == SScriptManager::SkipRead && isRead )))
		{
			if (waitComponent)
			{
				waitComponent->catchMouseLeftClick = originHandler;
				originHandler = NULL;
				waitComponent = NULL;
			}

			refreshScreen = true;
			waiting = false;
			return true;
		}

		//
		// else if time set, wait until time out.
		// 

		if (IsSet(L"time", args))
		{
			waitTimeS = SPStringHelper::StringToFloat(args[L"time"].value);

			args.erase(L"time");
		}

		if (!waiting)
		{
			waiting = true;
			totalTimeS = 0;
		}

		totalTimeS += SPGameManager::GetSingleton().GetGame()->GetLastTimeS();

		refreshScreen = true;

		if (totalTimeS > waitTimeS)
		{
			if (waitComponent)
			{
				waitComponent->catchMouseLeftClick = originHandler;
				originHandler = NULL;
				waitComponent = NULL;
			}

			totalTimeS = 0;
			waiting = false;
			return true;
		}

		//
		// Wait click
		// 

		if (IsSet(L"click",args))
		{
			//
			// If auto mode, wait till auto wait time out.
			// 

			//if (SScriptManager::GetSingleton().IsSkipModeOn())
			//{
			//	if (SScriptManager::GetSingleton().GetSkipMode() == SScriptManager::SkipAuto)
			//	{
			//		if (!waiting)
			//		{
			//			waiting = true;
			//			totalTimeS = 0;
			//		}

			//		totalTimeS += SPGameManager::GetSingleton().GetGame()->GetLastTimeS();

			//		refreshScreen = true;

			//		if (totalTimeS > SScriptManager::GetSingleton().GetAutoWaitTimeS())
			//		{
			//			totalTimeS = 0;
			//			waiting = false;
			//			return true;
			//		}
			//	}
			//}
			
			if (SPStringHelper::StringToInt(args[L"click"].value) != 0)
			{
				if (IsSet(L"component", args))
				{
					SPString name = args[L"component"].value;

					args.erase(L"component");

					waitComponent = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(name);

					if (waitComponent)
					{
						if (!waiting || waitComponent->catchMouseLeftClick != waitHandler)
						{
							originHandler = waitComponent->catchMouseLeftClick;
							waitComponent->catchMouseLeftClick = waitHandler;
						}
						else if (isClicked)
						{
							isClicked = false;
							waitComponent->catchMouseLeftClick = originHandler;
							originHandler = NULL;
							waitComponent = NULL;
							refreshScreen = false;
							waiting = false;
							return true;
						}

						refreshScreen = true;
						waiting = true;
						return true;
					}
				}

				if (refreshScreen == false)
				{
					refreshScreen = true;
					waiting = true;
					return true;
				}		

				if (SPInputManager::GetSingleton().GetMouse()->ButtonJustDown(0))
				{
					SUIManager::GetSingleton().InterceptMouseBotton(0);
					refreshScreen = true;
					waiting = false;
					return true;
				}
			}		

			args.erase(L"click");
		}

		waiting = true;
		return false;
	}
};

SUIWaitHandler::SUIWaitHandler(SSFWait* wc)
{
	ssf = wc;
}

bool SUIWaitHandler::Function( SUIEventPtr e )
{
	ssf->isClicked = true;

	return true;
}