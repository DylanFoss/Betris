#include "IState.h"

IState::IState()
	: manager(nullptr)
{
}

IState::IState(IStateChanger* stateManager)
	: manager(stateManager)
{
}
