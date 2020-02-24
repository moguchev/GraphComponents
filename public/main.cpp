#include <chrono>
#include <memory>
#include <iostream>
#include <string>
#include <filesystem>

#include "CFileParser.hpp"
#include "CDSU.hpp"
#include "Graphs/CArcGraph.hpp"
#include "GraphsCListGraph.hpp"
#include "Walkers/CBFSWalker.hpp"
#include "Walkers/CDFSWalker.hpp"
#include "Walkers/CDSUWalker.hpp"
#include "Utils.hpp"

const auto BFS = "bfs";
const auto DFS = "dfs";
const auto DSU = "dsu";
const auto ALL = "all";

int main(int argc, const char* argv[]) {
    if (argc >= 4) {
        CListGraph<std::string> lg; // Граф на списках смежных вершин
        CArcGraph<std::string> ag; // Граф на списках рёбер

        CFileParser::parth(argv[2], lg);
        CFileParser::parth(argv[2], ag);

        // отвечает за поиск компонент связности с помощью обхода в ширину
        CBFSWalker<std::string> w0;
        // отвечает за поиск компонент связности с помощью обхода в глубину
        CDFSWalker<std::string> w1;
        // отвечает за поиск компонент связности с помощью системы непересекающихся множеств
        CDSUWalker<std::string> w2;
        const auto mode = std::string(argv[1]);
        if (mode == BFS) {
            showStatisticsOfWalking(lg, w0, argv[3]);
        }
        else if (mode == DFS) {
            showStatisticsOfWalking(lg, w1, argv[3]);
        }
        else if (mode == DSU) {
            showStatisticsOfWalking(lg, w2, argv[3]);
        }
        else if (mode == ALL && argc >= 6) {
            showStatisticsOfWalking(lg, w0, argv[3]);
            showStatisticsOfWalking(lg, w1, argv[4]);
            showStatisticsOfWalking(ag, w2, argv[5]);
        }
    }
    return 0;
}
