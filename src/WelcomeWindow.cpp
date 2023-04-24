#include "WelcomeWindow.h"

WelcomeWindow::WelcomeWindow() {
    width = 1600;
    height = 1224;
    windowSprite.setTexture(TextureManager::GetTexture("window"));
    happyClosed.setTexture(TextureManager::GetTexture("happy_mouth_closed"));
    happyOpen.setTexture(TextureManager::GetTexture("happy_mouth_open"));
    mouthOpen = false;
}

// credit to: UF COP3503 Minesweeper Project PDF
void WelcomeWindow::setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

bool WelcomeWindow::WelcomeScreen() {
    // initializes a window
    sf::RenderWindow window(sf::VideoMode(width, height), "recipe finder: welcome", sf::Style::Close);

    // got this cursor functionality from https://en.sfml-dev.org/forums/index.php?topic=27646.0
    sf::Image curimg;
    curimg.loadFromFile("files/sprites/cursor.png");
    sf::Cursor cur;
    cur.loadFromPixels(curimg.getPixelsPtr(), curimg.getSize(), sf::Vector2u(0,0));
    window.setMouseCursor(cur);

    // load a font
    sf::Font font;
    font.loadFromFile("files/monogram.ttf");

    // title
    sf::Text title("welcome to the recipe finder!", font);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setCharacterSize(80);
    setText(title, width/2.0f, height/2.0f - 300);

    // "made by" credits
    sf::Text credits("made by: maeson vallee, ria gandhi, and lyndsey laborde", font);
    credits.setCharacterSize(50);
    setText(credits, width/2.0f, height/2.0f);

    // start game text
    sf::Text start("press the space bar to begin!", font);
    start.setCharacterSize(50);
    setText(start, width/2.0f, height/2.0f + 100);

    // set up window sprite
    windowSprite.setScale(8.0f, 8.0f);
    windowSprite.setPosition(width/2.0f - 135, height/2.0f + 200);

    // set up character sprites
    happyClosed.setScale(4.0f, 4.0f);
    happyClosed.setPosition(width/2.0f - 60, height/2.0f + 265);
    happyOpen.setScale(4.0f, 4.0f);
    happyOpen.setPosition(width/2.0f - 60, height/2.0f + 265);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
                // if the user pressed the space button, we are done with this window,
                // and we can open up the next one
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    return true;
                }
            }
        }

        // draw background, text, and sprites
        sf::Color background(210, 214, 199);
        window.clear(background);
        window.draw(title);
        window.draw(credits);
        window.draw(start);
        window.draw(windowSprite);

        // alternate between 2 sprites for the character
        if (mouthOpen) {
            window.draw(happyOpen);
            sf::sleep(sf::seconds(0.5));
            mouthOpen = false;
        }
        else if (!mouthOpen) {
            window.draw(happyClosed);
            sf::sleep(sf::seconds(0.5));
            mouthOpen = true;
        }
        window.display();
    }
    // don't open up next window
    return false;
}