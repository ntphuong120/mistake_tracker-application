#include "../include/Tracker.hpp"
#include <cctype>
#include <algorithm>
#include <string>
#include <iomanip>
#include <map>

// Constructors
Tracker::Tracker() {
    mistakes = FileHandler::loadFromFile("data/mistake.txt");
}

Tracker::Tracker(const std::vector<Mistake>& mistakes) : mistakes(mistakes) {
    // Load additional mistakes from file if needed
    auto fileMistakes = FileHandler::loadFromFile("data/mistake.txt");
    this->mistakes.insert(this->mistakes.end(), fileMistakes.begin(), fileMistakes.end());
}

// Helper methods
bool Tracker::containsCaseInsensitive(const std::string& str, const std::string& sub) const {
    std::string strLower = str;
    std::string subLower = sub;
    std::transform(strLower.begin(), strLower.end(), strLower.begin(), ::tolower);
    std::transform(subLower.begin(), subLower.end(), subLower.begin(), ::tolower);
    return strLower.find(subLower) != std::string::npos;
}

void Tracker::displaySearchHeader(const std::string& searchType, const std::string& searchValue) const {
    displaySeparator();
    std::cout << std::setw(30) << std::left << ("🔍 Search Results: " + searchType) << std::endl;
    std::cout << "Search term: \"" << searchValue << "\"" << std::endl;
    displaySeparator();
}

void Tracker::displayNoResultsMessage() const {
    std::cout << "┌─────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│                        ❌ No Results Found                       │" << std::endl;
    std::cout << "│                                                                 │" << std::endl;
    std::cout << "│  No mistakes match your search criteria.                       │" << std::endl;
    std::cout << "│  Try using different keywords or check your spelling.          │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────────┘" << std::endl;
}

void Tracker::displaySuccessMessage(const std::string& message) const {
    std::cout << "┌─────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│                           ✅ Success                            │" << std::endl;
    std::cout << "│  " << std::setw(61) << std::left << message << "│" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────────┘" << std::endl;
}

void Tracker::displayErrorMessage(const std::string& message) const {
    std::cout << "┌─────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│                            ❌ Error                             │" << std::endl;
    std::cout << "│  " << std::setw(61) << std::left << message << "│" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────────┘" << std::endl;
}

void Tracker::displaySeparator() const {
    std::cout << "═══════════════════════════════════════════════════════════════════" << std::endl;
}

// Core functionality
void Tracker::addMistake(const Mistake& mistake) {
    mistakes.push_back(mistake);
    displaySuccessMessage("Mistake added successfully!");
}

bool Tracker::removeMistake(int mistakeId) {
    auto it = std::find_if(mistakes.begin(), mistakes.end(),
        [mistakeId](const Mistake& mistake) {
            return mistake.getID() == mistakeId;
        });
    
    if (it != mistakes.end()) {
        mistakes.erase(it);
        
        // Update IDs for remaining mistakes
        for (size_t i = 0; i < mistakes.size(); ++i) {
            mistakes[i].setID();
        }
        
        saveToFile("data/mistake.txt");
        return true;
    }
    
    return false;
}

// Search methods
int Tracker::searchById(int id) {
    for (size_t i = 0; i < mistakes.size(); ++i) {
        if (mistakes[i].getID() == id) {
            displaySearchHeader("ID", std::to_string(id));
            mistakes[i].display();
            displaySeparator();
            return static_cast<int>(i);
        }
    }
    
    displaySearchHeader("ID", std::to_string(id));
    displayNoResultsMessage();
    displaySeparator();
    return -1;
}

std::vector<Mistake> Tracker::searchByDescription(const std::string& description) {
    std::vector<Mistake> results;
    
    for (const auto& mistake : mistakes) {
        if (containsCaseInsensitive(mistake.getDescription(), description)) {
            results.push_back(mistake);
        }
    }
    
    displaySearchResults(results, "Description", description);
    return results;
}

std::vector<Mistake> Tracker::searchByCategory(const std::string& category) {
    std::vector<Mistake> results;
    
    for (const auto& mistake : mistakes) {
        if (containsCaseInsensitive(mistake.getCategory(), category)) {
            results.push_back(mistake);
        }
    }
    
    displaySearchResults(results, "Category", category);
    return results;
}

std::vector<Mistake> Tracker::searchByLevel(const std::string& level) {
    std::vector<Mistake> results;
    
    for (const auto& mistake : mistakes) {
        if (containsCaseInsensitive(mistake.getLevel(), level)) {
            results.push_back(mistake);
        }
    }
    
    displaySearchResults(results, "Level", level);
    return results;
}

std::vector<Mistake> Tracker::searchByDate(const std::string& date) {
    std::vector<Mistake> results;
    
    for (const auto& mistake : mistakes) {
        if (containsCaseInsensitive(mistake.getDate(), date)) {
            results.push_back(mistake);
        }
    }
    
    displaySearchResults(results, "Date", date);
    return results;
}

