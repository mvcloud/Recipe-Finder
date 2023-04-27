#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h"

class ChooseAlgorithmAndSizeWindow {

    struct Button {
        sf::Sprite clickedButton, unclickedButton, checkMark;
        bool clicked;

        Button();
        void draw(sf::RenderWindow &window, float x, float y);
        sf::FloatRect getBounds();
    };

    int width, height;
    int spriteChanger;
    sf::Text purpose, choose, merge, quick, max, displayNum;
    sf::Font font;
    sf::Cursor cur;
    bool enteredMaxIngredients;
    Button mergeSortButton, quickSortButton;

public:
    ChooseAlgorithmAndSizeWindow();
    void setText(sf::Text &text, float x, float y);
    void setUpTexts();
    void draw(sf::RenderWindow &window);
    void ChooseAlgorithmScreen(bool &choseSortingAlgo, char &sortingAlgo, int &maxIngredients);
};