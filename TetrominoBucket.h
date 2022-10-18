#pragma once
#include <queue>
#include <random>
class TetrominoBucket
{
public:
	TetrominoBucket();
	int GetNext();
	void GenerateTetrominoes();

private:
	std::queue<int> tetrominoQueue;
};

