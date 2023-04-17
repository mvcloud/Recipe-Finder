#include <iostream>
#include <map>
#include <set>
#include "recipe.h"
#include "GetData.h"
#include "WelcomeWindow.h"
#include "IngredientWindow.h"
using namespace std;

int main() {

    set<Recipe*> recipes = GetDataFromCSVFile();

    bool doneWithWelcome = false;
    WelcomeWindow welcome;
    doneWithWelcome = welcome.WelcomeScreen();

    if (doneWithWelcome) {
        IngredientWindow ingredientWindow;
        ingredientWindow.IngredientScreen();
    }

}
