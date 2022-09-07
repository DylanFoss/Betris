#pragma once
#include "Tetromino.h"
class GhostPiece : public Tetromino
{

	public:

		GhostPiece();
		GhostPiece(const Tetromino& tetromino);

		void UpdatePosition(const Tetromino &currentTetromino);
		void Draw();
};

