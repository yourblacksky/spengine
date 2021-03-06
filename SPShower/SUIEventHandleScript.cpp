#include "StdAfx.h"
#include "SUIEventHandleScript.h"
#include "SScriptManager.h"

bool SUIEventHandleScript::SetStringScript( SPString setScript )
{
	stringScript = setScript;
	script = new KScript::Script();
	script->LoadStringScript(setScript, L"SUIEvent");
	return true;
}

bool SUIEventHandleScript::Function( SUIEventPtr e )
{
	if (stringScript.size() <= 1)
	{
		return false;
	}

	SScriptManager::GetSingleton().SetInsertPosFront(0);
	SScriptManager::GetSingleton().ExecuteInnerScript(script);
	SScriptManager::GetSingleton().SetInsertPosBack();

	return true;
}

SUIEventHandleScript::SUIEventHandleScript( SPString setScript )
{
	SetStringScript(setScript);
}

