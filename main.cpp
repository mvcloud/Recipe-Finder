#include <iostream>
#include <unordered_map>
#include "recipe.h"
#include "GetData.h"
#include "WelcomeWindow.h"
#include "IngredientWindow.h"
using namespace std;

int main() {

    unordered_map<string, Recipe> recipes = GetDataFromCSVFile();

    bool doneWithWelcome = false;
    WelcomeWindow welcome;
    doneWithWelcome = welcome.WelcomeScreen();

    if (doneWithWelcome) {
        IngredientWindow ingredientWindow;
        ingredientWindow.IngredientScreen();
    }

}
