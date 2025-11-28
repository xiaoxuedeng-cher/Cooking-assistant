#include "CookingAssistant.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
#include <limits>
#include <cctype>  // std::isspace

// ---------------------
// internal helpers
// ---------------------

namespace {

void printDivider() {
    std::cout << "\n----------------------------------------\n";
}

void countdownTimer(int totalSeconds) {
    using namespace std::chrono_literals;

    for (int remaining = totalSeconds; remaining > 0; --remaining) {
        int minutes = remaining / 60;
        int seconds = remaining % 60;

        std::cout << "\rTime remaining: "
                  << std::setw(2) << std::setfill('0') << minutes << ":"
                  << std::setw(2) << std::setfill('0') << seconds
                  << std::flush;

        std::this_thread::sleep_for(1s);
    }

    std::cout << "\rTime remaining: 00:00\n";
    std::cout << "Timer finished!\n";
}

// trim helper (in-place)
void trim(std::string& s) {
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front()))) {
        s.erase(s.begin());
    }
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back()))) {
        s.pop_back();
    }
}

} // anonymous namespace

// ---------------------
// public functions
// ---------------------

bool loadRecipeFromFile(const std::string& filename, std::vector<Step>& steps) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file: " << filename << "\n";
        return false;
    }

    steps.clear();
    std::string line;
    const char DELIM = '|';
    int lineNumber = 0;

    while (std::getline(file, line)) {
        ++lineNumber;

        if (line.empty() || line[0] == '#') {
            continue; // skip empty or comment lines
        }

        std::size_t pos = line.find(DELIM);
        if (pos == std::string::npos) {
            std::cerr << "Warning: Missing '|' at line " << lineNumber << ". Skipping.\n";
            continue;
        }

        std::string secondsStr = line.substr(0, pos);
        std::string description = line.substr(pos + 1);

        trim(secondsStr);
        trim(description);

        if (secondsStr.empty() || description.empty()) {
            std::cerr << "Warning: Empty duration or description at line "
                      << lineNumber << ". Skipping.\n";
            continue;
        }

        int seconds = 0;
        try {
            seconds = std::stoi(secondsStr);
            if (seconds < 0) {
                std::cerr << "Warning: Negative duration at line "
                          << lineNumber << ". Skipping.\n";
                continue;
            }
        } catch (...) {
            std::cerr << "Warning: Invalid duration at line "
                      << lineNumber << ". Skipping.\n";
            continue;
        }

        steps.emplace_back(description, seconds);
    }

    if (steps.empty()) {
        std::cerr << "Error: No valid steps found.\n";
        return false;
    }

    return true;
}

void runRecipe(const std::vector<Step>& steps) {
    printDivider();
    std::cout << "Cooking Assistant — Guided Mode\n";
    printDivider();

    std::cout << "Press ENTER to begin...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (std::size_t i = 0; i < steps.size(); ++i) {
        const Step& s = steps[i];

        printDivider();
        std::cout << "Step " << (i + 1) << "/" << steps.size() << ":\n";
        std::cout << s.getDescription() << "\n";
        std::cout << "Suggested time: " << s.getDuration() << " seconds\n\n";

        std::cout << "Press ENTER when you're ready to start this step...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (s.getDuration() > 0) {
            // 1) Run the countdown
            countdownTimer(s.getDuration());

            // 2) Confirmation buffer after timer hits 0
            std::cout << "\n Timer reached 0. You may still need a moment to finish.\n";
            std::cout << "When you have actually finished this step, press ENTER to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cout << "This step has no timer.\n";
            std::cout << "When you have finished this step, press ENTER to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    printDivider();
    std::cout << "All steps completed! Enjoy your meal!\n";
    printDivider();
}
