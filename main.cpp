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
    sf::RectangleShape squares[18];
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 3; ++j) {
            int index = i * 3 + j;
            squares[index].setSize(sf::Vector2f(50, 50));
            
            if(find(y1_home.begin(), y1_home.end(), index) != y1_home.end()){
                squares[index].setFillColor(sf::Color::Green);
            }else{
                squares[index].setFillColor(sf::Color::White);
            }

            // squares[index].setFillColor(sf::Color::White);
            squares[index].setPosition(300 + (50 * j), 50 * i);
            squares[index].setOutlineThickness(2);
            squares[index].setOutlineColor(sf::Color::Black);
            window.draw(squares[index]);
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

        for(int i = 0; i < 18; ++i) {
            window.draw(squares[i]);
        }

        window.display();
    }

    return 0;
}
