#pragma once
#include <SPGame.h>
#include <SPAdventureGame.h>

class AVGTest : public SPEngine::SPAdventureGame
{
	//AVGTest();
public:	

	AVGTest(HINSTANCE hInstance);
	~AVGTest();

	//virtual bool LoadContent();

	virtual bool Update( float timeDelta );

	//virtual void CleanUp();

	//virtual bool UnloadContent();

	virtual bool Initialize();

	//virtual bool Start();

	//virtual bool Draw( float timeDelta );

};