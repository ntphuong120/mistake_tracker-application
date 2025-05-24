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

    // Add a mistake
    void addMistake(const Mistake& mistake);

    // Search
    void searchByID(int ID_toFind) const;
    void searchByDescription(const std::string& Description_toFind);
    void searchByCategory(const std::string& Category_toFind);
    void searchByLevel(const std::string& Level_toFind);
    void searchByDate(const std::string& Date_toFind);

    // Edit - Setters
    bool removeMistake(int Mistake_ID);

    // Display All
    void displayAll() const;

    // File Handle
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif