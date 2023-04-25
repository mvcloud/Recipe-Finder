#include "GetData.h"
using namespace std;

vector<Recipe*> GetDataFromCSVFile(unordered_set<string> &userIngredients) {

    ifstream file("files/data.csv");
    vector<Recipe*> recipeList;
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

            getline(stream, buffer, '"');
            getline(stream, buffer, '[');
            getline(stream, buffer, '"');

            getline(stream, ingredients, ']');
            ingredients.erase(std::remove(ingredients.begin(), ingredients.end(), '"'), ingredients.end());

            getline(stream, buffer, '"');
            getline(stream, buffer, '"');

            getline(stream, instructions, ']');
            instructions.erase(std::remove(instructions.begin(), instructions.end(), '"'), instructions.end());
            instructions.erase(std::remove(instructions.begin(), instructions.end(), '['), instructions.end());

            getline(stream, buffer, '"');
            getline(stream, buffer, ',');

            getline(stream, link, ',');

            getline(stream, buffer, ',');

            getline(stream, NER, ']');
            NER.erase(std::remove(NER.begin(), NER.end(), '['), NER.end());
            NER.erase(std::remove(NER.begin(), NER.end(), '"'), NER.end());

            Recipe* recipe = new Recipe(name,ingredients, instructions, link, NER);
            recipe->numMatching(userIngredients);
            if (recipe->getMatching() > 0) {
                recipeList.push_back(recipe);
            }
        }
    }
    return recipeList;
}
