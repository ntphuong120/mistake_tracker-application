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

    void addMistake(const Mistake& mistake);
    void removeMistake(const Mistake& mistake);
    void displayAll() const;
    void searchByCategory(const std::string& fcategory);
    void searchByLevel(const std::string& flevel);
    void searchByName(const std::string& fname);

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif