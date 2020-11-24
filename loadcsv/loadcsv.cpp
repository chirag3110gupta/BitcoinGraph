#include "loadcsv.h"

#include <fstream>
#include <iostream>

LoadCSV::LoadCSV(std::string filepath, bool has_header) {
    std::ifstream data(filepath);
    std::string entry;

    if (data.is_open()) {
        if (has_header) {  // Ignore the headers of the csv
            getline(data, entry);
        }

        while (getline(data, entry)) {
            /** TODO: Implement graph */
        }
    } else {
        std::cerr << "Invalid csv filepath" << std::endl;
    }
    data.close();
}
