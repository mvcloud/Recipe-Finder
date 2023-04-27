#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h"

class WelcomeWindow {
    int width;
    int height;
    sf::Sprite windowSprite, happyClosed, happyOpen;
    sf::Text title, credits, start;
    sf::Font font;
    sf::Cursor cur;
    bool mouthOpen;

public:
    WelcomeWindow();
    void setText(sf::Text &text, float x, float y);
    void setUpSprites();
    void setUpTexts();
    void draw(sf::RenderWindow &window);
    bool WelcomeScreen();
};