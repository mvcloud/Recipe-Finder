#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h"

class WelcomeWindow {
    int width;
    int height;
    sf::Sprite windowSprite, happyClosed, happyOpen;
    bool mouthOpen;

public:
    WelcomeWindow();
    void setText(sf::Text &text, float x, float y);
    bool WelcomeScreen();
};
