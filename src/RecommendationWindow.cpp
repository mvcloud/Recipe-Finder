#include "RecommendationWindow.h"

RecommendationWindow::Button::Button() {
    clickedButton.setTexture(TextureManager::GetTexture("clicked_square_button"));
    unclickedButton.setTexture(TextureManager::GetTexture("unclicked_square_button"));
    checkMark.setTexture(TextureManager::GetTexture("check_mark"));
    forwardArrow.setTexture(TextureManager::GetTexture("forward_arrow"));
    backwardArrow.setTexture(TextureManager::GetTexture("backward_arrow"));
    forwardArrowClicked.setTexture(TextureManager::GetTexture("forward_arrow_clicked"));
    backwardArrowClicked.setTexture(TextureManager::GetTexture("backward_arrow_clicked"));
    clicked = false;
}

// function for drawing buttons, passing in the x,y position and the type of button (left or right)
void RecommendationWindow::Button::drawLeftAndRight(sf::RenderWindow &window, float x, float y, char type) {
    if (clicked) {
        clickedButton.setScale(2.5f, 2.5f);
        clickedButton.setPosition(x, y);
        window.draw(clickedButton);
        if (type == 'l') {
            backwardArrowClicked.setScale(3.0f, 3.0f);
            backwardArrowClicked.setPosition(x + 20, y + 15);
            window.draw(backwardArrowClicked);
        } else {
            forwardArrowClicked.setScale(3.0f, 3.0f);
            forwardArrowClicked.setPosition(x + 23, y + 15);
            window.draw(forwardArrowClicked);
        }
    }
    else if (!clicked) {
        unclickedButton.setScale(2.5f, 2.5f);
        unclickedButton.setPosition(x, y);
        window.draw(unclickedButton);
        if (type == 'l') {
            backwardArrow.setScale(3.0f, 3.0f);
            backwardArrow.setPosition(x + 20, y + 15);
            window.draw(backwardArrow);
        } else {
            forwardArrow.setScale(3.0f, 3.0f);
            forwardArrow.setPosition(x + 23, y + 15);
            window.draw(forwardArrow);

        }
    }
}

// function for drawing the checklist buttons
void RecommendationWindow::Button::drawCheckList(sf::RenderWindow &window, float x, float y) {
    if (clicked) {
        clickedButton.setPosition(x, y);
        checkMark.setScale(1.5f, 1.5f);
        checkMark.setPosition(x + 2.5f, y + 6);
        window.draw(clickedButton);
        window.draw(checkMark);
    }
    else if (!clicked) {
        unclickedButton.setPosition(x, y);
        window.draw(unclickedButton);
    }
}

// function for drawing the "i choose this recipe" button
void RecommendationWindow::Button::drawDecidedButton(sf::RenderWindow &window, float x, float y) {
    if (clicked) {
        clickedButton.setScale(1.5f, 1.5f);
        clickedButton.setPosition(x, y);
        checkMark.setScale(2.0f, 2.0f);
        checkMark.setPosition(x + 6, y + 10);
        window.draw(clickedButton);
        window.draw(checkMark);
    }
    else if (!clicked) {
        unclickedButton.setScale(1.5f, 1.5f);
        unclickedButton.setPosition(x, y);
        window.draw(unclickedButton);
    }
}

// get bounds of the button
sf::FloatRect RecommendationWindow::Button::getBounds() {
    return unclickedButton.getGlobalBounds();
}

RecommendationWindow::RecommendationWindow(string &name, string &ingredients, string &instructions, string &link) {
    this->name = name;
    this->ingredients = ingredients;
    this->instructions = instructions;
    this->link = link;
    width = 1600;
    height = 1224;
    choseRecipe = false;
    mouthOpen = 0;
    spriteChanger = 0;

    parseIngredients();
    parseInstructions();

    // initialize size of the checklist buttons vector
    vector<Button> checkButtonTemp(ingredientsVector.size());
    checkButtons = checkButtonTemp;

    windowSprite.setTexture(TextureManager::GetTexture("window"));
    laidBackClosed.setTexture(TextureManager::GetTexture("laid_back_happy"));
    laidBackOpen.setTexture(TextureManager::GetTexture("laid_back_open"));
    coolClosed.setTexture(TextureManager::GetTexture("cool_closed"));
    coolOpen.setTexture(TextureManager::GetTexture("cool_open"));
    dialogBox.setTexture(TextureManager::GetTexture("dialog_box_big"));
}

