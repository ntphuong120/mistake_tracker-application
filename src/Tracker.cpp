#include "../include/Tracker.hpp"
#include <cctype>
#include <algorithm>
#include <string>

Tracker::Tracker() {}

Tracker::Tracker(std::vector<Mistake>& mistakes) {
    this->mistakes = mistakes;
}

bool Tracker::containsCaseInsensitive(const std::string& str, const std::string& sub) const {
    std::string strLower = str;
    std::string subLower = sub;
    std::transform(strLower.begin(), strLower.end(), strLower.begin(), ::tolower);
    std::transform(subLower.begin(), subLower.end(), subLower.begin(), ::tolower);
    return strLower.find(subLower) != std::string::npos;
}

void Tracker::addMistake(const Mistake& mistake) {
    mistakes.push_back(mistake);
} 

void Tracker::removeMistake(const Mistake& mistake) {

}

void Tracker::displayAll() const {
    for (const auto& mistake : mistakes)
        mistake.display();
}

void Tracker::searchByName(const std::string& fname) {
    std::vector<Mistake> result;
    for (const auto& mistake : mistakes) {
        if (containsCaseInsensitive(mistake.getName(), fname)) 
            result.push_back(mistake);
    }

    for (const auto& re : result) {
        re.display();
    }
}

void Tracker::searchByCategory(const std::string& fcategory) {
    std::vector<Mistake> result;
    for (const auto& mistake : mistakes) {
        if (containsCaseInsensitive(mistake.getCategory(), fcategory))
            result.push_back(mistake);
    }

    for (const auto& re : result) {
        re.display();
    }
}

void Tracker::searchByLevel(const std::string& flevel) {
    std::vector<Mistake> result;
    for  (const auto& mistake : mistakes) {
        if (containsCaseInsensitive(mistake.getLevel(), flevel))
            result.push_back(mistake); 
    }

    for (const auto& re : result) {
        re.display();
    }
}

void Tracker::saveToFile(const std::string& filename) const {
    FileHandler::saveToFile(mistakes, filename);
}

void Tracker::loadFromFile(const std::string& filename) {
    mistakes = FileHandler::loadFromFile(filename);
}