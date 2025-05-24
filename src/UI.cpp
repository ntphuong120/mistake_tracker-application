#include "../include/UI.hpp"
#include <ctime>
#include <iomanip>

void UI::run() {
    int choice;
    std::cout << "==========================================================\n";
    std::cout << "           Welcome To Mistake Tracker Application\n";
    std::cout << "==========================================================\n\n";
    do
    {
        std::cout << "============================Menu==========================\n";
        std::cout << "1. Add" << std::endl;
        std::cout << "2. Search" << std::endl;
        std::cout << "3. Edit" << std::endl;
        std::cout << "4. Statistical" << std::endl;
        std::cout << "5. Show All" << std::endl;
        std::cout << "0. Quit" << std::endl;
        std::cout << "==========================================================\n";
        std::cout << "Your Selection: ";
        std::cin >> choice;
        std::cin.ignore();
        std::cout << "\n";

        switch (choice)
        {
            case 1: // Add 
            {
                std::string na, desc, cau, sol, cat, lev, dat;
                status stat;
                std::cout << "============================Add===========================\n";
                std::cout << "Name: ";
                std::getline(std::cin, na);
                std::cout << "Description: ";
                std::getline(std::cin, desc);
                std::cout << "Cause: ";
                std::getline(std::cin, cau);
                std::cout << "Solution: ";
                std::getline(std::cin, sol);
                std::cout << "Category: ";
                std::getline(std::cin, cat);
                
                time_t currentTime = time(0);
                tm* localTime = localtime(&currentTime);
                char buffer[80];
                strftime(buffer, sizeof(buffer), "%d/%m/%y", localTime);
                dat = buffer;

                std::cout << "Level(1->10): ";
                std::getline(std::cin, lev);

                stat = NOTSTARTED;

                tracker.addMistake(Mistake(na, desc, cau, sol, cat, lev, dat, stat));
                tracker.saveToFile("data/mistakes.txt");
                std::cout << "==========================================================\n\n";
                break;
            }
            case 2: // Search
            {
                int searchChoice;
                std::cout << "============================Search========================\n";
                std::cout << "1. Search By Name" << "\n2. Search By Category" << "\n3. Search By Level\n";
                std::cout << "==========================================================\n";
                std::cout << "Your Selection: ";
                std::cin >> searchChoice;
                std::cin.ignore();
                std::cout << "\n";

                switch (searchChoice) {
                    case 1: 
                    {
                        std::cout << "=====================Search By Name=======================\n";
                        std::string nameMistake;
                        std::cout << "Enter Name's Mistake: ";
                        std::getline(std::cin, nameMistake);
                        std::cout << "\n";
                        tracker.searchByName(nameMistake);
                        std::cout << "==========================================================\n\n";
                        break;
                    }

                    case 2:
                    {
                        std::cout << "====================Search By Category====================\n";
                        std::string categoryMistake;
                        std::cout << "Enter Category's Mistake: ";
                        std::getline(std::cin, categoryMistake);
                        std::cout << "\n";
                        tracker.searchByCategory(categoryMistake);
                        std::cout << "==========================================================\n\n";
                        break;
                    }

                    case 3:
                    {
                        std::cout << "====================Search By Level======================\n";
                        std::string levelMistake;
                        std::cout << "Enter Level's Mistake: ";
                        std::getline(std::cin, levelMistake);
                        std::cout << "\n";
                        tracker.searchByLevel(levelMistake);
                        std::cout << "==========================================================\n\n";
                        break;
                    }
                    
                    default:
                        std::cout << "Invalid!\n\n";
                        break;
                }

                break;
        }
        case 3: // Edit
            break;

        case 4: // statistical
            break;

        case 5: // Show All
        {
            std::cout << "=========================Display All======================\n";
            tracker.displayAll();
            std::cout << "==========================================================\n\n";
            break;
        }

        case 0: // Quit
            std::cout << "Quit!\n";
            break;
        
        default:
            std::cout << "Invaild!\n";
        }
    } while (choice != 0);
    
}