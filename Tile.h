#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <random>

using namespace std;

class Tile {
	static const int ADJACENT_TILES = 8;
private:
	sf::Texture texture;
	sf::Sprite sprite;
	bool hasMine;
	bool wasRevealed;
	bool flagPlaced;
public:
	Tile();
	Tile(bool hasMine);
	Tile *adjacentTiles[ADJACENT_TILES];
	unsigned short getMineValue();
	sf::Sprite& GetSprite();
	void setMine();
	void reveal();
	void switchFlag();
	bool checkIfMine();
	bool checkIfRevealed();
	bool checkIfFlag();
};