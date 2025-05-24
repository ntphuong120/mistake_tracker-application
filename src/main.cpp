#include "../include/Tracker.hpp"
#include "../include/UI.hpp"

int main() {
    Tracker tracker;
    UI ui(tracker);

    ui.run();

    return 0;
}
