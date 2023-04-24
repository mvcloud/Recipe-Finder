#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h"

class ThankYouWindow {
    int width, height;
    sf::Sprite windowSprite, lovelyClosed, lovelyOpen;
    bool open;

public:
    ThankYouWindow();
    void setText(sf::Text &text, float x, float y);
    void ThankYouScreen();
};

