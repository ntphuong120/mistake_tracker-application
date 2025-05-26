#ifndef UI_HPP
#define UI_HPP

#include <string>
#include <iostream>
// Assume these includes exist
#include "Tracker.hpp"
#include "Mistake.hpp"

class UI {
private:
    Tracker tracker;
    
    // UI Helper methods
    void displayWelcomeMessage() const;
    void displayMainMenu() const;
    void displaySearchMenu() const;
    void displayHeader(const std::string& title) const;
    void displaySeparator() const;
    void displayFooter() const;
    void clearScreen() const;
    void pauseScreen() const;
    
    // Input validation methods
    int getValidMenuChoice(int minChoice, int maxChoice) const;
    std::string getValidLevel() const;
    std::string getValidStatus() const;
    std::string getMultilineInput(const std::string& prompt) const;
    std::string getCurrentDate() const;
    
    // Menu handlers
    void handleAddMistake();
    void handleSearchMenu();
    void handleEditMistake();
    void handleDisplayAll();
    void handleStatistics();
    
    // Search handlers
    void handleSearchById();
    void handleSearchByCategory();
    void handleSearchByDescription();
    void handleSearchByLevel();
    void handleSearchByDate();
    
    // Utility methods
    void displayErrorMessage(const std::string& message) const;
    void displaySuccessMessage(const std::string& message) const;
    void displayInfoMessage(const std::string& message) const;
    
public:
    UI();
    ~UI() = default;
    
    // Main application entry point
    void run();
    
    // Additional features
    void displayHelp() const;
    void displayAbout() const;
};

#endif // UI_HPP