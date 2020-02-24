#ifndef UTILS_HPP
#define UTILS_HPP

#include <chrono>
#include <memory>
#include <iostream>
#include "Interfaces/IGraph.hpp"
#include "Interfaces/IGraphWalker.hpp"

template <class T>
void showStatisticsOfWalking(
    IGraph<T>& graph,
    IGraphWalker<T>& walker,
    const std::string& filename
) {
    // ����� ������ ������ ���������
    auto begin = std::chrono::steady_clock::now();

    // ����� ���������� ��������� � �����
    std::unique_ptr<IGraphComponents<T>> c =
        std::move(walker.findComponentsInGraph(graph));

    // ����� ����� ������ ���������
    auto end = std::chrono::steady_clock::now();

    // ������� ������� ������ ���������
    auto elapsed_ms =
        std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    // ����� ��������� ���������
    //c->print();
    c->printToFile(filename);

    // ����� ������������� ������
    std::cout << "Working time of algorithm: " << elapsed_ms.count() << " mcs\n";
}

#endif //  UTILS_HPP
