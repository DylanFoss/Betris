#include "GhostPiece.h"

GhostPiece::GhostPiece() 
	: Tetromino()
{
}

GhostPiece::GhostPiece(const Tetromino& tetromino)
	: Tetromino(tetromino)
{
}


void GhostPiece::UpdatePosition(const Tetromino& currentTetromino)
{
	x = currentTetromino.x;
	y = currentTetromino.y;

	if (type != currentTetromino.getType() || rotation != currentTetromino.rotation)
	{
		type = currentTetromino.getType();
		rotation = currentTetromino.rotation;
		std::memcpy(tiles, currentTetromino.tiles, 4 * 4 * sizeof(unsigned char));
	}
	
	while (Advance()); //advance till we can't
}

void GhostPiece::Draw()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (tiles[i][j] == 0) {}
			else if (tiles[i][j] == 1)
				renderer->drawHollowSquare(board->cellSize, x + (j * (board->cellSize)), y + (i * (board->cellSize)), 0, 255 - 90, 255 - 90);
			else if (tiles[i][j] == 2)
				renderer->drawHollowSquare(board->cellSize, x + (j * (board->cellSize)), y + (i * (board->cellSize)), 0, 150 - 90, 200 - 90);
			else if (tiles[i][j] == 3)
				renderer->drawHollowSquare(board->cellSize, x + (j * (board->cellSize)), y + (i * (board->cellSize)), 255 - 90, 165 - 90, 0);
			else if (tiles[i][j] == 4)
				renderer->drawHollowSquare(board->cellSize, x + (j * (board->cellSize)), y + (i * (board->cellSize)), 255 - 90, 255 - 90, 0);
			else if (tiles[i][j] == 5)
				renderer->drawHollowSquare(board->cellSize, x + (j * (board->cellSize)), y + (i * (board->cellSize)), 0, 255 - 90, 40);
			else if (tiles[i][j] == 6)
				renderer->drawHollowSquare(board->cellSize, x + (j * (board->cellSize)), y + (i * (board->cellSize)), 255 - 90, 0, 0);
			else if (tiles[i][j] == 7)
				renderer->drawHollowSquare(board->cellSize, x + (j * (board->cellSize)), y + (i * (board->cellSize)), 255 - 90, 0, 255 - 90);
		}
}