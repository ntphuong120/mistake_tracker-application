#ifndef UI_HPP
#define UI_HPP

#include "Tracker.hpp"

class UI {
private:
    Tracker tracker;
public:
    UI(Tracker& tracker) : tracker(tracker) {}
    void run();
};

#endif