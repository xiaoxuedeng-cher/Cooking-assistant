#ifndef STEP_H
#define STEP_H

#include <string>

class Step {
private:
    std::string description_;
    int durationSeconds_;

public:
    Step(); // default constructor
    Step(const std::string& desc, int seconds);

    // Getters
    const std::string& getDescription() const;
    int getDuration() const;

    // Setters
    void setDescription(const std::string& desc);
    void setDuration(int seconds);
};

#endif // STEP_H
