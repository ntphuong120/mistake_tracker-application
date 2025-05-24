#include "../include/Mistake.hpp"

Mistake::Mistake() {}

Mistake::Mistake(std::string& name, std::string& wrongDescription, std::string& cause, std::string& solution, 
                std::string& category, std::string& level, std::string& date, status statusOfimproving) {

    this->name = name;
    this->wrongDescription = wrongDescription;
    this->cause = cause;
    this->solution = solution;
    this->category = category;
    this->level = level;
    this->statusOfimproving = statusOfimproving;
}

void Mistake::display() const {
    std::cout << "Name: " << name << "\nCategory: " << category << "\nDescription: " << wrongDescription
    << "\nCause: " << cause << "\nSolution: " << solution << "\nLevel: " << level 
    << "\ndate" << date << "\nStatus Of Improving: " << statusOfimproving << "\n\n";
}

std::string Mistake::getName() const {
    return name;
}

std::string Mistake::getDescription() const {
    return wrongDescription;
}

std::string Mistake::getCause() const {
    return cause;
}

std::string Mistake::getSolution() const {
    return solution;
}

std::string Mistake::getCategory() const {
    return category;
}

std::string Mistake::getLevel() const {
    return level;
}

std::string Mistake::getDate() const {
    return date;
}

status Mistake::getStatus() const {
    return statusOfimproving;
}

std::string Mistake::enumTostring(status e_status) {
    switch (e_status)
    {
    case NOTSTARTED:
        return "NOT STARTED";
    case ONGOING:
        return "ONGOING";
    case DONE:
        return "DONE";
    default:
        return "NOT STARTED";
    }
}

status Mistake::stringToenum(const std::string& str) {
    if (str == "Not Started" || str == "NOT STARTED")
        return NOTSTARTED;
    else if (str == "Ongoing" || str == "ONGOING")
        return ONGOING;
    else 
        return DONE;
    
    return NOTSTARTED;
}

std::string Mistake::getStatusString() const {
    return Mistake::enumTostring(statusOfimproving);
}