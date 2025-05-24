#include "../include/Tracker.hpp"
#include <cctype>
#include <algorithm>
#include <string>

Tracker::Tracker() {
    mistakes = FileHandler::loadFromFile("data/mistake.txt");
}
Tracker::Tracker(std::vector<Mistake>& mistakes) {
    this->mistakes = mistakes;
    mistakes = FileHandler::loadFromFile("data/mistake.txt");
}

bool Tracker::containsCaseInsensitive(const std::string& str, const std::string& sub) const {
    std::string strLower = str;
    std::string subLower = sub;
    std::transform(strLower.begin(), strLower.end(), strLower.begin(), ::tolower);
    std::transform(subLower.begin(), subLower.end(), subLower.begin(), ::tolower);
    return strLower.find(subLower) != std::string::npos;
}

// Add a mistake
void Tracker::addMistake(const Mistake& mistake) {
    mistakes.push_back(mistake);
}

// Search
void Tracker::searchByID(int ID_toFind) const {
    for (const Mistake& mistake : mistakes) {
        if (mistake.getID() == ID_toFind) {
            mistake.display();
            return;
        }
    }

    std::cout << "\nNot Found!\n\n";
}

void Tracker::searchByDescription(const std::string& Description_toFind) {
    std::vector<Mistake> result;

    for (const Mistake& mistake : mistakes) {
        if (containsCaseInsensitive(mistake.getDescription(), Description_toFind)) {
            result.push_back(mistake);
        }
    }

    if (result.empty()) {
        std::cout << "\nNot Found!\n\n";
        return;
    }

    for (const Mistake& re : result) {
        re.display();
    }
}

void Tracker::searchByCategory(const std::string& Category_toFind) {
    std::vector<Mistake> result;

    for (const Mistake& mistake : mistakes) {
        if (containsCaseInsensitive(mistake.getCategory(), Category_toFind)) {
            result.push_back(mistake);    
        }
    }

    if (result.empty()) {
        std::cout << "\nNot Found!\n\n";
        return;
    }

    for (const Mistake& re : result) {
        re.display();
    }
}

void Tracker::searchByLevel(const std::string& Level_toFind) {
    std::vector<Mistake> result;    

    for (const Mistake& mistake : mistakes) {
        if (mistake.getLevel() == Level_toFind)
            result.push_back(mistake);
    }
    
    if (result.empty()) {
        std::cout << "\nNot Found!\n\n";
        return;
    }

    for (const Mistake& re : result) {
        re.display();
    }
}

void Tracker::searchByDate(const std::string& Date_toFind) {
    std::vector<Mistake> result;

    for (const Mistake& mistake : mistakes) {
        if (containsCaseInsensitive(mistake.getDate(), Date_toFind))
            result.push_back(mistake);
    }

    if (result.empty()) {
        std::cout << "\nNot Found!\n\n";
        return;
    }

    for (const Mistake& re : result) {
        re.display();
    }
}

// Edit
bool Tracker::removeMistake(int Mistake_ID) {
    bool Found = false;

    for (size_t i = 0; i < mistakes.size(); ++i) {
        if (!Found && mistakes[i].getID() == Mistake_ID) {
            mistakes.erase(mistakes.begin() + i);
            Found = true;
        }

        if (Found) 
            mistakes[i].setID();
    }

    return Found;
}

// Display All
void Tracker::displayAll() const {
    for (const Mistake& mistake : mistakes)
        mistake.display();
}

// File Handle
void Tracker::saveToFile(const std::string& filename) const {
    FileHandler::saveToFile(mistakes, filename);
}

void Tracker::loadFromFile(const std::string& filename) {
    mistakes = FileHandler::loadFromFile(filename);
}
