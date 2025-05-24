#include "../include/FileHandler.hpp"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

void FileHandler::saveToFile(const std::vector<Mistake>& mistakes, const std::string& filename) {
    std::ofstream myFile(filename, std::ios::app);
    
    if (myFile.is_open()) {
        for (auto& mistake : mistakes) {
            myFile << "Name Description Cause Solution Category Level Status\n";
            myFile << std::quoted(mistake.getName()) << ' ';
            myFile << std::quoted(mistake.getDescription()) << ' ' << 
                      std::quoted(mistake.getCause()) << ' ' << std::quoted(mistake.getSolution()) << ' ';
            myFile << std::quoted(mistake.getCategory()) << ' ';
            myFile << std::quoted(mistake.getLevel()) << ' ';
            myFile << std::quoted(mistake.getStatusString()) << ' ';
            myFile << std::quoted(mistake.getDate()) << ' ';
            myFile << std::endl;
        }

        myFile.close();
    } else {
        std::cout << "Unable to open file";
    }
}

std::vector<Mistake> FileHandler::loadFromFile(const std::string& filename) {
    std::ifstream myFile(filename);
    std::vector<Mistake> mistakes;

    if (!myFile.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        return mistakes;
    } 

    std::string line;
    while (std::getline(myFile, line)) {
        std::stringstream ss(line);
        std::string na, desc, cau, sol, cat, lev, dat, stat;
        std::getline(ss, na, '|');
        std::getline(ss, desc, '|');
        std::getline(ss, cau, '|');
        std::getline(ss, sol, '|');
        std::getline(ss, cat, '|');
        std::getline(ss, lev, '|');
        std::getline(ss, stat, '|');
        std::getline(ss, dat, '|');
        status statusEnum = Mistake::stringToenum(stat);
        mistakes.emplace_back(na, desc, cau, sol, cat, lev, dat, statusEnum);

    }

    myFile.close();
    return mistakes;
}