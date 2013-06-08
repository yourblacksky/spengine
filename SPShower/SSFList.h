#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIList.h"

#pragma warning(disable:4244)

using namespace KScript;
class SSFList : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		if (!SUIManager::GetSingleton().GetCurrentScreen())
		{
			return true;
		}

		if (IsSet(L"name", args))
		{
			SUIListPtr list;

			SPString name = args[L"name"].value;			

			list = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(name);

			if (!list)
			{
				list = new SUIList();
				list->SetName(name);

				SUIManager::GetSingleton().GetCurrentScreen()->AddComponent(list);
			}

			SetComponentProperties(list, args);

			if (IsSet(L"scroll_position",args))
			{
				list->SetScrollPosition(SPStringHelper::StringToFloat(args[L"scroll_position"].value));

				args.erase(L"scroll_position");
			}

			if (IsSet(L"scroll_position_delta",args))
			{
				list->SetScrollPosition(list->GetScrollPosition() + 
					SPStringHelper::StringToFloat(args[L"scroll_position_delta"].value));

				args.erase(L"scroll_position_delta");
			}

			if (IsSet(L"scroll_delta",args))
			{
				list->Scroll(SPStringHelper::StringToInt(args[L"scroll_delta"].value));

				args.erase(L"scroll_delta");
			}

			if (IsSet(L"max_item", args))
			{
				list->SetMaxItemNum(SPStringHelper::StringToInt(args[L"max_item"].value));

				args.erase(L"max_item");
			}

			if (IsSet(L"direction", args))
			{
				SPString direction = args[L"direction"].value;

				if (direction == L"vertical")
				{
					list->SetDirection(SUIList::Vertacal);
				}

				if (direction == L"horizontal")
				{
					list->SetDirection(SUIList::Horizontal);
				}

				args.erase(L"direction");
			}

			if (IsSet(L"clear", args))
			{
				if (SPStringHelper::StringToInt(args[L"clear"].value) != 0)
				{
					list->ClearChild();
				}

				args.erase(L"clear");
			}

			SUIManager::GetSingleton().GetCurrentScreen()->SetCurrentComponent(list);

			args.erase(L"name");
		}

		return true;
	}
};

