#include "Tile.h"

Tile::Tile() {
	texture.loadFromFile("images/tile_hidden.png");
	sprite.setTexture(texture);
	hasMine = false;
	wasRevealed = false;
	flagPlaced = false;
}

Tile::Tile(bool hasMine) {
	texture.loadFromFile("images/tile_hidden.png");
	sprite.setTexture(texture);
	this->hasMine = hasMine;
	wasRevealed = false;
	flagPlaced = false;
}

sf::Sprite& Tile::GetSprite() {
	return sprite;
}

void Tile::setMine() {
	hasMine = true;
}

void Tile::reveal() {
	texture.loadFromFile("images/tile_revealed.png");
	sprite.setTexture(texture);
	wasRevealed = true;
	if (hasMine) {
		return;
	}
	if (getMineValue() == 0) {
		for (unsigned int i = 0; i < ADJACENT_TILES; i++) {
			if (adjacentTiles[i] != nullptr) {
				if (!adjacentTiles[i]->wasRevealed) {
					adjacentTiles[i]->reveal();
				}
			}
		}
	}
}

void Tile::switchFlag() {
	if (flagPlaced) {
		flagPlaced = false;
	}
	else {
		flagPlaced = true;
	}
}

unsigned short Tile::getMineValue() {
	unsigned short mines = 0;
	for (unsigned int i = 0; i < ADJACENT_TILES; i++) {
		if (adjacentTiles[i] != nullptr) {
			if (adjacentTiles[i]->hasMine) {
				mines++;
			}
		}
	}
	return mines;
}

bool Tile::checkIfMine() {
	return hasMine;
}
bool Tile::checkIfRevealed() {
	return wasRevealed;
}
bool Tile::checkIfFlag() {
	return flagPlaced;
}