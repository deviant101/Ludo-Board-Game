#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

    vector<int> y1_home = {4,5,7,10,13,16};
    vector<int> y2_home = {1,4,7,10,13,};
    vector<int> x1_home = {1,7,8,9,12,13};
    vector<int> x2_home = {1,4,7,10,13};

int main() {
    sf::RenderWindow window(sf::VideoMode(750, 750), "Ludo-Board Game");

    // Create four rectangles representing clickable squares
    sf::RectangleShape square1(sf::Vector2f(300, 300));
    square1.setFillColor(sf::Color::Red);
    square1.setPosition(0, 0);

    sf::RectangleShape square2(sf::Vector2f(300, 300));
    square2.setFillColor(sf::Color::Green);
    square2.setPosition(450, 0);

    sf::RectangleShape square3(sf::Vector2f(300, 300));
    square3.setFillColor(sf::Color::Blue);
    square3.setPosition(0, 450);

    sf::RectangleShape square4(sf::Vector2f(300, 300));
    square4.setFillColor(sf::Color::Yellow);
    square4.setPosition(450, 450);

    sf::RectangleShape center(sf::Vector2f(150, 150));
    center.setFillColor(sf::Color::Black);
    center.setPosition(300, 300);

    sf::RectangleShape insideCenter(sf::Vector2f(100, 100));
    insideCenter.setFillColor(sf::Color::Magenta);
    insideCenter.setPosition(325, 325);

    // Create the squares
    sf::RectangleShape squares[52];
    for(int i = 0; i < 52; ++i) {
        squares[i].setSize(sf::Vector2f(50, 50));
        squares[i].setOutlineColor(sf::Color::Black);
        squares[i].setOutlineThickness(2);
        squares[i].setFillColor(sf::Color::White);
        if(i<6){
            squares[i].setPosition(400,(i*50));
        }else if(i<12){
            squares[i].setPosition(450 + ((i - 6) * 50), 300);
        }else if(i==12){
            squares[i].setPosition(700, 350);
        }else if(i<19){
            squares[i].setPosition(750 - (i - 12) * 50, 400);
        }else if(i<25){
            squares[i].setPosition(400, 400 + (i - 18) * 50);
        }else if(i==25){
            squares[i].setPosition(350, 700);
        }else if(i<32){
            squares[i].setPosition(300, 750 - (i - 25) * 50);
        }else if(i<38){
            squares[i].setPosition(300 - (i - 31) * 50, 400);
        }else if(i==38){
            squares[i].setPosition(0,350);
        }else if(i<45){
            squares[i].setPosition(-50 + (i - 38) * 50, 300);
        }else if(i<51){
            squares[i].setPosition(300, 250 - (i - 45) * 50);
        }else if(i==51){
            squares[i].setPosition(350,0);
            // squares[i].setFillColor(sf::Color::Blue);
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if the mouse click is within any of the squares
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (square1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        cout << "Square 1 clicked!" << endl;
                    } else if (square2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        cout << "Square 2 clicked!" << endl;
                    } else if (square3.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        cout << "Square 3 clicked!" << endl;
                    } else if (square4.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        cout << "Square 4 clicked!" << endl;
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        // Draw the squares
        window.draw(square1);
        window.draw(square2);
        window.draw(square3);
        window.draw(square4);

        window.draw(center);
        window.draw(insideCenter);

        for(int i = 0; i < 52; ++i){
            window.draw(squares[i]);
        }

        window.display();
    }

    return 0;
}
