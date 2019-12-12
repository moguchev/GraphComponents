#include <chrono>
#include <filesystem>
#include <memory>
#include <iostream>
#include <string>
#include <sstream>
#include "../CourseProject/CArcGraph.hpp"
#include "../CourseProject/CBFSWalker.hpp"
#include "../CourseProject/CDFSWalker.hpp"
#include "../CourseProject/CDSUWalker.hpp"
#include "../CourseProject/CFileParser.hpp"
#include "../CourseProject/CListGraph.hpp"
#include "../CourseProject/Utils.hpp"

namespace fs = std::filesystem;

const auto BASE_DIR = ".";
const auto SOURCES = "sources";
const auto TESTS = "tests";
const auto RESULTS = "results";
const auto BFS_EXT = ".bfs";
const auto DFS_EXT = ".dfs";
const auto DSU_EXT = ".dsu";
const auto ANS_EXT = ".ans";

int main() {
    const fs::path baseDir(BASE_DIR);
    const fs::path pathToSources = baseDir / SOURCES;
    const fs::path pathToTests = baseDir / TESTS;

    fs::create_directory(baseDir / RESULTS);
    const fs::path pathToResults = baseDir / RESULTS;

    if (fs::exists(pathToSources) && fs::is_directory(pathToSources)) {
        for (const auto& entry : std::filesystem::directory_iterator(pathToSources)) {
            if (!fs::is_directory(entry.status())) {
                CListGraph<std::string> lg; // Граф на списках смежных вершин
                CArcGraph<std::string> ag; // Граф на списках рёбер

                CFileParser::parth(entry.path().generic_string(), lg);
                CFileParser::parth(entry.path().generic_string(), ag);

                auto filename = entry.path().stem().generic_string();

                // отвечает за поиск компонент связности с помощью обхода в ширину
                auto filepath = pathToResults / (filename + BFS_EXT);
                CBFSWalker<std::string> w0;
                showStatisticsOfWalking(lg, w0, filepath.string());

                // отвечает за поиск компонент связности с помощью обхода в глубину
                CDFSWalker<std::string> w1;
                filepath = pathToResults / (filename + DFS_EXT);
                showStatisticsOfWalking(lg, w1, filepath.string());

                // отвечает за поиск компонент связности с помощью системы непересекающихся множеств
                CDSUWalker<std::string> w2;
                filepath = pathToResults / (filename + DSU_EXT);
                showStatisticsOfWalking(ag, w2, filepath.string());
            }
        }
        for (const auto& entry : std::filesystem::directory_iterator(pathToResults)) {
            if (!fs::is_directory(entry.status())) {
                std::cout << "Test: " << entry.path().filename() << " is running..." << std::endl;
                std::ifstream ifs;

                ifs.open(entry.path());
                auto result = (std::stringstream() << ifs.rdbuf()).str();
                ifs.close();

                auto filename = entry.path().stem().generic_string();
                auto answerpath = pathToTests / (filename + ANS_EXT);
                std::cout << "Control test: " << answerpath.filename() << std::endl;

                ifs.open(answerpath);
                auto answer = (std::stringstream() << ifs.rdbuf()).str();
                ifs.close();

                if (result != answer) {
                    std::cerr << "Wrong result in " << entry.path().stem() <<
                        std::endl << "Expected " << answer << std::endl;
                    return EXIT_FAILURE;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}