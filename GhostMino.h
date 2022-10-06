#pragma once
#include "ActiveMino.h"
class GhostMino : public ActiveMino
{

	public:

		GhostMino();
		GhostMino(const ActiveMino& tetromino);

		void UpdatePosition(const ActiveMino &currentTetromino);
		void Draw();
};

