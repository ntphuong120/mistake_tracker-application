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
    Category = Category_toSet;
}

void Mistake::setDescription(const std::string& Description_toSet) {
    Description = Description_toSet;
}

void Mistake::setCause(const std::string& Cause_toSet) {
    Cause = Cause_toSet;
}

void Mistake::setSolution(const std::string& Solution_toSet) {
    Solution = Solution_toSet;
}

void Mistake::setLevel(const std::string& Level_toSet) {
    Level = Level_toSet;
}

void Mistake::setStatusOfImproving(const std::string& Status_toSet) {
    StatusOfImproving enumStatus = stringToEnum(Status_toSet);

    status_ofimproving = enumStatus;
}

// Display information 
void Mistake::display() const {
    std::cout << "---------------------------------------------------\n";    
    std::cout << "ID: " << ID << "\n";
    std::cout << "Category: " << Category << "\n";
    std::cout << "Description: " << Description << "\n";
    std::cout << "Cause: " << Cause << "\n";
    std::cout << "Solution: " << Solution << "\n";
    std::cout << "Level: "  << Level << "\n";
    std::cout << "Status Of Improving: " << enumToString(status_ofimproving) << "\n";
    std::cout << "---------------------------------------------------\n\n";

}

// Methods for status of improving
std::string Mistake::enumToString(StatusOfImproving enum_status) {
    switch (enum_status)
    {
    case NOTSTARTED:
        return "NOT STARTED";
    case ONGOING:
        return "ON GOING";
    case DONE:
        return "DONE";
    
    default:
        return "NOT STARTED";
    }    
}

StatusOfImproving Mistake::stringToEnum(const std::string& str_status) {
    std::string status_lower = str_status;
    std::transform(status_lower.begin(), status_lower.end(), status_lower.begin(), ::tolower);
    
    if (status_lower == "not started") 
        return NOTSTARTED;
    if (status_lower == "on going")
        return ONGOING;
    if (status_lower == "done")
        return DONE;
        
    return NOTSTARTED;
}

std::string Mistake::getStatusString(StatusOfImproving enum_status) {
    return enumToString(enum_status);    
}