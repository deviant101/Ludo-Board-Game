#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

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

        window.display();
    }

    return 0;
}
