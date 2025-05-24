#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include "Mistake.hpp"
#include <vector>
#include <string>

class FileHandler {
public:
    static void saveToFile(const std::vector<Mistake>& mistakes, const std::string& filename);
    static std::vector<Mistake> loadFromFile(const std::string& filename);
};

#endif