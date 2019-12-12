#ifndef UTILS_HPP
#define UTILS_HPP

#include <chrono>
#include <memory>
#include <iostream>
#include "../Interfaces/IGraph.hpp"
#include "../Interfaces/IGraphWalker.hpp"

template <class T>
void showStatisticsOfWalking(
    IGraph<T>& graph,
    IGraphWalker<T>& walker,
    const std::string& filename
) {
    // Время начала работы алгоритма
    auto begin = std::chrono::steady_clock::now();

    // Поиск компонентс связности в графе
    std::unique_ptr<IGraphComponents<T>> c =
        std::move(walker.findComponentsInGraph(graph));

    // Время конца работы алгоритма
    auto end = std::chrono::steady_clock::now();

    // Подсчёт времени работы алгоритма
    auto elapsed_ms =
        std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    // Вывод компонент связности
    //c->print();
    c->printToFile(filename);

    // Вывод затраченнного времен
    std::cout << "Working time of algorithm: " << elapsed_ms.count() << " mcs\n";
}

#endif //  UTILS_HPP
