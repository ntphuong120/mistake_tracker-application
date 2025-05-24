#ifndef MISTAKE_HPP
#define MISTAKE_HPP

#include <iostream>
#include <atomic>

enum StatusOfImproving {
    NOTSTARTED,
    ONGOING,
    DONE
};

class Mistake {
private:
    static std::atomic<int> nextID;
    int ID;
    std::string Category;
    std::string Description;
    std::string Cause;
    std::string Solution;
    std::string Level;
    std::string Date;
    StatusOfImproving status_ofimproving;
public:
    Mistake();
    Mistake(const std::string& Category, const std::string& Description, 
            const std::string& Cause, const std::string& Solution, const std::string& Level,
            const std::string Date, StatusOfImproving status_ofimproving);
    Mistake(int ID, const std::string& Category, const std::string& Description, 
            const std::string& Cause, const std::string& Solution, const std::string& Level,
            const std::string Date, StatusOfImproving status_ofimproving);

    // Getters
    int getID() const;
    std::string getCategory() const;
    std::string getDescription() const;
    std::string getCause() const;
    std::string getSolution() const;
    std::string getLevel() const;
    std::string getDate() const;
    StatusOfImproving getStatusOfImproving() const;

    // Setters
    void setID();
    void setCategory(const std::string& Category_toSet);
    void setDescription(const std::string& Description_toSet);
    void setCause(const std::string& Cause_toSet);
    void setSolution(const std::string& Solution_toSet);
    void setLevel(const std::string& Level_toSet);
    void setStatusOfImproving(const std::string& Status_toSet);

    // Display information about this mistake
    void display() const;

    // Methods for status of improving
    static std::string enumToString(StatusOfImproving enum_status);
    static StatusOfImproving stringToEnum(const std::string& str_status);
    static std::string getStatusString(StatusOfImproving enum_status);
};

#endif