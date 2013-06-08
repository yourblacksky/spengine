#include "StdAfx.h"
#include "TestScreen.h"
#include <SPEngine.h>
#include <SPFontWriter.h>
#include <SPVideoManager.h>

float angle = 0;

TestScreen::TestScreen(void)
{
	transitionOnTime = 1;
	transitionOffTime = 1;
	transitionPosition = 0;
	video = NULL;	
}


TestScreen::~TestScreen(void)
{	
	Unload();
}

bool TestScreen::Load()
{
	video =		SPVideoManager::GetSingleton().GetVideo(L"logo01.mpg");
	texture =	SPTextureManager::GetSingleton().GetTexture(L"sicily.jpg");
	blank =		SPTextureManager::GetSingleton().GetTexture(L"blank.jpg");
	anime =		SPTextureManager::GetSingleton().GetAnime(L"loading.png", 2, 4, 30);
	font =		SPFontManager::GetSingleton().CreateFont(L"yh_100", 100, 0, 1, 5, false, L"裏罷囘菜");
	tex3D =		SPTextureManager::GetSingleton().GetTexture(L"loading.png");
	videoTexture = SPTextureManager::GetSingleton().GetVideo(L"logo01.mpg");
	sound = SPSoundManager::GetSingleton().CreateSound(L"menu", L"menu.ogg");
	SPSoundManager::GetSingleton().CreateSoundTrack(L"BGM");
	SPSoundManager::GetSingleton().PlaySoundInTrack(L"menu", L"BGM");
	pixelShader = new SPEffect(L"testPS.txt");
	pixelShader->SetTexture(1, texture);

	p = new Print(this);

	print.Load(L"test.ks");

	print.AddExtension(L"print", p);

	return true;
}

bool TestScreen::Update( float timeDelta )
{
	SPSoundManager::GetSingleton().PlayTrack(L"BGM");

	return true;
}