void Tracker::displaySearchResults(const std::vector<Mistake>& results, 
                                 const std::string& searchType, 
                                 const std::string& searchValue) const {
    displaySearchHeader(searchType, searchValue);
    
    if (results.empty()) {
        displayNoResultsMessage();
    } else {
        std::cout << "Found " << results.size() << " result(s):" << std::endl << std::endl;
        for (const auto& mistake : results) {
            mistake.display();
            std::cout << std::endl;
        }
    }
    
    displaySeparator();
}

// Edit functionality
bool Tracker::editMistake(int mistakeId) {
    int index = searchById(mistakeId);
    
    if (index == -1) {
        displayErrorMessage("Mistake with ID " + std::to_string(mistakeId) + " not found!");
        return false;
    }
    
    displaySeparator();
    std::cout << "🛠️  EDIT MISTAKE #" << mistakeId << std::endl;
    displaySeparator();
    
    std::string input;
    std::cout << "Do you want to remove this mistake? (yes/no): ";
    std::getline(std::cin, input);
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    
    if (input == "yes" || input == "y") {
        if (removeMistake(mistakeId)) {
            displaySuccessMessage("Mistake removed successfully!");
            return true;
        } else {
            displayErrorMessage("Failed to remove mistake!");
            return false;
        }
    }
    
    std::cout << "\n📝 Edit fields (press Enter to skip any field):\n" << std::endl;
    
    // Edit Category
    std::cout << "Current Category: " << mistakes[index].getCategory() << std::endl;
    std::cout << "New Category: ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        mistakes[index].setCategory(input);
    }
    
    // Edit Description
    std::cout << "\nCurrent Description: " << mistakes[index].getDescription() << std::endl;
    std::cout << "New Description: ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        mistakes[index].setDescription(input);
    }
    
    // Edit Cause
    std::cout << "\nCurrent Cause: " << mistakes[index].getCause() << std::endl;
    std::cout << "New Cause: ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        mistakes[index].setCause(input);
    }
    
    // Edit Solution
    std::cout << "\nCurrent Solution: " << mistakes[index].getSolution() << std::endl;
    std::cout << "New Solution: ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        mistakes[index].setSolution(input);
    }
    
    // Edit Level
    std::cout << "\nCurrent Level: " << mistakes[index].getLevel() << std::endl;
    std::cout << "New Level (Low/Medium/High): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        mistakes[index].setLevel(input);
    }
    
    // Edit Status
    std::cout << "\nCurrent Status: " << mistakes[index].getStatusOfImproving() << std::endl;
    std::cout << "New Status (NOTSTARTED/ONGOING/DONE): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        mistakes[index].setStatusOfImproving(input);
    }
    
    saveToFile("data/mistake.txt");
    displaySuccessMessage("Mistake updated successfully!");
    displaySeparator();
    
    return true;
}

// Display methods
void Tracker::displayAll() const {
    if (mistakes.empty()) {
        std::cout << "┌─────────────────────────────────────────────────────────────────┐" << std::endl;
        std::cout << "│                     📝 No Mistakes Recorded                     │" << std::endl;
        std::cout << "│                                                                 │" << std::endl;
        std::cout << "│  Start tracking your mistakes to improve your learning!        │" << std::endl;
        std::cout << "└─────────────────────────────────────────────────────────────────┘" << std::endl;
        return;
    }
    
    displaySeparator();
    std::cout << "📋 ALL MISTAKES (" << mistakes.size() << " total)" << std::endl;
    displaySeparator();
    
    for (const auto& mistake : mistakes) {
        mistake.display();
        std::cout << std::endl;
    }
    
    displayStatistics();
}

void Tracker::displayStatistics() const {
    if (mistakes.empty()) return;
    
    std::map<std::string, int> levelCount;
    std::map<std::string, int> statusCount;
    std::map<std::string, int> categoryCount;
    
    for (const auto& mistake : mistakes) {
        levelCount[mistake.getLevel()]++;
        statusCount[mistake.getStatusString(mistake.getStatusOfImproving())]++;
        categoryCount[mistake.getCategory()]++;
    }
    
    displaySeparator();
    std::cout << "📊 STATISTICS" << std::endl;
    displaySeparator();
    
    std::cout << "By Level:" << std::endl;
    for (const auto& pair : levelCount) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }
    
    std::cout << "\nBy Status:" << std::endl;
    for (const auto& pair : statusCount) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }
    
    std::cout << "\nTop Categories:" << std::endl;
    for (const auto& pair : categoryCount) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }
    
    displaySeparator();
}

// File operations
void Tracker::saveToFile(const std::string& filename) const {
    FileHandler::saveToFile(mistakes, filename);
}

void Tracker::loadFromFile(const std::string& filename) {
    mistakes = FileHandler::loadFromFile(filename);
}