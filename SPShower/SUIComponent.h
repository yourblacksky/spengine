#pragma once
#include "SRectangle.h"
#include "SUIProperties.h"
#include "SUIAnimation.h"
#include "SUIEffect.h"
#include <queue>
#include "SUIEvent.h"
#include "SUIEventHandler.h"

#define  MaxLayer 255

using namespace SPEngine;

class SUIComponent;

typedef SPPointer<SUIComponent> SUIComponentPtr;

class SUIComponent : 
	public ISPDrawable,
	public ISPLoadable,
	public SPTransition
{
protected:
	typedef list<SUIAnimationPtr> AnimationQueue;
	typedef list<SUIEffectPtr> EffectQueue;

	/// @name Event Handlers
	/// @{
public:
	SUIEventHandlerPtr onMouseLeftClick;
	SUIEventHandlerPtr onMouseLeftDClick;
	SUIEventHandlerPtr onMouseLeftDown;
	SUIEventHandlerPtr onMouseLeftUp;

	SUIEventHandlerPtr onMouseRightClick;
	SUIEventHandlerPtr onMouseRightDClick;
	SUIEventHandlerPtr onMouseRightDown;
	SUIEventHandlerPtr onMouseRightUp;

	SUIEventHandlerPtr onMouseMiddleClick;
	SUIEventHandlerPtr onMouseMiddleDClick;
	SUIEventHandlerPtr onMouseMiddleDown;
	SUIEventHandlerPtr onMouseMiddleUp;

	SUIEventHandlerPtr onMouseScrollUp;
	SUIEventHandlerPtr onMouseScrollDown;

	SUIEventHandlerPtr catchMouseLeftClick;
	SUIEventHandlerPtr catchMouseLeftDClick;
	SUIEventHandlerPtr catchMouseLeftDown;
	SUIEventHandlerPtr catchMouseLeftUp;

	SUIEventHandlerPtr catchMouseRightClick;
	SUIEventHandlerPtr catchMouseRightDClick;
	SUIEventHandlerPtr catchMouseRightDown;
	SUIEventHandlerPtr catchMouseRightUp;

	SUIEventHandlerPtr catchMouseMiddleClick;
	SUIEventHandlerPtr catchMouseMiddleDClick;
	SUIEventHandlerPtr catchMouseMiddleDown;
	SUIEventHandlerPtr catchMouseMiddleUp;

	SUIEventHandlerPtr catchMouseScrollUp;
	SUIEventHandlerPtr catchMouseScrollDown;

	SUIEventHandlerPtr onMouse;
	SUIEventHandlerPtr onMouseIn;
	SUIEventHandlerPtr onMouseOut;

	SUIEventHandlerPtr onFocus;
	SUIEventHandlerPtr onBlur;

	SUIEventHandlerPtr onKeyPress[256];
	SUIEventHandlerPtr onKeyDown[256];
	SUIEventHandlerPtr onKeyUp[256];

	/// @}

protected:
	/// @name Properties
	/// @{
	SPString			name;
	SUIProperties		properties;
	AnimationQueue		animations;
	SPTexturePtr		renderTarget;
	SPTexturePtr		childTarget;
	EffectQueue			effects;
	SUIComponentPtr		father;
	VariableMap			propertiesMap;
	/// @}	
	
public:
	/// @name Getter and Setter
	/// @{
	SPString GetName();
	bool SetName(SPString setName);

	SUIProperties GetProperties();
	SUIProperties GetTargetProperties();
	bool SetProperties(SUIProperties setProperties);
	SPTexturePtr GetComponentTexture();

	/// @name Set Effect
	/// @{
	bool SetRenderTarget(SPTexturePtr setTarget);
	bool AddEffect(SUIEffectPtr setEffect);
	bool ClearEffect();
	SUIEffectPtr GetCurrentEffect();
	bool AddAnimation(SUIAnimationPtr setAnimation);
	bool MergerAnimation(SUIAnimationPtr setAnimation);
	/// @}

	/// @name Set Background
	/// @{
	SPTexturePtr GetBackgroundImage();
	bool SetBackgroundImage(SPTexturePtr setImage);
	D3DCOLOR GetBackgroundColor();
	bool SetBackgroundColor(D3DCOLOR setColor);
	/// @}

	/// @name Set Box
	/// @{
	int GetWidth();	
	int GetHeight();
	bool SetWidth(int setWidth);
	bool SetHeight(int setHeight);

	bool SetPosition(D3DXVECTOR2 pos);
	D3DXVECTOR2 GetPosition();
	bool SetPositionX(int setX);
	bool SetPositionY(int setY);

	float GetRotation();
	bool SetRotation(float setRotation);	
	D3DXVECTOR2 GetRotationCenter();	
	bool SetRotationCenter(D3DXVECTOR2 pos);
	bool SetRotationCenterX(int setX);
	bool SetRotationCenterY(int setY);
	/// @}

	/// @name Other
	/// @{
	float GetTransparency();
	bool SetTransparency(float setTrans);

	float GetLayer();
	bool SetLayer(float setLayer);
	float GetDepth();

	bool SetBackgroundX(int setX);
	int GetBackgroundX();
	bool SetBackgroundY(int setY);
	int GetBackgroundY();

	bool SetBackgroundMode(SUIProperties::BackgroundMode setMode);
	bool SetBackgroundPositionMode(SUIProperties::BackgroundPosition setMode);

	SRectangle GetBackgroundRect();
	bool SetProperties(VariableMap args);
	/// @}
	/// @}

public:
	SUIComponent(void);
	~SUIComponent(void);

	virtual bool Update(float timeDelta) = 0;
	virtual bool PreDraw() = 0;
	virtual bool Draw(float timeDelta) = 0;
	virtual bool PostDraw() = 0;
	virtual bool Load() = 0;
	virtual bool Unload() = 0;
	virtual bool Reload() = 0;
	virtual bool HandleEvent(SUIEventPtr e) = 0;
	virtual bool Render(float timeDelta);
	virtual bool AddChild(SUIComponentPtr setChild);
	virtual bool RemoveChild(SUIComponentPtr setChild);
	virtual bool SetFather(SUIComponentPtr setFather);
	virtual SUIComponentPtr GetFather();

	bool Hide();
	bool Unhide();
	bool IsDisplay();
	
	bool PlayAnimation();
	bool PlayEffect();
	virtual bool Skip() = 0;

	virtual bool LoadFromString(SPString stringStream) = 0;
	virtual SPString SaveAsString() = 0;
	bool SaveAsImage(SPString path);
	SPTexturePtr SaveAsTexture();

protected:
	bool UpdateAnimation(float timeDelta);
	bool UpdateEffect(float timeDelta);
	SPString PropertiesToString();
	
};



