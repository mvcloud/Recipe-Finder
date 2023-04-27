#include "IngredientWindow.h"
#include "WordsOfEncouragement.h"

IngredientWindow::IngredientWindow() {
    width = 1600;
    height = 1224;
    clickedButton.setTexture(TextureManager::GetTexture("clicked_square_button"));
    unclickedButton.setTexture(TextureManager::GetTexture("unclicked_square_button"));
    checkMark.setTexture(TextureManager::GetTexture("check_mark"));
    dialogBox.setTexture(TextureManager::GetTexture("dialog_box_full"));
    veryHappyOpen.setTexture(TextureManager::GetTexture("very_happy_open"));
    veryHappyClosed.setTexture(TextureManager::GetTexture("very_happy_closed"));
    clicked = false;
    entered = false;
}

//credit to: UF COP3503 Minesweeper Project PDF
void IngredientWindow::setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void IngredientWindow::setUpSprites() {
    // set up cursor
    // got this cursor functionality from https://en.sfml-dev.org/forums/index.php?topic=27646.0
    sf::Image curimg;
    curimg.loadFromFile("files/sprites/cursor.png");
    cur.loadFromPixels(curimg.getPixelsPtr(), curimg.getSize(), sf::Vector2u(0,0));

    // set up sprite for diolog box
    dialogBox.setScale(3.0f, 3.0f);
    dialogBox.setPosition(443, 525);

    // set up sprites for the character
    veryHappyClosed.setScale(3.0f, 3.0f);
    veryHappyClosed.setPosition(497, 576);
    veryHappyOpen.setScale(3.0f, 3.0f);
    veryHappyOpen.setPosition(497, 576);
}

void IngredientWindow::setUpTexts() {
    // load a font
    font.loadFromFile("files/monogram.ttf");

    // instructions for entering the ingredients
    title.setString("please insert the ingredients you would like to use:");
    title.setFont(font);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setCharacterSize(60);
    setText(title, width/2.0f, height/2.0f - 300);

    // instructions for entering the ingredients
    enter.setString("press enter/return after each ingredient");
    enter.setFont(font);
    enter.setCharacterSize(40);
    setText(enter, width/2.0f, height/2.0f - 200);

    // instructions to click the checkbox when done
    click.setString("click the checkbox when you are done! :)");
    click.setFont(font);
    click.setCharacterSize(40);
    setText(click, width/2.0f, height/2.0f - 150);

    // ingredient input textbox
    ingredient.setFont(font);
    ingredient.setStyle(sf::Text::Bold);
    ingredient.setCharacterSize(50);
    setText(ingredient, width/2.0f, height/2.0f + 200);

    // text for the character's words of encouragement
    encouragement.setFont(font);
    encouragement.setStyle(sf::Text::Bold);
    encouragement.setCharacterSize(40);
    encouragement.setPosition(650, 603);
}

// function to draw button, based on if it was clicked or not
void IngredientWindow::DrawButton(sf::RenderWindow &window) {
    if (clicked) {
        clickedButton.setScale(2.5f, 2.5f);
        clickedButton.setPosition(width/2.0f - 40, height/2.0f + 400);
        window.draw(clickedButton);
        checkMark.setScale(3.0f, 3.0f);
        checkMark.setPosition(width/2.0f -27, height/2.0f + 417);
        window.draw(checkMark);
    } else {
        unclickedButton.setScale(2.5f, 2.5f);
        unclickedButton.setPosition(width/2.0f - 40, height/2.0f + 400);
        window.draw(unclickedButton);
    }
}

// function to draw and display everything
void IngredientWindow::drawAndDisplay(sf::RenderWindow &window) {
    window.draw(title);
    window.draw(enter);
    window.draw(ingredient);
    window.draw(click);
    window.draw(dialogBox);
    DrawButton(window);

    // draw alternating characters
    if (entered) {
        window.draw(veryHappyOpen);
        Encouragement saying;
        encouragement.setString(saying.RandomEncouragement());
        window.draw(encouragement);
        window.display();
        sf::sleep(sf::seconds(1));
        entered = false;
    } 
    else {
        window.draw(veryHappyClosed);
        window.display();
    }
}

unordered_set<string> IngredientWindow::IngredientScreen() {
    // initializes a window
    sf::RenderWindow window(sf::VideoMode(width, height), "recipe finder: enter ingredients", sf::Style::Close);

    setUpTexts();
    setUpSprites();
    window.setMouseCursor(cur);

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
                // add a space to the input
                if (event.key.code == sf::Keyboard::Space) {
                    ingredientInput += " ";
                }
                    // delete one letter of the input
                else if (event.key.code == sf::Keyboard::BackSpace) {
                    if (!ingredientInput.empty()) {
                        ingredientInput.pop_back();
                    }
                }
                // ingredient input is finished, add to set and start over
                else if (event.key.code == sf::Keyboard::Return) {
                    ingredientList.emplace(ingredientInput);
                    ingredientInput = "";
                    entered = true;
                }
            }
            // add to input
            else if (event.type == sf::Event::TextEntered) {
                if (isalpha(event.text.unicode)) {
                    ingredientInput += event.text.unicode;
                }
            }
            //done with input
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f coordinates(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (unclickedButton.getGlobalBounds().contains(coordinates))
                        clicked = true;
                }
            }
        }

        // display the input as it is typed
        ingredient.setString(ingredientInput + '|');
        setText(ingredient, width/2.0f, height/2.0f + 200);

        // set up background, text, and sprites
        sf::Color background(210, 214, 199);
        window.clear(background);
        drawAndDisplay(window);

        // close window if button was clicked
        if (clicked) {
            window.close();
        }

    }
    // return ingredient set
    return ingredientList;
}