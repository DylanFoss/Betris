#pragma once
#include "Tetromino.h"

#define PI 3.14159
class ActiveMino : public Tetromino
{

private:
	bool rotatedThisTick;
	bool movedThisTick;
	bool wasLastMoveRotation;
	int	numWallKicksThisTick;

	bool HasRotated();
	bool HasMoved();

	float timer = 0;

	bool isFlashing;

public:

	ActiveMino();
	ActiveMino(const Renderer* renderer, Board* board, int X, int Y, MinoType type);

	bool Move(int X, int Y);
	bool Rotate(bool lr);
	bool CollisionCheck();
	bool CollisionCheck(int x, int y=0);
	bool Advance();
	void Lock();

	void Reset();
	void Reset(MinoType type);
	void Reset(MinoType type, int x, int y);

	void ResetFlags();

	bool MovedThisTick() const { return movedThisTick; }
	bool RotatedThisTick() const { return rotatedThisTick; }
	int	NumWallKicksThisTick() const { return numWallKicksThisTick; }
	bool WasLastMoveRotation() const { return wasLastMoveRotation; }
	void SetIsFlashing(bool isFlash) { isFlashing = isFlash; };

	void Update(double dt);
	void Draw(double dt);

	void ShouldFlash();
};

