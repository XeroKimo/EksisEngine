#pragma once
#include "EngineFiles.h"
enum ScreenID { SCEEN_GAME };

class Screen
{
public:
	Screen();
	virtual ~Screen();

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(double delta) = 0;
	virtual void Render() = 0;
	virtual void Input() = 0;
	virtual void Shutdown() = 0;
	virtual ScreenID GetID() = 0;
};