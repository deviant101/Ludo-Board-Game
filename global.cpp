#pragma once
#include <SFML/Graphics.hpp>
// #include
// Create the playGroundGrids
sf::RectangleShape playGroundGrids[52];
sf::RectangleShape greenHome[5];
sf::RectangleShape redHome[5];
sf::RectangleShape blueHome[5];
sf::RectangleShape yellowHome[5];
sf::RectangleShape DICE(sf::Vector2f(150,150));
sf::Texture shuffleDiceTexture;
sf::RectangleShape playerturn(sf::Vector2f(90,90));
sf::RenderWindow mainWindow;

sf::RectangleShape *playerHomes[4]={redHome, greenHome, blueHome, yellowHome};

sf::RectangleShape heartSym(sf::Vector2f(200, 200));
sf::RectangleShape spadeSym(sf::Vector2f(200, 200));
sf::RectangleShape clubSym(sf::Vector2f(200, 200));
sf::RectangleShape diamondSym(sf::Vector2f(200, 200));
sf::RectangleShape SymbolArray[4] = {heartSym, spadeSym, clubSym, diamondSym};

sf::Texture greenstop;
sf::Texture redstop;
sf::Texture yellowstop;
sf::Texture bluestop;


sf::Font mainFont;
sf::Font secFont;

int NO_PLAYERS;
int NO_TOKENS;
int Cycle = 0;

pthread_mutex_t turnMutex;