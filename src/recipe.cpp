#include "recipe.h"
using namespace std;

Recipe::Recipe(string &name, string &ingredients, string &instructions,
               string &link, string &NER) {
    this->name = name;
    this->ingredients = ingredients;
    this->instructions = instructions;
    this->link = link;
    this->NER = NER;
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

int Recipe::getMatching() {
    return matchingIngredients;
}

void Recipe::numMatching(unordered_set<std::string> &userIngredients) {
    // break ingredients string into separate strings (NER) before adding to data structure in GetData
    // source: https://www.geeksforgeeks.org/program-to-parse-a-comma-separated-string-in-c/

    vector<string> recipeIngredients;
    stringstream ss(NER);
    while (ss.good()) {
        string substring;
        getline(ss, substring, ',');
        if (substring.substr(0, 1) == " ") {
            recipeIngredients.push_back(substring.substr(1));
        }
        else {
            recipeIngredients.push_back(substring);
        }
    }

    // iterate through vector to compare with user input for this recipe
    int matches = 0;
    for (int i = 0; i < recipeIngredients.size(); i++) {
        if (userIngredients.find(recipeIngredients[i]) != userIngredients.end()) { // user has that ingredient
            matches++;
        }
    }
    matchingIngredients = matches;
}
