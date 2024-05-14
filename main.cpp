// #pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <bits/stdc++.h>
#include <semaphore.h>
#include "Player.cpp"
using namespace std;

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

sf::Font mainFont;
sf::Font secFont;

int NO_PLAYERS;
int NO_TOKENS;
int Cycle = 0;

Player *PLAYERS;

pthread_mutex_t turnMutex;

void inputWindow();
void drawHomeGrids(sf::RectangleShape *homeGrid, string color);
void initialize();
void *turn(void* arg);
void *MasterThread(void*);

int main(){

    srand(time(0));
    mainFont.loadFromFile("fonts/SalvarRegular-gxwoP.ttf");
    secFont.loadFromFile("fonts/AAbsoluteEmpire-EaXpg.ttf");
    shuffleDiceTexture.loadFromFile("images/dice.png");
    
    inputWindow();
    initialize();

    mainWindow.create(sf::VideoMode(1100, 750), "Ludo-Board Game");
    mainWindow.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - mainWindow.getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - mainWindow.getSize().y / 2));

    // Create four rectangles representing clickable playGroundGrids
    // Red Area
    sf::RectangleShape Heart(sf::Vector2f(300, 300));
    Heart.setFillColor(sf::Color(228,28,36,255));
    Heart.setPosition(0, 0);
    sf::RectangleShape heartSym(sf::Vector2f(200, 200));
    sf::Texture redTexture;
    if (redTexture.loadFromFile("images/red_heart.png")) {
        heartSym.setTexture(&redTexture);
    }
    heartSym.setPosition(50, 50);

    // Green Area
    sf::RectangleShape Spade(sf::Vector2f(300, 300));
    Spade.setFillColor(sf::Color(98,180,70,255));
    Spade.setPosition(450, 0);
    sf::RectangleShape spadeSym(sf::Vector2f(200, 200));
    sf::Texture greenTexture;
    if (greenTexture.loadFromFile("images/green_spade.png")) {
        spadeSym.setTexture(&greenTexture);
    }
    spadeSym.setPosition(500, 50);

    // Blue Area
    sf::RectangleShape Club(sf::Vector2f(300, 300));
    Club.setFillColor(sf::Color(30,112,185,255));
    Club.setPosition(0, 450);
    sf::RectangleShape clubSym(sf::Vector2f(200, 200));
    sf::Texture blueTexture;
    if (blueTexture.loadFromFile("images/blue_club.png")) {
        clubSym.setTexture(&blueTexture);
    }
    clubSym.setPosition(50, 500);

    // Yellow Area
    sf::RectangleShape Diamond(sf::Vector2f(300, 300));
    Diamond.setFillColor(sf::Color(254,205,7,255));
    Diamond.setPosition(450, 450);
    sf::RectangleShape diamondSym(sf::Vector2f(200, 200));
    sf::Texture yellowTexture;
    if (yellowTexture.loadFromFile("images/yellow_diamond.png")) {
        diamondSym.setTexture(&yellowTexture);
    }
    diamondSym.setPosition(500, 500);

    DICE.setFillColor(sf::Color::Black);
    DICE.setPosition(850, 50);
    // sf::Texture diceTexture;
    // if(diceTexture.loadFromFile("images/dice.png")){
    //     DICE.setTexture(&diceTexture);
    // }

    playerturn.setPosition(880, 250);

    // Center and Inside Center
    sf::RectangleShape center(sf::Vector2f(150, 150));
    sf::Texture centerTexture;
    if (centerTexture.loadFromFile("images/center.png")){
        center.setTexture(&centerTexture);
    }
    center.setPosition(300, 300);

    for(int i = 0; i < 52; ++i) {
        playGroundGrids[i].setSize(sf::Vector2f(50, 50));
        playGroundGrids[i].setOutlineColor(sf::Color::Black);
        playGroundGrids[i].setOutlineThickness(2);
        playGroundGrids[i].setFillColor(sf::Color::White);
        if(i<6)
            playGroundGrids[i].setPosition(400,(i*50));
        else if(i<12)
            playGroundGrids[i].setPosition(450 + ((i - 6) * 50), 300);
        else if(i==12)
            playGroundGrids[i].setPosition(700, 350);
        else if(i<19)
            playGroundGrids[i].setPosition(750 - (i - 12) * 50, 400);
        else if(i<25)
            playGroundGrids[i].setPosition(400, 400 + (i - 18) * 50);
        else if(i==25)
            playGroundGrids[i].setPosition(350, 700);
        else if(i<32)
            playGroundGrids[i].setPosition(300, 750 - (i - 25) * 50);
        else if(i<38)
            playGroundGrids[i].setPosition(300 - (i - 31) * 50, 400);
        else if(i==38)
            playGroundGrids[i].setPosition(0,350);
        else if(i<45)
            playGroundGrids[i].setPosition(-50 + (i - 38) * 50, 300);
        else if(i<51)
            playGroundGrids[i].setPosition(300, 250 - (i - 45) * 50);
        else if(i==51)
            playGroundGrids[i].setPosition(350,0);
    }

    // Starting points
    
    sf::Texture greenstop;
    if (greenstop.loadFromFile("images/greenstop.gif")){
        playGroundGrids[1].setTexture(&greenstop);
    }
    sf::Texture redstop;
    if (redstop.loadFromFile("images/redstop.gif")){
        playGroundGrids[40].setTexture(&redstop);
    }
    sf::Texture yellowstop;
    if (yellowstop.loadFromFile("images/yellowstop.gif")){
        playGroundGrids[14].setTexture(&yellowstop);
    }
    sf::Texture bluestop;
    if (bluestop.loadFromFile("images/bluestop.gif")){
        playGroundGrids[27].setTexture(&bluestop);
    }

    drawHomeGrids(greenHome, "green");
    drawHomeGrids(redHome, "red");
    drawHomeGrids(blueHome, "blue");
    drawHomeGrids(yellowHome, "yellow");

    // Create threads for each player
    pthread_t playerThreads[NO_PLAYERS];
    for (int i = 0; i < NO_PLAYERS; ++i){
        int* value = new int(i);
        pthread_create(&playerThreads[i], NULL, turn, value);
    }
    pthread_t masterThreadId;
    pthread_create(&masterThreadId, NULL, MasterThread, NULL);

    while (mainWindow.isOpen()) {
        sf::Event event;
        while (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                mainWindow.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if the mouse click is within any of the playGroundGrids
                    sf::Vector2i mousePos = sf::Mouse::getPosition(mainWindow);
                    if (Heart.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        cout << "Square 1 clicked!" << endl;
                    } else if (Spade.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        cout << "Square 2 clicked!" << endl;
                    } else if (Club.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        cout << "Square 3 clicked!" << endl;
                    } else if (Diamond.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        cout << "Square 4 clicked!" << endl;
                    }
                }
            }
        }

        mainWindow.clear(sf::Color::White);

        // Draw the playGroundGrids
        mainWindow.draw(Heart);
        mainWindow.draw(Spade);
        mainWindow.draw(Club);
        mainWindow.draw(Diamond);
        mainWindow.draw(DICE);
        mainWindow.draw(playerturn);

        mainWindow.draw(center);

        for(int i = 0; i < 52; ++i){
            mainWindow.draw(playGroundGrids[i]);
        }

        for(int i = 0; i < 5; ++i){
            mainWindow.draw(greenHome[i]);
            mainWindow.draw(redHome[i]);
            mainWindow.draw(blueHome[i]);
            mainWindow.draw(yellowHome[i]);
        }

        mainWindow.draw(heartSym);
        mainWindow.draw(diamondSym);
        mainWindow.draw(spadeSym);
        mainWindow.draw(clubSym);
        
        mainWindow.display();
    }
    // Join the threads
    for (int i = 0; i < NO_PLAYERS; ++i)
        pthread_join(playerThreads[i], NULL);

    return 0;
}

