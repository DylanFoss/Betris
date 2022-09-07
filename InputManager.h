#pragma once
class InputManager
{
private:

	bool keyStates[256];
	bool keyStatesOld[256];

	const float keyDelayInterval = 0.25f;
	float keyDelayTimer[256];
	const float keyRepeatInterval = 0.07f;
	float keyRepeatTimer[256];

public:

	InputManager();

	void KeysDown(unsigned char key, int x, int y);
	void KeysUp(unsigned char key, int x, int y);
	void KeysHeld();

	bool IsKeyPressed(const char key) const;
	bool IsKeyPressedRepeatable(const char key, const float dt);
	bool IsKeyHeld(const char key) const;
};

