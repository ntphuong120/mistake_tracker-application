#include "../include/UI.hpp"
#include <ctime>
#include <chrono>
#include <string>
#include <iostream> 

void UI::run() {
    std::cout << "====================================================================\n";
    std::cout << "              Welcome To Mistake Tracker Application\n";
    std::cout << "====================================================================\n\n";

    int choice_menu;

    do
    {
        std::cout << "================================Menu================================\n";
        std::cout << "1. Add\n";
        std::cout << "2. Search\n";
        std::cout << "3. Edit\n";
        std::cout << "4. Display All\n";
        std::cout << "0. Quit\n\n";
        std::cout << "Your Selection: ";
        std::cin >> choice_menu;
        std::cin.ignore(); // Xóa ký tự newline còn lại sau std::cin >> choice_menu
        std::cout << "====================================================================\n\n";

        switch (choice_menu)
        {
            case 1: // Add
            {
                std::cout << "=================================Add================================\n";
                std::string category, description, cause, solution, level, status; // Bỏ 'date' ở đây
                std::cout << "Category: ";
                std::getline(std::cin, category);
                std::cout << "Description: \n";
                std::getline(std::cin, description);
                std::cout << "Cause: \n";
                std::getline(std::cin, cause);
                std::cout << "Solution: \n";
                std::getline(std::cin, solution);
                std::cout << "Level(Low, Medium, High): ";
                std::getline(std::cin, level);

                // Lấy ngày hiện tại
                auto now = std::chrono::system_clock::now();
                std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
                std::tm localTime;

                // Sử dụng phiên bản an toàn hơn cho Windows, hoặc phiên bản chuẩn cho POSIX
                #ifdef _MSC_VER // Dành cho Visual Studio
                    localtime_s(&localTime, &currentTime);
                #else // Dành cho các hệ thống khác (Linux, macOS, v.v.)
                    localTime = *std::localtime(&currentTime);
                #endif

                char buffer[80];
                std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", &localTime);

                // Gán giá trị cho biến 'date' từ buffer
                std::string date = buffer; // Gán 'date' ở đây

                std::cout << "Status (NOTSTARTED, ONGOING, DONE): "; // Yêu cầu người dùng nhập status
                std::getline(std::cin, status);

                // Chuyển đổi status string sang enum
                StatusOfImproving enum_status = Mistake::stringToEnum(status);

                tracker.addMistake(Mistake(category, description, cause, solution, level, date, enum_status));
                tracker.saveToFile("data/mistake.txt");

                std::cout << "\nAdd Completed!\n"; // Thêm thông báo xác nhận
                std::cout << "====================================================================\n\n";
                break;
            }

            case 2: // Search
            {
                int choice_search;
                
                do {
                    std::cout << "================================Search==============================\n";
                    std::cout << "1. Search By ID\n";
                    std::cout << "2. Search By Category\n";
                    std::cout << "3. Search By Description\n";
                    std::cout << "4. Search By Level\n";
                    std::cout << "5. Search By Date\n";
                    std::cout << "0. Quit\n\n";
                    std::cout << "Your Selection: ";
                    std::cin >> choice_search;
                    std::cin.ignore();
                    std::cout << "====================================================================\n\n";


                    if (choice_search == 1) {
                        int SearchID;
                        std::cout << "=============================Search By ID===========================\n";
                        std::cout << "Enter ID's Mistake: ";
                        std::cin >> SearchID;
                        std::cin.ignore();

                        tracker.searchByID(SearchID);
                        std::cout << "====================================================================\n\n";
                        break;
                    } else if (choice_search == 2) {
                        std::string searchCategory;
                        std::cout << "==========================Search By Category========================\n";
                        std::cout << "Enter Category's Mistake: ";
                        std::getline(std::cin, searchCategory);

                        tracker.searchByCategory(searchCategory);
                        std::cout << "====================================================================\n\n";
                    } else if (choice_search == 3) {
                        std::string searchDescription;
                        std::cout << "=========================Search By Description======================\n";
                        std::cout << "Enter Description's Mistake: ";
                        std::getline(std::cin, searchDescription);

                        tracker.searchByDescription(searchDescription);
                        std::cout << "====================================================================\n\n";
                    } else if (choice_search == 4) {
                        std::string searchLevel;
                        std::cout << "================================Level===============================\n";
                        std::cout << "Enter Level: ";
                        std::getline(std::cin, searchLevel);

                        tracker.searchByLevel(searchLevel);
                        std::cout << "====================================================================\n\n";
                    } else if (choice_search == 5) {
                        std::string searchDate;
                        std::cout << "=================================Date===============================\n";
                        std::cout << "Enter Date's Mistake: ";
                        std::getline(std::cin, searchDate);

                        tracker.searchByDate(searchDate);
                        std::cout << "====================================================================\n\n";
                    } else if (choice_search == 0){
                        std::cout << "=================================Exit===============================\n";
                        std::cout << "---------------------------------------------------\n";
                        std::cout << "Quit!\n";
                        std::cout << "---------------------------------------------------\n";
                        std::cout << "====================================================================\n\n";
                        break;
                    } else {
                        std::cout << "=================================Error==============================\n";
                        std::cout << "---------------------------------------------------\n";
                        std::cout << "Invaild Number!\n";
                        std::cout << "---------------------------------------------------\n";
                        std::cout << "====================================================================\n\n";
                    }
                    

                } while(choice_search != 0); 
                
                break;
            }

            case 3: // Edit
            {
                std::cout << "===========================Identify Object==========================\n";
                // Find object to Edit
                int Mistake_ID;
                std::cout << "Enter ID's Mistake: ";
                std::cin >> Mistake_ID;
                std::cin.ignore();

                int index_ID = tracker.searchByID(Mistake_ID);

                if (index_ID != -1) {
                    // Editing
                    tracker.Edit(Mistake_ID, index_ID);
                }
                std::cout << "====================================================================\n\n";
                break;
            }

            case 4: // Display All
            {
                std::cout << "==============================Display All===========================\n";
                tracker.displayAll();
                std::cout << "====================================================================\n\n";
                break;
            }

            case 0: 
            {
                std::cout << "=================================Exit===============================\n";
                std::cout << "---------------------------------------------------\n";
                std::cout << "Quit!\n";
                std::cout << "---------------------------------------------------\n";
                std::cout << "====================================================================\n\n";
                break;
            }

            default: {
                std::cout << "=================================Error==============================\n";
                std::cout << "---------------------------------------------------\n";
                std::cout << "Invaild Number!\n";
                std::cout << "---------------------------------------------------\n";
                std::cout << "====================================================================\n\n";
            }
        }

    } while (choice_menu != 0);

}