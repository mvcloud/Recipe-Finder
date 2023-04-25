#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
using namespace std;

class Recipe {
    string name;
    string ingredients;
    string instructions;
    string link;
    string NER;
    int matchingIngredients;

public:
    //constructor
    Recipe(string &name, string &ingredients,
           string &instructions, string &link, string &NER);

    //accessors:
    string getName();

    string getIngredients();

    string getInstructions();

    string getLink();

    int getMatching();

    // function to find matching ingredients between the recipe and userIngredients
    void numMatching(unordered_set<string> &userIngredients);
};
