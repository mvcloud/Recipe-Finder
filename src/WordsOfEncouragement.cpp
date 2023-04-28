#include "WordsOfEncouragement.h"

// returns a random string from the array
string Encouragement::RandomEncouragement() {
    std::mt19937 random(time(0));
    uniform_int_distribution<> distribution(0, 10);
    return arr[distribution(random)];
}
