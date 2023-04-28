#include "ThankYouWindow.h"

ThankYouWindow::ThankYouWindow() {
    width = 1600;
    height = 1224;
    windowSprite.setTexture(TextureManager::GetTexture("window"));
    lovelyClosed.setTexture(TextureManager::GetTexture("lovely_closed"));
    lovelyOpen.setTexture(TextureManager::GetTexture("lovely_open"));
    open = false;
}

// credit to: UF COP3503 Minesweeper Project PDF
void ThankYouWindow::setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void ThankYouWindow::setUpSprites() {

    // got this cursor functionality from https://en.sfml-dev.org/forums/index.php?topic=27646.0
    sf::Image curimg;
    curimg.loadFromFile("files/sprites/cursor.png");
    cur.loadFromPixels(curimg.getPixelsPtr(), curimg.getSize(), sf::Vector2u(0,0));

    // set up window sprite
    windowSprite.setScale(10.0f, 10.0f);
    windowSprite.setPosition(width/2.0f - 150, height/2.0f - 100);

    // set up character sprites
    lovelyClosed.setScale(5.0f, 5.0f);
    lovelyClosed.setPosition(width/2.0f - 60, height/2.0f -20);
    lovelyOpen.setScale(5.0f, 5.0f);
    lovelyOpen.setPosition(width/2.0f - 60, height/2.0f - 20);
}

void ThankYouWindow::setUpTexts() {
    // load a font
    font.loadFromFile("files/monogram.ttf");

    // thank you message
    title.setString("thank you for choosing \'the recipe finder\'!");
    title.setFont(font);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setCharacterSize(80);
    setText(title, width/2.0f, height/2.0f - 200);
}

// function to draw everything
void ThankYouWindow::draw(sf::RenderWindow &window) {
    window.draw(title);
    window.draw(windowSprite);

    // alternate between 2 sprites
    if (open) {
        window.draw(lovelyOpen);
        sf::sleep(sf::seconds(0.5));
        open = false;
    }
    else if (!open) {
        window.draw(lovelyClosed);
        sf::sleep(sf::seconds(0.5));
        open = true;
    }
}

void ThankYouWindow::ThankYouScreen() {

    // initializes a window
    sf::RenderWindow window(sf::VideoMode(width, height), "recipe finder: thank you for playing!", sf::Style::Close);

    setUpSprites();
    setUpTexts();
    window.setMouseCursor(cur);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // draw background, text, and sprites
        sf::Color background(210, 214, 199);
        window.clear(background);
        draw(window);
        window.display();
    }
}
