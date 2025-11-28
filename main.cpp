#include <iostream>
#include <string>
#include <vector>

#include "Step.h"
#include "CookingAssistant.h"

int main() {
    std::cout << "=== Real-Time Cooking Assistant ===\n\n";
    std::cout << "Enter the recipe file path (e.g., omelette.txt): ";

    std::string filename;
    std::getline(std::cin, filename);

    std::vector<Step> steps;
    if (!loadRecipeFromFile(filename, steps)) {
        return 1;
    }

    runRecipe(steps);

    return 0;
}
