#pragma once
#include "SFML/Graphics.hpp"
#include "textures.h"

class WelcomeWindow {
    int width = 1600;
    int height = 1224;

public:
    void setText(sf::Text &text, float x, float y);
    bool WelcomeScreen();
};

//credit to: COP3503 Minesweeper Project PDF
void WelcomeWindow::setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

bool WelcomeWindow::WelcomeScreen() {
    // initializes a window
    sf::RenderWindow window(sf::VideoMode(width, height), "recipe finder: welcome", sf::Style::Close);

    //load a font
    sf::Font font;
    font.loadFromFile("files/monogram.ttf");

    //title
    sf::Text title("welcome to the recipe finder!", font);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setCharacterSize(80);
    setText(title, width/2.0f, height/2.0f - 300);

    //"made by" credits
    sf::Text credits("made by: maeson vallee, ria gandhi, and lyndsey laborde", font);
    credits.setCharacterSize(50);
    setText(credits, width/2.0f, height/2.0f);

    //start game text
    sf::Text start("press the space bar to begin!", font);
    start.setCharacterSize(50);
    setText(start, width/2.0f, height/2.0f + 100);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    return true;
                }
            }
        }

        sf::Color background(185, 202, 222);
        window.clear(background);
        window.draw(title);
        window.draw(credits);
        window.draw(start);
        window.display();
    }
    return false;
}