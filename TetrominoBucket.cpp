#include "TetrominoBucket.h"

TetrominoBucket::TetrominoBucket()
{
}

int TetrominoBucket::GetNext()
{
	int returnVal = tetrominoQueue.front();
	tetrominoQueue.pop();

	if (tetrominoQueue.size() < 7)
		GenerateTetrominoes();

	return returnVal;
}

void TetrominoBucket::GenerateTetrominoes()
{
	int tetrominoes[7] = { 0,1,2,3,4,5,6 };
	std::random_device rd;
	unsigned seed = rd();
	std::shuffle(std::begin(tetrominoes), std::end(tetrominoes), std::default_random_engine(seed));
	for (int type : tetrominoes)
		tetrominoQueue.push(type);
}