void drawHomeGrids(sf::RectangleShape *homeGrid, string color){

    for(int i=0; i<5; ++i){
        
        homeGrid[i].setSize(sf::Vector2f(50, 50));
        homeGrid[i].setOutlineColor(sf::Color::Black);
        homeGrid[i].setOutlineThickness(2);

        if(color == "green"){
            homeGrid[i].setFillColor(sf::Color(98,180,70,255));
            homeGrid[i].setPosition(350, 50 + (i*50));
        }else if(color == "red"){
            homeGrid[i].setFillColor(sf::Color(228,28,36,255));
            homeGrid[i].setPosition(50 + (i*50), 350);
        }else if(color == "blue"){
            homeGrid[i].setFillColor(sf::Color(30,112,185,255));
            homeGrid[i].setPosition(350, 650 - (i*50));
        }else if(color == "yellow"){
            homeGrid[i].setFillColor(sf::Color(254,205,7,255));
            homeGrid[i].setPosition(650 - (i*50), 350);
        }
    }
}


void inputWindow(){

    sf::Text Title;
    Title.setFont(mainFont);
    Title.setString("LUDO BOARD");
    Title.setCharacterSize(75);
    Title.setFillColor(sf::Color::White);
    Title.setPosition(40, 120);

    sf::Text printText;
    printText.setFont(secFont);
    printText.setString("No of Players");
    printText.setCharacterSize(40);
    printText.setFillColor(sf::Color::White);
    printText.setPosition(140,350);

    sf::RenderWindow window(sf::VideoMode(625, 900), "Ludo-Board Game");
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - window.getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - window.getSize().y / 2));
    sf::RectangleShape Background(sf::Vector2f(625, 900));
    sf::Texture tex;
    if (tex.loadFromFile("images/window-1.jpg")) {
        Background.setTexture(&tex);
    }
    Background.setPosition(0, 0);

    // window.display();
    int inputflag=0;

    sf::Text inputField;
    inputField.setFont(secFont);
    inputField.setCharacterSize(80);
    inputField.setFillColor(sf::Color::White);
    inputField.setPosition(275,450);
    string input;

    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == 8 && !input.empty()) { // Backspace
                        input.pop_back();
                    }else if (event.text.unicode == 13) { // Enter
                        if(inputflag==0){
                            NO_PLAYERS = stoi(input);
                            if(NO_PLAYERS<2 || NO_PLAYERS>4){
                                input.clear();
                                inputField.setString("");
                                continue;
                            }
                            input.clear();
                            inputflag=1;
                            cout<<"No of Player: "<<NO_PLAYERS<<endl;
                            
                            printText.setString("No of Tokens");
                            printText.setPosition(160,350);
                        }else if(inputflag==1){
                            NO_TOKENS = stoi(input);
                            if(NO_TOKENS<1 || NO_TOKENS>4){
                                input.clear();
                                inputField.setString("");
                                continue;
                            }
                            input.clear();
                            cout<<"No of Tokens: "<<NO_TOKENS<<endl;
                            window.close();
                        }
                    }
                    else{
                        input += static_cast<char>(event.text.unicode);
                    }
                    inputField.setString(input);
                }
            }
        }
        window.clear(sf::Color::White);
        window.draw(Background);
        window.draw(Title);
        window.draw(printText);
        window.draw(inputField);
        window.display();
    }
}

