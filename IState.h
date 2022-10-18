#pragma once
#include "IStateChanger.h"
class IState
{
public:
	IState();
	IState(IStateChanger* stateManager);
	virtual ~IState() = 0 {};

	virtual void Update(const double dt)=0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

protected:
	virtual void ChangeState(int newState) = 0;
	IStateChanger* manager;
};

