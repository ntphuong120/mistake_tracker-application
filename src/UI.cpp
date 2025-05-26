#include "../include/UI.hpp"
#include <ctime>
#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>

// Constructor
UI::UI() : tracker() {}

// UI Helper methods
void UI::displayWelcomeMessage() const {
    clearScreen();
    std::cout << "╔═══════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                                                                   ║" << std::endl;
    std::cout << "║            🎯 WELCOME TO MISTAKE TRACKER APPLICATION 🎯            ║" << std::endl;
    std::cout << "║                                                                   ║" << std::endl;
    std::cout << "║                   Learn from your mistakes and                    ║" << std::endl;
    std::cout << "║                     improve continuously!                         ║" << std::endl;
    std::cout << "║                                                                   ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;
}

void UI::displayMainMenu() const {
    displayHeader("MAIN MENU");
    std::cout << "┌─────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│  1. ➕ Add New Mistake                                           │" << std::endl;
    std::cout << "│  2. 🔍 Search Mistakes                                           │" << std::endl;
    std::cout << "│  3. ✏️  Edit Mistake                                             │" << std::endl;
    std::cout << "│  4. 📋 Display All Mistakes                                      │" << std::endl;
    std::cout << "│  5. 📊 View Statistics                                           │" << std::endl;
    std::cout << "│  6. ❓ Help                                                      │" << std::endl;
    std::cout << "│  7. ℹ️  About                                                     │" << std::endl;
    std::cout << "│  0. 🚪 Exit                                                       │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────────┘" << std::endl;
    std::cout << std::endl;
}

void UI::displaySearchMenu() const {
    displayHeader("SEARCH MENU");
    std::cout << "┌─────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│  1. 🔢 Search by ID                                              │" << std::endl;
    std::cout << "│  2. 📂 Search by Category                                        │" << std::endl;
    std::cout << "│  3. 📝 Search by Description                                     │" << std::endl;
    std::cout << "│  4. 📈 Search by Level                                           │" << std::endl;
    std::cout << "│  5. 📅 Search by Date                                            │" << std::endl;
    std::cout << "│  0. ⬅️  Back to Main Menu                                        │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────────┘" << std::endl;
    std::cout << std::endl;
}

void UI::displayHeader(const std::string& title) const {
    displaySeparator();
    std::cout << "🎯 " << title << std::endl;
    displaySeparator();
}

void UI::displaySeparator() const {
    std::cout << "═══════════════════════════════════════════════════════════════════" << std::endl;
}

void UI::displayFooter() const {
    std::cout << "───────────────────────────────────────────────────────────────────" << std::endl;
}

