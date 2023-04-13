#pragma once
#include <string>
#include <vector>
using namespace std;

class Recipe {
    string name;
    string ingredients;
    string instructions;
    string link;
    string NER;

public:
    //constructor
    Recipe(string &name, string &ingredients,
           string &instructions, string &link, string &NER);

    //accessors:
    string getName();
    string getIngredients();
    string getInstructions();
    string getLink();
    string getNER();
};
