#include "../include/UI.hpp"
#include <ctime>
#include <iomanip>

void UI::run() {
    int choice;
    do
    {
        std::cout << "1. Add" << "\n2. Watch" << "\n3. Save To File" << "\n0. Quit\nYour Selection: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1: 
        {
            std::string na, desc, cau, sol, cat, lev, dat;
            status stat;
            std::cout << "Name: ";
            std::getline(std::cin, na);
            std::cout << "Description: ";
            std::getline(std::cin, desc);
            std::cout << "Cause: ";
            std::getline(std::cin, cau);
            std::cout << "Solution: ";
            std::getline(std::cin, sol);
            
            time_t currentTime = time(0);
            tm* localTime = localtime(&currentTime);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%d/%m/%y", localTime);
            dat = buffer;

            std::cout << "Level(1->10): ";
            std::getline(std::cin, lev);

            stat = NOTSTARTED;

            tracker.addMistake(Mistake(na, desc, cau, sol, cat, lev, dat, stat));
            break;
        }
        case 2:
            tracker.displayAll();
            break;
        case 3:
            tracker.saveToFile("data/mistakes.txt");
            break;
        case 0:
            std::cout << "Quit!\n";
            break;
        
        default:
            std::cout << "Invaild!\n";
        }
    } while (choice != 0);
    
}