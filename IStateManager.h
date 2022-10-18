#pragma once
#include "IStateChanger.h"
class IStateManager :
	public IStateChanger
{
public:
	IStateManager();
	virtual  ~IStateManager() = 0 {};
	virtual void ChangeState(int newstate) = 0;
};

