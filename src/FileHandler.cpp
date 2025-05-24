#include "../include/FileHandler.hpp"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

void FileHandler::saveToFile(const std::vector<Mistake>& mistakes, const std::string& filename) {
    std::ofstream myFile(filename, std::ios::out); // Ghi đè file
    if (!myFile.is_open()) {
        std::cout << "Unable to open file: " << filename << std::endl;
        return;
    }

    // Tùy chọn: Ghi tiêu đề một lần (nếu cần)
    myFile << "Name|Description|Cause|Solution|Category|Level|Date|Status\n";

    for (const auto& mistake : mistakes) {
        myFile << mistake.getName() << "|" 
               << mistake.getDescription() << "|" 
               << mistake.getCause() << "|" 
               << mistake.getSolution() << "|" 
               << mistake.getCategory() << "|" 
               << mistake.getLevel() << "|" 
               << mistake.getDate() << "|" 
               << mistake.getStatusString();
    }

    myFile.close();
}

std::vector<Mistake> FileHandler::loadFromFile(const std::string& filename) {
    std::ifstream myFile(filename, std::ios::in);
    std::vector<Mistake> mistakes;

    if (!myFile.is_open()) {
        std::cout << "Unable to open file: " << filename << std::endl;
        return mistakes;
    } 

    std::string line;
    int lineCount = 0;
    // Bỏ qua dòng tiêu đề nếu có
    bool firstLine = true;
    while (std::getline(myFile, line)) {
        lineCount++;
        if (line.empty()) {
            std::cout << "Skipping empty line at line " << lineCount << std::endl;
            continue;
        }
        if (firstLine && line.find("Name|Description|Cause|Solution|Category|Level|Date|Status") == 0) {
            firstLine = false;
            continue; // Bỏ qua dòng tiêu đề
        }
        firstLine = false;

        std::stringstream ss(line);
        std::string na, desc, cau, sol, cat, lev, dat, stat;
        if (!std::getline(ss, na, '|') || !std::getline(ss, desc, '|') ||
            !std::getline(ss, cau, '|') || !std::getline(ss, sol, '|') ||
            !std::getline(ss, cat, '|') || !std::getline(ss, lev, '|') ||
            !std::getline(ss, dat, '|') || !std::getline(ss, stat, '|')) {
            std::cout << "Invalid line format at line " << lineCount << ": " << line << std::endl;
            continue;
        }

        try {
            status statusEnum = Mistake::stringToenum(stat);
            mistakes.emplace_back(na, desc, cau, sol, cat, lev, dat, statusEnum);
        } catch (const std::exception& e) {
            std::cout << "Error parsing status at line " << lineCount << ": " << stat 
                      << " (" << e.what() << ")" << std::endl;
            continue;
        }
    }

    myFile.close();
    std::cout << "Loaded " << mistakes.size() << " mistakes from file" << std::endl;
    return mistakes;
}