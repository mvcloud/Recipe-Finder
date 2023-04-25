#include "MergeSort.h"
//source : Professor Kapoor- Module 6 Slide # 89

void mergeSort(vector<Recipe*>& recipes, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; //find midpoint
        //recursively break the vector into smaller chunks until there is only 1 in each chunk
        mergeSort(recipes, left, mid);
        mergeSort(recipes, mid + 1, right);
        //merge all sorted chunks back together using helper function
        merge(recipes, left, mid, right);
    }
}

//merge helper function
void merge(vector<Recipe*>& recipes, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Recipe*> vec1; //vector for left through mid
    vector<Recipe*> vec2; //vector for mid + 1 through right

    for (int i = 0; i < n1; i++) {
        vec1.push_back(recipes[left + i]);
    }
    for (int j = 0; j < n2; j++) {
        vec2.push_back(recipes[mid + 1 + j]);
    }

    //merge vec1 & vec2 vectors into recipe vector
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (vec1[i]->getMatching() <= vec2[j]->getMatching()) {
            recipes[k] = vec1[i];
            i++;
        }
        else {
            recipes[k] = vec2[j];
            j++;
        }
        k++;
    }
    //when elements of 1 subarray run out, just add all the elements left in the 2nd
    while (i < n1) {
        recipes[k] = vec1[i];
        i++;
        k++;
    }
    while (j < n2) {
        recipes[k] = vec2[j];
        j++;
        k++;
    }
}