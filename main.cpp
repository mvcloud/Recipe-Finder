#include <iostream>
#include <unordered_map>
#include "recipe.h"
#include "GetData.h"
#include "WelcomeWindow.h"
#include "IngredientWindow.h"
#include "RecommendationWindow.h"
using namespace std;

/*
 * No-Bake Nut Cookies
1 c. firmly packed brown sugar, 1/2 c. evaporated milk, 1/2 tsp. vanilla, 1/2 c. broken nuts (pecans), 2 Tbsp. butter or margarine, 3 1/2 c. bite size shredded rice biscuits
In a heavy 2-quart saucepan, mix brown sugar, nuts, evaporated milk and butter or margarine., Stir over medium heat until mixture bubbles all over top., Boil and stir 5 minutes more. Take off heat., Stir in vanilla and cereal; mix well., Using 2 teaspoons, drop and shape into 30 clusters on wax paper., Let stand until firm, about 30 minutes.
www.cookbooks.com/Recipe-Details.aspx?id=44874
brown sugar, milk, vanilla, nuts, butter, bite size shredded rice biscuits
 * */


int main() {

    bool doneWithWelcome = false;
    WelcomeWindow welcome;
    doneWithWelcome = welcome.WelcomeScreen();

    unordered_set<string> userIngredients;

    if (doneWithWelcome) {
        IngredientWindow ingredientWindow;
        userIngredients = ingredientWindow.IngredientScreen();
    }

    if (!userIngredients.empty()) {
        unordered_map<string, Recipe*> recipes = GetDataFromCSVFile(userIngredients);

        //testing
        string name = "No-Bake Nut Cookies";
        string ingredients = "1 c. firmly packed brown sugar, 1/2 c. evaporated milk, 1/2 tsp. vanilla, 1/2 c. broken nuts (pecans), 2 Tbsp. butter or margarine, 3 1/2 c. bite size shredded rice biscuits";
        string instructions = "In a heavy 2-quart saucepan, mix brown sugar, nuts, evaporated milk and butter or margarine., Stir over medium heat until mixture bubbles all over top., Boil and stir 5 minutes more. Take off heat., Stir in vanilla and cereal; mix well., Using 2 teaspoons, drop and shape into 30 clusters on wax paper., Let stand until firm, about 30 minutes.";
        string link = "www.cookbooks.com/Recipe-Details.aspx?id=44874";
        RecommendationWindow recommendationWindow(name, ingredients, instructions, link);
        recommendationWindow.RecommendationScreen();
    }

}
