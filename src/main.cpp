#include "recipe.h"
#include "GetData.h"
#include "MergeSort.h"
#include "WelcomeWindow.h"
#include "ChooseAlgorithmWindow.h"
#include "IngredientWindow.h"
#include "RecommendationWindow.h"
#include "ThankYouWindow.h"
#include "leaker.h"
using namespace std;

int main() {
    // open welcome window
    bool doneWithWelcome = false;
    WelcomeWindow welcome;
    doneWithWelcome = welcome.WelcomeScreen();

    // get the user's decision on what sorting algorithm to use
    bool choseSortingAlgo = false;
    char sortingAlgo;
    if (doneWithWelcome) {
        ChooseAlgorithmWindow choseAlgorithmWindow;
        choseAlgorithmWindow.ChooseAlgorithmScreen(choseSortingAlgo, sortingAlgo);
    }

    // when done with welcome window and choosing an algo, open up ingredient window and get/store
    // the user's current ingredients
    unordered_set<string> userIngredients;
    if (choseSortingAlgo) {
        IngredientWindow ingredientWindow;
        userIngredients = ingredientWindow.IngredientScreen();
    }

    // if the user actually entered any ingredients...
    if (!userIngredients.empty()) {
        // get a vector of recipes sorted from highest to lowest according
        // to number of matching ingredients
        vector<Recipe*> recipes = GetDataFromCSVFile(userIngredients);

        // call the  user's sorting algo of choice
        if (sortingAlgo == 'm') {
            mergeSort(recipes, 0, recipes.size()-1);
        }

        vector<Recipe*> visitedRecipes;
        char decision;
        int x = 0;
        bool decidedOnRecipe = false;

        //  while loop to be able to loop through recipe recommendation windows
        while (true) {

            // if the user hasn't decided, show the recipe at the current index
            if (!decidedOnRecipe) {
                string name = recipes[x]->getName();
                string ingredients = recipes[x]->getIngredients();
                string instructions = recipes[x]->getInstructions();
                string link = recipes[x]->getLink();

                RecommendationWindow recommendationWindow(name, ingredients, instructions, link);
                decision = recommendationWindow.RecommendationScreen(decidedOnRecipe);
                visitedRecipes.push_back(recipes[x]);
            }
            // if the user closed the window, break the while loop
            if (decision == 'd') break;
            // if the user decided to go left, go left one index
            // unless we are already at the first index
            else if (decision == 'l' && x != 0) x--;
            // if the user decided to go right, go right one index
            // unless we are already at the last index
            else if (decision == 'r' && x != recipes.size() - 1) x++;
        }
        //if the user has decided on their recipe, display the 'thank you' window
        if (decidedOnRecipe) {
            ThankYouWindow thankyouwindow;
            thankyouwindow.ThankYouScreen();
        }
    }
}
