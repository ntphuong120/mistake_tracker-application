#include "../include/FileHandler.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

// Helper method to trim whitespace
std::string FileHandler::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

// Helper method to handle pipe characters
std::string FileHandler::escapePipeCharacters(const std::string& str) {
    std::string result = str;
    size_t pos = 0;
    while ((pos = result.find('|', pos)) != std::string::npos) {
        result.replace(pos, 1, "||");
        pos += 2;
    }
    return result;
}

std::string FileHandler::unescapePipeCharacters(const std::string& str) {
    std::string result = str;
    size_t pos = 0;
    while ((pos = result.find("||", pos)) != std::string::npos) {
        result.replace(pos, 2, "|");
        pos += 1;
    }
    return result;
}

void FileHandler::saveToFile(const std::vector<Mistake>& mistakes, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
        return;
    }

    // Write header
    file << "ID|Category|Description|Cause|Solution|Level|Date|Status\n";

    // Write each mistake
    for (const Mistake& mistake : mistakes) {
        file << mistake.getID() << "|"
             << escapePipeCharacters(mistake.getCategory()) << "|"
             << escapePipeCharacters(mistake.getDescription()) << "|"
             << escapePipeCharacters(mistake.getCause()) << "|"
             << escapePipeCharacters(mistake.getSolution()) << "|"
             << escapePipeCharacters(mistake.getLevel()) << "|"
             << escapePipeCharacters(mistake.getDate()) << "|"
             << mistake.getStatusString(mistake.getStatusOfImproving()) << "\n";
    }

    file.close();
    std::cout << "Successfully saved " << mistakes.size() << " mistakes to " << filename << std::endl;
}

std::vector<std::string> FileHandler::splitLineRespectingEscapedPipes(const std::string& line) {
    std::vector<std::string> tokens;
    std::string current;
    
    for (size_t i = 0; i < line.length(); i++) {
        if (line[i] == '|') {
            // Check if this is an escaped pipe (||)
            if (i + 1 < line.length() && line[i + 1] == '|') {
                // This is an escaped pipe, add single | to current token
                current += '|';
                i++; // Skip the next |
            } else {
                // This is a field separator
                tokens.push_back(current);
                current.clear();
            }
        } else {
            current += line[i];
        }
    }
    
    // Add the last token
    if (!current.empty() || !tokens.empty()) {
        tokens.push_back(current);
    }
    
    return tokens;
}

std::vector<Mistake> FileHandler::loadFromFile(const std::string& filename) {
    std::vector<Mistake> mistakes;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Warning: Unable to open file " << filename << " for reading." << std::endl;
        return mistakes;
    }

    std::string line;
    bool headerSkipped = false;
    int lineCount = 0;

    while (std::getline(file, line)) {
        lineCount++;
        line = trim(line);

        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        // Skip header
        if (!headerSkipped) {
            headerSkipped = true;
            continue;
        }

        // Parse line using improved splitting method
        std::vector<std::string> tokens = splitLineRespectingEscapedPipes(line);
        
        // Trim each token
        for (auto& token : tokens) {
            token = trim(token);
        }

        // Validate token count
        if (tokens.size() != 8) {
            std::cerr << "Warning: Invalid line format at line " << lineCount 
                      << " (expected 8 fields, got " << tokens.size() << ")" << std::endl;
            std::cerr << "Line content: " << line << std::endl;
            continue;
        }

        try {
            // Parse fields - no need to unescape since we handled it during splitting
            int id = std::stoi(tokens[0]);
            std::string category = tokens[1];
            std::string description = tokens[2];
            std::string cause = tokens[3];
            std::string solution = tokens[4];
            std::string level = tokens[5];
            std::string date = tokens[6];
            std::string status = tokens[7];

            // Convert status to enum
            StatusOfImproving enumStatus = Mistake::stringToEnum(status);

            // Create and add mistake
            mistakes.emplace_back(id, category, description, cause, solution, level, date, enumStatus);
        }
        catch (const std::exception& e) {
            std::cerr << "Warning: Error parsing line " << lineCount << ": " << e.what() << std::endl;
            std::cerr << "Line content: " << line << std::endl;
            continue;
        }
    }

    file.close();
    std::cout << "Successfully loaded " << mistakes.size() << " mistakes from " << filename << std::endl;
    
    return mistakes;
}