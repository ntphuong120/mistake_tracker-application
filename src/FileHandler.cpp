#include "../include/FileHandler.hpp"
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <sstream>

void FileHandler::saveToFile(const std::vector<Mistake>& mistakes, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for Writing\n";
        return;
    }

    try
    {
        file << "ID|Category|Description|Cause|Solution|Level|Date|Status\n";

        for (const Mistake& mistake : mistakes) {
            file << mistake.getID() << "|"
                 << mistake.getCategory() << "|"
                 << mistake.getDescription() << "|"
                 << mistake.getCause() << "|"
                 << mistake.getSolution() << "|"
                 << mistake.getLevel() << "|"
                 << mistake.getDate() << "|"
                 << mistake.getStatusString(mistake.getStatusOfImproving()) << '\n';
        }

        file.close();
        return;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error writing to text file: " << e.what() << '\n';
        return;
    }
}

std::vector<Mistake> FileHandler::loadFromFile(const std::string& filename) {
    std::vector<Mistake> mistakes;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for reading\n";
        return mistakes;
    }

    std::string line;
    int lineCount = 0;
    // Skip the first line in file
    bool firstLine = true;

    while(std::getline(file, line)) {
        lineCount++;
        if (firstLine && line.find("ID|Category|Description|Cause|Solution|Level|Date|Status") == 0) {
            firstLine = false;
            continue;
        }
        firstLine = false;

        std::stringstream ss(line);
        int id;
        std::string id_str, category, description, cause, solution, level, date, status;
        if (!std::getline(ss, id_str, '|') || !std::getline(ss, category, '|') ||
            !std::getline(ss, description, '|') || !std::getline(ss, cause, '|') ||
            !std::getline(ss, solution, '|') || !std::getline(ss, level, '|') ||
            !std::getline(ss, date, '|') || !std::getline(ss, status, '|')) 
        {
            std::cout << "Invalid line format at line " << lineCount << ": " << line << "\n";
            continue;
        }

        try
        {
            id = std::stoi(id_str);
            StatusOfImproving enum_status = Mistake::stringToEnum(status);
            mistakes.emplace_back(id, category, description, cause, solution, level, date, enum_status);
        }
        catch(const std::exception& e)
        {
            std::cout << "Error parsing status at line " << lineCount << ": " << status 
                      << " (" << e.what() << ")" << std::endl;

            continue;
        }    
    }

    file.close();
    std::cout << "Loaded " << mistakes.size() << " mistakes from file " << filename << '\n';
    return mistakes;
}