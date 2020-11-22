#pragma once

#include <vector>

class LoadCSV {
   public:
    LoadCSV() {}
    LoadCSV(std::string filepath, bool has_header);

   private:
    std::vector<std::string> data;
};