#pragma once
#include "TextureManager.h"
#include "SFML/Graphics.hpp"
#include <sstream>
using namespace std;

class RecommendationWindow {

    struct Button {

        sf::Sprite clickedButton, unclickedButton, checkMark, forwardArrow,
            backwardArrow, forwardArrowClicked, backwardArrowClicked;
        bool clicked;

        Button();
        void draw(sf::RenderWindow &window, float x, float y, char type);
        sf::FloatRect getBounds();
    };

    int width, height;
    string name, ingredients, instructions, link;
    vector<string> ingredientsVector, instructionsVector;
    vector<Button> checkButtons;
    Button rightArrowButton, leftArrowButton, decidedButton;
    bool choseRecipe;
    int mouthOpen, spriteChanger;
    sf::Sprite windowSprite, laidBackClosed, laidBackOpen, coolOpen, coolClosed, dialogBox;

public:
    RecommendationWindow(string &name, string &ingredients, string &instructions, string &link);
    void setText(sf::Text &text, float x, float y);
    void drawButtons(sf::RenderWindow &window);
    char RecommendationScreen(bool &decidedReturn);
};
