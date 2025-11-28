#include "Step.h"

Step::Step() : description_(), durationSeconds_(0) {}

Step::Step(const std::string& desc, int seconds)
    : description_(desc), durationSeconds_(seconds) {}

const std::string& Step::getDescription() const {
    return description_;
}

int Step::getDuration() const {
    return durationSeconds_;
}

void Step::setDescription(const std::string& desc) {
    description_ = desc;
}

void Step::setDuration(int seconds) {
    durationSeconds_ = seconds;
}
