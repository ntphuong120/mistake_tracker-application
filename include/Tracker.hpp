#ifndef TRACKER_HPP
#define TRACKER_HPP

#include <vector>
#include <string>
#include <iostream>
// Assume these includes exist
#include "Mistake.hpp"
#include "FileHandler.hpp"

class Tracker {
private:
    std::vector<Mistake> mistakes;
    
    // Helper methods
    bool containsCaseInsensitive(const std::string& str, const std::string& sub) const;
    void displaySearchHeader(const std::string& searchType, const std::string& searchValue) const;
    void displayNoResultsMessage() const;
    void displaySuccessMessage(const std::string& message) const;
    void displayErrorMessage(const std::string& message) const;
    void displaySeparator() const;
    
public:
    // Constructors
    Tracker();
    explicit Tracker(const std::vector<Mistake>& mistakes);
    
    // Core functionality
    void addMistake(const Mistake& mistake);
    bool removeMistake(int mistakeId);
    
    // Search methods
    int searchById(int id);
    std::vector<Mistake> searchByDescription(const std::string& description);
    std::vector<Mistake> searchByCategory(const std::string& category);
    std::vector<Mistake> searchByLevel(const std::string& level);
    std::vector<Mistake> searchByDate(const std::string& date);
    
    // Edit functionality
    bool editMistake(int mistakeId);
    
    // Display methods
    void displayAll() const;
    void displaySearchResults(const std::vector<Mistake>& results, 
                            const std::string& searchType, 
                            const std::string& searchValue) const;
    
    // File operations
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    
    // Utility methods
    size_t getMistakeCount() const { return mistakes.size(); }
    bool isEmpty() const { return mistakes.empty(); }
    
    // Statistics
    void displayStatistics() const;
};

#endif // TRACKER_HPP