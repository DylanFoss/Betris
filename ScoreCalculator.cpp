#include "ScoreCalculator.h"
#include <iostream>

ScoreCalculator::ScoreCalculator()
	: scoreTracker(nullptr), currentTetromino(nullptr), board(nullptr), level(1), softDropCounter(0), hardDropCounter(0), wasTSpin(false), wasMiniTSpin(false), linesCleared(0), comboMultiplier(-1), backToBackCounter(-1), fullCalculation(false)
{

}

ScoreCalculator::ScoreCalculator(Score* scoreTracker)
	: scoreTracker(scoreTracker), currentTetromino(nullptr), board(nullptr), level(1), softDropCounter(0), hardDropCounter(0), wasTSpin(false), wasMiniTSpin(false), linesCleared(0), comboMultiplier(-1), backToBackCounter(-1), fullCalculation(false)
{

}

ScoreCalculator::ScoreCalculator(Score* scoreTracker, ActiveMino* currentTetromino, Board* board)
	: scoreTracker(scoreTracker), currentTetromino(currentTetromino), board(board), level(1), softDropCounter(0), hardDropCounter(0), wasTSpin(false), wasMiniTSpin(false), linesCleared(0), comboMultiplier(-1), backToBackCounter(-1), fullCalculation(false)
{

}

void ScoreCalculator::CalculateScore()
{
	int roundScore = 0;

	//calculate soft drops
	if (countSoftDrops)
		roundScore += softDropCounter;

	if (fullCalculation)
	{
		int actionScore = 0;
		bool dificultAction = false;

		//calculate hard drops
		if (countHardDrops)
			roundScore += hardDropCounter * 2;

		//Tspin detection
		if (currentTetromino != nullptr && board != nullptr)
		{
			if (currentTetromino->getType() == MinoType::T && currentTetromino->RotatedThisTick())
			{

				int xOffset = 0;
				int yOffset = 0;

				switch (currentTetromino->rotation)
				{
				case 0:
					break;
				case 1:
					yOffset = 1;
					break;
				case 2:
					xOffset = 1;
					yOffset = 1;
					break;
				case 3:
					xOffset = 1;
					break;
				}

				// we can detect if a Tspin occured if at least three of the diagonal coners of the T aren't empty.

				std::vector<bool> diags; //clockwise starting from top left
				diags.reserve(4);
				diags.emplace_back(board->IsElementEmpty(board->GetGridX(currentTetromino->x) + xOffset, (board->GetGridY(currentTetromino->y) + yOffset + 2)));
				diags.emplace_back(board->IsElementEmpty(board->GetGridX(currentTetromino->x) + xOffset + 2, board->GetGridY(currentTetromino->y) + yOffset + 2));
				diags.emplace_back(board->IsElementEmpty(board->GetGridX(currentTetromino->x) + xOffset + 2, board->GetGridY(currentTetromino->y) + yOffset));
				diags.emplace_back(board->IsElementEmpty(board->GetGridX(currentTetromino->x) + xOffset, board->GetGridY(currentTetromino->y) + yOffset));

				//std::cout << diags.at(0) << diags.at(1) << diags.at(2) << diags.at(3) << "\n";

				int emptyCornerCounter = 0;
				for (bool empty : diags)
					emptyCornerCounter += empty;

				if (emptyCornerCounter < 2)
				{
					wasTSpin = true;

					//check if it was a MINI Tspin

					int emptyForwardCounter = 0;

					//first check if the T is "facing" two occupied spaces (if not, potentially a mini)
					switch (currentTetromino->rotation)
					{
					case 0:
						emptyForwardCounter += diags.at(0);
						emptyForwardCounter += diags.at(1);
						break;
					case 1:
						emptyForwardCounter += diags.at(1);
						emptyForwardCounter += diags.at(2);
						break;
					case 2:
						emptyForwardCounter += diags.at(2);
						emptyForwardCounter += diags.at(3);
						break;
					case 3:
						emptyForwardCounter += diags.at(3);
						emptyForwardCounter += diags.at(0);
						break;
					}

					if (emptyForwardCounter > 0)
					{
						wasMiniTSpin = true;

						// exception, if a 1,2 offset was applied during rotation (the 4th test), it still counts as a full T spin.
						if (currentTetromino->NumWallKicksThisTick() == 4) wasMiniTSpin = false;
					}

				}
			}
		}

		if (wasTSpin)
		{
			std::cout << "T-Spin Performed";
			if (wasMiniTSpin) std::cout << " but it was a mini :(";
			std::cout << '\n';
		}

		//line clears
		if (linesCleared == 0)
		{
			comboMultiplier = -1;

			if (wasTSpin)
			{
				if (wasMiniTSpin)
				{
					actionScore = 100 * level;
				}
				else
				{
					actionScore = 200 * level;
				}
				dificultAction = true;
			}
			else
			{
				backToBackCounter = -1;
			}
		}
		else
		{
			switch (linesCleared)
			{
			case(1):
				if (wasTSpin)
				{
					if (wasMiniTSpin)
					{
						actionScore += 200 * level;
					}
					else
					{
						actionScore += 800 * level;
					}
					dificultAction = true;
					backToBackCounter++;
				}
				else
				{
					actionScore += 100 * level;
					backToBackCounter = -1;
				}
				break;
			case(2):
				if (wasTSpin)
				{
					if (wasMiniTSpin)
					{
						actionScore += 400 * level;
					}
					else
					{
						actionScore += 1200 * level;
					}
					dificultAction = true;
					backToBackCounter++;
				}
				else
				{
					actionScore += 300 * level;
					backToBackCounter = -1;
				}
				break;
			case(3):
				if (wasTSpin && !wasMiniTSpin)
				{
					actionScore += 1600 * level;
					dificultAction = true;
					backToBackCounter++;
				}
				else
				{
					actionScore += 500 * level;
					backToBackCounter = -1;
				}
				break;
			case(4):
				roundScore += 800 * level;
				dificultAction = true;
				backToBackCounter++;
				break;
			}

			comboMultiplier++;
		}

		//Back TO Back

		if (backToBackCounter > 0)
			if (dificultAction)
				actionScore *= 1.5;

		roundScore += actionScore;

		//Combo
		if (comboMultiplier > 0)
			roundScore += 50 * comboMultiplier * level;
	}

	scoreTracker->UpdateScore(roundScore, linesCleared);
	SoftReset();
}

void ScoreCalculator::SoftReset()
{
	softDropCounter = 0;
	hardDropCounter = 0;

	wasTSpin = false;
	wasMiniTSpin = false;

	linesCleared = 0;

	fullCalculation = false;
}

void ScoreCalculator::Init()
{
}
