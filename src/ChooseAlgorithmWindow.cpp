#include "ChooseAlgorithmWindow.h"

ChooseAlgorithmWindow::Button::Button() {
    clickedButton.setTexture(TextureManager::GetTexture("clicked_square_button"));
    unclickedButton.setTexture(TextureManager::GetTexture("unclicked_square_button"));
    checkMark.setTexture(TextureManager::GetTexture("check_mark"));
    clicked = false;
}

// draw button based on if it was clicked or not
void ChooseAlgorithmWindow::Button::draw(sf::RenderWindow &window, float x, float y) {
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

sf::FloatRect ChooseAlgorithmWindow::Button::getBounds() {
    return unclickedButton.getGlobalBounds();
}

ChooseAlgorithmWindow::ChooseAlgorithmWindow() {
    width = 1600;
    height = 1224;
    spriteChanger = 0;
    windowSprite.setTexture(TextureManager::GetTexture("window"));
    neutralClosed.setTexture(TextureManager::GetTexture("neutral_closed"));
    neutralOpen.setTexture(TextureManager::GetTexture("neutral_open"));
    mouthOpen = false;
}

// credit to: UF COP3503 Minesweeper Project PDF
void ChooseAlgorithmWindow::setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void ChooseAlgorithmWindow::ChooseAlgorithmScreen(bool &choseSortingAlgo) {

    // initializes a window
    sf::RenderWindow window(sf::VideoMode(width, height), "recipe finder: choose", sf::Style::Close);

    // got this cursor functionality from https://en.sfml-dev.org/forums/index.php?topic=27646.0
    sf::Image curimg;
    curimg.loadFromFile("files/sprites/cursor.png");
    sf::Cursor cur;
    cur.loadFromPixels(curimg.getPixelsPtr(), curimg.getSize(), sf::Vector2u(0,0));
    window.setMouseCursor(cur);

    // load a font
    sf::Font font;
    font.loadFromFile("files/monogram.ttf");

    // text to describe purpose
    sf::Text purpose("the purpose of this project is to compare two sorting algorithms", font);
    purpose.setStyle(sf::Text::Bold);
    purpose.setCharacterSize(60);
    setText(purpose, width/2.0f, height/2.0f - 300);

    sf::Text choose("so, please choose which sorting algorithm you would like to use:", font);
    choose.setStyle(sf::Text::Bold);
    choose.setCharacterSize(50);
    setText(choose, width/2.0f, height/2.0f - 200);

    sf::Text merge("merge sort", font);
    merge.setCharacterSize(50);
    setText(merge, width/2.0f + 25, height/2.0f);

    sf::Text quick("quick sort", font);
    quick.setCharacterSize(50);
    setText(quick, width/2.0f + 25, height/2.0f + 100);

    // set up window sprite
    windowSprite.setScale(8.0f, 8.0f);
    windowSprite.setPosition(width/2.0f - 135, height/2.0f + 200);

    // set up character sprites
    neutralClosed.setScale(4.0f, 4.0f);
    neutralClosed.setPosition(width/2.0f - 60, height/2.0f + 265);
    neutralOpen.setScale(4.0f, 4.0f);
    neutralOpen.setPosition(width/2.0f - 60, height/2.0f + 265);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            // if user clicked either button, that means they chose the sorting algorithm
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f coordinates(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (mergeSortButton.getBounds().contains(coordinates) && !quickSortButton.clicked) {
                        mergeSortButton.clicked = true;
                        choseSortingAlgo = true;
                    }
                    else if (quickSortButton.getBounds().contains(coordinates) && !mergeSortButton.clicked) {
                        quickSortButton.clicked = true;
                        choseSortingAlgo = true;
                    }
                }
            }
        }

        // draw background, text, and sprites
        sf::Color background(210, 214, 199);
        window.clear(background);
        window.draw(purpose);
        window.draw(choose);
        window.draw(merge);
        window.draw(quick);
        mergeSortButton.draw(window, width/2.0f - 125, height/2.0f - 21);
        quickSortButton.draw(window, width/2.0f - 125, height/2.0f + 80);
        window.draw(windowSprite);

        // alternate between two sprites
        if ((spriteChanger / 200) % 2 == 0) {
            window.draw(neutralOpen);
            spriteChanger++;
        } else {
            window.draw(neutralClosed);
            spriteChanger++;
        }

        window.display();

        // close window if the sorting algorithm was chosen
        if (mergeSortButton.clicked || quickSortButton.clicked) {
            sf::sleep(sf::seconds(0.5));
            window.close();
        }
    }
}
