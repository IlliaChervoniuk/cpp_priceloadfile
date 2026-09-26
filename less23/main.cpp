#include <iostream>
#include <fstream>
#include <string>
#include "product.h"
#include "price.h"
int main()
{
    setlocale(LC_ALL, "UA");
    Price* price = new Price();
    while (true) {
        int choice;
        std::cout << "\nChoice an action:\n"
            << "1: init price\n"
            << "2: load price\n"
            << "3: show price\n"
            << "0: exit\n"
            << "> ";
        if (!(std::cin >> choice)) {
            break;
        }

        switch (choice) {/
            case 1:
                if (price->init()) {
                    std::cout << "Price init success" << std::endl;
                }
                else {
                    std::cout << "Price init error" << std::endl;
                }
                break;
            case 2:
                if (price->load()) {
                    std::cout << "Price load success" << std::endl;
                }
                else {
                    std::cout << "Price load error" << std::endl;
                }
                break;
            case 3:
                price->show();
                break;
            case 0:
                return 0;
            default:
                std::cout << "Invalid choice" << std::endl;
        }
    }

    return 0;
}


