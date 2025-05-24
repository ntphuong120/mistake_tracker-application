#ifndef TRACKER_HPP
#define TRACKER_HPP

#include "Mistake.hpp"
#include "FileHandler.hpp"

class Tracker {
private:
    std::vector<Mistake> mistakes;
public:
    Tracker();
    Tracker(std::vector<Mistake>& mistakes);

    bool containsCaseInsensitive(const std::string& str, const std::string& sub) const;

    // Add
    void addMistake(const Mistake& mistake);
    // Display
    void displayAll() const;
    // Search
    void searchByCategory(const std::string& fcategory);
    void searchByLevel(const std::string& flevel);
    void searchByName(const std::string& fname);

    // File Handle
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    // Edit
    
};

#endif