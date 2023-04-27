#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <fstream>
using namespace std;

// class for each individual recipe
class Recipe {
    string name;
    string ingredients;
    string instructions;
    string link;
    string NER;
    int matchingIngredients;
    int totalIngredients;
	
public:
    Recipe(string &name, string &ingredients,
           string &instructions, string &link, string &NER);

    string getName();

    string getIngredients();

    string getInstructions();

    string getLink();

    string getNER();

    int getMatchingIngredients();

    int getTotalIngredients();

    // function to find matching ingredients between the recipe and userIngredients
    void numMatching(unordered_set<string> &userIngredients);
};