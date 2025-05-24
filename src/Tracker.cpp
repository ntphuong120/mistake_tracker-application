#include "../include/Tracker.hpp"
#include <cctype>
#include <algorithm>
#include <string>

Tracker::Tracker() {
    mistakes = FileHandler::loadFromFile("data/mistakes.txt");
}

Tracker::Tracker(std::vector<Mistake>& mistakes) {
    this->mistakes = mistakes;
    mistakes = FileHandler::loadFromFile("data/mistakes.txt");
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

void Tracker::displayAll() const {
    for (const auto& mistake : mistakes)
        mistake.display();
}

void Tracker::searchByName(const std::string& fname) {
    if (mistakes.empty()) {
        std::cout << "You don't have any databse!\n\n";
        return;
    }

    std::vector<Mistake> result;
    for (const auto& mistake : mistakes) {
        if (containsCaseInsensitive(mistake.getName(), fname)) 
            result.push_back(mistake);
    }

    if (result.empty()) {
        std::cout << "Not Found!\n\n";
        return;
    }

    for (const auto& re : result) {
        re.display();
    }
}

void Tracker::searchByCategory(const std::string& fcategory) {
    if (mistakes.empty()) {
        std::cout << "You don't have any databse!\n\n";
        return;
    }


    std::vector<Mistake> result;
    for (const auto& mistake : mistakes) {
        if (containsCaseInsensitive(mistake.getCategory(), fcategory))
            result.push_back(mistake);
    }

    if (result.empty()) {
        std::cout << "Not Found!\n\n";
        return;
    }

    for (const auto& re : result) {
        re.display();
    }
}

void Tracker::searchByLevel(const std::string& flevel) {
    if (mistakes.empty()) {
        std::cout << "You don't have any databse!\n\n";
        return;
    }

    std::vector<Mistake> result;
    for  (const auto& mistake : mistakes) {
        if (containsCaseInsensitive(mistake.getLevel(), flevel))
            result.push_back(mistake); 
    }

    if (result.empty()) {
        std::cout << "Not Found!\n\n";
        return;
    }

    for (const auto& re : result) {
        re.display();
    }
}

void Tracker::saveToFile(const std::string& filename) const {
    FileHandler::saveToFile(mistakes, filename);
}

void Tracker::loadFromFile(const std::string& filename) {
    std::cout << "Loading from file: " << filename << std::endl;
    mistakes = FileHandler::loadFromFile(filename);
}