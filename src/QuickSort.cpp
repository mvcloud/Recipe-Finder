#include "QuickSort.h"

//vector of Recipe pointers to be sorted and left and right bounds of the current subarray to be sorted
void quickSort(vector<Recipe*>& recipes, int left, int right) {
    //return subarray
	if (left >= right) {
        return;
    }

    int pivotIndex = (left + right) / 2;
    int pivotValue = recipes[pivotIndex]->getMatchingIngredients();

    //pivot element and retrieve the corresponding Recipe object from the vector
    int i = left;
    int j = right;
    while (i <= j) {
        while (recipes[i]->getMatchingIngredients() > pivotValue) {
            i++;
        }

        while (recipes[j]->getMatchingIngredients() < pivotValue) {
            j--;
        }

        if (i <= j) {
            swap(recipes[i], recipes[j]);
            i++;
            j--;
        }
    }

    quickSort(recipes, left, j);
    quickSort(recipes, i, right);
}