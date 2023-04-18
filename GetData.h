#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "recipe.h"
#pragma once
using namespace std;

unordered_map<string, Recipe> GetDataFromCSVFile() {
    ifstream file("files/data.csv");
    unordered_map<string, Recipe> recipeList;

    if (file.is_open()) {
        string lineFromFile;
        getline(file, lineFromFile);
        while(getline(file, lineFromFile)) {
            istringstream stream(lineFromFile);

            string buffer; //we don't store buffers
            string name;
            string ingredients;
            string instructions;
            string link;
            string NER;


            getline(stream, buffer, ',');

            getline(stream, name, ',');
            //cout << name << endl;

            getline(stream, buffer, '"');
            getline(stream, buffer, '[');
            getline(stream, buffer, '"');

            getline(stream, ingredients, ']');
            ingredients.erase(std::remove(ingredients.begin(), ingredients.end(), '"'), ingredients.end());
            //cout << ingredients << endl;

            getline(stream, buffer, '"');
            getline(stream, buffer, '"');

            getline(stream, instructions, ']');
            instructions.erase(std::remove(instructions.begin(), instructions.end(), '"'), instructions.end());
            instructions.erase(std::remove(instructions.begin(), instructions.end(), '['), instructions.end());

            //cout << instructions << endl;

            getline(stream, buffer, '"');
            getline(stream, buffer, ',');

            getline(stream, link, ',');
            //cout << link << endl;

            getline(stream, buffer, ',');

            getline(stream, NER, ']');
            NER.erase(std::remove(NER.begin(), NER.end(), '['), NER.end());
            NER.erase(std::remove(NER.begin(), NER.end(), '"'), NER.end());
            //cout << NER << endl;

            //cout << endl;
            Recipe recipe(name,ingredients, instructions, link, NER);
            recipeList.emplace(name, recipe);

        }
    }
    return recipeList;
}
