#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <vector>
#include <string>
#include <iostream>
#include "Mistake.hpp"

class FileHandler {
private:
    static std::vector<std::string> splitLineRespectingEscapedPipes(const std::string& line);
public:
    // Static method to save mistakes to file
    static void saveToFile(const std::vector<Mistake>& mistakes, const std::string& filename);
    
    // Static method to load mistakes from file
    static std::vector<Mistake> loadFromFile(const std::string& filename);

private:
    // Helper method to trim whitespace from strings
    static std::string trim(const std::string& str);
    
    // Helper method to replace pipe characters in text to avoid conflicts
    static std::string escapePipeCharacters(const std::string& str);
    
    // Helper method to restore pipe characters when reading
    static std::string unescapePipeCharacters(const std::string& str);
};

#endif // FILEHANDLER_HPP