bool TestScreen::HandleInput(float timeDelta)
{
	if (SPInputManager::GetSingleton().GetKeyboard()->ButtonDown(DIK_W) || 
		SPInputManager::GetSingleton().GetMouse()->ButtonDown(0) ||
		SPInputManager::GetSingleton().GetXController(0)->ButtonDown(XINPUT_GAMEPAD_DPAD_UP) ||
		SPInputManager::GetSingleton().GetXController(0)->ButtonDown(XINPUT_GAMEPAD_A))
	{
		//GetCamera()->Walk(10 * timeDelta);
		SPCamera::GetSingleton().Fly(10 * timeDelta);
	}

	if (SPInputManager::GetSingleton().GetKeyboard()->ButtonDown(DIK_S) ||
		SPInputManager::GetSingleton().GetMouse()->ButtonDown(1)||
		SPInputManager::GetSingleton().GetXController(0)->ButtonDown(XINPUT_GAMEPAD_DPAD_DOWN)||
		SPInputManager::GetSingleton().GetXController(0)->ButtonDown(XINPUT_GAMEPAD_B))
	{
		//GetCamera()->Walk(-10 * timeDelta);
		SPCamera::GetSingleton().Fly(-10 * timeDelta);
	}

	if(SPInputManager::GetSingleton().GetMouse()->IsScrolledUp())
	{
		SPCamera::GetSingleton().Walk(1);
	}

	if(SPInputManager::GetSingleton().GetMouse()->IsScrolledDown())
	{
		SPCamera::GetSingleton().Walk(-1);
	}

	if(SPInputManager::GetSingleton().GetKeyboard()->ButtonJustDown(DIK_P))
	{
		video->Play();
	}

	if(SPInputManager::GetSingleton().GetKeyboard()->ButtonJustDown(DIK_O))
	{
		video->Stop();
	}
	
	//camera.Walk(inputManager.GetMouseWheelPos()*timeDelta);

	SPInputManager::GetSingleton().GetXController(0)->SetVibration((int)(
		SPInputManager::GetSingleton().GetXController(0)->MagnitudeLeft() * 60000),
		(int)SPInputManager::GetSingleton().GetXController(0)->MagnitudeRight() * 60000);

	SPConfig config1;
	SPConfig config2;

	config1.windowWidth = 1024;
	config1.windowHeight = 768;
	config1.workingHeight = 600;
	config1.workingWidth = 800;

	config2.windowed = false;
	config2.windowWidth = 1920;
	config2.windowHeight = 1080;
	config2.workingWidth = 800;
	config2.workingHeight = 600;
	

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

bool TestScreen::Draw( float timeDelta )
{
	SPTexturePtr target = SPTextureManager::GetSingleton().CreateRenderTarget(512, 512);

	//target->Fill(0x00000000);

	//videoTexture.RenderByPosition(D3DXVECTOR3(0,2,0));
	SPSpriteManager3D::GetSingleton().RenderByPosition(videoTexture, NULL, D3DXVECTOR3(0,2,0));

	
	//video.Draw(timeDelta);

	//ID3DXMesh* mesh = 0; 
	// Set rotation
	D3DXMATRIX Rx, Ry; 
	static float x = 0.0f;
	D3DXMatrixRotationX(&Rx, x); 
	x += timeDelta;
	static float y = 0.0f; 
	D3DXMatrixRotationY(&Ry, y); 
	y += timeDelta; 

	// Reset
	if( y >= 6.28f ) 
		y = 0.0f; 
	if( x >= 6.28f ) 
		x = 0.0f; 

	// Construct rotation matrix
	D3DXMATRIX p = Rx * Ry; 
	//D3DXCreateTeapot(GetDevice(), &mesh, 0); 

	//GetDevice()->SetTransform(D3DTS_WORLD, &p); 
	//mesh->DrawSubset(0); 
	//mesh->Release(); 
	//mesh = 0;

	static float rotation = 0;
	rotation += timeDelta;

	// Render texture
	SPSpriteManager::GetSingleton().RenderWithScaling(texture, NULL,
		D3DXVECTOR3(100, 200, 0.4f),
		D3DXVECTOR2(0.5,0.5), SPColor::White, NULL);

	SPSpriteManager::GetSingleton().RenderWithRotation(texture, NULL, 
		D3DXVECTOR3(200, 300, 0.3f),
		rotation, SPColor::White, NULL);

	SPRectangle srcRect(100, 100, 200, 200);
	SPRectangle rect(0, 0, 800, 600);
	

	RECT r = {0,0,800,600};

	static string text = "込込込\n込込込込込込込込込込込込込込";

	/*if(GetInput()->GetXController(0)->ButtonJustDown(XINPUT_GAMEPAD_A) ||
		GetInput()->keyboard->ButtonJustDown(DIK_UP)||
		GetInput()->mouse->ButtonJustDown(0))
	{
		text += "込";
	}

	if(GetInput()->GetXController(0)->ButtonJustDown(XINPUT_GAMEPAD_B) ||
		GetInput()->keyboard->ButtonJustDown(DIK_LALT)||
		GetInput()->mouse->ButtonJustDown(1))
	{
		text.pop_back();
		text.pop_back();
	}*/
	SPSpriteManager::GetSingleton().Render(target, NULL, D3DXVECTOR3(0, 0, 0),
		SPColor::White, NULL);

	//SPSpriteManager::GetSingleton().RenderOnScreen(texture, NULL, rect, SPColor::White, 1, NULL);
	SPSpriteManager::GetSingleton().RenderCentered(texture, NULL, srcRect, D3DXVECTOR3(600, 300, 0.4f),
		1.5f, rotation, SPColor::White, NULL);
	SPSpriteManager::GetSingleton().ARenderWithRotation(anime, NULL, D3DXVECTOR3(100, 200, 0.4f),
		rotation,  SPColor::White, target);

	SPSpriteManager::GetSingleton().ARenderCentered(anime, NULL, 400, 300, 2.5f, 0, SPColor::Red, 0, target);

	if (state == Active)
	{
		SPFontWriter::GetSingleton().Write(font, NULL, SPStringHelper::ToWString(text), -1, rect,
			(TextFormat)(RightReading | Center | WordBreak ), 
			SPColor::LightBlue, 0, 1, target);
		SPFontWriter::GetSingleton().WriteCentered(font, NULL, 
			L"こんにちは", D3DXVECTOR2(400,500), SPColor::Green, 0, 0, NULL);
	
		print.Execute();

		RECT winRect;
		GetClientRect(SPWindow::GetSingleton().GetHWnd(), &winRect);

		SPFontWriter::GetSingleton().WriteCentered(font, pixelShader,
			SPStringHelper::ToWString(winRect.right), 
			D3DXVECTOR2(400,300), SPColor::Red, 0, 0, NULL);
		SPFontWriter::GetSingleton().WriteCentered(font, pixelShader,
			SPStringHelper::ToWString(winRect.bottom), 
			D3DXVECTOR2(400,350), SPColor::Red, 0, 0, NULL);


		SPFontWriter::GetSingleton().WriteCentered(font, pixelShader, 
			SPStringHelper::ToWString(
			SPInputManager::GetSingleton().GetMouse()->GetPositionX()), 
			D3DXVECTOR2(200,300), SPColor::Red, 0, 0, target);
		SPFontWriter::GetSingleton().WriteCentered(font, pixelShader,
			SPStringHelper::ToWString(
			SPInputManager::GetSingleton().GetMouse()->GetPositionY()), 
			D3DXVECTOR2(200,350), SPColor::Red, 0, 0, target);
	}


	SPSpriteManager::GetSingleton().RenderOnScreen(blank, NULL, SPRectangle(0,0,
		SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth, 
		SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight),
		D3DXCOLOR(0, 0, 0, 1 - transitionPosition), 0, NULL);

	angle += 0.01f;

	SPSpriteManager3D::GetSingleton().Render(tex3D, NULL, D3DXVECTOR3(0, 0, 0), 
		D3DXQUATERNION(0, 0, 0, 0),	D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0.2f, 0, 0.2f),
		D3DXQUATERNION(0, 0, sin(angle / 2), cos(angle / 2)), D3DXVECTOR3(-100, 0, -200));

	SPSpriteManager3D::GetSingleton().RenderByPosition(tex3D, NULL, D3DXVECTOR3(0, 0, 0));

	SPSpriteManager3D::GetSingleton().RenderByPositionWithRotateself(tex3D, NULL, 
		D3DXVECTOR3(100, 0, 100), D3DXVECTOR3(0.2f, 0, 0.2f),
		D3DXVECTOR3(0, 0, 1), angle);

	//tex3D.Render();

	//fontManager.Renderer->Begin(D3DXSPRITE_ALPHABLEND);
	//font.Font->DrawTextA(fontManager.Renderer, StringHelper::ToString(
	//	inputManager.GetMouseWheelPos()).c_str(), 
	//	-1, &r, DT_CENTER | DT_VCENTER, 0xFFFFFFFF);
	//fontManager.Renderer->End();
	// 



	return true;
}

bool TestScreen::Initialize()
{
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	return true;
}

bool TestScreen::Unload()
{
	video = NULL;
	texture = NULL;
	anime = NULL;
	tex3D = NULL;

	return true;
}

KScript::Value Print::Function( Script* currentScript, vector<Value> args )
{
	SPFontWriter::GetSingleton().Write(test->font, NULL, L"KS : " + 
		args[0].value, D3DXVECTOR2(0, 0), 
		SPColor::Magenta, 0, 0, NULL);
	return args[0];
}