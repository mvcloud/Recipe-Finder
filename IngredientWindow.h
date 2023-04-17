#pragma once
#include "SFML/Graphics.hpp"
#include "textures.h"
#include <set>

class IngredientWindow {
    int width = 1600;
    int height = 1224;
    set<string> ingredientList;
    sf::Sprite clickedButton, unclickedButton, checkMark;
    bool clicked = false;

public:
    IngredientWindow();
    void setText(sf::Text &text, float x, float y);
    void DrawButtons(sf::RenderWindow &window);
    set<string> IngredientScreen();
};

IngredientWindow::IngredientWindow() {
    clickedButton.setTexture(TextureManager::GetTexture("clicked_square_button"));
    unclickedButton.setTexture(TextureManager::GetTexture("unclicked_square_button"));
    checkMark.setTexture(TextureManager::GetTexture("check_mark"));
}

void IngredientWindow::setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void IngredientWindow::DrawButtons(sf::RenderWindow &window) {
    if (clicked) {
        clickedButton.setScale(2.5f, 2.5f);
        clickedButton.setPosition(width/2.0f - 40, height/2.0f + 400);
        window.draw(clickedButton);
    }
    else {
        unclickedButton.setScale(2.5f, 2.5f);
        unclickedButton.setPosition(width/2.0f - 40, height/2.0f + 400);
        window.draw(unclickedButton);
    }
    checkMark.setScale(3.0f, 3.0f);
    checkMark.setPosition(width/2.0f -27, height/2.0f + 417);
    window.draw(checkMark);
}


set<string> IngredientWindow::IngredientScreen() {

    // initializes a window
    sf::RenderWindow window(sf::VideoMode(width, height), "recipe finder: enter ingredients", sf::Style::Close);

    //load a font
    sf::Font font;
    font.loadFromFile("files/monogram.ttf");

    //instructions for entering the ingredients
    sf::Text title("please insert the ingredients you would like to use:", font);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setCharacterSize(60);
    setText(title, width/2.0f, height/2.0f - 300);

    //instructions for entering the ingredients
    sf::Text enter("press enter/return after each ingredient", font);
    enter.setCharacterSize(40);
    setText(enter, width/2.0f, height/2.0f - 200);

    sf::Text click("click the checkbox when you are done! :)", font);
    click.setCharacterSize(40);
    setText(click, width/2.0f, height/2.0f - 150);

    //ingredient input textbox
    sf::Text ingredient("", font);
    ingredient.setStyle(sf::Text::Bold);
    ingredient.setCharacterSize(50);
    setText(ingredient, width/2.0f, height/2.0f + 200);

    string ingredientInput = "";


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    ingredientInput += " ";
                }
                else if (event.key.code == sf::Keyboard::BackSpace) {
                    if (!ingredientInput.empty()) {
                        ingredientInput.pop_back();
                    }
                }
                else if (event.key.code == sf::Keyboard::Return) {
                    ingredientList.emplace(ingredientInput);
                    ingredientInput = "";
                }
            }
            else if (event.type == sf::Event::TextEntered) {
                if (isalpha(event.text.unicode)) {
                    ingredientInput += event.text.unicode;
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f coordinates(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (unclickedButton.getGlobalBounds().contains(coordinates))
                        clicked = true;
                }
            }
        }

        ingredient.setString(ingredientInput + '|');
        setText(ingredient, width/2.0f, height/2.0f + 200);

        sf::Color background(185, 202, 222);
        window.clear(background);
        window.draw(title);
        window.draw(enter);
        window.draw(ingredient);
        window.draw(click);
        DrawButtons(window);
        window.display();
    }
    //maybe have to fix
    return ingredientList;
}

