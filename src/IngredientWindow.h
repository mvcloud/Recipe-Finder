#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h"
#include <unordered_set>
using namespace std;

class IngredientWindow {
    int width, height;
    unordered_set<string> ingredientList;
    sf::Sprite clickedButton, unclickedButton, checkMark, dialogBox, veryHappyOpen, veryHappyClosed;
    sf::Text title, enter, click, ingredient, encouragement;
    sf::Font font;
    sf::Cursor cur;
    bool clicked, entered;

public:
    IngredientWindow();
    void setText(sf::Text &text, float x, float y);
    void setUpSprites();
    void setUpTexts();
    void DrawButton(sf::RenderWindow &window);
    void drawAndDisplay(sf::RenderWindow &window);
    unordered_set<string> IngredientScreen();
};
