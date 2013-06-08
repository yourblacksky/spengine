#include "StdAfx.h"
#include "SUIPictureBox.h"

#pragma warning(disable : 4244)

SUIPictureBox::SUIPictureBox(void)
{
	imagePos = D3DXVECTOR2(0,0);
	fillMode = ResizeBox;
	positionMode = Normal;
	picture = new SUIPictureList();
}


SUIPictureBox::~SUIPictureBox(void)
{
}

bool SUIPictureBox::SetMixImage(SUIMixImage image)
{
	picture->SetMixImage(image);

	return true;
}

bool SUIPictureBox::Draw( float timeDelta )
{
	SRectangle texRect = GetTexRect();

	picture->Draw(timeDelta);

	if (transformation && transformation->State() != Hidden)
	{
		if (targetPicture)
		{
			targetPicture->Draw(timeDelta);
			transformation->SetTarget(targetPicture->GetTarget());
		}		

		SPSpriteManager::GetSingleton().RenderOnScreen(picture->GetTarget(),
			transformation, texRect, SPColor::White, 1, childTarget );
	}
	else
	{
		SPSpriteManager::GetSingleton().RenderOnScreen(picture->GetTarget(),
			NULL, texRect, SPColor::White, 1, childTarget );
	}

	return true;
}

bool SUIPictureBox::SetBaseImage( SPTexturePtr base )
{
	picture->SetBaseImage(base);

	return true;
}

bool SUIPictureBox::SetImagePosition( D3DXVECTOR2 setPos )
{
	imagePos = setPos;

	return true;
}

SRectangle SUIPictureBox::GetTexRect()
{
	if (!picture)
	{
		return properties.rectangle;
	}

	SRectangle rect;
	int imageWidth = picture->GetWidth();
	int imageHeight = picture->GetHeight();
	int boxWidth = properties.rectangle.Width;
	int boxHeight = properties.rectangle.Height;

	if (fillMode == Positioning)
	{
		rect.Width = imageWidth;
		rect.Height = imageHeight;

		switch(positionMode)
		{
		case TopLeft:
			rect.X = 0;
			rect.Y = 0;
			break;

		case TopRight:
			rect.X = boxWidth - imageWidth;
			rect.Y = 0;
			break;

		case TopCenter:
			rect.X = (boxWidth - imageWidth) / 2;
			rect.Y = 0;
			break;

		case BottomLeft:
			rect.X = 0;
			rect.Y = boxHeight - imageHeight;
			break;

		case BottomRight:
			rect.X = boxWidth - imageWidth;
			rect.Y = boxHeight - imageHeight;
			break;

		case BottomCenter:
			rect.X = (boxWidth - imageWidth) / 2;
			rect.Y = boxHeight - imageHeight;
			break;

		case CenterLeft:
			rect.X = 0;
			rect.Y = (boxHeight - imageHeight) / 2;
			break;

		case CengerRight:
			rect.X = boxWidth - imageWidth;
			rect.Y = (boxHeight - imageHeight) / 2;
			break;

		case CenterAll:
			rect.X = (boxWidth - imageWidth) / 2;
			rect.Y = (boxHeight - imageHeight) / 2;
			break;

		default:
			rect.X = imagePos.x;
			rect.Y = imagePos.y;
			break;
		}
		
		return rect;
	}

	switch(fillMode)
	{
	case Fill:
		rect = properties.rectangle;
		rect.X = 0;
		rect.Y = 0;
		break;

	case FitWidth:
		rect.Width = boxWidth;
		rect.Height = (float)boxWidth / imageWidth * imageHeight;
		rect.X = 0;
		rect.Y = (boxHeight - rect.Height) / 2;
		break;

	case FitHeight:
		rect.Width = (float)boxHeight / imageHeight * imageWidth;
		rect.Height = boxHeight;
		rect.X = (boxWidth - rect.Width) / 2;
		rect.Y = 0;
		break;

	case FitMin:
		if ((float)boxWidth / imageWidth < 
			(float)boxHeight / imageHeight)
		{
			rect.Width = boxWidth;
			rect.Height = (float)boxWidth / imageWidth * imageHeight;
			rect.X = 0;
			rect.Y = (boxHeight - rect.Height) / 2;
		}
		else
		{
			rect.Width = (float)boxHeight / imageHeight * imageWidth;
			rect.Height = boxHeight;
			rect.X = (boxWidth - rect.Width) / 2;
			rect.Y = 0;
		}
		break;

	case FitMax:
		if ((float)boxWidth / imageWidth > 
			(float)boxHeight / imageHeight)
		{
			rect.Width = boxWidth;
			rect.Height = (float)boxWidth / imageWidth * imageHeight;
			rect.X = 0;
			rect.Y = (boxHeight - rect.Height) / 2;
		}
		else
		{
			rect.Width = (float)boxHeight / imageHeight * imageWidth;
			rect.Height = boxHeight;
			rect.X = (boxWidth - rect.Width) / 2;
			rect.Y = 0;
		}
		break;

	case ResizeBox:
		properties.rectangle.Width = imageWidth;
		properties.rectangle.Height = imageHeight;
		rect = properties.rectangle;
		rect.X = 0;
		rect.Y = 0;
		break;
	}

	return rect;
} 

bool SUIPictureBox::PreDraw()
{
	GetTexRect();

	return SUIComponentComposite::PreDraw();
}

bool SUIPictureBox::SetPositionMode( ImagePosition setMode )
{
	positionMode = setMode;

	return true;
}

bool SUIPictureBox::SetFillMode( ImageMode setMode )
{
	fillMode = setMode;

	return true;
}

bool SUIPictureBox::Transform()
{
	if (transformation)
	{
		transformation->Play();
	}
	
	return true;
}

bool SUIPictureBox::SetTransformation( SUITransformationPtr setTrans )
{
	transformation = setTrans;

	return true;
}

bool SUIPictureBox::SetTransformationTarget( SUIPictureListPtr setTarget )
{
	targetPicture = setTarget;

	return true;
}

bool SUIPictureBox::Update( float timeDelta )
{
	if(transformation)
	{
		if(!transformation->Update(timeDelta))
		{
			picture = targetPicture;
			transformation = NULL;
			targetPicture = NULL;
		}
	}

	return SUIComponentComposite::Update(timeDelta);
}

bool SUIPictureBox::SetPicture( SUIPictureListPtr setPicture )
{
	picture = setPicture;

	return true;
}

bool SUIPictureBox::Reload()
{
	return Load();
}

bool SUIPictureBox::Load()
{
	if (targetPicture)
	{
		targetPicture->Load();
	}

	if (picture)
	{
		picture->Load();
	}

	return true;
}

bool SUIPictureBox::Unload()
{
	renderTarget = NULL;
	childTarget = NULL;

	if (targetPicture)
	{
		targetPicture->Unload();
	}

	if (picture)
	{
		picture->Unload();
	}

	return true;
}

bool SUIPictureBox::LoadFromString( SPString stringStream )
{
	return true;
}

SPString SUIPictureBox::SaveAsString()
{
	SPString result = SPStringHelper::XMLSurroundWith(PropertiesToString(),L"SUIPB");

	return result;
}

bool SUIPictureBox::SetImagePositionX( int setX )
{
	imagePos.x = setX;

	return true;
}

bool SUIPictureBox::SetImagePositionY( int setY )
{
	imagePos.y = setY;

	return true;
}
