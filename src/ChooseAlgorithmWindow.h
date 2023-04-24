#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h"

class ChooseAlgorithmWindow {

    struct Button {
        sf::Sprite clickedButton, unclickedButton, checkMark;
        bool clicked;

        Button();
        void draw(sf::RenderWindow &window, float x, float y);
        sf::FloatRect getBounds();
    };

    int width, height;
    int spriteChanger;
    sf::Sprite windowSprite, neutralClosed, neutralOpen;
    bool mouthOpen;
    Button mergeSortButton, quickSortButton;


public:
    ChooseAlgorithmWindow();
    void setText(sf::Text &text, float x, float y);
    void ChooseAlgorithmScreen(bool &choseSortingAlgo);
};