void UI::clearScreen() const {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void UI::pauseScreen() const {
    std::cout << "\n📱 Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Input validation methods
int UI::getValidMenuChoice(int minChoice, int maxChoice) const {
    int choice;
    
    while (true) {
        std::cout << "👉 Your selection: ";
        
        if (std::cin >> choice) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            if (choice >= minChoice && choice <= maxChoice) {
                return choice;
            } else {
                displayErrorMessage("Invalid choice! Please select between " + 
                                  std::to_string(minChoice) + " and " + 
                                  std::to_string(maxChoice));
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            displayErrorMessage("Invalid input! Please enter a number.");
        }
    }
}

std::string UI::getValidLevel() const {
    std::string level;
    
    while (true) {
        std::cout << "📈 Level (Low/Medium/High): ";
        std::getline(std::cin, level);
        
        std::transform(level.begin(), level.end(), level.begin(), ::tolower);
        
        if (level == "low" || level == "medium" || level == "high") {
            // Capitalize first letter
            level[0] = std::toupper(level[0]);
            return level;
        } else {
            displayErrorMessage("Invalid level! Please enter Low, Medium, or High.");
        }
    }
}

std::string UI::getValidStatus() const {
    std::string status;
    
    while (true) {
        std::cout << "📊 Status (NOTSTARTED/ONGOING/DONE): ";
        std::getline(std::cin, status);
        
        std::transform(status.begin(), status.end(), status.begin(), ::toupper);
        
        if (status == "NOTSTARTED" || status == "ONGOING" || status == "DONE") {
            return status;
        } else {
            displayErrorMessage("Invalid status! Please enter NOTSTARTED, ONGOING, or DONE.");
        }
    }
}

std::string UI::getMultilineInput(const std::string& prompt) const {
    std::cout << prompt << std::endl;
    std::cout << "💡 Type your content (enter 'END' on a new line to finish):" << std::endl;
    
    std::string result;
    std::string line;
    
    while (std::getline(std::cin, line) && line != "END") {
        if (!result.empty()) {
            result += "\n";
        }
        result += line;
    }
    
    return result;
}

std::string UI::getCurrentDate() const {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime;
    
    #ifdef _MSC_VER
        localtime_s(&localTime, &currentTime);
    #else
        localTime = *std::localtime(&currentTime);
    #endif
    
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", &localTime);
    return std::string(buffer);
}

// Message display methods
void UI::displayErrorMessage(const std::string& message) const {
    std::cout << "┌─────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│                            ❌ ERROR                             │" << std::endl;
    std::cout << "│  " << std::setw(61) << std::left << message << "│" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────────┘" << std::endl;
}

void UI::displaySuccessMessage(const std::string& message) const {
    std::cout << "┌─────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│                           ✅ SUCCESS                            │" << std::endl;
    std::cout << "│  " << std::setw(61) << std::left << message << "│" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────────┘" << std::endl;
}

void UI::displayInfoMessage(const std::string& message) const {
    std::cout << "┌─────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│                             ℹ️ INFO                              │" << std::endl;
    std::cout << "│  " << std::setw(61) << std::left << message << "│" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────────┘" << std::endl;
}

// Menu handlers
void UI::handleAddMistake() {
    displayHeader("ADD NEW MISTAKE");
    
    std::string category, description, cause, solution, level, status;
    
    std::cout << "📂 Category: ";
    std::getline(std::cin, category);
    
    description = getMultilineInput("📝 Description");
    cause = getMultilineInput("🔍 Cause");
    solution = getMultilineInput("💡 Solution");
    
    level = getValidLevel();
    status = getValidStatus();
    
    std::string date = getCurrentDate();
    
    StatusOfImproving enumStatus = Mistake::stringToEnum(status);
    tracker.addMistake(Mistake(category, description, cause, solution, level, date, enumStatus));
    tracker.saveToFile("data/mistake.txt");
    
    displaySuccessMessage("Mistake added successfully on " + date);
    pauseScreen();
}

void UI::handleSearchMenu() {
    int choice;
    
    do {
        clearScreen();
        displaySearchMenu();
        choice = getValidMenuChoice(0, 5);
        
        switch (choice) {
            case 1: handleSearchById(); break;
            case 2: handleSearchByCategory(); break;
            case 3: handleSearchByDescription(); break;
            case 4: handleSearchByLevel(); break;
            case 5: handleSearchByDate(); break;
            case 0: 
                displayInfoMessage("Returning to main menu...");
                break;
        }
        
        if (choice != 0) {
            pauseScreen();
        }
        
    } while (choice != 0);
}

void UI::handleEditMistake() {
    displayHeader("EDIT MISTAKE");
    
    int mistakeId;
    std::cout << "🔢 Enter Mistake ID to edit: ";
    
    if (!(std::cin >> mistakeId)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        displayErrorMessage("Invalid ID! Please enter a valid number.");
        pauseScreen();
        return;
    }
    
    std::cin.ignore();
    
    if (!tracker.editMistake(mistakeId)) {
        displayErrorMessage("Failed to edit mistake with ID " + std::to_string(mistakeId));
    }
    
    pauseScreen();
}

void UI::handleDisplayAll() {
    clearScreen();
    displayHeader("ALL MISTAKES");
    tracker.displayAll();
    pauseScreen();
}

void UI::handleStatistics() {
    clearScreen();
    tracker.displayStatistics();
    pauseScreen();
}

// Search handlers
void UI::handleSearchById() {
    displayHeader("SEARCH BY ID");
    
    int searchId;
    std::cout << "🔢 Enter Mistake ID: ";
    
    if (!(std::cin >> searchId)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        displayErrorMessage("Invalid ID! Please enter a valid number.");
        return;
    }
    
    std::cin.ignore();
    tracker.searchById(searchId);
}

void UI::handleSearchByCategory() {
    displayHeader("SEARCH BY CATEGORY");
    
    std::string searchCategory;
    std::cout << "📂 Enter Category to search: ";
    std::getline(std::cin, searchCategory);
    
    if (searchCategory.empty()) {
        displayErrorMessage("Category cannot be empty!");
        return;
    }
    
    tracker.searchByCategory(searchCategory);
}

void UI::handleSearchByDescription() {
    displayHeader("SEARCH BY DESCRIPTION");
    
    std::string searchDescription;
    std::cout << "📝 Enter Description keyword to search: ";
    std::getline(std::cin, searchDescription);
    
    if (searchDescription.empty()) {
        displayErrorMessage("Description cannot be empty!");
        return;
    }
    
    tracker.searchByDescription(searchDescription);
}

void UI::handleSearchByLevel() {
    displayHeader("SEARCH BY LEVEL");
    
    std::string searchLevel;
    std::cout << "📈 Enter Level (Low/Medium/High): ";
    std::getline(std::cin, searchLevel);
    
    // Validate level input
    std::transform(searchLevel.begin(), searchLevel.end(), searchLevel.begin(), ::tolower);
    if (searchLevel == "low" || searchLevel == "medium" || searchLevel == "high") {
        searchLevel[0] = std::toupper(searchLevel[0]);
        tracker.searchByLevel(searchLevel);
    } else {
        displayErrorMessage("Invalid level! Please enter Low, Medium, or High.");
    }
}

void UI::handleSearchByDate() {
    displayHeader("SEARCH BY DATE");
    
    std::string searchDate;
    std::cout << "📅 Enter Date (DD/MM/YYYY or partial date): ";
    std::getline(std::cin, searchDate);
    
    if (searchDate.empty()) {
        displayErrorMessage("Date cannot be empty!");
        return;
    }
    
    tracker.searchByDate(searchDate);
}

// Additional features
void UI::displayHelp() const {
    clearScreen();
    displayHeader("HELP & INSTRUCTIONS");
    
    std::cout << "┌─────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│                         📚 HOW TO USE                           │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────────┘" << std::endl;
    std::cout << std::endl;
    
    std::cout << "🎯 PURPOSE:" << std::endl;
    std::cout << "   Track your mistakes to learn and improve continuously!" << std::endl;
    std::cout << std::endl;
    
    std::cout << "📝 ADDING MISTAKES:" << std::endl;
    std::cout << "   • Choose option 1 from main menu" << std::endl;
    std::cout << "   • Fill in all required fields" << std::endl;
    std::cout << "   • Use 'END' to finish multi-line inputs" << std::endl;
    std::cout << "   • Levels: Low, Medium, High" << std::endl;
    std::cout << "   • Status: NOTSTARTED, ONGOING, DONE" << std::endl;
    std::cout << std::endl;
    
    std::cout << "🔍 SEARCHING:" << std::endl;
    std::cout << "   • Search by ID for exact matches" << std::endl;
    std::cout << "   • Search by other fields supports partial matches" << std::endl;
    std::cout << "   • Searches are case-insensitive" << std::endl;
    std::cout << std::endl;
    
    std::cout << "✏️ EDITING:" << std::endl;
    std::cout << "   • Find mistake by ID first" << std::endl;
    std::cout << "   • Choose to remove or edit fields" << std::endl;
    std::cout << "   • Press Enter to skip fields you don't want to change" << std::endl;
    std::cout << std::endl;
    
    std::cout << "📊 STATISTICS:" << std::endl;
    std::cout << "   • View breakdown by level, status, and category" << std::endl;
    std::cout << "   • Track your improvement progress" << std::endl;
    std::cout << std::endl;
    
    displayFooter();
}

void UI::displayAbout() const {
    clearScreen();
    displayHeader("ABOUT");
    
    std::cout << "┌─────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│                    🎯 MISTAKE TRACKER v2.0                      │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────────────┘" << std::endl;
    std::cout << std::endl;
    
    std::cout << "💡 PHILOSOPHY:" << std::endl;
    std::cout << "   \"Mistakes are proof that you are trying.\"" << std::endl;
    std::cout << "   This application helps you track, analyze, and learn from" << std::endl;
    std::cout << "   your mistakes to accelerate your growth and improvement." << std::endl;
    std::cout << std::endl;
    
    std::cout << "✨ FEATURES:" << std::endl;
    std::cout << "   • 📝 Add and categorize mistakes" << std::endl;
    std::cout << "   • 🔍 Powerful search functionality" << std::endl;
    std::cout << "   • ✏️ Edit and update mistake records" << std::endl;
    std::cout << "   • 📊 View insightful statistics" << std::endl;
    std::cout << "   • 💾 Persistent data storage" << std::endl;
    std::cout << "   • 🎨 Beautiful, user-friendly interface" << std::endl;
    std::cout << std::endl;
    
    std::cout << "🎨 DESIGN PRINCIPLES:" << std::endl;
    std::cout << "   • Intuitive and easy to use" << std::endl;
    std::cout << "   • Clear visual feedback" << std::endl;
    std::cout << "   • Comprehensive error handling" << std::endl;
    std::cout << "   • Consistent user experience" << std::endl;
    std::cout << std::endl;
    
    std::cout << "📧 SUPPORT:" << std::endl;
    std::cout << "   For questions or feedback, refer to the Help section" << std::endl;
    std::cout << "   or consult the application documentation." << std::endl;
    std::cout << std::endl;
    
    displayFooter();
}

// Main application entry point
void UI::run() {
    displayWelcomeMessage();
    pauseScreen();
    
    int choice;
    
    do {
        clearScreen();
        
        // Display current status
        if (!tracker.isEmpty()) {
            std::cout << "📊 Current Status: " << tracker.getMistakeCount() 
                      << " mistakes tracked" << std::endl;
            std::cout << std::endl;
        }
        
        displayMainMenu();
        choice = getValidMenuChoice(0, 7);
        
        clearScreen();
        
        switch (choice) {
            case 1:
                handleAddMistake();
                break;
                
            case 2:
                handleSearchMenu();
                break;
                
            case 3:
                handleEditMistake();
                break;
                
            case 4:
                handleDisplayAll();
                break;
                
            case 5:
                handleStatistics();
                break;
                
            case 6:
                displayHelp();
                pauseScreen();
                break;
                
            case 7:
                displayAbout();
                pauseScreen();
                break;
                
            case 0:
                displayHeader("GOODBYE");
                std::cout << "┌─────────────────────────────────────────────────────────────────┐" << std::endl;
                std::cout << "│                          👋 GOODBYE!                            │" << std::endl;
                std::cout << "│                                                                 │" << std::endl;
                std::cout << "│            Thank you for using Mistake Tracker!                │" << std::endl;
                std::cout << "│              Keep learning from your mistakes! 🚀               │" << std::endl;
                std::cout << "│                                                                 │" << std::endl;
                std::cout << "└─────────────────────────────────────────────────────────────────┘" << std::endl;
                break;
                
            default:
                displayErrorMessage("Invalid choice! Please try again.");
                pauseScreen();
                break;
        }
        
    } while (choice != 0);
}