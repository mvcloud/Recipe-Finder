#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h"

class ThankYouWindow {
    int width, height;
    sf::Sprite windowSprite, lovelyClosed, lovelyOpen;
    sf::Text title;
    sf::Font font;
    sf::Cursor cur;
    bool open;

public:
    ThankYouWindow();
    void setText(sf::Text &text, float x, float y);
    void setUpSprites();
    void setUpTexts();
    void draw(sf::RenderWindow &window);
    void ThankYouScreen();
};