void RecommendationWindow::parseIngredients() {
    // got this from https://www.geeksforgeeks.org/program-to-parse-a-comma-separated-string-in-c/
    // to remember how to parse through comma separated string
    stringstream ss(ingredients);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        if (std::any_of(substr.begin(), substr.end(), ::isdigit)) {
            ingredientsVector.push_back(substr);
        }
    }
    // add a space in the first ingredient, so it matches the rest
    ingredientsVector[0] = ' ' + ingredientsVector[0];
}

void RecommendationWindow::parseInstructions() {
    // parse through instructions string and get rid of unnecessary characters
    for (int i = 0; i < instructions.size(); i++) {
        if (instructions[i] == '.' && i < instructions.size() - 1) {
            if (instructions[i+1] == ',') {
                instructions.erase(i+1, 1);
            }
        }
    }

    // split up the instructions into bits and add each substring to vector
    for (int i = 0; i < instructions.size(); i++) {
        if (instructions.size() >= 46) {
            string substrTemp = instructions.substr(0, 45);
            if (isalpha(substrTemp[substrTemp.size()-1]) && isalpha(instructions[substrTemp.size()]))
                substrTemp += '-';

            instructionsVector.push_back(substrTemp);
            instructions = instructions.substr(45);
        }
        else break;
    }
    instructionsVector.push_back(instructions);
}

// credit to: UF COP3503 Minesweeper Project PDF
void RecommendationWindow::setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void RecommendationWindow::setUpSprites() {

    // got this cursor functionality from https://en.sfml-dev.org/forums/index.php?topic=27646.0
    sf::Image curimg;
    curimg.loadFromFile("files/sprites/cursor.png");
    cur.loadFromPixels(curimg.getPixelsPtr(), curimg.getSize(), sf::Vector2u(0,0));

    // sprite for the window, 216-
    windowSprite.setScale(3.0f, 3.0f);
    windowSprite.setPosition(50, 40);

    // sprites for the character
    laidBackClosed.setScale(1.75f, 1.75f);
    laidBackClosed.setPosition(75, 60);
    laidBackOpen.setScale(1.75f, 1.75f);
    laidBackOpen.setPosition(75, 60);
    coolOpen.setScale(1.75f, 1.75f);
    coolOpen.setPosition(75, 60);
    coolClosed.setScale(1.75f, 1.75f);
    coolClosed.setPosition(75, 60);

    //sprite for the dialog box
    dialogBox.setScale(2.0f, 1.0f);
    dialogBox.setPosition(150, 50);
}

void RecommendationWindow::setUpTexts() {
    // load a font
    font.loadFromFile("files/monogram.ttf");

    // instructions for entering the ingredients
    title.setString("we recommend: " + name + "!");
    title.setFont(font);
    title.setStyle(sf::Text::Bold);
    title.setCharacterSize(80);
    setText(title, width/2.0f, 125);

    // link text
    source.setString("link to recipe: " + link);
    source.setFont(font);
    source.setCharacterSize(40);
    setText(source, width/2.0f, height - 100);

    // google images text
    image.setString("feel free to look up what this recipe looks like on https://images.google.com/");
    image.setFont(font);
    image.setCharacterSize(40);
    setText(image, width/2.0f, height - 50);

    // "ingredients" title
    ingredientTitle.setString("ingredients:");
    ingredientTitle.setFont(font);
    ingredientTitle.setStyle(sf::Text::Underlined);
    ingredientTitle.setCharacterSize(60);
    ingredientTitle.setPosition(115, 150);

    // "instructions" title
    instructionsTitle.setString("instructions:");
    instructionsTitle.setFont(font);
    instructionsTitle.setStyle(sf::Text::Underlined);
    instructionsTitle.setCharacterSize(60);
    instructionsTitle.setPosition(width/2.0f + 75, 150);

    // decide on recipe
    decided.setString("i choose this recipe!");
    decided.setFont(font);
    decided.setStyle(sf::Text::Bold | sf::Text::Underlined);
    decided.setCharacterSize(50);
    decided.setPosition(width/2.0f - 150, height - 200);

    // text for when user is done
    done.setString("click me when you are done!");
    done.setFont(font);
    done.setStyle(sf::Text::Bold);
    done.setCharacterSize(30);
    done.setPosition(171, 50);
}

