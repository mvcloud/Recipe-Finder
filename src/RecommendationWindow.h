#pragma once
#include <sstream>
#include "TextureManager.h"
#include "SFML/Graphics.hpp"
using namespace std;

class RecommendationWindow {
    struct Button {
        sf::Sprite clickedButton, unclickedButton, checkMark, forwardArrow,
            backwardArrow, forwardArrowClicked, backwardArrowClicked;
        bool clicked;

        Button();
        void drawLeftAndRight(sf::RenderWindow &window, float x, float y, char type);
        void drawCheckList(sf::RenderWindow &window, float x, float y);
        void drawDecidedButton(sf::RenderWindow &window, float x, float y);
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
    sf::Text title, source, image, ingredientTitle, instructionsTitle, decided, done;
    sf::Font font;
    sf::Cursor cur;

public:
    RecommendationWindow(string &name, string &ingredients, string &instructions, string &link);
    void parseIngredients();
    void parseInstructions();
    void setText(sf::Text &text, float x, float y);
    void setUpSprites();
    void setUpTexts();
    void drawButtons(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
    char RecommendationScreen(bool &decidedReturn);
};
