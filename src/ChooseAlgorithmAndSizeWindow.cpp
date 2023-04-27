#include "ChooseAlgorithmAndSizeWindow.h"

ChooseAlgorithmAndSizeWindow::Button::Button() {
    clickedButton.setTexture(TextureManager::GetTexture("clicked_square_button"));
    unclickedButton.setTexture(TextureManager::GetTexture("unclicked_square_button"));
    checkMark.setTexture(TextureManager::GetTexture("check_mark"));
    clicked = false;
}

// draw button based on if it was clicked or not
void ChooseAlgorithmAndSizeWindow::Button::draw(sf::RenderWindow &window, float x, float y) {
    if (clicked) {
        clickedButton.setScale(1.5f, 1.5f);
        clickedButton.setPosition(x,y);
        window.draw(clickedButton);
        checkMark.setScale(2.0f, 2.0f);
        checkMark.setPosition(x + 6, y + 10);
        window.draw(checkMark);
    } else {
        unclickedButton.setScale(1.5f, 1.5f);
        unclickedButton.setPosition(x,y);
        window.draw(unclickedButton);
    }
}

sf::FloatRect ChooseAlgorithmAndSizeWindow::Button::getBounds() {
    return unclickedButton.getGlobalBounds();
}

ChooseAlgorithmAndSizeWindow::ChooseAlgorithmAndSizeWindow() {
    width = 1600;
    height = 1224;
    spriteChanger = 0;
    enteredMaxIngredients = false;
}

// credit to: UF COP3503 Minesweeper Project PDF
void ChooseAlgorithmAndSizeWindow::setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void ChooseAlgorithmAndSizeWindow::setUpTexts() {
    // load a font
    font.loadFromFile("files/monogram.ttf");

    // text to describe purpose
    purpose.setString("the purpose of this project is to compare two sorting algorithms");
    purpose.setFont(font);
    purpose.setStyle(sf::Text::Bold);
    purpose.setCharacterSize(60);
    setText(purpose, width/2.0f, height/2.0f - 300);

    choose.setString("so, please choose which sorting algorithm you would like to use:");
    choose.setFont(font);
    choose.setStyle(sf::Text::Bold);
    choose.setCharacterSize(50);
    setText(choose, width/2.0f, height/2.0f - 200);

    merge.setString("merge sort");
    merge.setFont(font);
    merge.setCharacterSize(50);
    setText(merge, width/2.0f + 25, height/2.0f);

    quick.setString("quick sort");
    quick.setFont(font);
    quick.setCharacterSize(50);
    setText(quick, width/2.0f + 25, height/2.0f + 100);

    max.setString("please enter the max number of ingredients you would like to have in the recipe:");
    max.setFont(font);
    max.setCharacterSize(50);
    setText(max, width/2.0f, height/2.0f + 300);

    displayNum.setFont(font);
    displayNum.setCharacterSize(50);
    setText(displayNum, width/2.0f, height/2.0f + 400);
}

void ChooseAlgorithmAndSizeWindow::draw(sf::RenderWindow &window) {
    window.draw(purpose);
    window.draw(choose);
    window.draw(merge);
    window.draw(quick);
    window.draw(max);
    window.draw(displayNum);
    mergeSortButton.draw(window, width/2.0f - 125, height/2.0f - 21);
    quickSortButton.draw(window, width/2.0f - 125, height/2.0f + 80);
}

void ChooseAlgorithmAndSizeWindow::ChooseAlgorithmScreen(bool &choseSortingAlgo, char &sortingAlgo, int& maxIngredients) {

    // initializes a window
    sf::RenderWindow window(sf::VideoMode(width, height), "recipe finder: choose", sf::Style::Close);

    setUpTexts();

    //set up cursor sprite
    // got this cursor functionality from https://en.sfml-dev.org/forums/index.php?topic=27646.0
    sf::Image curimg;
    curimg.loadFromFile("files/sprites/cursor.png");
    sf::Cursor cur;
    cur.loadFromPixels(curimg.getPixelsPtr(), curimg.getSize(), sf::Vector2u(0,0));
    window.setMouseCursor(cur);

    string maxIngredientInput = "";

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                //no sorting algorithm chosen
                sortingAlgo = 'n';
                window.close();
            }
            // if user clicked either button, that means they chose the sorting algorithm
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f coordinates(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (mergeSortButton.getBounds().contains(coordinates) && !quickSortButton.clicked) {
                        mergeSortButton.clicked = true;
                        choseSortingAlgo = true;
                        sortingAlgo = 'm';
                    }
                    else if (quickSortButton.getBounds().contains(coordinates) && !mergeSortButton.clicked) {
                        quickSortButton.clicked = true;
                        choseSortingAlgo = true;
                        sortingAlgo = 'q';
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                // delete one letter of the input
                if (event.key.code == sf::Keyboard::BackSpace) {
                    if (!maxIngredientInput.empty()) {
                        maxIngredientInput.pop_back();
                    }
                }
                // ingredient input is finished, add to set and start over
                else if (event.key.code == sf::Keyboard::Return) {
                    maxIngredients = stoi(maxIngredientInput);
                    enteredMaxIngredients = true;
                    maxIngredientInput = "";
                }
            }
            // add to input
            else if (event.type == sf::Event::TextEntered) {
                if (isdigit(event.text.unicode)) {
                    maxIngredientInput += event.text.unicode;
                }
            }
        }

        displayNum.setString(maxIngredientInput + '|');
        setText(displayNum, width/2.0f, height/2.0f + 400);

        // draw background, text, and sprites
        sf::Color background(210, 214, 199);
        window.clear(background);
        draw(window);
        window.display();

        // close window if the sorting algorithm was chosen
        if ((mergeSortButton.clicked || quickSortButton.clicked) && enteredMaxIngredients) {
            sf::sleep(sf::seconds(0.5));
            window.close();
        }
    }
}