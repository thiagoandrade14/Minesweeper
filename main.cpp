#include <map>
#include "Board.h"

using namespace std;

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");

	/*TEXTURES MAP*/
	map<string, sf::Texture> resources;
	sf::Texture tileHidden;
	tileHidden.loadFromFile("images/tile_hidden.png");
	resources.insert(pair<string, sf::Texture>("hidden", tileHidden));
	sf::Texture tileRevealed;
	tileRevealed.loadFromFile("images/tile_revealed.png");
	resources.insert(pair<string, sf::Texture>("revealed", tileRevealed));
	sf::Texture debugTexture;
	debugTexture.loadFromFile("images/debug.png");
	resources.insert(pair<string, sf::Texture>("debug", debugTexture));
	sf::Texture digitsTexture;
	digitsTexture.loadFromFile("images/digits.png");
	resources.insert(pair<string, sf::Texture>("digits", digitsTexture));
	sf::Texture happyTexture;
	happyTexture.loadFromFile("images/face_happy.png");
	resources.insert(pair<string, sf::Texture>("happy", happyTexture));
	sf::Texture sadTexture;
	sadTexture.loadFromFile("images/face_lose.png");
	resources.insert(pair<string, sf::Texture>("lose", sadTexture));
	sf::Texture coolTexture;
	coolTexture.loadFromFile("images/face_win.png");
	resources.insert(pair<string, sf::Texture>("win", coolTexture));
	sf::Texture flagTexture;
	flagTexture.loadFromFile("images/flag.png");
	resources.insert(pair<string, sf::Texture>("flag", flagTexture));
	sf::Texture mineTexture;
	mineTexture.loadFromFile("images/mine.png");
	resources.insert(pair<string, sf::Texture>("mine", mineTexture));
	sf::Texture oneTexture;
	oneTexture.loadFromFile("images/number_1.png");
	resources.insert(pair<string, sf::Texture>("one", oneTexture));
	sf::Texture twoTexture;
	twoTexture.loadFromFile("images/number_2.png");
	resources.insert(pair<string, sf::Texture>("two", twoTexture));
	sf::Texture threeTexture;
	threeTexture.loadFromFile("images/number_3.png");
	resources.insert(pair<string, sf::Texture>("three", threeTexture));
	sf::Texture fourTexture;
	fourTexture.loadFromFile("images/number_4.png");
	resources.insert(pair<string, sf::Texture>("four", fourTexture));
	sf::Texture fiveTexture;
	fiveTexture.loadFromFile("images/number_5.png");
	resources.insert(pair<string, sf::Texture>("five", fiveTexture));
	sf::Texture sixTexture;
	sixTexture.loadFromFile("images/number_6.png");
	resources.insert(pair<string, sf::Texture>("six", sixTexture));
	sf::Texture sevenTexture;
	sevenTexture.loadFromFile("images/number_7.png");
	resources.insert(pair<string, sf::Texture>("seven", sevenTexture));
	sf::Texture eightTexture;
	eightTexture.loadFromFile("images/number_8.png");
	resources.insert(pair<string, sf::Texture>("eight", eightTexture));
	sf::Texture testOneTexture;
	testOneTexture.loadFromFile("images/test_1.png");
	resources.insert(pair<string, sf::Texture>("testOne", testOneTexture));
	sf::Texture testTwoTexture;
	testTwoTexture.loadFromFile("images/test_2.png");
	resources.insert(pair<string, sf::Texture>("testTwo", testTwoTexture));
	sf::Texture testThreeTexture;
	testThreeTexture.loadFromFile("images/test_3.png");
	resources.insert(pair<string, sf::Texture>("testThree", testThreeTexture));

	/*BOARD AND BUTTONS*/
	Board* tempBoard;
	Board board;
	sf::Sprite debug;
	debug.setTexture(resources["debug"]);
	debug.setPosition(336.0f + (64 * 2), 32 * 16.0f);
	sf::Sprite testOne;
	testOne.setTexture(resources["testOne"]);
	testOne.setPosition(336.0f + (64 * 3), 32 * 16.0f);
	sf::Sprite testTwo;
	testTwo.setTexture(resources["testTwo"]);
	testTwo.setPosition(336.0f + (64 * 4), 32 * 16.0f);
	sf::Sprite testThree;
	testThree.setTexture(resources["testThree"]);
	testThree.setPosition(336.0f + (64 * 5), 32 * 16.0f);
	
	while (window.isOpen()) {
		if (board.checkForVictory()) {
			while (board.getScore() != 0) {
				board.decreaseScore();
			}
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (!board.checkForDefeat()) {
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
						sf::FloatRect bounds;
						for (unsigned int i = 0; i < 16; i++) {
							for (unsigned int j = 0; j < 25; j++) {
								bounds = board.getTile(j, i).GetSprite().getGlobalBounds();
								if (bounds.contains(mouse)) {
									if (!board.getTile(j, i).checkIfRevealed() && !board.getTile(j, i).checkIfFlag()) {
										board.getTile(j, i).reveal();
										if (board.getTile(j, i).checkIfMine()) {
											board.defeatRoutine();
										}
									}
								}
							}
						}

						bounds = board.GetSmiley().getGlobalBounds();
						if (bounds.contains(mouse)) {
							tempBoard = new Board();
							board = *tempBoard;
						}
						bounds = testOne.getGlobalBounds();
						if (bounds.contains(mouse)) {
							tempBoard = new Board("boards/testboard1.brd");
							board = *tempBoard;
						}
						bounds = testTwo.getGlobalBounds();
						if (bounds.contains(mouse)) {
							tempBoard = new Board("boards/testboard2.brd");
							board = *tempBoard;
						}
						bounds = testThree.getGlobalBounds();
						if (bounds.contains(mouse)) {
							tempBoard = new Board("boards/testboard3.brd");
							board = *tempBoard;
						}
						bounds = debug.getGlobalBounds();
						if (bounds.contains(mouse)) {
							board.debugMode();
						}
					}
					else if (event.mouseButton.button == sf::Mouse::Right) {
						sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
						sf::FloatRect bounds;
						for (unsigned int i = 0; i < 16; i++) {
							for (unsigned int j = 0; j < 25; j++) {
								bounds = board.getTile(j, i).GetSprite().getGlobalBounds();
								if (bounds.contains(mouse)) {
									if (!board.getTile(j, i).checkIfRevealed() && !board.getTile(j, i).checkIfFlag()) {
										board.getTile(j, i).switchFlag();
										board.decreaseScore();
									}
									else if (board.getTile(j, i).checkIfFlag()) {
										board.getTile(j, i).switchFlag();
										board.increaseScore();
									}
								}
							}
						}
					}
				}
			}

			else {
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
						sf::FloatRect bounds;
						bounds = board.GetSmiley().getGlobalBounds();
						if (bounds.contains(mouse)) {
							tempBoard = new Board();
							board = *tempBoard;
						}
					}
				}
			}
		}
			window.clear();
		for (unsigned int i = 0; i < 16; i++) {
			for (unsigned int j = 0; j < 25; j++) {
				window.draw(board.getTile(j, i).GetSprite());
				board.getTile(j, i).GetSprite().setPosition(j*32.0f, i*32.0f);
				if (board.getTile(j, i).checkIfFlag()) {
						sf::Sprite flag;
						flag.setTexture(resources["flag"]);
						flag.setPosition(j*32.0f, i*32.0f);
						window.draw(flag);
				}

				if (board.isBeingDebugged()) {
					if (board.getTile(j, i).checkIfMine()) {
						sf::Sprite mine;
						mine.setTexture(resources["mine"]);
						mine.setPosition(j*32.0f, i*32.0f);
						window.draw(mine);
					}
				}

				if (board.getTile(j, i).checkIfRevealed()) {
					if (board.getTile(j, i).checkIfMine()) {
						sf::Sprite mine;
						mine.setTexture(resources["mine"]);
						mine.setPosition(j*32.0f, i*32.0f);
						window.draw(mine);
					}
					else if (board.getTile(j, i).getMineValue() == 1) {
						sf::Sprite one;
						one.setTexture(resources["one"]);
						one.setPosition(j*32.0f, i*32.0f);
						window.draw(one);
					}
					else if (board.getTile(j, i).getMineValue() == 2) {
						sf::Sprite two;
						two.setTexture(resources["two"]);
						two.setPosition(j*32.0f, i*32.0f);
						window.draw(two);
					}
					else if (board.getTile(j, i).getMineValue() == 3) {
						sf::Sprite three;
						three.setTexture(resources["three"]);
						three.setPosition(j*32.0f, i*32.0f);
						window.draw(three);
					}
					else if (board.getTile(j, i).getMineValue() == 4) {
						sf::Sprite four;
						four.setTexture(resources["four"]);
						four.setPosition(j*32.0f, i*32.0f);
						window.draw(four);
					}
					else if (board.getTile(j, i).getMineValue() == 5) {
						sf::Sprite five;
						five.setTexture(resources["five"]);
						five.setPosition(j*32.0f, i*32.0f);
						window.draw(five);
					}
					else if (board.getTile(j, i).getMineValue() == 6) {
						sf::Sprite six;
						six.setTexture(resources["six"]);
						six.setPosition(j*32.0f, i*32.0f);
						window.draw(six);
					}
					else if (board.getTile(j, i).getMineValue() == 7) {
						sf::Sprite seven;
						seven.setTexture(resources["seven"]);
						seven.setPosition(j*32.0f, i*32.0f);
						window.draw(seven);
					}
					else if (board.getTile(j, i).getMineValue() == 8) {
						sf::Sprite eight;
						eight.setTexture(resources["eight"]);
						eight.setPosition(j*32.0f, i*32.0f);
						window.draw(eight);
					}
				}
			}
		}
		string scoreString = to_string(board.getScore());
		for (unsigned int i = 0; i < scoreString.size(); i++) {
			sf::Sprite digit;
			digit.setTexture(resources["digits"]);
			if (scoreString.at(i) == '-') {
				digit.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
				digit.setPosition(21.0f*i, 32 * 16.0f);
				window.draw(digit);
			}
			else if (scoreString.at(i) == '0') {
				digit.setTextureRect(sf::IntRect(21 * 0, 0, 21, 32));
				digit.setPosition(21.0f*i, 32 * 16.0f);
				window.draw(digit);
			}
			else if (scoreString.at(i) == '1') {
				digit.setTextureRect(sf::IntRect(21 * 1, 0, 21, 32));
				digit.setPosition(21.0f*i, 32 * 16.0f);
				window.draw(digit);
			}
			else if (scoreString.at(i) == '2') {
				digit.setTextureRect(sf::IntRect(21 * 2, 0, 21, 32));
				digit.setPosition(21.0f*i, 32 * 16.0f);
				window.draw(digit);
			}
			else if (scoreString.at(i) == '3') {
				digit.setTextureRect(sf::IntRect(21 * 3, 0, 21, 32));
				digit.setPosition(21.0f*i, 32 * 16.0f);
				window.draw(digit);
			}
			else if (scoreString.at(i) == '4') {
				digit.setTextureRect(sf::IntRect(21 * 4, 0, 21, 32));
				digit.setPosition(21.0f*i, 32 * 16.0f);
				window.draw(digit);
			}
			else if (scoreString.at(i) == '5') {
				digit.setTextureRect(sf::IntRect(21 * 5, 0, 21, 32));
				digit.setPosition(21.0f*i, 32 * 16.0f);
				window.draw(digit);
			}
			else if (scoreString.at(i) == '6') {
				digit.setTextureRect(sf::IntRect(21 * 6, 0, 21, 32));
				digit.setPosition(21.0f*i, 32 * 16.0f);
				window.draw(digit);
			}
			else if (scoreString.at(i) == '7') {
				digit.setTextureRect(sf::IntRect(21 * 7, 0, 21, 32));
				digit.setPosition(21.0f*i, 32 * 16.0f);
				window.draw(digit);
			}
			else if (scoreString.at(i) == '8') {
				digit.setTextureRect(sf::IntRect(21 * 8, 0, 21, 32));
				digit.setPosition(21.0f*i, 32 * 16.0f);
				window.draw(digit);
			}
			else if (scoreString.at(i) == '9') {
				digit.setTextureRect(sf::IntRect(21 * 9, 0, 21, 32));
				digit.setPosition(21.0f*i, 32 * 16.0f);
				window.draw(digit);
			}
		}
		board.GetSmiley().setPosition(336.0f, 32 * 16.0f);
		window.draw(board.GetSmiley());
		window.draw(debug);
		window.draw(testOne);
		window.draw(testTwo);
		window.draw(testThree);

		window.display();
	}	

	return 0;
}