void initialize(){
    PLAYERS = new Player[NO_PLAYERS];
    string colors[4] = {"Red", "Green", "Blue", "Yellow"};
    int starts[4] = {40, 1, 27, 14};
    for(int i=0; i<NO_PLAYERS; ++i){
        PLAYERS[i].initializePlayer(colors[i], NO_TOKENS, starts[i], playerHomes[i]);
    }
}
void* turn(void* arg){
    int player_id = *((int*)arg);
    delete (int*)arg;
    while(true){
        while(PLAYERS[player_id].continue_running){

            PLAYERS[player_id].continue_running = false;    //blocking self untill next cycle turn
            
            pthread_mutex_lock(&turnMutex);
            
            DICE.setTexture(&shuffleDiceTexture);
            playerturn.setTexture(&PLAYERS[player_id].tokenTexture);
            
            while(mainWindow.isOpen()){
                sf::Event event;
                bool flag = false;
                while (mainWindow.pollEvent(event)) {
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(mainWindow);
                            if (DICE.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                while(PLAYERS[player_id].throwDice(&DICE));
                                flag = true;
                            }
                        }
                    }
                }
                if(flag)
                    break;
            }

            

            int ch;
            cout<<"Enter";
            cin>>ch;
            
            Cycle++;
            
            pthread_mutex_unlock(&turnMutex);
        }
    }
    return NULL;
}

void *MasterThread(void*){
    while(true){
        if(Cycle==NO_PLAYERS){
            Cycle=0;
            cout<<"Cycle Completed"<<endl;
            for(int i=0; i<NO_PLAYERS; ++i)
                PLAYERS[i].continue_running = true;
        }
    }
    return NULL;
}