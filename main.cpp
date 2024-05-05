#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

// Create the playGroundGrids
sf::RectangleShape playGroundGrids[52];
sf::RectangleShape greenHome[5];
sf::RectangleShape redHome[5];
sf::RectangleShape blueHome[5];
sf::RectangleShape yellowHome[5];

void drawHomeGrids(sf::RectangleShape *homeGrid, string color, sf::RectangleShape *grids);

int main() {
    sf::RenderWindow window(sf::VideoMode(750, 750), "Ludo-Board Game");

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

    // Center and Inside Center
    sf::RectangleShape center(sf::Vector2f(150, 150));
    sf::Texture centerTexture;
    if (centerTexture.loadFromFile("images/center.png")) {
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

    drawHomeGrids(greenHome, "green", playGroundGrids);
    drawHomeGrids(redHome, "red",playGroundGrids);
    drawHomeGrids(blueHome, "blue",playGroundGrids);
    drawHomeGrids(yellowHome, "yellow",playGroundGrids);

    // sf::Texture token;
    // if(token.loadFromFile("images/diamond_tkn.png")){
    //     yellowHome[3].setTexture(&token);
    // }


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if the mouse click is within any of the playGroundGrids
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
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

        window.clear(sf::Color::White);

        // Draw the playGroundGrids
        window.draw(Heart);
        window.draw(Spade);
        window.draw(Club);
        window.draw(Diamond);

        window.draw(center);

        for(int i = 0; i < 52; ++i){
            window.draw(playGroundGrids[i]);
        }

        for(int i = 0; i < 5; ++i){
            window.draw(greenHome[i]);
            window.draw(redHome[i]);
            window.draw(blueHome[i]);
            window.draw(yellowHome[i]);
        }

        window.draw(heartSym);
        window.draw(diamondSym);
        window.draw(spadeSym);
        window.draw(clubSym);

        window.display();
    }

    return 0;
}

void drawHomeGrids(sf::RectangleShape *homeGrid, string color, sf::RectangleShape *grids){
    cout<<color<<endl;

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