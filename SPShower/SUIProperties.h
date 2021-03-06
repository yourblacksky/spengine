#pragma once
#include "SRectangle.h"

#define PI 3.1415926

class SUIProperties
{
public:
	enum BackgroundMode
	{
		Positioning,
		Fill,
		FitWidth,
		FitHeight,
		FitMin,
		FitMax,
	};

	enum BackgroundPosition
	{
		Normal,
		TopLeft,
		TopRight,
		TopCenter,
		BottomLeft,
		BottomRight,
		BottomCenter,
		CenterLeft,
		CengerRight,
		CenterAll,
	};

public:
	SRectangle		rectangle;
	float			rotation;
	D3DXVECTOR2		rotationCenter;
	SPTexturePtr	backgroundImage;
	D3DCOLOR		backgroundColor;
	float			transparency;	
	float			layer;
	int				backgroundX;
	int				backgroundY;
	BackgroundMode	backgroundMode;
	BackgroundPosition backgroundPosition;

public:
	SUIProperties(void);
	~SUIProperties(void);
};

