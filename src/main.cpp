#include "Recipes.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "WelcomeWindow.h"
#include "ChooseAlgorithmAndSizeWindow.h"
#include "IngredientWindow.h"
#include "RecommendationWindow.h"
#include "ThankYouWindow.h"
#include "TextureManager.h"
using namespace std;

int main() {

    // open welcome window
    bool doneWithWelcome = false;
    WelcomeWindow welcome;
    doneWithWelcome = welcome.WelcomeScreen();

    // get the user's decision on what sorting algorithm to use and max num of ingredients
    bool choseSortingAlgo = false;
    char sortingAlgo;
    int maxIngredients;
    if (doneWithWelcome) {
        ChooseAlgorithmAndSizeWindow choseAlgorithmWindow;
        choseAlgorithmWindow.ChooseAlgorithmScreen(choseSortingAlgo, sortingAlgo, maxIngredients);
    }

    // when done with welcome window and choosing an algo, open up ingredient window and get/store
    unordered_set<string> userIngredients;
    if (choseSortingAlgo) {
        IngredientWindow ingredientWindow;
        userIngredients = ingredientWindow.IngredientScreen();
    }

    // if the user actually entered any ingredients...
    if (!userIngredients.empty()) {
        // get a vector of recipes sorted from highest to lowest according to number of matching ingredients
        Recipes recipes;
        recipes.GetDataFromCSVFile(userIngredients, maxIngredients);
        vector<Recipe*> recipeVector = recipes.getRecipeVector();

        // call the  user's sorting algo of choice
        if (sortingAlgo == 'm') {
            mergeSort(recipeVector, 0, recipeVector.size()-1);
        }
        else if (sortingAlgo == 'q') {
            quickSort(recipeVector, 0, recipeVector.size()-1);
        }

        vector<Recipe*> visitedRecipes;
        char decision;
        int x = 0;
        bool decidedOnRecipe = false;

        //  while loop to be able to loop through recipe recommendation windows
        while (true) {

            // if the user hasn't decided, show the recipe at the current index
            if (!decidedOnRecipe) {
                string name = recipeVector[x]->getName();
                string ingredients = recipeVector[x]->getIngredients();
                string instructions = recipeVector[x]->getInstructions();
                string link = recipeVector[x]->getLink();

                RecommendationWindow recommendationWindow(name, ingredients, instructions, link);
                decision = recommendationWindow.RecommendationScreen(decidedOnRecipe);
                visitedRecipes.push_back(recipeVector[x]);
            }
            // if the user closed the window, break the while loop
            if (decision == 'd') break;
            // user decided to go backward (left)
            else if (decision == 'l' && x != 0) x--;
            // user decided to go forward (right)
            else if (decision == 'r' && x != recipeVector.size() - 1) x++;
        }
        //if the user has decided on their recipe, display the 'thank you' window
        if (decidedOnRecipe) {
            ThankYouWindow thankyouwindow;
            thankyouwindow.ThankYouScreen();
        }
    }
    //clear texture unordered map
    TextureManager::Clear();
}
