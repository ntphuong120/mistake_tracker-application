#include "../include/Mistake.hpp"
#include <string>
#include <algorithm>

std::atomic<int> Mistake::nextID = 1;

Mistake::Mistake() : ID(nextID++) {}
Mistake::Mistake(
            const std::string& Category, const std::string& Description, 
            const std::string& Cause, const std::string& Solution, const std::string& Level,
            const std::string Date, StatusOfImproving status_ofimproving)
            : 
            ID(nextID++), Category(Category), Description(Description), Cause(Cause), 
            Solution(Solution), Level(Level), Date(Date), status_ofimproving(status_ofimproving) {}
Mistake::Mistake(
            int ID, const std::string& Category, const std::string& Description, 
            const std::string& Cause, const std::string& Solution, const std::string& Level,
            const std::string Date, StatusOfImproving status_ofimproving)
            : 
            ID(nextID++), Category(Category), Description(Description), Cause(Cause), 
            Solution(Solution), Level(Level), Date(Date), status_ofimproving(status_ofimproving) {}


// Getters
int Mistake::getID() const {
    return ID;
}

std::string Mistake::getCategory() const {
    return Category;
}

std::string Mistake::getDescription() const {
    return Description;
}

std::string Mistake::getCause() const {
    return Cause;
}

std::string Mistake::getSolution() const {
    return Solution;
}

std::string Mistake::getLevel() const {
    return Level;
}

std::string Mistake::getDate() const {
    return Date;
}

StatusOfImproving Mistake::getStatusOfImproving() const {
    return status_ofimproving;
}

// Setters
void Mistake::setID() {
    this->ID = ID - 1;
}

void Mistake::setCategory(const std::string& Category_toSet) {
    if (Category_toSet.empty()) return;

    Category = Category_toSet;
}

void Mistake::setDescription(const std::string& Description_toSet) {
    if (Description_toSet.empty()) return;
    
    Description = Description_toSet;
}

void Mistake::setCause(const std::string& Cause_toSet) {
    if (Cause_toSet.empty()) return;
    Cause = Cause_toSet;
}

void Mistake::setSolution(const std::string& Solution_toSet) {
    if (Solution_toSet.empty()) return;

    Solution = Solution_toSet;
}

void Mistake::setLevel(const std::string& Level_toSet) {
    if (Level_toSet.empty()) return;

    Level = Level_toSet;
}

void Mistake::setStatusOfImproving(const std::string& Status_toSet) {
    if (Status_toSet.empty()) return;

    StatusOfImproving enumStatus = stringToEnum(Status_toSet);

    status_ofimproving = enumStatus;
}

// Display information 
void Mistake::display() const {
    std::cout << "---------------------------------------------------\n";    
    std::cout << "ID: " << ID << "\n";
    std::cout << "Category: " << Category << "\n";
    std::cout << "Description: \n" << Description << "\n";
    std::cout << "Cause: \n" << Cause << "\n";
    std::cout << "Solution: \n" << Solution << "\n";
    std::cout << "Level: "  << Level << "\n";
    std::cout << "Date: " << Date << "\n";
    std::cout << "Status Of Improving: " << enumToString(status_ofimproving) << "\n";
    std::cout << "---------------------------------------------------\n\n";

}

// Methods for status of improving
std::string Mistake::enumToString(StatusOfImproving enum_status) {
    switch (enum_status)
    {
    case NOTSTARTED:
        return "NOTSTARTED";
    case ONGOING:
        return "ONGOING";
    case DONE:
        return "DONE";
    
    default:
        return "NOTSTARTED";
    }    
}

StatusOfImproving Mistake::stringToEnum(const std::string& str_status) {
    std::string status_lower = str_status;
    std::transform(status_lower.begin(), status_lower.end(), status_lower.begin(), ::tolower);
    
    if (status_lower == "notstarted") 
        return NOTSTARTED;
    if (status_lower == "ongoing")
        return ONGOING;
    if (status_lower == "done")
        return DONE;
        
    return NOTSTARTED;
}

std::string Mistake::getStatusString(StatusOfImproving enum_status) {
    return enumToString(enum_status);    
}