#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include "recipe.h"
using namespace std;

// class that holds a vector of recipes
class Recipes {
    vector<Recipe*> recipes;

public:

    // only really need the destructor to delete the dynamically allocated recipes
    ~Recipes();

    // function to parse through the CSV file and add to the recipes vector
    void GetDataFromCSVFile(unordered_set<string> &userIngredients, int &maxIngredients);

    vector<Recipe*> getRecipeVector();
};

