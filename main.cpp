#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "graph/graph.h"

bool cmp(std::pair<int, double>& a, std::pair<int, double>& b) { return a.second > b.second; }

std::vector<std::pair<int, double>> sort(std::unordered_map<int, double> map) {
    std::vector<std::pair<int, double>> A;
    for (auto& it : map) {
        A.push_back(it);
    }
    std::sort(A.begin(), A.end(), cmp);
    return A;
}

void usageErr() {
    std::cout << "\nUsage:\n" << std::endl;
    std::cout << "1st param is the filepath for the csv data relative to cwd\n";
    std::cout << "      EX: assets/data.csv\n\n";
    std::cout << "2nd param is a bool for whether csv file has headings or not\n";
    std::cout << "      EX: true\n\n";
    std::cout << "3rd param is the vertex the user wants data of (or type 'all' to save all data to a txt file)\n";
    std::cout << "      EX: 1200\n\n";
    std::cout << "4th param (optional) is the numnber of iterations for pagerank (defaults to 100) \n";
    std::cout << "      EX: 500\n\n";
    std::cout << "Example CLI command: ./final_proj assets/data.csv true 1200 500 \n" << std::endl;
}

int main(int argc, const char** argv) {
    /**argument 1 is the command ./final_proj
     * argument 2 is the filepath,
     * argument 3 is a bool for whether csv file has headings or not
     * argument 4 is the vertex the user wants data of (or type 'all' to save all data to a txt file)
     * argument 5 is the numnber of iterations for pagerank (defaults to 100)
     **/
    // std::cout << argc << std::endl;
    if (argc < 4 || argc >= 6) {
        usageErr();
        return 0;
    }
    
    int iter = 100;
    if (argc == 5) {
        iter = atoi(argv[4]);
        if (iter == 0) {
            std::cout << "Please enter integers for 4th param only!" << std::endl;
            return 0;
        }
    }

    string filepath = argv[1];
    bool hasHeaders = false;
    if (strcmp(argv[2], "true") == 0) {
        hasHeaders = true;
    } else if (strcmp(argv[2], "false") != 0) {
        hasHeaders = false;
    } else {
        std::cout << "Please enter either a true or a false for the 2nd param only!" << std::endl;
    }

    auto g = Graph(filepath, hasHeaders);
    if (g.getNumVertices() == 0) {
        return 0;
    }

    auto cent = g.betweennessCentrality();
    auto page = g.PageRank(iter);

    int uid;
    if (strcmp(argv[3], "all") == 0)
        uid = -1;
    else
        uid = atoi(argv[3]);
    if (uid != -1 && !g.vertexExists(uid)) {
        std::cout << "Invalid user ID... saving data to txt file" << std::endl;
        uid = -1;
    }
    if (uid == -1) {
        auto vcent = sort(cent);
        auto vrank = sort(page);
        std::ofstream out("betweenness.txt");
        out << "User ID"
            << "   :   "
            << "Betweenness Number\n";
        for (auto& obj : vcent) {
            out << obj.first << "         :   " << obj.second << "\n";
        }
        out.close();

        std::ofstream out2("pagerank.txt");
        out2 << "User ID"
             << "   :   "
             << "Rank\n";
        for (auto& obj : vrank) {
            out2 << obj.first << "         :   " << obj.second << "\n";
        }
        out2.close();
    } else {
        std::cout << "The vertex with User ID " << uid << " has \n";
        std::cout << "Betweenness Number :" << cent[uid] << "   "
                  << "Page rank :" << page[uid] << std::endl;
    }
}