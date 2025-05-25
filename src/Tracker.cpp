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
int Tracker::searchByID(int ID_toFind) {
    for (int i = 0; i < mistakes.size(); ++i) {
        if (mistakes[i].getID() == ID_toFind) {
            mistakes[i].display();
            return i;
        }
    }

    std::cout << "================================Unable==============================\n";
    std::cout << "---------------------------------------------------\n";
    std::cout << "Not Found!\n";
    std::cout << "---------------------------------------------------\n";
    std::cout << "====================================================================\n\n";

    return -1;
}

void Tracker::searchByDescription(const std::string& Description_toFind) {
    std::vector<Mistake> result;

    for (const Mistake& mistake : mistakes) {
        if (containsCaseInsensitive(mistake.getDescription(), Description_toFind)) {
            result.push_back(mistake);
        }
    }

    if (result.empty()) {
        std::cout << "================================Unable==============================\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "Not Found!\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "====================================================================\n\n";
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
        std::cout << "================================Unable==============================\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "Not Found!\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "====================================================================\n\n";
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
        std::cout << "================================Unable==============================\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "Not Found!\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "====================================================================\n\n";
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
        std::cout << "================================Unable==============================\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "Not Found!\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "====================================================================\n\n";
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

    Tracker::saveToFile("data/mistake.txt");
    return Found;
}

void Tracker::Edit(int Mistake_ID, int index) {
    std::cout << "=================================Edit===============================\n";
    std::string editRemove;
    std::cout << "Remove(NO or YES): ";
    std::getline(std::cin, editRemove);

    if (editRemove == "YES") {
        bool check_remove = removeMistake(Mistake_ID);

        if (check_remove == 1) {
            std::cout << "---------------------------------------------------\n";
            std::cout << "Removed!\n";
            std::cout << "---------------------------------------------------\n";
            std::cout << "====================================================================\n";
            return;
        }

        else {
            std::cout << "---------------------------------------------------\n";
            std::cout << "Cannot remove this mistake";
            std::cout << "---------------------------------------------------\n";
            std::cout << "====================================================================\n";
            return;
        }
    }

    std::cout << "-Press Enter To Skip Edit-\n";

    std::string editCategory;
    std::cout << "Enter Category To Edit: ";
    std::getline(std::cin, editCategory);
    mistakes[index].setCategory(editCategory);
    

    std::string editDescription;
    std::cout << "Enter Description To Edit: \n";
    std::getline(std::cin, editDescription);
    mistakes[index].setDescription(editDescription);

    std::string editCause;
    std::cout << "Enter Cause To Edit: \n";
    std::getline(std::cin, editCause);
    mistakes[index].setCause(editCause);

    std::string editSolution;
    std::cout << "Enter Solution To Edit: \n";
    std::getline(std::cin, editSolution);
    mistakes[index].setSolution(editSolution);
    
    std::string editLevel;
    std::cout << "Enter Level To Edit: ";
    std::getline(std::cin, editLevel);
    mistakes[index].setLevel(editLevel);

    std::string editStatus;
    std::cout << "Enter Status To Edit: ";
    std::getline(std::cin, editStatus);
    mistakes[index].setStatusOfImproving(editStatus);

    std::cout << "====================================================================\n";

    Tracker::saveToFile("data/mistake.txt");
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
