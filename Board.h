#include "Tile.h"

class Board {
private:
	Tile board[25][16];
	short remainingMinesScore;
	short actualMines;
	sf::Texture smiley;
	sf::Sprite smileyFace;
	bool lostBoard;
	bool beingDebugged;
public:
	Board();
	~Board();
	Board(const Board &copy);
	Board& operator= (Board& copy);
	Board(string filepath);
	Tile& getTile(int x, int y);
	short getScore();
	sf::Sprite& GetSmiley();
	void decreaseScore();
	void increaseScore();
	void setAdjacency();
	bool checkForVictory();
	bool checkForDefeat();
	bool isBeingDebugged();
	void defeatRoutine();
	void debugMode();
};