// function to draw buttons, calls the individual draw functions
void RecommendationWindow::drawButtons(sf::RenderWindow &window) {
    if (!choseRecipe) {
        leftArrowButton.drawLeftAndRight(window, 50, height - 115, 'l');
        rightArrowButton.drawLeftAndRight(window, width - 115, height - 115, 'r');
    }
    for (int i = 0; i < checkButtons.size(); i++) {
        checkButtons[i].drawCheckList(window, 75, (i * 40) + 241);
    }
    decidedButton.drawDecidedButton(window, width/2.0f - 225, height - 180);
}

// function to draw sprites and texts
void RecommendationWindow::draw(sf::RenderWindow &window) {
    // draw ingredients list
    for (int i = 0; i < ingredientsVector.size(); i++) {
        sf::Text ingredient(ingredientsVector[i], font);
        ingredient.setCharacterSize(40);
        ingredient.setPosition(100, (i * 40) + 225);
        window.draw(ingredient);
    }

    // draw instructions
    for (int i = 0; i < instructionsVector.size(); i++) {
        sf::Text instruction(instructionsVector[i], font);
        instruction.setCharacterSize(40);
        instruction.setPosition(width/2.0f + 75, (i * 40) + 225);
        window.draw(instruction);
    }

    // draw other text and sprites
    window.draw(title);
    window.draw(source);
    window.draw(image);
    window.draw(ingredientTitle);
    window.draw(instructionsTitle);
    window.draw(decided);
    drawButtons(window);
    window.draw(windowSprite);

    // alternate between 2 sprites
    if ((spriteChanger / 500) % 2 == 0) {
        window.draw(laidBackOpen);
        spriteChanger++;
    } else {
        window.draw(laidBackClosed);
        spriteChanger++;
    }

    // alternate between 2 sprites
    if (choseRecipe) {
        if ((mouthOpen / 300) % 2 == 0) {
            window.draw(coolOpen);
            mouthOpen++;
        } else {
            window.draw(coolClosed);
            mouthOpen++;
        }
    }

    if (choseRecipe) {
        window.draw(dialogBox);
        window.draw(done);
    }
}

char RecommendationWindow::RecommendationScreen(bool &decidedReturn) {
    char decision = ' ';

    // initializes a window
    sf::RenderWindow window(sf::VideoMode(width, height), "recipe finder: recommendation", sf::Style::Close);
    setUpTexts();
    setUpSprites();
    window.setMouseCursor(cur);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // if user is done, close window and break the loop in main
            if (event.type == sf::Event::Closed){
                window.close();
                return 'd';
            }
            // check if any of the buttons/sprites has been clicked
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f coordinates(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (int i = 0; i < checkButtons.size(); i++) {
                        if (checkButtons[i].getBounds().contains(coordinates))
                            checkButtons[i].clicked = !checkButtons[i].clicked;
                    }
                    // if it has been clicked tell main that we need the previous recipe
                    if (leftArrowButton.getBounds().contains(coordinates)) {
                        if (!rightArrowButton.clicked) {
                            leftArrowButton.clicked = true;
                            decision = 'l';
                        }
                    }
                    // if it has been clicked tell main that we need the next recipe
                    else if (rightArrowButton.getBounds().contains(coordinates)) {
                        if (!leftArrowButton.clicked) {
                            rightArrowButton.clicked = true;
                            decision = 'r';
                        }
                    }
                    // user has clicked the button that solidifies their recipe of choice
                    else if (decidedButton.getBounds().contains(coordinates)) {
                        if (!decidedButton.clicked) {
                            decidedButton.clicked = true;
                            choseRecipe = true;
                            sf::sleep(sf::seconds(0.5));
                        }
                    }
                    // if the sprite has been clicked, close the window, change the bool, and return done
                    else if (windowSprite.getGlobalBounds().contains(coordinates)) {
                        if (choseRecipe) {
                            sf::sleep(sf::seconds(0.5));
                            window.close();
                            decidedReturn = true;
                            return 'd';
                        }
                    }
                }
            }
        }

        // draw everything
        sf::Color background(210, 214, 199);
        window.clear(background);
        draw(window);
        window.display();

        // close window if left or right button is clicked
        if (leftArrowButton.clicked || rightArrowButton.clicked) {
            sf::sleep(sf::seconds(0.5));
            window.close();
        }
    }
    return decision;
}
