#include "recipe.h"
using namespace std;

Recipe::Recipe(string &name, string &ingredients, string &instructions,
               string &link, string &NER) {
    this->name = name;
    this->ingredients = ingredients;
    this->instructions = instructions;
    this->link = link;
    this->NER = NER;
    this->matchingIngredients = 0;
}

//accessors:
string Recipe::getName() {
    return name;
}

string Recipe::getIngredients() {
    return ingredients;
}

string Recipe::getInstructions() {
    return instructions;
}

string Recipe::getLink() {
    return link;
}

string Recipe::getNER() {
    return NER;
}

//mutator:
void Recipe::changeMatching(int &matching) {
    matchingIngredients = matching;
}
