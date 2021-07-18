#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "Clear.h"
#include <filesystem> // C++17 standard header file name
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <iostream>
using namespace std::experimental::filesystem::v1;

void Clear::removeLoadFiles()
{
    std::string files[3] = { "ficheiros\\my\\UC_Students.csv" , "ficheiros\\my\\ShiftsInformation.csv" , "ficheiros\\my\\Booking.csv" };
    try {
        for (int i = 0; i < 3; i++) {
            std::ofstream ofs;
            ofs.open(files[i], std::ofstream::out | std::ofstream::trunc);
            ofs.close();
        }
        for (const auto& entry : recursive_directory_iterator("ficheiros\\my\\placed"))
            remove_all(entry.path());
        for (const auto& entry : recursive_directory_iterator("shifts"))
            remove_all(entry.path());
    }
    catch (...) {
        std::cout << "Error: Impossible to remove load files!\n";
    }


}

bool Clear::empty(const std::string& folder)
{
    try 
    { 
        if (is_empty(folder))
            return true;
        return false;
    }
    catch (...) { return true; }
}