#include "StdAfx.h"
#include "SUIList.h"
#pragma warning(disable:4244)
#pragma warning(disable:4018)
#include "SUIManager.h"

SUIList::SUIList(void)
{
	maxItemNum = 255;
	scrollPosition = 0;
	type = Vertacal;
	maxLength = 0;
}


SUIList::~SUIList(void)
{
}

bool SUIList::SetScrollPosition( float setPos )
{
	if (setPos < 0)
	{
		setPos = 0;
	}

	if (setPos > 1)
	{
		setPos = 1;
	}

	scrollPosition = setPos;

	return true;
}

float SUIList::GetScrollPosition()
{
	return scrollPosition;
}

bool SUIList::Update( float timeDelta )
{
	SUIComponentComposite::Update(timeDelta);

	// Keep list in size.
	while(children.size() > maxItemNum)
	{
		children.front()->SetFather(NULL);
		SUIManager::GetSingleton().GetCurrentScreen()->RemoveComponent(children.front()->GetName());
		children.pop_front();
	}

	return true;
}

bool SUIList::Draw( float timeDelta )
{
	// Render children UI component.

	int currentPos = 0;
	int currentLength = 0;
	maxLength = 0;

	// Keep list in size.
	while(children.size() > maxItemNum)
	{
		children.front()->SetFather(NULL);
		SUIManager::GetSingleton().GetCurrentScreen()->RemoveComponent(children.front()->GetName());
		children.pop_front();
	}

	// iter must be assigned after deletion.
	SPComposite::ChildIterator iter = children.begin();

	// Calculate max length.
	while(iter != children.end())
	{
		if (*iter)
		{
			if (type == Vertacal)
			{
				maxLength += (*iter)->GetHeight();
			}
			else
			{
				maxLength += (*iter)->GetWidth();
			}

			iter++;
		}
		else
		{
			iter = children.erase(iter);
		}
	}

	// Get the target length.
	int targetLenght = (maxLength - GetHeight()) * scrollPosition;

	if (targetLenght < 0)
	{
		targetLenght = 0;
	}

	currentPos = -targetLenght;

	// Loop through list item.
	iter = children.begin();
	while(iter != children.end())
	{
		// Check if target in list rectangle.
		if (currentLength + (*iter)->GetHeight() > targetLenght)
		{
			// Get the relative position.
			D3DXVECTOR2 originalPos = (*iter)->GetPosition();
			D3DXVECTOR2 realPos = (*iter)->GetPosition();

			if (type == Vertacal)
			{
				realPos.y += currentPos;
			}
			else
			{
				realPos.x += currentPos;
			}

			// Set real position and render.
			(*iter)->SetPosition(realPos);
			(*iter)->Render(timeDelta);

			// Reset position.
			(*iter)->SetPosition(originalPos);

			// Update current position.
			if (type == Vertacal)
			{
				currentPos = realPos.y + (*iter)->GetHeight();

				if (currentPos > GetHeight())
				{
					break;
				}
			}
			else
			{
				currentPos = realPos.x + (*iter)->GetWidth();

				if (currentPos > GetWidth())
				{
					break;
				}
			}
		}
		else
		{
			// Update current length.
			if (type == Vertacal)
			{				
				currentLength += (*iter)->GetHeight();	
				currentPos = currentLength - targetLenght;
			}
			else
			{				
				currentLength += (*iter)->GetWidth();
				currentPos = currentLength - targetLenght;
			}
		}	

		iter++;
	}	

	return true;
}

bool SUIList::SetDirection( ListType setType )
{
	type = setType;

	return true;
}

SUIList::ListType SUIList::GetDirection()
{
	return type;
}

bool SUIList::SetMaxItemNum( int setNum )
{
	maxItemNum = setNum;

	return true;
}

int SUIList::GetMaxItemNum()
{
	return maxItemNum;
}

bool SUIList::LoadFromString( SPString stringStream )
{
	return true;
}

SPString SUIList::SaveAsString()
{
	SPString result = SPStringHelper::XMLSurroundWith(PropertiesToString(),L"SUIL");

	return result;
}

bool SUIList::Scroll( int delta )
{
	float deltaPos = (float)delta / (maxLength - GetHeight());

	SetScrollPosition(scrollPosition + deltaPos);

	return true;
}

bool SUIList::ClearChild()
{
	SPComposite::ChildIterator iter = children.begin();

	// Calculate max length.
	while(iter != children.end())
	{
		if (*iter)
		{
			SUIManager::GetSingleton().GetCurrentScreen()->RemoveComponent((*iter)->GetName());
		}

		iter = children.erase(iter);
	}

	return true;
}
