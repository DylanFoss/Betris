#include "InputManager.h"
#include <cstring>
#include <iostream>

InputManager::InputManager()
{
	std::memset(keyStates, 0, sizeof(bool) * 256);
	std::memset(keyStatesOld, 0, sizeof(bool) * 256);

	std::memset(keyDelayTimer, 0, sizeof(float) * 256);
	std::memset(keyRepeatTimer, 0, sizeof(float) * 256);
}

void InputManager::KeysDown(unsigned char key, int x, int y)
{
	keyStates[key] = true;
}

void InputManager::KeysUp(unsigned char key, int x, int y)
{
	keyStates[key] = false;
}

void InputManager::KeysHeld()
{
	for (int i = 0; i < 256; i++)
		keyStatesOld[i] = keyStates[i];
}

bool InputManager::IsKeyPressed(const char key) const
{
	return keyStates[key] && !keyStatesOld[key];
}

bool InputManager::IsKeyHeld(const char key) const
{
	return keyStates[key] && keyStatesOld[key];
}

bool InputManager::IsKeyPressedRepeatable(const char key, const float dt)
{

	if (IsKeyHeld(key))
	{
		keyDelayTimer[key] += dt;
		if (keyDelayTimer[key] >= keyDelayInterval)
		{
			keyDelayTimer[key] += dt;
			if (keyDelayTimer[key] >= keyRepeatInterval)
			{
				keyDelayTimer[key] -= keyRepeatInterval;
				return true;
			}
		}
	}
	else if (IsKeyPressed(key))
	{
		return true;
	}
	else if (!IsKeyPressed(key))
	{
		keyDelayTimer[key] = 0.0f;
	}

	return false;
}