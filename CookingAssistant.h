#ifndef COOKING_ASSISTANT_H
#define COOKING_ASSISTANT_H

#include <string>
#include <vector>
#include "Step.h"

// Load steps from a text file: "seconds|description"
bool loadRecipeFromFile(const std::string& filename, std::vector<Step>& steps);

// Run the interactive guided cooking flow
void runRecipe(const std::vector<Step>& steps);

#endif // COOKING_ASSISTANT_H
