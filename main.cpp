#include <algorithm>
#include <fstream>
#include <iomanip>
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
    std::cout << "4th param is program code (p for pagerank, b for betweenness, f for finding path)\n";
    std::cout << "      EX: p\n\n";
    std::cout << "5th param (optional) is the numnber of iterations for pagerank (defaults to 100) or the source for "
                 "finding path\n";
    std::cout << "      EX: 500\n\n";
    std::cout << "6th param (optional) is the target for finding path \n";
    std::cout << "      EX: 53\n\n";
    std::cout << "Example CLI command: ./final_proj assets/data.csv true all f 20 13 \n" << std::endl;
}

int main(int argc, const char** argv) {
    /**argument 1 is the command ./final_proj
     * argument 2 is the filepath,
     * argument 3 is a bool for whether csv file has headings or not
     * argument 4 is the vertex the user wants data of (or type 'all' to save all data to a txt file)
     * argument 5 is program code (p for pagerank, b for betweenness, all for both, f for finding path)
     * argument 6 is the number of iterations for pagerank (defaults to 100) or the source for finding path
     * argument 7 is the target for finding path (if applicable)
     **/

    if (argc < 5 || argc > 7) {
        usageErr();
        return 0;
    }

    int iter = 100;

    if (argc >= 6) {
        iter = atoi(argv[5]);

        if (iter == 0) {
            std::cout << "Please enter integers for 4th param only!" << std::endl;
            return 0;
        }
    }

    string filepath = argv[1];
    bool hasHeaders = false;

    if (strcmp(argv[2], "true") == 0) {
        hasHeaders = true;
    }

    else if (strcmp(argv[2], "false") != 0) {
        hasHeaders = false;
    }

    else {
        std::cout << "Please enter either a true or a false for the 2nd param only!" << std::endl;
    }

    auto g = Graph(filepath, hasHeaders);
    if (g.getNumVertices() == 0) {
        return 0;
    }

    if (strcmp(argv[4], "p") == 0) {
        auto page = g.PageRank(iter);
        int uid;

        if (strcmp(argv[3], "all") == 0) {
            uid = -1;
            std::cout << "The data has been written to the respective text files\n";
        }

        else {
            uid = atoi(argv[3]);
        }

        if (uid != -1 && !g.vertexExists(uid)) {
            std::cout << "Invalid user ID... saving data to txt file" << std::endl;
            uid = -1;
        }

        if (uid == -1) {
            auto vrank = sort(page);

            std::ofstream out2("pagerank.txt");
            out2.clear();
            out2 << std::setw(10) << "User ID" << std::setw(10) << ":" << std::setw(10) << "Rank\n";

            for (auto& obj : vrank) {
                out2 << std::setw(10) << obj.first << std::setw(10) << ":" << std::setw(10) << obj.second << "\n";
            }

            out2.close();
        }

        else {
            std::cout << "The vertex with User ID " << uid << " has \n";
            std::cout << "Page rank :" << page[uid] << std::endl;
        }
    }

    else if (strcmp(argv[4], "b") == 0) {
        auto cent = g.betweennessCentrality();
        int uid;

        if (strcmp(argv[3], "all") == 0) {
            uid = -1;
            std::cout << "The data has been written to the respective text files\n";
        }

        else {
            uid = atoi(argv[3]);
        }

        if (uid != -1 && !g.vertexExists(uid)) {
            std::cout << "Invalid user ID... saving data to txt file" << std::endl;
            uid = -1;
        }

        if (uid == -1) {
            auto vcent = sort(cent);
            std::ofstream out("betweenness.txt");
            out.clear();
            out << std::setw(10) << "User ID" << std::setw(10) << ":" << std::setw(10) << "Betweenness Number\n";

            for (auto& obj : vcent) {
                out << std::setw(10) << obj.first << std::setw(10) << ":" << std::setw(10) << obj.second << "\n";
            }

            out.close();
        }

        else {
            std::cout << "The vertex with User ID " << uid << " has \n";
            std::cout << "Betweenness Number :" << cent[uid] << "   " << std::endl;
        }
    }

    else if (strcmp(argv[4], "f") == 0) {
        int source = atoi(argv[5]);
        int target = atoi(argv[6]);
        auto bfs = g.findPath(source, target);

        for (auto& obj : bfs) {
            std::cout << obj << std::endl;
        }
    }

    else {
        usageErr();
    }
}