#pragma once
#include <SPBaseScreen.h>
#include <SPTexture.h>
#include <SPFont.h>
#include <SPPointer.h>
#include <List>
#include "textBox.h"
#include <string>

using namespace SPEngine;

class Test : public SPEngine::SPBaseScreen {

	float countDown;
	SPTexturePtr logo;
	SPTexturePtr blank;
	SPFontPtr font;
	float logoPosition;

	//add
	SPTexturePtr tex;
	bool textWriter(list<pair<SPFontPtr, string>> textList, textBox rect, string punctuations);

public:
	Test(void);
	~Test(void);

	bool HandleInput( float timeDelta );
	bool Update(float timeDelta);
	bool Draw(float timeDelta);
	bool Load();
	bool Unload();
	bool Initialize();
	//add
	SPTexturePtr TurnGray(SPTexturePtr a);
};
