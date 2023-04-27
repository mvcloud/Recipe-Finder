#pragma once
#include <string>
#include <random>
using namespace std;

class Encouragement {
    string arr[11] = {"yummy!", "looks good!", "im excited!", "awesome!", "amazing decision!", "wow!",
                      "im so ready!", "tasty!", "delicious!", "out of this world!", "compliments to the chef!"};
public:
    string RandomEncouragement();
};