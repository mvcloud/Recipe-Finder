#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h"
#include <unordered_set>
using namespace std;

class IngredientWindow {
    int width, height;
    unordered_set<string> ingredientList;
    sf::Sprite clickedButton, unclickedButton, checkMark, dialogBox, veryHappyOpen, veryHappyClosed;
    bool clicked, entered;

public:
    IngredientWindow();
    void setText(sf::Text &text, float x, float y);
    void DrawButton(sf::RenderWindow &window);
    unordered_set<string> IngredientScreen();
};
