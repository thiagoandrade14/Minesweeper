#include "Board.h"

Board::Board() {
	remainingMinesScore = 50;
	actualMines = 0;
	unsigned seed = time(0);
	default_random_engine generator(seed);
	while (actualMines < 50) {
		uniform_int_distribution<int> distributionI(0, 15);
		int i = distributionI(generator);
		uniform_int_distribution<int> distributionJ(0, 24);
		int j = distributionJ(generator);
		if (!board[j][i].checkIfMine()) {
			board[j][i].setMine();
			actualMines++;
		}		
	}	
	setAdjacency();
	smiley.loadFromFile("images/face_happy.png");
	smileyFace.setTexture(smiley);
	lostBoard = false;
	bool beingDebugged = false;
}

Board::Board(string filepath) {
	fstream inFS;
	inFS.open(filepath);
	remainingMinesScore = 0;
	actualMines = 0;
	if (inFS.is_open()) {
		for (unsigned int i = 0; i < 16; i++) {
			string row = "";
			inFS >> row;
			for (unsigned int j = 0; j < 25; j++) {
				if (row.at(j) == '1') {
					board[j][i].setMine();
					actualMines++;
					remainingMinesScore++;
				}
			}
		}
	}
	setAdjacency();
	smiley.loadFromFile("images/face_happy.png");
	smileyFace.setTexture(smiley);
	lostBoard = false;
	bool beingDebugged = false;
}

Board::~Board() {
	//cout << "Destructor was called" << endl;
}

Board::Board(const Board &copy) {
	for (unsigned int i = 0; i < 16; i++) {
		for (unsigned int j = 0; j < 25; j++) {
			board[i][j] = copy.board[j][i];
		}
	}
	remainingMinesScore = copy.remainingMinesScore;
	actualMines = copy.actualMines;
	smiley = copy.smiley;
	smileyFace = copy.smileyFace;
	lostBoard = copy.lostBoard;
	setAdjacency();
	bool beingDebugged = copy.beingDebugged;
}

Board& Board::operator= (Board& copy) {
	for (unsigned int i = 0; i < 16; i++) {
		for (unsigned int j = 0; j < 25; j++) {
			board[j][i] = copy.board[j][i];
		}
	}
	remainingMinesScore = copy.remainingMinesScore;
	actualMines = copy.actualMines;
	smiley = copy.smiley;
	smileyFace = copy.smileyFace;
	lostBoard = copy.lostBoard;
	setAdjacency();
	bool beingDebugged = copy.beingDebugged;
	return *this;
}

Tile& Board::getTile(int x, int y) {
	return board[x][y];
}

short Board::getScore() {
	return remainingMinesScore;
}

void Board::decreaseScore() {
	remainingMinesScore--;
}

void Board::increaseScore() {
	remainingMinesScore++;
}

sf::Sprite& Board::GetSmiley() {
	return smileyFace;
}

bool Board::checkForVictory() {
	unsigned short revealedCount = 0;
	for (unsigned int i = 0; i < 16; i++) {
		for (unsigned int j = 0; j < 25; j++) {
			if (getTile(j, i).checkIfRevealed()) {
				revealedCount++;
			}
		}
	}
	if (revealedCount >= 400-actualMines) {
		for (unsigned int i = 0; i < 16; i++) {
			for (unsigned int j = 0; j < 25; j++) {
				if (getTile(j, i).checkIfMine() && !getTile(j, i).checkIfFlag()) {
					getTile(j, i).switchFlag();
				}
			}
		}
		smiley.loadFromFile("images/face_win.png");
		smileyFace.setTexture(smiley);
		return true;
	}
	else {
		return false;
	}
}

bool Board::checkForDefeat() {
	return lostBoard;
}

void Board::defeatRoutine() {
	smiley.loadFromFile("images/face_lose.png");
	smileyFace.setTexture(smiley);
	lostBoard = true;
}

void Board::setAdjacency() {
	for (unsigned int i = 0; i < 16; i++) {
		for (unsigned int j = 0; j < 25; j++) {
			if (i > 0) {
				board[j][i].adjacentTiles[1] = &board[j][i-1];
				if (j > 0) {
					board[j][i].adjacentTiles[0] = &board[j-1][i-1];
				}
				else {
					board[j][i].adjacentTiles[0] = nullptr;
				}
				if (j < 24) {
					board[j][i].adjacentTiles[2] = &board[j+1][i-1];
				}
				else {
					board[j][i].adjacentTiles[2] = nullptr;
				}
			}
			else {
				board[j][i].adjacentTiles[0] = nullptr;
				board[j][i].adjacentTiles[1] = nullptr;
				board[j][i].adjacentTiles[2] = nullptr;
			}
			if (i < 15) {
				board[j][i].adjacentTiles[6] = &board[j][i+1];
				if (j > 0) {
					board[j][i].adjacentTiles[5] = &board[j-1][i+1];
				}
				else {
					board[j][i].adjacentTiles[5] = nullptr;
				}
				if (j < 24) {
					board[j][i].adjacentTiles[7] = &board[j+1][i+1];
				}
				else {
					board[j][i].adjacentTiles[7] = nullptr;
				}
			}
			else {
				board[j][i].adjacentTiles[5] = nullptr;
				board[j][i].adjacentTiles[6] = nullptr;
				board[j][i].adjacentTiles[7] = nullptr;
			}
			if (j > 0) {
				board[j][i].adjacentTiles[3] = &board[j-1][i];
			}
			else {
				board[j][i].adjacentTiles[3] = nullptr;
			}
			if (j < 24) {
				board[j][i].adjacentTiles[4] = &board[j+1][i];
			}
			else {
				board[j][i].adjacentTiles[4] = nullptr;
			}
		}
	}
}

void Board::debugMode() {
	if (!beingDebugged) {
		beingDebugged = true;
	}
	else {
		beingDebugged = false;
	}
}

bool Board::isBeingDebugged() {
	return !beingDebugged;
}