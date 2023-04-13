#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;


void GetDataFromCSVFile() {
    ifstream file("data.csv");

    if (file.is_open()) {
        string lineFromFile;
        getline(file, lineFromFile);

        while(getline(file, lineFromFile)) {
            istringstream stream(lineFromFile);

            string buffer; //we don't store buffers
            string name;
            string tempIngredients;
            vector<string> ingredients;
            string instructions;
            string link;
            string NER;


            getline(stream, buffer, ',');

            getline(stream, name, ',');
            cout << name << endl;

            getline(stream, buffer, '"');
            getline(stream, buffer, '[');
            getline(stream, buffer, '"');

            getline(stream, tempIngredients, ']');
            tempIngredients.erase(std::remove(tempIngredients.begin(), tempIngredients.end(), '"'), tempIngredients.end());
            cout << tempIngredients << endl;

            getline(stream, buffer, '"');
            getline(stream, buffer, '"');

            getline(stream, instructions, ']');
            instructions.erase(std::remove(instructions.begin(), instructions.end(), '"'), instructions.end());
            instructions.erase(std::remove(instructions.begin(), instructions.end(), '['), instructions.end());

            cout << instructions << endl;

            getline(stream, buffer, '"');
            getline(stream, buffer, ',');

            getline(stream, link, ',');
            cout << link << endl;

            getline(stream, buffer, ',');

            getline(stream, NER, ']');
            NER.erase(std::remove(NER.begin(), NER.end(), '['), NER.end());
            NER.erase(std::remove(NER.begin(), NER.end(), '"'), NER.end());
            cout << NER << endl;

            cout << endl;

        }
    }
}

int main() {
    GetDataFromCSVFile();
}