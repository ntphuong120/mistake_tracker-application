#ifndef MISTAKE_HPP
#define MISTAKE_HPP

#include <iostream>

enum status {
    NOTSTARTED,
    ONGOING,
    DONE
};

class Mistake {
private:
    std::string name;
    std::string wrongDescription;
    std::string cause;
    std::string solution;
    std::string category;
    std::string level;
    std::string date;
    status statusOfimproving;
public: 
    Mistake();
    Mistake(const std::string& name, const std::string& wrongDescription, const std::string& cause,
        const std::string& solution, const std::string& category, const std::string& level,
        const std::string& date, status statusOfimproving);
    
    
    void display() const;

    // Read
    std::string getName() const;
    std::string getDescription() const;
    std::string getCause() const;
    std::string getSolution() const;
    std::string getCategory() const;
    std::string getLevel() const;
    std::string getDate() const;
    status getStatus() const;

    // Another feature
    static std::string enumTostring(status e_status);
    static status stringToenum(const std::string& str);
    std::string getStatusString() const;
};

#endif