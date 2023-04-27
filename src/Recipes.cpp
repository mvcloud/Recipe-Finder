#include <iostream>
#include "Recipes.h"
using namespace std;

Recipes::~Recipes() {
    for (int i = 0; i < recipes.size(); i++) {
        delete recipes[i];
    }
    recipes.clear();
}

void Recipes::GetDataFromCSVFile(unordered_set<string> &userIngredients, int &maxIngredients) {

    ifstream file("files/data.csv");
    if (file.is_open()) {
        string lineFromFile;
        getline(file, lineFromFile);

        while(getline(file, lineFromFile)) {
            istringstream stream(lineFromFile);

	    //we don't store buffers
            string buffer;
            string name;
            string ingredients;
            string instructions;
            string link;
            string NER;

            getline(stream, buffer, ',');

            getline(stream, name, ',');

            getline(stream, ingredients, ']');
            ingredients.erase(std::remove(ingredients.begin(), ingredients.end(), '['), ingredients.end());
            ingredients.erase(std::remove(ingredients.begin(), ingredients.end(), '"'), ingredients.end());

            getline(stream, instructions, ']');
            instructions.erase(std::remove(instructions.begin(), instructions.end(), '"'), instructions.end());
            instructions.erase(std::remove(instructions.begin(), instructions.end(), '['), instructions.end());
            instructions.erase(0,1);

            getline(stream, buffer, '"');
            getline(stream, buffer, ',');

            getline(stream, link, ',');

            getline(stream, buffer, ',');

            getline(stream, NER, ']');
            NER.erase(std::remove(NER.begin(), NER.end(), '['), NER.end());
            NER.erase(std::remove(NER.begin(), NER.end(), '"'), NER.end());

            Recipe* recipe = new Recipe(name,ingredients, instructions, link, NER);
            recipe->numMatching(userIngredients);

            if (recipe->getMatchingIngredients() > 0 && recipe->getTotalIngredients() <= maxIngredients) {
                recipes.push_back(recipe);
            }
            else {
                delete recipe;
            }
        }
    }
}

vector<Recipe*> Recipes::getRecipeVector() {
    return recipes;
}