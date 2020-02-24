#ifndef C_FILE_PARSER_HPP
#define C_FILE_PARSER_HPP

#include <exception>
#include <fstream>
#include <string>
#include <type_traits>
#include "Interfaces/IGraph.hpp"

class CFileParser {
public:
    CFileParser() = default;

    ~CFileParser() = default;

    template <class T = std::string>
    static void parth(const std::string& filename, IGraph<T>& graph) {
        std::string line;
        std::ifstream in;
        in.open(filename);

        if (in.is_open()) {
            while (std::getline(in, line)) {
                if (!in) break;
                size_t space = line.find_first_of(SPACE);
                if (space != std::string::npos) {
                    const auto fitstVertex = line.substr(0, space);
                    const auto secondVertex = line.substr(space + 1);
                    if (secondVertex.size()) {
                        graph.addEdge(fitstVertex, secondVertex);
                    }
                }
            }
        }
        else {
            std::cerr << "Error in opening " << filename << std::endl;
        }
        in.close();
    }
private:
    static const char SPACE = ' ';
};

#endif // C_FILE_PARSER_HPP